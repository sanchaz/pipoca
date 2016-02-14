#include <string.h>

void fix_str(char *s) {
	
	int i, j;
	if(s[1] == '\'') {
		s[0] = '\0';
		return;
	}
	for(i = 0, j = i+1; i < strlen(s) - 2; i++, j++) {
		s[i] = s[j];
	}
	s[i] = '\0';
	
	return;
}
