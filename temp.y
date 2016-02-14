declarg:		ID
			|	declarg ',' ID
			;

inst:		inst2
		|	inst inst2
		;
		
inst2:	IF exp
		|	WHILE exp
		|	DO doexp
		|	CONST constexp
		|	VAR varexp
		|	INIT initexp
		|	EXTERN externexp
		|	ID idexp
		|	STRING stringexp
		;
		
doexp:
		;
		
constexp:
			;

varexp:
			;
			
initexp:
			;
			
externexp:
				;
				
idexp:
		;

stringexp:
				;
			
exp:		ID
		|	'(' exp ')'
		|	exp '=' ID
		|	exp NOTEQUAL ID
		|	exp '>' ID
		|	exp '<' ID
		|	exp MOREOREQUAL ID
		|	exp LESSOREQUAL ID
		|	exp POT ID
		|	'@' ID
		|	NOT ID
		|	ID PLUSONE exp
		|	ID MINUSONE exp
		;
