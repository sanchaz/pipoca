/* $Id: code.c,v 1.7 2004/12/09 17:25:13 prs Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include "lib/node.h"
#include "y.tab.h"
#include "lib/tabid.h"
#include "lib/postfix.h"

#define SUB(x)	value.sub.n[x]
#define READLN_BUF	10
#include "extras.h"

static int lbl;
static void eval(Node *p);
static FILE *out;
static char *mklbl(int);
static int offset;
static int offset2;
static int _bc[100];
static int _bcindex = -1;
static char buf[80];
static char infunc[80];

void evaluate(Node *p) {
	extern char *outfile, **yynames;
	extern int errors, tree, floatfound;
	lbl = 0;
	if(floatfound == 1) {
		/*exit(1);*/
		yyerror("No floating point support.");
	}
	
	if (tree > 0) { printNode(p, stdout, yynames); return; }
	if (outfile == 0) outfile = "out.asm";
	if ((out = fopen(outfile, "w")) == 0) {
		perror(outfile);
		exit(2);
	}
	
	eval(p);
	/* import library functions */
	fprintf(out, pfEXTRN, "readln");
	fprintf(out, pfEXTRN, "printi");
	fprintf(out, pfEXTRN, "prints");
	fprintf(out, pfEXTRN, "println");
	fprintf(out, pfEXTRN, "power");
	/* reserv buffer for readln */
	fprintf(out, pfBSS);
	fprintf(out, pfALIGN);
	fprintf(out, pfGLOBL, "_READLN_BUF", pfOBJ);
	fprintf(out, pfLABEL, "_READLN_BUF");
	fprintf(out, pfBYTE, 4*READLN_BUF);
	fprintf(out, pfTEXT);
	fprintf(out, pfALIGN);
	fclose(out);
	if (errors > 0) unlink(outfile);

}


static void eval(Node *p) {
	int i, j, lbl1, lbl2, lbl3, lbl4, _type, _type2, _attrib, _attrib2;
	char *name;
	Node *aux;
	
	if (p == 0) return;
	switch(p->attrib) {
		case DECL:
			for (i = 0; i < p->value.sub.num; i++) {
				eval(p->SUB(i));
			}
			break;
		case FUNC:
			fprintf(out, pfTEXT);
			fprintf(out, pfALIGN);
			IDnew(FUNC, p->SUB(0)->value.s, count_args(p->SUB(1)));	/* create function name */
			sprintf(infunc, "%s", p->SUB(0)->value.s);		/* define in which function we're in */
			fprintf(out, pfGLOBL, p->SUB(0)->value.s, pfFUNC);
			fprintf(out, pfLABEL, p->SUB(0)->value.s);
			fprintf(out, pfENTER, calc_enter(p->SUB(2)));
			IDpush();
			offset = -4;
			offset2 = 8;
			eval(p->SUB(1));					/* evaluate arguments */
			/*IDnew(ID, p->SUB(0)->value.s, offset);*/
			eval(p->SUB(2));					/* evaluate function exps */
			IDpop();
			sprintf(infunc, "");
			fprintf(out, pfLOCAL, -4);				/* return value */
			fprintf(out, pfLOAD);
			fprintf(out, pfPOP);
			fprintf(out, pfLEAVE);
			fprintf(out, pfRET);
			break;
		case LISTEXP3:
			for(i = 0; i < p->value.sub.num; i++) {		/* function args */
					switch(p->SUB(i)->attrib) {
						case LISTEXP4:
							eval(p->SUB(i));
							break;
						case ID:
							IDnew(ID, p->SUB(i)->value.s, offset2);
							offset2 += 4;
							break;
						case UNALLOCVECTOR:
							IDnew(IDVEC, p->SUB(i)->SUB(0)->value.s, offset2);
							offset2 += 4;
							break;
					}
			}
			break;
		case LISTEXP4:
			for(i = 0; i < p->value.sub.num; i++) {		/* function args */
					switch(p->SUB(i)->attrib) {
						case LISTEXP4:
							eval(p->SUB(i));
							break;
						case ID:
							IDnew(ID, p->SUB(i)->value.s, offset2);
							offset2 += 4;
							break;
						case UNALLOCVECTOR:
							IDnew(IDVEC, p->SUB(i)->SUB(0)->value.s, offset2);
							offset2 += 4;
							break;
					}
			}
			break;
		case VAR:
			for(i = 0; i < p->value.sub.num; i++) {
				switch(p->SUB(i)->attrib) {
					case ID:						/* var is a simple 4 byte integer */
						offset -= 4;
						IDnew(ID, p->SUB(i)->value.s, offset);
						break;
					case IDVEC:						/* var is an unallocated vector */
						offset -= 4;
						IDnew(IDVEC, p->SUB(i)->value.s, offset);
						break;
					case IDVECINT:						/* var is an allocated vector */
						offset -= (4 * p->SUB(i)->SUB(1)->value.i);	/* size of allocated vector */
						IDnew(IDVECINT, p->SUB(i)->SUB(0)->value.s, offset);
						break;
				}
			}
			break;
		case CONST:
			for(i = 0; i < p->value.sub.num; i++) {
				fprintf(out, pfRODATA);			/* const are DATA readonly  */
				fprintf(out, pfALIGN);			/* make sure we are aligned   */
				fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));	/* give the const a name     */
				offset -= 4;
				if(p->SUB(i)->SUB(1)->attrib == INT) {
					IDnew(ICONST, p->SUB(i)->SUB(0)->value.s, offset);		/* keep it in tabid along it's label */
					fprintf(out, pfCONST, p->SUB(i)->SUB(1)->value.i);
				}else if(p->SUB(i)->SUB(1)->attrib == STRING) {
					IDnew(SCONST, p->SUB(i)->SUB(0)->value.s, offset);		/* keep it in tabid along it's label */
					fix_str(p->SUB(i)->SUB(1)->value.s);				/* take out the '' from the string so we don't print them */
					if(fix_special_chars(p->SUB(i)->SUB(1)->value.s) == 1) {
						for(j = 0; j < strlen(p->SUB(i)->SUB(1)->value.s); j++) {
							fprintf(out, pfCHAR, p->SUB(i)->SUB(1)->value.s[j]);
						}
						fprintf(out, pfCHAR, 0);
					}else{
						fprintf(out, pfSTR, p->SUB(i)->SUB(1)->value.s);		/* output string characters   */
					}
				}else{
					IDnew(VCONST, p->SUB(i)->SUB(0)->value.s, offset);		/* keep it in tabid along it's label */
					eval(p->SUB(i)->SUB(1));
				}
				fprintf(out, pfTEXT);						/* return to text segment */
				fprintf(out, pfALIGN);
				fprintf(out, pfADDR, mklbl(lbl1));				/* load the const address */
				fprintf(out, pfLOCAL, offset);					/* load the local address */
				fprintf(out, pfSTORE);						/* store the address in the local var */
			}
			break;
		case EXTERN:
			fprintf(out, pfTEXT);
			fprintf(out, pfALIGN);
			for (i = 0; i < p->value.sub.num; i++) {			/* declare external functions and vars */
				if(p->SUB(i)->attrib == ID) {				/* if ID declare as INTVEC */
					fprintf(out, pfEXTRN, p->SUB(i)->value.s);
					IDnew(INTVEC, p->SUB(i)->value.s, 0);
				}else{							/* if function declare as function */
					fprintf(out, pfEXTRN, p->SUB(i)->SUB(0)->value.s);
					if(p->SUB(i)->value.sub.num > 1) {		/* check number of args */
						IDnew(FUNC, p->SUB(i)->SUB(0)->value.s, p->SUB(i)->SUB(1)->value.sub.num);
					}else{
						IDnew(FUNC, p->SUB(i)->SUB(0)->value.s, 0);
						
					}
				}
			}
			break;
		case INIT:
			eval(p->SUB(0));
			eval(p->SUB(1));
			fprintf(out, pfTEXT);						/* return to text segment */
			fprintf(out, pfALIGN);
			break;
		case INITN:
			for(i = 0; i < p->value.sub.num; i++) {				/* init values */
				if(p->SUB(i)->attrib == NEG) {				/* check if positive or neg */
					fprintf(out, pfCONST, -(p->SUB(i)->SUB(0)->value.i));
				}else{
					fprintf(out, pfCONST, p->SUB(i)->value.i);
				}
			}
			break;
		case INITID:
			fprintf(out, pfDATA);
			fprintf(out, pfALIGN);
			IDnew(INTVEC, p->value.s, 0);			/* put init id into tabid */
			fprintf(out, pfGLOBL, p->value.s, pfOBJ);	/* declare init label */
			fprintf(out, pfLABEL, p->value.s);
			break;
		case FUNC2:
			for (i = 0; i < p->value.sub.num; i++) {	/* evaluate funcs exps */
				eval(p->SUB(i));
			}
			break;
		case INT:
			fprintf(out, pfINT, p->value.i);		/* push an integer	      */
			break;
		case STRING:
			/* generate the string */
			fprintf(out, pfRODATA);			/* strings are DATA readonly  */
			fprintf(out, pfALIGN);			/* make sure we are aligned   */
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));	/* give the string a name     */
			fprintf(out, pfSTR, p->value.s);		/* output string characters   */
			break;
		case '?':
			_attrib2 = 1;
			if((p->SUB(0)->attrib == ID) && ((_type2 = IDfind(p->SUB(0)->value.s, &_attrib2)) == VCONST || _type2 == SCONST || _type2 == ICONST)) {
				sprintf(buf, "\t%s: is a constant value.", p->SUB(0)->value.s);
        			yyerror(buf);
			}else if((p->SUB(0)->attrib == IDVECA) && ((_type2 = IDfind(p->SUB(0)->SUB(0)->value.s, &_attrib2)) == VCONST || _type2 == SCONST || _type2 == ICONST)) {
				sprintf(buf, "\t%s: is a constant value.", p->SUB(0)->SUB(0)->value.s);
        			yyerror(buf);
			}else{
	  			fprintf(out, pfINT, READLN_BUF);		/* put buffer size */
	  			fprintf(out, pfADDR, "_READLN_BUF");		/* put buffer address */
	  			fprintf(out, pfCALL, "readln");			/* readln */
	  			fprintf(out, pfPUSH);
	  			fprintf(out, pfDUP);
	  			fprintf(out, pfINT, -1); 			/* compare return value to end of file */
	  			fprintf(out, pfEQ);
	  			fprintf(out, pfJNZ, mklbl(lbl1 = ++lbl)); 	/* jmp and return -1 if end of file */
	  			fprintf(out, pfINT, 0);
	  			fprintf(out, pfEQ);
	  			fprintf(out, pfJNZ, mklbl(lbl2 = ++lbl));	/* jmp and return 0 if error */
	  			fprintf(out, pfADDR, "_READLN_BUF");		/* buffer address */
	  			fprintf(out, pfCALL, "atoi");			/* convert string to int */
	  			fprintf(out, pfPUSH);
	  			eval(p->SUB(0));
	  			fprintf(out, pfSTORE);
	  			fprintf(out, pfINT, 1);				/* jmp and return 1 if read from terminal was successful */
	  			fprintf(out, pfJMP, mklbl(lbl3 = ++lbl));
	  			fprintf(out, pfLABEL, mklbl(lbl1));
	  			fprintf(out, pfTRASH, 4);
	  			fprintf(out, pfINT, 0);				/* return 0 read failed */
	  			fprintf(out, pfJMP, mklbl(lbl3));
	  			fprintf(out, pfLABEL, mklbl(lbl2));
	  			fprintf(out, pfINT, -1);			/* return -1 for EOF */
	  			fprintf(out, pfLABEL, mklbl(lbl3));
	  		}
			break;
		case '!':
			for (i = 0; i < p->value.sub.num; i++) {	/* print line */
				eval(p->SUB(i));
			}
			break;
		case PRINTLN:
			for (i = 0; i < p->value.sub.num; i++) {	/* print line */
				eval(p->SUB(i));
			}
			fprintf(out, pfCALL, "println");		/* print new line */
			break;
		case PRINTSTRING:
			/* generate the string */
			fprintf(out, pfRODATA);				/* strings are DATA readonly */
			fprintf(out, pfALIGN);				/* make sure we are aligned */
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));	/* give the string a name */
			fix_str(p->value.s);				/* take out the '' from the string so we don't print them */
			if(fix_special_chars(p->value.s) == 1) {	/* check for special chars */
				for(i = 0; i < strlen(p->value.s); i++) {	/* print eash char if special chars are present */
					fprintf(out, pfCHAR, p->value.s[i]);
				}
				fprintf(out, pfCHAR, 0);
			}else{
				fprintf(out, pfSTR, p->value.s);		/* output string characters if no special chars are present */
			}
			/* make the call */
			fprintf(out, pfTEXT);				/* return to the TEXT segment */
			fprintf(out, pfALIGN);				/* make sure we are aligned */
			fprintf(out, pfADDR, mklbl(lbl1));		/* the string to be printed */
			fprintf(out, pfCALL, "prints");			/* call the print rotine */
			fprintf(out, pfTRASH, 4);			/* remove the string label */
			break;
		case PRINTINT:
			fprintf(out, pfTEXT);				/* return to the TEXT segment */
			fprintf(out, pfALIGN);				/* make sure we are aligned */
			fprintf(out, pfINT, p->value.i);		/* push an integer */
			fprintf(out, pfCALL, "printi");			/* call the print rotine */
			fprintf(out, pfTRASH, 4);			/* remove the int */
			break;
		case PRINTFUNCCALL:
			eval(p->SUB(0));
			fprintf(out, pfCALL, "printi");			/* call the print rotine */
			break;
		case PRINTID:
			_attrib2 = 1;
			if(p->SUB(0)->attrib == ID) {			/* check if ID or IDVECA if defined */
				_type2 = IDfind(p->SUB(0)->value.s, &_attrib2);
				
			}else{
				_type2 = IDfind(p->SUB(0)->SUB(0)->value.s, &_attrib2);
			}
			switch(_type2) {	/* if string prints if int printi */
					case SCONST:
						fprintf(out, pfLOCAL, _attrib2);
						fprintf(out, pfLOAD);
						fprintf(out, pfCALL, "prints");			/* call the print rotine */
						fprintf(out, pfTRASH, 4);			/* remove the string label */
						break;
					default:
						eval(p->SUB(0));
						fprintf(out, pfLOAD);
						fprintf(out, pfCALL, "printi");			/* call the print rotine */
						fprintf(out, pfTRASH, 4);			/* remove the int */
						break;
			}
			break;
		case PRINTP:
			eval(p->SUB(0));
			eval(p->SUB(1));
       			break;
       		case SSM:
       			eval(p->SUB(0));				/* print other strings, ids, ints */
       			eval(p->SUB(2));				/* get the number of times to print the string */
       			fprintf(out, pfLABEL, mklbl(lbl2 = ++lbl));	/* make label to start printing n times */
       			fprintf(out, pfDUP);				/* Duplicate value */
       			fprintf(out, pfINT, 0);				/* push an integer */
       			fprintf(out, pfEQ);				/* check how many times string has been printed */
       			fprintf(out, pfJNZ, mklbl(lbl3 = ++lbl));	/* jump to end if printed every thing x times */
			eval(p->SUB(1));				/* generate and print the string */
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfSUB);				/* subtract to the number of times printed */
			fprintf(out, pfJMP, mklbl(lbl2));		/* print string again if not printed x times yet */
			fprintf(out, pfLABEL, mklbl(lbl3));		/* make label to start print n times */
       			break;
       		case PRINTSM:
       			eval(p->SUB(1));
       			fprintf(out, pfLABEL, mklbl(lbl2 = ++lbl));	/* make label to start printing n times */
       			fprintf(out, pfDUP);				/* Duplicate value */
       			fprintf(out, pfINT, 0);				/* push an integer */
       			fprintf(out, pfEQ);				/* check how many times string has been printed */
       			fprintf(out, pfJNZ, mklbl(lbl3 = ++lbl));	/* jump to end if printed every thing x times */
       			eval(p->SUB(0));				/* generate and print the string */
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfSUB);				/* subtract to the number of times printed */
			fprintf(out, pfJMP, mklbl(lbl2));		/* print string again if not printed x times yet */
			fprintf(out, pfLABEL, mklbl(lbl3));		/* make label to start print n times */
       			break;
       		case FUNCCALL:
       			eval(p->SUB(1));
       			eval(p->SUB(0));
       			break;
       		case FID:
       			_attrib2 = 1;
			_type2 = IDfind(p->value.s, &_attrib2);		/*check id type */
			switch (_type2) {	/* if id is function type then call function */
				case FUNC:
					fprintf(out, pfCALL, p->value.s);	/* CALL FUNCTION */
					fprintf(out, pfTRASH, _attrib2 * 4);	/* TRASH ARGUMENTS */
					fprintf(out, pfPUSH);				/* Push the function return value and print it */
					break;
				default:	/* id is not a valid function name */
					sprintf(buf, "\t%s: not a valid function name.", p->value.s);
        				yyerror(buf);
					break;
			}
       			break;
       		case LISTEXP:
       			for(i = p->value.sub.num - 1; i >= 0; i--) {
       				eval(p->SUB(i));			/* get arg address */
       				if(p->SUB(i)->attrib == IDVECA) {	/* Load them to stack */
       					fprintf(out, pfLOAD);
       				}else if(p->SUB(i)->attrib == ID) {
       					_attrib2 = 1;
					_type2 = IDfind(p->SUB(i)->value.s, &_attrib2);
					switch(_type2) {
						case INTVEC:
						case ID:
							fprintf(out, pfLOAD);
							break;
						default:
							break;
					}
       				}
       			}
       			break;
       		case LISTEXP2:
       			for(i = p->value.sub.num - 1; i >= 0; i--) {
       				eval(p->SUB(i));			/* get arg address */
       				if(p->SUB(i)->attrib == IDVECA) {	/* Load them to stack */
       					fprintf(out, pfLOAD);
       				}else if(p->SUB(i)->attrib == ID) {
       					_attrib2 = 1;
					_type2 = IDfind(p->SUB(i)->value.s, &_attrib2);
					switch(_type2) {
						case INTVEC:
						case ID:
							fprintf(out, pfLOAD);
						default:
							break;
					}
       				}
       			}
       			break;
       		case MEMRESERV:
       			_attrib2 = 1;
			_type2 = IDfind(p->SUB(0)->value.s, &_attrib2);		/* check id type */
       			if(_type2 == IDVEC) {					/* if id is unallocted vector then reserv mem */
       				if(p->SUB(1)->attrib != INT) {			/* bytes to allocate */
       					eval(p->SUB(1));
       				}else{
       					fprintf(out, pfINT, p->SUB(1)->value.i);
       				}
	       			fprintf(out, pfALLOC);				/* alloc n bytes */
	       			fprintf(out, pfSP);				/* get stack pointer address */
	       			fprintf(out, pfLOCAL, _attrib2);		/* store reference to vector in id */
	       			fprintf(out, pfSTORE);
	       		}else{
	       			sprintf(buf, "\t%s: memory cannot be allocated for this type of var.", p->SUB(0)->value.s);
        			yyerror(buf);
        		}
       			break;
       		case MEMRESERVP:
       			eval(p->SUB(0));
       			break;
       		case WHILE:
       			_bcindex++;
       			_bc[_bcindex] = lbl3 = ++lbl;			/* generate break label */
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));	/* continue label */
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfJZ, mklbl(lbl2 = ++lbl));	/* jump to else if false */
			IDpush();
			eval(p->SUB(1));
			IDpop();
			fprintf(out, pfJMP, mklbl(lbl1));		/* continue while cycle */
			fprintf(out, pfLABEL, mklbl(lbl2));		/* else label */
			IDpush();
			eval(p->SUB(2));				/* else if no else is present nothing is written */
			IDpop();
			fprintf(out, pfLABEL, mklbl(lbl3));		/*break label */
			_bcindex--;
			break;
		case DO:
       			_bcindex++;
			_bc[_bcindex] = lbl3 = ++lbl;			/* generate break label */
       			lbl4 = ++lbl;					/* generate continue label */
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));
			IDpush();
			eval(p->SUB(0));
			IDpop();
			fprintf(out, pfLABEL, mklbl(lbl4));		/* continue label */
			eval(p->SUB(1));
			if((p->SUB(1)->attrib == ID) || (p->SUB(1)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfJZ, mklbl(lbl2 = ++lbl));
			fprintf(out, pfJMP, mklbl(lbl1));
			fprintf(out, pfLABEL, mklbl(lbl2));
			IDpush();
			eval(p->SUB(2));				/* else if no else is present nothing is written */
			IDpop();
			fprintf(out, pfLABEL, mklbl(lbl3));		/* break label */
			_bcindex--;
			break;
		case IF:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfJZ, mklbl(lbl1 = ++lbl));	/* jmp to else if false */
			IDpush();
			eval(p->SUB(1));
			IDpop();
			fprintf(out, pfJMP, mklbl(lbl2 = ++lbl));	/* jmp to end if first condition was entered */
			fprintf(out, pfLABEL, mklbl(lbl1));
			IDpush();
			eval(p->SUB(2));				/* else if no else is present nothing is written */
			IDpop();
			fprintf(out, pfLABEL, mklbl(lbl2));
			break;
		case ELSE:
			/* evalutate the block */
			eval(p->SUB(0));
			break;
		case BREAK:
			/* print out break label */
			if((_bcindex == -1) || (_bcindex-(p->SUB(0)->value.i-1) < 0)) {
        			yyerror("Cannot break out of non existing cycle.");	
			}
			fprintf(out, pfJMP, mklbl(_bc[_bcindex-(p->SUB(0)->value.i-1)]));
			break;
		case CONTINUE:
			/* print out continue label */
			if((_bcindex == -1) || (_bcindex-(p->SUB(0)->value.i-1) < 0)) {
        			yyerror("Cannot continue non existing cycle.");	
			}
			fprintf(out, pfJMP, mklbl(_bc[_bcindex-(p->SUB(0)->value.i-1)]+1));	/* continue labels are always the same as break label +1 */
			break;
		case ID:
			if(strcmp(infunc,p->value.s) != 0) {
				_attrib2 = 1;
				_type2 = IDfind(p->value.s, &_attrib2);
				switch (_type2) {	/* Get address for diferent types of vars */
					case IDVEC:	/* integer vector type var a[] */
						fprintf(out, pfLOCAL, _attrib2);
						fprintf(out, pfLOAD);
						break;
					case INTVEC:	/* init vector type init := [9] */
						fprintf(out, pfADDR, p->value.s);
						break;
					case VCONST:	/* a vector of consts type const a := [8, 8, 8] */
						fprintf(out, pfLOCAL, _attrib2);
						fprintf(out, pfLOAD);
						break;
					case ICONST:	/* const integer type const a := 8 */
						fprintf(out, pfLOCAL, _attrib2);
						fprintf(out, pfLOAD);
						break;
					case ID:	/* integer type var a */
						fprintf(out, pfLOCAL, _attrib2);
						break;
					case IDVECINT:	/* integer vector type var a[8] */
						fprintf(out, pfLOCAL, _attrib2);
						break;
					case -1:	/* id not defined */
						break;
					default:	/* id is not a valid lvalue probably a func name or const string */
						sprintf(buf, "\t%s: not a valid.", p->value.s);
						yyerror(buf);
						break;
				}
			}else{
				fprintf(out, pfLOCAL, -4);
			}
			break;
		case IDVECA:
			switch(p->SUB(1)->attrib) {
				case INT:
					eval(p->SUB(1));
					fprintf(out, pfINT, 4);	/* push 4 */
					fprintf(out, pfMUL);			/* 4 bytes = 32 bits */
					break;
				case ID:
					eval(p->SUB(1));
					fprintf(out, pfLOAD);
					fprintf(out, pfINT, 4);	/* push 4 */
					fprintf(out, pfMUL);			/* 4 bytes = 32 bits */
					break;	
			}				
			_type2 = IDfind(p->SUB(0)->value.s, &_attrib2);
			switch(_type2) {
				case IDVEC:	/* integer vector type var a[] */
					fprintf(out, pfLOCAL, _attrib2);
					fprintf(out, pfLOAD);
					fprintf(out, pfADD);
					break;
				case INTVEC:	/* init vector type init := [9] */
					fprintf(out, pfADDR, p->SUB(0)->value.s);
					fprintf(out, pfADD);
					break;
				case IDVECINT:	/* integer vector type var a[8] */
					fprintf(out, pfLOCAL, _attrib2);
					fprintf(out, pfADD);
					break;
				case VCONST:	/* a vector of consts type const a := [8, 8, 8] */
					fprintf(out, pfLOCAL, _attrib2);
					fprintf(out, pfLOAD);
					fprintf(out, pfADD);
					break;
				case -1:	/* id not defined */
					break;
				default:	/* id is not a valid lvalue probably not vector */
					sprintf(buf, "\t%s: not a vector.", p->SUB(0)->value.s);
        				yyerror(buf);
					break;
			}
			break;
		case OPATR:
			_attrib2 = 1;
			if((p->SUB(0)->attrib == ID) && ((_type2 = IDfind(p->SUB(0)->value.s, &_attrib2)) == VCONST || _type2 == SCONST || _type2 == ICONST)) {
				sprintf(buf, "\t%s: is a constant value.", p->SUB(0)->value.s);
        			yyerror(buf);
			}else if((p->SUB(0)->attrib == IDVECA) && ((_type2 = IDfind(p->SUB(0)->SUB(0)->value.s, &_attrib2)) == VCONST || _type2 == SCONST || _type2 == ICONST)) {
				sprintf(buf, "\t%s: is a constant value.", p->SUB(0)->SUB(0)->value.s);
        			yyerror(buf);
			}else{
				eval(p->SUB(1));	/* evaluate the value */
				if(p->SUB(1)->attrib == OPATR) {	/* if multiple atribuition load value after store */
					eval(p->SUB(1)->SUB(0));	/* address */
					fprintf(out, pfLOAD);		/* value */
				}else if((p->SUB(1)->attrib == ID) || (p->SUB(1)->attrib == IDVECA)) {	/* if ID or IDVECA load value */
					fprintf(out, pfLOAD);		/* load value */
				}
				eval(p->SUB(0));			/* address */
				fprintf(out, pfSTORE);			/* store value */
			}
			break;
		case AND:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfDUP);
			fprintf(out, pfJZ, mklbl(lbl1 = ++lbl));
			fprintf(out, pfTRASH, 4);	/* last value was != 0 to get here so true so we can get rid of it */
			eval(p->SUB(1));
			if((p->SUB(1)->attrib == ID) || (p->SUB(1)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfLABEL, mklbl(lbl1));
			break;
		case OR:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfDUP);
			fprintf(out, pfJNZ, mklbl(lbl1 = ++lbl));
			fprintf(out, pfTRASH, 4);	/* last value was = 0 to get here so true so we can get rid of it */
			eval(p->SUB(1));
			if((p->SUB(1)->attrib == ID) || (p->SUB(1)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfLABEL, mklbl(lbl1));
			break;
		case NEG:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			/* load value and do complement */
			fprintf(out, pfNEG);
			break;
		case NOT:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfJZ, mklbl(lbl1 = ++lbl));	/* if 0 then return 1 if 1 then return 0 */
			fprintf(out, pfTRASH, 4);
			fprintf(out, pfINT, 0);				/* return 0 */
			fprintf(out, pfJMP, mklbl(lbl2 = ++lbl));
			fprintf(out, pfLABEL, mklbl(lbl1));
			fprintf(out, pfINT, 1);				/* return 1 */
			fprintf(out, pfLABEL, mklbl(lbl2));
			break;
		case PLUSONE:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfADD);				/* add 1 */
			fprintf(out, pfDUP);				/* return new value */
			eval(p->SUB(0));				/* store the new value */
			fprintf(out, pfSTORE);
			break;
		case PLUSONEA:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfDUP);				/* return old value */
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfADD);				/* add 1 */
			eval(p->SUB(0));				/* store the new value */
			fprintf(out, pfSTORE);
			break;
		case MINUSONE:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfSUB);				/* subtract 1 */
			fprintf(out, pfDUP, 1);				/* return new value */
			eval(p->SUB(0));				/* store the new value */
			fprintf(out, pfSTORE);
			break;
		case MINUSONEA:
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			fprintf(out, pfDUP, 1);				/* return the old value */
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfSUB);				/* 1 */
			eval(p->SUB(0));				/* store the new value */
			fprintf(out, pfSTORE);
			break;
		case '@':
			eval(p->SUB(0));				/* return the address */
			break;
		case EXPP:
			eval(p->SUB(0));				/* exp with () define priority */
			break;
		default:
			/* load the first value */
			eval(p->SUB(0));
			if((p->SUB(0)->attrib == ID) || (p->SUB(0)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			/* load the second value */
			eval(p->SUB(1));
			if((p->SUB(1)->attrib == ID) || (p->SUB(1)->attrib == IDVECA)) { /* if id load the value of the address */
				fprintf(out, pfLOAD);
			}
			switch(p->attrib) {
				case '+':
					fprintf(out, pfADD);		/* add */
					break;
				case '-':
					fprintf(out, pfSUB);		/* subtract */
					break;
				case '*':
					fprintf(out, pfMUL);		/* multiply */
					break;
				case '/':
					fprintf(out, pfDIV);		/* divide */
					break;
				case '%':
					fprintf(out, pfMOD);		/* mod */
					break;
				case POT:
					fprintf(out, pfCALL, "power");	/* call the power (pow) rotine      */
					fprintf(out, pfTRASH, 8);	/* TRASH THE ARGUMENTS */
					fprintf(out, pfPUSH);		/* PUSH the result of pow routine to the stack */
					break;
				case '<':
					fprintf(out, pfLT);		/* Less than  */
					break;
				case '>':
					fprintf(out, pfGT);		/* Greater than  */
					break;
				case '=':
					fprintf(out, pfEQ);		/* Equal to */
					break;
				case MOREOREQUAL:
					fprintf(out, pfGE);		/* Greater or Equal to */
					break;
				case LESSOREQUAL:
					fprintf(out, pfLE);		/* Less or Equal to */
					break;
				case NOTEQUAL:
					fprintf(out, pfNE);		/* Not Equal to */
					break;
			}
			break;
			
       	}
}

static char *mklbl(int n) {
  static char str[20];
  if (n < 0)
    sprintf(str, ".L%d", -n);
  else
    sprintf(str, "_L%d", n);
  return str;
}
