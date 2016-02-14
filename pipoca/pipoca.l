%{
#include <stdio.h>
#include "lib/node.h"
#include "y.tab.h"
#include "block.h"

int blockstack[100] = {0};
int comcounter = 0;
int *b = blockstack;
int countblock = 0;
int virtualline = 0;
%}

DIG [0-9]
INT {DIG}+
EXP [Ee][+-]?{INT}
REAL {INT}"."{INT}({EXP})?
ID [a-zA-Z][a-zA-Z0-9_]*
STRING \'([^\']*|\\\n*)\'

%x COM1 COM2 CODE
%%

<COM1>"\}"							{printf("ASD\n");if(--comcounter == 0) {BEGIN INITIAL;}}
<COM1>"\{"							{comcounter++;}
<COM1>.|\n							{}
<COM2>\n							{BEGIN INITIAL;}
<COM2>.								{}

^[ \t]*"\{"							{comcounter++; BEGIN COM1;}
^[ \t]*"\#"							{BEGIN COM2;}
^"\n"								{}
^[ \t]+"\n"							{}
^[ \t]*								{
								countblock = countblockspaces(yytext);
								if(virtualline == 0) {
									if(countblock == *b) {
										countblock = 0;
										/*return CNTBLOCK;*/
									} else if(countblock > *b) {
										b++;
										if(b == blockstack+100) {
											fprintf(stderr, "Compiler onlys supports 100 sequencial blocks\n");
											exit(1);
											}
										*b = countblock;
										countblock = 0;
										return STARTBLOCK;
									} else {
										countblock = 0;
										b--;
										return ENDBLOCK;
									}
								} else {
									virtualline == 0;
								}
								}
^"end"								{b--; return ENDENDBLOCK;}		
"not"								{return NOT;}
"and"								{return AND;}
"or"								{return OR;}
"if"								{return IF;}
"then"								{return THEN;}
"else"								{return ELSE;}
"endif"								{return ENDIF;}
"while"								{return WHILE;}
"do"								{return DO;}
"done"								{return DONE;}
"until"								{return UNTIL;}
"break"								{return BREAK;}
"continue"							{return CONTINUE;}
"goto"								{return GOTO;}
"real"								{return REAL;}
"integer"							{return INTEGER;}
"const"								{return CONST;}
"var"								{return VAR;}
"init"								{return INIT;}
"extern"							{return EXTERN;}
"end"								{return END;}

"-"								{return yytext[0];}
"\+"								{return yytext[0];}
"\*"								{return yytext[0];}
"\/"								{return yytext[0];}
"\%"								{return yytext[0];}
"**"								{return POT;}
"\<"								{return yytext[0];}
"\>"								{return yytext[0];}
"\="								{return yytext[0];}
">="								{return MOREOREQUAL;}
"<="								{return LESSOREQUAL;}
"<>"								{return NOTEQUAL;}
":="								{return OPATR;}
"@"								{return yytext[0];}
"++"								{return PLUSONE;}
"--"								{return MINUSONE;}

"\["								{return yytext[0];}
"\]"								{return yytext[0];}
"\("								{return yytext[0];}
"\)"								{return yytext[0];}
"\,"								{return yytext[0];}

"!!"								{return PRINTLN;}
"!"								{return yytext[0];}
"?"								{return yytext[0];}

{ID}								{yylval.s = (char*) dupstr(yytext); return ID;}
{INT}								{	
								strtof(yytext, NULL);
								if(errno == ERANGE) {
									fprintf(stderr, "Int Overflow\n");
									exit(1);
								}
								yylval.i = atoi(yytext);
								return INT;
								}
{REAL}								{return REALN;}
{EXP}								{return EXP;}
{STRING}							{yylval.s = (char*) dupstr(yytext); return STRING;}
"\\\n"								{virtualline = 1;}
[ ]								{}
"\n"								{return NEWLINE;}
.								{return yytext[0];}

%%
