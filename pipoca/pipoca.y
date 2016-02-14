%{
#include <stdio.h>
#include "lib/node.h"
int yylineno;
int floatfound = 0;
%}

%start pipoca

%union {char *s; double real,exp; int i; Node *n;}

%token NOT AND OR IF THEN ELSE ENDIF WHILE DO DONE UNTIL BREAK CONTINUE GOTO REAL INTEGER CONST VAR INIT EXTERN END MOREOREQUAL LESSOREQUAL NOTEQUAL OPATR PLUSONE MINUSONE PRINTLN POT STARTBLOCK ENDBLOCK NEWLINE ENDENDBLOCK
%token <s>ID STRING
%token <real>REALN
%token <exp>EXP
%token <i>INT
%token INIT2 INIT3 EXTERN2 MULTIIDS CONST2 FUNC UNALLOCVECTOR FUNC2 IDVEC IDVECINT IDVECID EXPP FUNCCALL IDVECA PLUSONEA MINUSONEA MEMRESERV MEMRESERVP SSM LISTEXP LISTEXP2 LISTEXP3 LISTEXP4 DECL INITN CONSTN DEC INTS EXP4 MEMRESERV PRINT PRINTP PRINTM PRINTSM PRINTINT PRINTID PRINTSTRING PRINTFUNCCALL
%type <n> pipoca file decl init init2 init3 extern extern2 const2 const func listexp3 listexp4 listexp listexp2 func2 breakcontinue dec type var ints elseif endelseif elsecycle endelsecycle exp4 exp5 exp6 exp exp2 exp3 memreserv memreserv2 memreserv3 memreserv4 print print2 print3 intorreal

%%

pipoca:		file	{evaluate($1); freeNode($1);}
	;

file:				{$$ = subNode(DECL,0);}
	|	file decl	{$$ = addNode($1, $2, -1); }
	;
decl:		init	{$$ = $1;}
	|	extern	{$$ = $1;}
	|	func	{$$ = $1;}
	|	NEWLINE	{$$ = 0;}
	;
init:		INIT ID OPATR init2 NEWLINE	{$$ = subNode(INIT, 2, strNode(ID, $2), $4);}
	;

init2:		'[' init3 ']'	{$$ = $2;}
	;

init3:		intorreal	{$$ = subNode(INITN, 1, $1);}
	|	'-' intorreal	{$$ = subNode(INITN, 1, subNode('-', 1, $2));}
	|	init3 ',' intorreal	{$$ = addNode($1, $3, $1->value.sub.num);}
	|	init3 ',' '-' intorreal	{$$ = addNode($1, subNode('-', 1, $4), $1->value.sub.num);}
	;
		
extern:		EXTERN extern2 NEWLINE	{$$ = $2;}
	;
			
extern2:	ID	{$$ = subNode(EXTERN, 1, strNode(ID, $1));}
	|	extern2 ',' ID	{$$ = addNode($1, strNode(ID, $3), $1->value.sub.num);}
	;

const2:		ID OPATR const	{$$ = subNode(CONSTN, 1, subNode(OPATR, 2, strNode(ID, $1), $3));}
	|	ID "," const2 "," const	{$$ = addNode($3, subNode(OPATR, 2, strNode(ID, $1), $5), $3->value.sub.num);}
	;
			
const:		init2	{$$ = $1;}
	|	STRING	{$$ = strNode(STRING, $1);}
	|	intorreal	{$$ = $1;}
	;

func:		REAL ID '(' listexp3 ')' NEWLINE STARTBLOCK func2 ENDENDBLOCK NEWLINE	{if(floatfound == 0) {fprintf(stderr, "No floating point support\n"); floatfound = 1;}}
	|	INTEGER ID '(' listexp3 ')' NEWLINE STARTBLOCK func2 ENDENDBLOCK NEWLINE	{$$ = subNode(FUNC, 3, strNode(ID, $2), $4, $8);}
	|	ID '(' listexp3 ')' NEWLINE STARTBLOCK func2 ENDENDBLOCK NEWLINE	{$$ = subNode(FUNC, 3, strNode(ID, $1), $3, $7);}
	;

listexp3:		{$$ = 0;}
		|	exp5	{$$ = $1;}
		|	ID '[' ']'	{$$ = subNode(UNALLOCVECTOR, 1, strNode(ID, $1));}
		|	listexp4 ',' ID '[' ']'	{$$ = subNode(LISTEXP3, 2, $1, subNode(UNALLOCVECTOR, 1, strNode(ID, $3)));}
		|	listexp4 ',' exp	{$$ = subNode(LISTEXP3, 2, $1, $3);}
		;
			
listexp4:		exp5	{$$ = $1;}
		|	ID '[' ']'	{$$ = subNode(UNALLOCVECTOR, 1, strNode(ID, $1));}
		|	listexp4 ',' ID '[' ']'	{$$ = subNode(LISTEXP4, 2, $1, subNode(UNALLOCVECTOR, 1, strNode(ID, $3)));}
		|	listexp4 ',' exp	{$$ = subNode(LISTEXP4, 2, $1, $3);}
		;

listexp:	
	|	exp5	{$$ = $1;}
	|	listexp2 ',' exp	{$$ = subNode(LISTEXP, 2, $1, $3);}
	;
			
listexp2:		exp5	{$$ = $1;}
		|	listexp2 ',' exp	{$$ = subNode(LISTEXP2, 2, $1, $3);}
		;

func2:		dec 		{$$ = subNode(FUNC2, 1, $1);}
	|	ints		{$$ = subNode(FUNC2, 1, $1);}
	|	exp4		{$$ = subNode(FUNC2, 1, $1);}
	|	memreserv	{$$ = subNode(FUNC2, 1, $1);}
	|	print		{$$ = subNode(FUNC2, 1, $1);}
	|	breakcontinue	{$$ = subNode(FUNC2, 1, $1);}
	|	func2 dec	{$$ = addNode($1, $2, -1);}
	|	func2 ints	{$$ = addNode($1, $2, -1);}
	|	func2 exp4	{$$ = addNode($1, $2, -1);}
	|	func2 memreserv	{$$ = addNode($1, $2, -1);}
	|	func2 print	{$$ = addNode($1, $2, -1);}
	|	func2 breakcontinue	{$$ = addNode($1, $2, -1);}
	;

breakcontinue:		BREAK NEWLINE	{$$ = subNode(BREAK, 1, intNode(INT, 1));}
		|	CONTINUE NEWLINE	{$$ = subNode(CONTINUE, 1, intNode(INT, 1));}
		|	BREAK INT NEWLINE	{$$ = subNode(BREAK, 1, intNode(INT, $2));}
		|	CONTINUE INT NEWLINE	{$$ = subNode(CONTINUE, 1, intNode(INT, $2));}
		;

dec:		VAR type var NEWLINE	{$$ = $3;}
	|	CONST const2 NEWLINE	{$$ = subNode(CONST, 1, $2);}
	;
	
type:
	|	REAL	{if(floatfound == 0) {fprintf(stderr, "No floating point support\n"); floatfound = 1;}}
	|	INTEGER	{$$ = 0;}
	;

var:		ID	{$$ = subNode(VAR, 1, strNode(ID, $1));}
	|	ID '[' ']'	{$$ = subNode(VAR, 1, strNode(IDVEC, $1));}
	|	ID '[' INT ']'	{$$ = subNode(VAR, 1, subNode(IDVECINT, 2, strNode(ID, $1), intNode(INT, $3)));}
	|	ID '[' ID ']'	{$$ = subNode(VAR, 1, subNode(IDVECID, 2, strNode(ID, $1), strNode(ID, $3)));}
	|	var ',' ID	{$$ = addNode($1, strNode(ID, $3), -1);}
	|	var ',' ID '[' ']'	{$$ = addNode($1, strNode(IDVEC, $3), -1);}
	|	var ',' ID '[' INT ']'	{$$ = addNode($1, subNode(IDVECINT, 2, strNode(ID, $3), intNode(INT, $5)), -1);}
	|	var ',' ID '[' ID ']'	{$$ = addNode($1, subNode(IDVECID, 2, strNode(ID, $3), strNode(ID, $5)), -1);}
	;

ints:		IF exp5 THEN NEWLINE STARTBLOCK func2 ENDBLOCK elseif	{$$ = subNode(IF, 3, $2, $6, $8);}
	|	WHILE exp5 DO NEWLINE STARTBLOCK func2 ENDBLOCK elsecycle	{$$ = subNode(WHILE, 3, $2, $6, $8);}
	|	DO NEWLINE STARTBLOCK func2 ENDBLOCK UNTIL exp5 elsecycle	{$$ = subNode(DO, 3, $4, $7, $8);}
	;

elsecycle:		ELSE NEWLINE STARTBLOCK func2 ENDBLOCK endelsecycle	{$$ = subNode(ELSE, 2, $4, $6);}
		|	endelsecycle	{$$ = $1;}
		;
		
elseif:		ELSE NEWLINE STARTBLOCK func2 ENDBLOCK endelseif	{$$ = subNode(ELSE, 2, $4, $6);}
	|	endelseif	{$$ = $1;}
	;
		
endelsecycle:		DONE NEWLINE	{$$ = 0;}
		;
	
endelseif:		ENDIF NEWLINE	{$$ = 0;}
		;

exp4:		exp6 NEWLINE	{$$ = $1;}
	;

exp5:		exp	{$$ = $1;}
	|	'(' exp5 AND exp ')'	{$$ = subNode(AND, 2, $2, $4);}
	|	exp5 AND exp	{$$ = subNode(AND, 2, $1, $3);}
	|	'(' exp5 OR exp ')'	{$$ = subNode(OR, 2, $2, $4);}
	|	exp5 OR exp	{$$ = subNode(OR, 2, $1, $3);}
	;

exp6:		exp5			{$$ = $1;}
	|	ID OPATR exp6		{$$ = subNode(OPATR, 2, strNode(ID, $1), $3);}
	;

exp:		exp2	{$$ = $1;}
	|	exp3	{$$ = $1;}
	|	exp '-' exp3	{$$ = subNode('-', 2, $1, $3);}
	|	exp '-' exp2	{$$ = subNode('-', 2, $1, $3);}
	|	exp '+' exp3	{$$ = subNode('+', 2, $1, $3);}
	|	exp '+' exp2	{$$ = subNode('+', 2, $1, $3);}
	|	exp '*' exp3	{$$ = subNode('*', 2, $1, $3);}
	|	exp '*' exp2	{$$ = subNode('*', 2, $1, $3);}
	|	exp '/' exp3	{$$ = subNode('/', 2, $1, $3);}
	|	exp '/' exp2	{$$ = subNode('/', 2, $1, $3);}
	|	exp '%' exp3	{$$ = subNode('%', 2, $1, $3);}
	|	exp '%' exp2	{$$ = subNode('%', 2, $1, $3);}
	|	exp POT exp3	{$$ = subNode(POT, 2, $1, $3);}
	|	exp POT exp2	{$$ = subNode(POT, 2, $1, $3);}
	|	exp '<' exp3	{$$ = subNode('<', 2, $1, $3);}
	|	exp '<' exp2	{$$ = subNode('<', 2, $1, $3);}
	|	exp '>' exp3	{$$ = subNode('>', 2, $1, $3);}
	|	exp '>' exp2	{$$ = subNode('>', 2, $1, $3);}
	|	exp '=' exp3	{$$ = subNode('=', 2, $1, $3);}
	|	exp '=' exp2	{$$ = subNode('=', 2, $1, $3);}
	|	exp MOREOREQUAL exp3	{$$ = subNode(MOREOREQUAL, 2, $1, $3);}
	|	exp MOREOREQUAL exp2	{$$ = subNode(MOREOREQUAL, 2, $1, $3);}
	|	exp LESSOREQUAL exp3	{$$ = subNode(LESSOREQUAL, 2, $1, $3);}
	|	exp LESSOREQUAL exp2	{$$ = subNode(LESSOREQUAL, 2, $1, $3);}
	|	exp NOTEQUAL exp3	{$$ = subNode(NOTEQUAL, 2, $1, $3);}
	|	exp NOTEQUAL exp2	{$$ = subNode(NOTEQUAL, 2, $1, $3);}
	|	ID '[' memreserv2 ']' OPATR exp3	{$$ = subNode(OPATR, 2, subNode(IDVECA, 2, strNode(ID, $1), $3), $6);}
	|	ID '[' memreserv2 ']' OPATR exp2	{$$ = subNode(OPATR, 2, subNode(IDVECA, 2, strNode(ID, $1), $3), $6);}
	|	exp '?'	{$$ = subNode('?', 1, $1);}
	;

exp2:		'(' exp ')'	{$$ = subNode(EXPP, 1, $2);}
	;
		
exp3:		ID	{$$ = strNode(ID, $1);}
	|	'@' ID	{$$ = subNode('@', 1, strNode(ID, $2));}
	|	ID '(' listexp ')'	{$$ = subNode(FUNCCALL, 2, strNode(ID, $1), $3);}
	|	ID '[' memreserv2 ']'	{$$ = subNode(IDVECA, 2, strNode(ID, $1), $3);}
	|	PLUSONE ID	{$$ = subNode(PLUSONE, 1, strNode(ID, $2));}
	|	MINUSONE ID	{$$ = subNode(MINUSONE, 1, strNode(ID, $2));}
	|	ID PLUSONE	{$$ = subNode(PLUSONEA, 1, strNode(ID, $1));}
	|	ID MINUSONE	{$$ = subNode(MINUSONEA, 1, strNode(ID, $1));}
	|	intorreal	{$$ = $1;}
	|	NOT ID	{$$ = subNode(NOT, 1, strNode(ID, $2));}
	|	'-' ID	{$$ = subNode('-', 1, strNode(ID, $2));}
	|	'-' intorreal	{$$ = subNode('-', 1, $2);}
	;
		
memreserv:		'[' ID ']' '=' memreserv2 NEWLINE {$$ = subNode(MEMRESERV, 2, strNode(ID, $2), $5);}
		;

memreserv2:		memreserv4	{$$ = $1;}
		|	memreserv3	{$$ = $1;}
		|	memreserv2 '*' memreserv3	{$$ = subNode('*', 2, $1, $3);}
		|	memreserv2 '*' memreserv4	{$$ = subNode('*', 2, $1, $3);}
		|	memreserv2 '/' memreserv3	{$$ = subNode('/', 2, $1, $3);}
		|	memreserv2 '/' memreserv4	{$$ = subNode('/', 2, $1, $3);}
		|	memreserv2 '+' memreserv3	{$$ = subNode('+', 2, $1, $3);}
		|	memreserv2 '+' memreserv4	{$$ = subNode('+', 2, $1, $3);}
		|	memreserv2 '-' memreserv3	{$$ = subNode('-', 2, $1, $3);}
		|	memreserv2 '-' memreserv4	{$$ = subNode('-', 2, $1, $3);}
		|	memreserv2 '%' memreserv3	{$$ = subNode('%', 2, $1, $3);}
		|	memreserv2 '%' memreserv4	{$$ = subNode('%', 2, $1, $3);}
		|	memreserv2 POT memreserv3	{$$ = subNode(POT, 2, $1, $3);}
		|	memreserv2 POT memreserv4	{$$ = subNode(POT, 2, $1, $3);}
		;
				
memreserv3:		intorreal {$$ = $1;}
		|	ID	{$$ = strNode(ID, $1);}
		;

memreserv4:		'(' memreserv2 ')'	{$$ = subNode(MEMRESERVP, 1, $2);}
		;
				
print:		print2 '!' NEWLINE	{$$ = subNode('!', 1, $1);} 
	|	print2 PRINTLN NEWLINE	{$$ = subNode(PRINTLN, 1, $1);}
	;

print2:		STRING	{$$ = strNode(PRINTSTRING, $1);}
	|	print2 '+' ID	{$$ = subNode(PRINTP, 2, $1, strNode(PRINTID, $3));}
	|	print2 '+' ID '(' listexp ')'	{$$ = subNode(PRINTP, 2, $1, subNode(PRINTFUNCCALL, 2, strNode(PRINTID, $3), $5));}
	|	print2 '+' STRING	{$$ = subNode(PRINTP, 2, $1, strNode(PRINTSTRING, $3));}
	|	print2 '+' INT	{$$ = subNode(PRINTP, 2, $1, intNode(PRINTINT, $3));}
	|	STRING '*' print3	{$$ = subNode(PRINTSM, 2, strNode(PRINTSTRING, $1), $3);}
	|	print2 '+' STRING '*' print3	{$$ = subNode(SSM, 3, $1, strNode(PRINTSTRING, $3), $5);}
	;

print3:		ID	{$$ = strNode(ID, $1);}
	|	intorreal	{$$ = $1;}
	|	print3 '*' ID	{$$ = subNode(PRINTM, 2, $1, strNode(ID, $3));}
	|	print3 '*' intorreal	{$$ = subNode(PRINTM, 2, $1, $3);}
	;
	
intorreal:		INT	{$$ = intNode(INT, $1);}
		|	REALN	{if(floatfound == 0) {fprintf(stderr, "No floating point support\n"); floatfound = 1;}}
		;	
		
%%
yywrap() {

  return 1;

}
char **yynames = (char**)yyname;
