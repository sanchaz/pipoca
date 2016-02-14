%{
#include <stdio.h>
int comcounter = 0;
int numberofchars = 0;
int numberofcharcomments = 0;
%}

%s COM1 COM2 IGNORESTRING
%%

<COM1>"\}\n"											{/*printf("%c", yytext[1]);*/ numberofchars++; if(--comcounter == 0) {BEGIN INITIAL;}}
<COM1>"\}"												{numberofchars++; if(--comcounter == 0) {BEGIN INITIAL;}}
<COM1>"\{"												{comcounter++; numberofchars++;}
<COM1>.|\n												{/*printf("%s", yytext);*/ numberofchars++; numberofcharcomments++;}

<COM2>\n													{ECHO; numberofchars++; numberofcharcomments++; BEGIN INITIAL;}
<COM2>.													{printf("%s", yytext); numberofchars++; numberofcharcomments++;}

<IGNORESTRING>"\\\""									{numberofchars++;}
<IGNORESTRING>"\""									{numberofchars++; BEGIN INITIAL;}
<IGNORESTRING>.|\n									{numberofchars++;}

"\{"														{comcounter++; numberofchars++; BEGIN COM1;}
"\#"														{numberofchars++; BEGIN COM2;}
"\""														{numberofchars++; BEGIN IGNORESTRING;}
.|\n														{numberofchars++;}

%%

int yywrap(void)
{return 1;
}

main() {

	printf("\nPDoc\nPipoca Documentator\n\n");

	yylex();

   printf("\nPDoc\nTotal Number of Characters - %d\nNumber of Comment Characters - %d\n", numberofchars, numberofcharcomments);
}

