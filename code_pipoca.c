/* $Id: code.c,v 1.7 2004/12/09 17:25:13 prs Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include "lib/node.h"
#include "y.tab.h"
#include "lib/tabid.h"
#include "lib/postfix.h"

#define SUB(x)	value.sub.n[x]

#include "extras.h"

static int lbl;
static void eval(Node *p);
static FILE *out;
static char *mklbl(int);
int cycles = 0;

void evaluate(Node *p) {
  extern char *outfile, **yynames;
  extern int errors, tree;
  lbl = 0;

  if (tree > 0) { printNode(p, stdout, yynames); return; }
  if (outfile == 0) outfile = "out.asm";
  if ((out = fopen(outfile, "w")) == 0) {
    perror(outfile);
    exit(2);
  }
  /*fprintf(out, pfTEXT);
  fprintf(out, pfALIGN);
  fprintf(out, pfGLOBL, "_start", pfFUNC);
  fprintf(out, pfLABEL, "_start");
  fprintf(out, pfENTER, 0);*/
  eval(p);
  /*fprintf(out, pfINT, 0);
  fprintf(out, pfPOP);
  fprintf(out, pfLEAVE);
  fprintf(out, pfRET);*/
  /* import library functions */
  fprintf(out, pfEXTRN, "readi");
  fprintf(out, pfEXTRN, "printi");
  fprintf(out, pfEXTRN, "prints");
  fprintf(out, pfEXTRN, "println");
  fprintf(out, pfEXTRN, "pow");
  fclose(out);
  if (errors > 0) unlink(outfile);
}


static void eval(Node *p) {
	int i, lbl1, lbl2, lbl3, offset, _attrib, _attrib2, _type, _type2;
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
			IDnew(FUNC, p->SUB(0)->value.s, count_args(p->SUB(1)));
			fprintf(out, pfGLOBL, p->SUB(0)->value.s, pfFUNC);
			fprintf(out, pfLABEL, p->SUB(0)->value.s);
			fprintf(out, pfENTER, 400);
			IDpush();
			offset = 0;
			eval(p->SUB(2));
			IDpop();
			fprintf(out, pfINT, 0);
			fprintf(out, pfPOP);
			fprintf(out, pfLEAVE);
			fprintf(out, pfRET);
			break;
		case VAR:
			for(i = 0; i < p->value.sub.num; i++) {
				switch(p->SUB(i)->attrib) {
					case ID:						/* var is a simple 4 byte int */
						offset += 4;
						IDnew(ID, p->SUB(i)->value.s, -offset);
						break;
					case IDVEC:						/* var is unallocated vector */
						offset += 4;
						IDnew(IDVEC, p->SUB(i)->value.s, -offset);
						break;
					case IDVECINT:						/* var is an allocated vector */
						offset += (4 * p->SUB(i)->SUB(1)->value.i);	/* size of allocated vector */
						IDnew(IDVECINT, p->SUB(i)->SUB(0)->value.s, -offset);
						break;
				}
			}
			break;
		case CONST:
			fprintf(out, pfRODATA);			/* const are DATA readonly  */
			fprintf(out, pfALIGN);			/* make sure we are aligned   */
			for(i = 0; i < p->value.sub.num; i++) {
				fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));	/* give the const a name     */
				offset += 4;
				IDnew(CONST, p->SUB(i)->SUB(0)->value.s, lbl1);		/* keep it in tabid along it's label */
				if(p->SUB(i)->SUB(1)->attrib == INT) {
					fprintf(out, pfCONST, p->SUB(i)->SUB(1)->value.i);
				}else if(p->SUB(i)->SUB(1)->attrib == STRING) {
					fix_str(p->SUB(i)->SUB(1)->value.s);				/* take out the '' from the string so we don't print them */
					fprintf(out, pfSTR, p->SUB(i)->SUB(1)->value.s);		/* output string characters   */
				}else{
					eval(p->SUB(i)->SUB(1));
				}
			}
			fprintf(out, pfTEXT);						/* return to text segment */
			fprintf(out, pfALIGN);
			break;
		case EXTERN:
			for(i = 0; i < p->value.sub.num; i++) {
				fprintf(out, pfEXTRN, p->SUB(i)->value.s);
			} 
			break;
		case INIT:
			eval(p->SUB(0));
			eval(p->SUB(1));
			fprintf(out, pfTEXT);						/* return to text segment */
			fprintf(out, pfALIGN);
			break;
		case INITN:
			for(i = 0; i < p->value.sub.num; i++) {
				if(p->SUB(i)->attrib == '-') {
					fprintf(out, pfCONST, -(p->SUB(i)->SUB(0)->value.i));
				}else{
					fprintf(out, pfCONST, p->SUB(i)->value.i);
				}
			}
			break;
		case INITID:
			fprintf(out, pfDATA);
			fprintf(out, pfALIGN);
			IDnew(INTVEC, p->value.s, 0);
			fprintf(out, pfGLOBL, p->value.s, pfOBJ);
			fprintf(out, pfLABEL, p->value.s);
			break;
		case INT:
			fprintf(out, pfINT, p->value.i);		/* push an integer	      */
			break;
		case STRING:
			/* generate the string */
			fprintf(out, pfRODATA);			/* strings are DATA readonly  */
			fprintf(out, pfALIGN);			/* make sure we are aligned   */
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));	/* give the string a name     */
			fix_str(p->value.s);				/* take out the '' from the string so we don't print them */
			fprintf(out, pfSTR, p->value.s);		/* output string characters   */
			break;
		case '!':
			for (i = 0; i < p->value.sub.num; i++) {
				eval(p->SUB(i));
			}
			break;
		case PRINTLN:
			for (i = 0; i < p->value.sub.num; i++) {
				eval(p->SUB(i));
			}
			fprintf(out, pfCALL, "println");		/* print a newline	      */
			break;
		case PRINTSTRING:
			/* generate the string */
			fprintf(out, pfRODATA);				/* strings are DATA readonly  */
			fprintf(out, pfALIGN);				/* make sure we are aligned   */
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));	/* give the string a name     */
			fix_str(p->value.s);				/* take out the '' from the string so we don't print them */
			fprintf(out, pfSTR, p->value.s);		/* output string characters   */
			/* make the call */
			fprintf(out, pfTEXT);			/* return to the TEXT segment */
			fprintf(out, pfADDR, mklbl(lbl1));		/* the string to be printed   */
			fprintf(out, pfCALL, "prints");			/* call the print rotine */
			fprintf(out, pfTRASH, 4);			/* remove the string label */
			break;
		case PRINTINT:
			fprintf(out, pfTEXT);				/* return to the TEXT segment */
			fprintf(out, pfALIGN);				/* make sure we are aligned   */
			fprintf(out, pfINT, p->value.i);		/* push an integer	      */
			fprintf(out, pfCALL, "printi");			/* call the print rotine      */
			fprintf(out, pfTRASH, 4);			/* remove the int */
			break;
		case PRINTFUNCCALL:
			fprintf(out, pfTEXT);				/* return to text segment */
			fprintf(out, pfALIGN);
			/* Funcioncall */
			fprintf(out, pfCALL, "printi");			/* call the print rotine      */
			fprintf(out, pfTRASH, 4);			/* remove the function return value (int) */
			break;
		case PRINTID:
			i = IDfind(p->value.s, 0);
			if(i >= 0) {
				fprintf(out, pfADDR, p->value.s);
				fprintf(out, pfLOAD);
				if(i == INTEGER) {
					fprintf(out, pfCALL, "printi");			/* call the print rotine */
					fprintf(out, pfTRASH, 4);			/* remove the int */
				}else if(i == STRING) {
					fprintf(out, pfCALL, "prints");			/* call the print rotine */
					fprintf(out, pfTRASH, 4);			/* remove the string label */
				}
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
       			fprintf(out, pfINT, 0);				/* push an integer */
       			fprintf(out, pfEQ);				/* check how many times string has been printed */
       			fprintf(out, pfJZ, mklbl(lbl3 = ++lbl));				/* jump to end if printed every thing x times */
			eval(p->SUB(1));				/* generate and print the string */
			fprintf(out, pfTRASH, 4);			/* remove the 0 used for jmp condition */
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfSUB);				/* subtract to the number of times printed */
			fprintf(out, pfJMP, mklbl(lbl2));		/* print string again if not printed x times yet */
			fprintf(out, pfLABEL, mklbl(lbl3));		/* make label to start print n times */
       			break;
       		case PRINTM:
       			/* equal to '*' ? */
       			break;
       		case PRINTSM:
       			eval(p->SUB(1));
       			fprintf(out, pfLABEL, mklbl(lbl2 = ++lbl));	/* make label to start printing n times */
       			fprintf(out, pfINT, 0);				/* push an integer */
       			fprintf(out, pfEQ);				/* check how many times string has been printed */
       			fprintf(out, pfJZ, mklbl(lbl3 = ++lbl));				/* jump to end if printed every thing x times */
       			eval(p->SUB(0));				/* generate and print the string */
       			fprintf(out, pfTRASH, 4);			/* remove the 0 used for jmp condition */
			fprintf(out, pfINT, 1);				/* push an integer */
			fprintf(out, pfSUB);				/* subtract to the number of times printed */
			fprintf(out, pfJMP, mklbl(lbl2));		/* print string again if not printed x times yet */
			fprintf(out, pfLABEL, mklbl(lbl3));		/* make label to start print n times */
       			break;
		case ID:
			if (IDfind(p->value.s, 0) >= 0) {
			  fprintf(out, pfADDR, p->value.s);
			  fprintf(out, pfLOAD);
			}
			break;
		case WHILE:
			IDpush();
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));
			eval(p->SUB(0));
			fprintf(out, pfJZ, mklbl(lbl2 = ++lbl));
			eval(p->SUB(1));
			fprintf(out, pfJMP, mklbl(lbl1));
			fprintf(out, pfLABEL, mklbl(lbl2));
			eval(p->SUB(2));
			fprintf(out, pfLABEL, mklbl(lbl3));
			IDpop();
			break;
		case DO:
			IDpush();
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));
			eval(p->SUB(0));
			eval(p->SUB(1));
			fprintf(out, pfJZ, mklbl(lbl2 = ++lbl));
			fprintf(out, pfJMP, mklbl(lbl1));
			fprintf(out, pfLABEL, mklbl(lbl2));
			eval(p->SUB(2));
			fprintf(out, pfLABEL, mklbl(lbl3));
			IDpop();
			break;
		case IF:
			IDpush();
			eval(p->SUB(0));
			fprintf(out, pfJZ, mklbl(lbl1 = ++lbl));
			eval(p->SUB(1));
			fprintf(out, pfJMP, mklbl(lbl2 = ++lbl));
			fprintf(out, pfLABEL, mklbl(lbl1));
			eval(p->SUB(2));
			fprintf(out, pfLABEL, mklbl(lbl2));
			IDpop();
			break;
		case OPATR:
			switch(p->SUB(0)->attrib) {
				case ID:
				_attrib = 1;
					_type = IDfind(p->SUB(0)->value.s, &_attrib);
					if(_type == ID) { /* normal id type var a */ 
						if(p->SUB(1)->attrib == INT) {
							eval(p->SUB(1));
						}else if((p->SUB(1)->attrib == ID) &&  (_type == IDfind(p->SUB(1)->value.s, &_attrib2))) {
							fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
							fprintf(out, pfLOAD);				/* load the value */
						}else if(p->SUB(1)->attrib == IDVECA && ((IDVEC == IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2)) || (IDVECINT == IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2)))) {
							_type2 = IDfind(p->SUB(1)->SUB(1)->value.s, &_attrib2);
							if(_type2 == ID) {
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfLOAD);				/* load the value */
								_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2);
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfADD);
								fprintf(out, pfLOAD);				/* load the value */
							}else if(_type2 == INT) {
								eval(p->SUB(1)->SUB(1));
								_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2);
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfADD);
								fprintf(out, pfLOAD);				/* load the value */
							}else{
								fprintf(stderr, "Not a valid rvalue\n");
							}
						}
						fprintf(out, pfLOCAL, _attrib);		/* access local variable */
						fprintf(out, pfSTORE);			/* store the value at address */
					}else if(_type == INTVEC) { /* inicialized var type init := [8] */
						
					}else{
						fprintf(stderr, "Not a valid lvalue\n");
					}
					break;
				case IDVECA:
					_type = IDfind(p->SUB(0)->value.s, &_attrib);
					if((_type == IDVECINT) || (_type == IDVEC)) {
						if(p->SUB(1)->attrib == INT) {
							eval(p->SUB(1));
						}else if((p->SUB(1)->attrib == ID) &&  (_type == IDfind(p->SUB(1)->value.s, &_attrib2))) {
							fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
							fprintf(out, pfLOAD);				/* load the value */
						}else if(p->SUB(1)->attrib == IDVECA && ((IDVEC == IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2)) || (IDVECINT == IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2)))) {
							_type2 = IDfind(p->SUB(1)->SUB(1)->value.s, &_attrib2);
							if(_type2 == ID) {
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfLOAD);				/* load the value */
								_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2);
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfADD);
								fprintf(out, pfLOAD);				/* load the value */
							}else if(_type2 == INT) {
								eval(p->SUB(1)->SUB(1));
								_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2);
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfADD);
								fprintf(out, pfLOAD);				/* load the value */
							}else{
								fprintf(stderr, "Not a valid rvalue\n");
							}
						}
						if(p->SUB(0)->SUB(1)->attrib == INT) {
							eval(p->SUB(0)->SUB(1));
						}else if((p->SUB(0)->SUB(1)->attrib == ID) && (ID == (_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2)))) {
							fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
							fprintf(out, pfLOAD);
						}
						fprintf(out, pfLOCAL, _attrib);		/* access local variable */
						fprintf(out, pfADD);
						fprintf(out, pfSTORE);			/* store the value at address */
					}else{
						fprintf(stderr, "ID is not a integer\n");
					}
					break;
			}
			break;
				case IDVECA:
					_type = IDfind(p->SUB(0)->value.s, &_attrib);
					if((_type == IDVECINT) || (_type == IDVEC)) {
						if(p->SUB(1)->attrib == INT) {
							eval(p->SUB(1));
						}else if((p->SUB(1)->attrib == ID) &&  (_type == IDfind(p->SUB(1)->value.s, &_attrib2))) {
							fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
							fprintf(out, pfLOAD);				/* load the value */
						}else if(p->SUB(1)->attrib == IDVECA && ((IDVEC == IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2)) || (IDVECINT == IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2)))) {
							_type2 = IDfind(p->SUB(1)->SUB(1)->value.s, &_attrib2);
							if(_type2 == ID) {
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfLOAD);				/* load the value */
								_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2);
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfADD);
								fprintf(out, pfLOAD);				/* load the value */
							}else if(_type2 == INT) {
								eval(p->SUB(1)->SUB(1));
								_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2);
								fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
								fprintf(out, pfADD);
								fprintf(out, pfLOAD);				/* load the value */
							}else{
								fprintf(stderr, "not a valid rvalue: ");
								yyerror("error");
							}
						}
						if(p->SUB(0)->SUB(1)->attrib == INT) {
							eval(p->SUB(0)->SUB(1));
						}else if((p->SUB(0)->SUB(1)->attrib == ID) && (ID == (_type2 = IDfind(p->SUB(1)->SUB(0)->value.s, &_attrib2))) {
							fprintf(out, pfLOCAL, _attrib2);		/* access local variable */
							fprintf(out, pfLOAD);
						}
						fprintf(out, pfLOCAL, _attrib);		/* access local variable */
						fprintf(out, pfADD);
						fprintf(out, pfSTORE);			/* store the value at address */
					}else{
						fprintf(stderr, "ID is not a integer: ");
						yyerror("error");
					}
					break;
			}
			break;
		case '?':
			if (IDfind(p->SUB(0)->value.s, 0) >= 0) {
			  fprintf(out, pfCALL, "readi");
			  fprintf(out, pfPUSH);
			  fprintf(out, pfADDR, p->SUB(0)->value.s);
			  fprintf(out, pfSTORE);
			}
			break;
		case '=':
			name = p->SUB(0)->value.s;
			if (IDfind(name, (int*)IDtest) == -1) { /* variable not found ?       */
			  fprintf(out, pfDATA);			/* variables are DATA         */
			  fprintf(out, pfALIGN);		/* make sure we are aligned   */
			  fprintf(out, pfLABEL, name);		/* name variable location     */
			  fprintf(out, pfCONST, 0);		/* initialize it to 0 (zero)  */
			  fprintf(out, pfTEXT);			/* return to the TEXT segment */
			  IDnew(INTEGER, name, 0);		/* put in the symbol table    */
			}
			eval(p->SUB(1));			/* determine the new value    */
			fprintf(out, pfADDR, name);		/* where to store the value   */
			fprintf(out, pfSTORE);			/* store the value at address */
			break;
		case UMINUS:
			eval(p->SUB(0));			/* determine the value	      */
			fprintf(out, pfNEG);			/* make the 2-compliment      */
			break;
		default:
			eval(p->SUB(0));			/* evaluate first argument    */
			eval(p->SUB(1));			/* evaluate second argument   */
			switch(p->attrib) {			/* make the operation ...     */
				case '+':   fprintf(out, pfADD); break;
				case '-':   fprintf(out, pfSUB); break;
				case '*':   fprintf(out, pfMUL); break;
				case '/':   fprintf(out, pfDIV); break;
				case '%':   fprintf(out, pfMOD); break;
				case '<':   fprintf(out, pfLT); break;
				case '>':   fprintf(out, pfGT); break;
				case GE:    fprintf(out, pfGE); break;
				case LE:    fprintf(out, pfLE); break;
				case NE:    fprintf(out, pfNE); break;
				case EQ:    fprintf(out, pfEQ); break;
				default:    printf("unknown %d ('%c')\n", p->attrib, p->attrib);
			}
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
