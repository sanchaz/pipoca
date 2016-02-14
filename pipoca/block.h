int countblockspaces(char *s) {
	int i = 0;
	int spaces = 0;
	for(i = 0; s[i] != '\0'; i++) {
		if(s[i] == ' ') {
			spaces++;
		}else if(s[i] == '\t') {
			spaces += 8;
		}
	}
	return spaces;
}
