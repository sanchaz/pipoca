/* $Id: code.c,v 1.7 2004/12/09 17:25:13 prs Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include "lib/node.h"
#include "y.tab.h"
#include "lib/tabid.h"
#include "lib/postfix.h"

#define SUB(x)	value.sub.n[x]

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
	int i, lbl1, lbl2, lbl3;
	char *name;
	Node *aux;

	if (p == 0) return;
	switch(p->attrib) {
		case DECL:
			eval(p->SUB(0));
			break;
		case FUNC:
			fprintf(out, pfTEXT);
			fprintf(out, pfALIGN);
			IDnew(FUNC, p->SUB(0)->value.s, 0);
			fprintf(out, pfGLOBL, p->SUB(0)->value.s, pfFUNC);
			fprintf(out, pfLABEL, p->SUB(0)->value.s);
			fprintf(out, pfENTER, 4);
			eval(p->SUB(2));
			fprintf(out, pfINT, 0);
			fprintf(out, pfPOP);
			fprintf(out, pfLEAVE);
			fprintf(out, pfRET);
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
			fprintf(out, pfSTR, p->value.s);		/* output string characters   */
			fprintf(out, pfCHAR, 0);			/* put a char so we dont risk printing every thing on stack */
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
       			eval(p->SUB(0)					/* generate and print the string */
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
			fprintf(out, pfLABEL, mklbl(lbl1 = ++lbl));
			eval(p->SUB(0));
			fprintf(out, pfJZ, mklbl(lbl2 = ++lbl));
			eval(p->SUB(1));
			fprintf(out, pfJMP, mklbl(lbl1));
			fprintf(out, pfLABEL, mklbl(lbl2));
			eval(p->SUB(2));
			fprintf(out, pfLABEL, mklbl(lbl3));
			break;
		case IF:
			eval(p->SUB(0));
			fprintf(out, pfJZ, mklbl(lbl1 = ++lbl));
			eval(p->SUB(1));
			if (p->value.sub.num > 2) { /* if else */
			    fprintf(out, pfJMP, mklbl(lbl2 = ++lbl));
			    fprintf(out, pfLABEL, mklbl(lbl1));
			    eval(p->SUB(2));
			    lbl1 = lbl2;
			}
			fprintf(out, pfLABEL, mklbl(lbl1));
			break;
		case READ:
			if (IDfind(p->value.s, 0) >= 0) {
			  fprintf(out, pfCALL, "readi");
			  fprintf(out, pfPUSH);
			  fprintf(out, pfADDR, p->value.s);
			  fprintf(out, pfSTORE);
			}
			break;
		case PRINT:
			eval(p->SUB(0));			/* determine the value        */
			fprintf(out, pfCALL, "printi");		/* call the print function    */
			fprintf(out, pfCALL, "println");		/* print a newline	      */
			fprintf(out, pfTRASH, 4);			/* delete the printed value   */
			break;
		case ';':
			for (i = 0; i < p->value.sub.num; i++)
			  eval(p->SUB(i));
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
