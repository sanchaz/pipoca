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

void pull_chars(char *s, int start_index) {
	
	int i;
	
	for(i = start_index; i < strlen(s); i++) {
		s[i-1] = s[i];
	}
	s[i-1] = '\0';
}

int fix_special_chars(char *s) {

	int i, special_char = 0, ret = 0;
	
	for(i = 0; i < strlen(s); i++) {
		if(s[i] == '\\') {
			switch(s[i+1]) {
				case '\\':
					s[i] = '\\';
					ret = 1;
					pull_chars(s, i+2);
					break;
				case '\'':
					s[i] = '\'';
					ret = 1;
					pull_chars(s, i+2);
					break;
				case 'n':
					s[i] = '\n';
					ret = 1;
					pull_chars(s, i+2);
					break;
				case 'r':
					s[i] = '\r';
					ret = 1;
					pull_chars(s, i+2);
					break;
				case 't':
					s[i] = '\t';
					ret = 1;
					pull_chars(s, i+2);
					break;
				case 'b':
					s[i] = '\b';
					ret = 1;
					pull_chars(s, i+2);
					break;
				default:
					break;
			}
		}	
	}
	
	return ret;
}

int count_args(Node *p) {
	
	Node *aux = p;
	int ret = 0, _break = 0;
	
	for( ; ; ) {
		if (aux == 0) return 0;
		switch(aux->attrib) {
			case LISTEXP3:
				ret++;
				aux = aux->SUB(0);
				break;
			case LISTEXP4:
				ret++;
				aux = aux->SUB(0);
				break;		
			default:
				return ret;
				break;
		}
	}
	return ret;
}

int static ret = 4;

int calc_enter(Node *p) {
	
	int i = 0;

	if (p == 0) return;
    	switch(p->attrib) {
    		case VAR:
			for(i = 0; i < p->value.sub.num; i++) {
				switch(p->SUB(i)->attrib) {
					case ID:
						ret += 4;
						break;
					case IDVEC:
						ret += 4;
						break;
					case IDVECINT:
						ret += (4 * p->SUB(i)->SUB(1)->value.i);
						break;
				}
			}
			break;
		case CONST:
			for(i = 0; i < p->value.sub.num; i++) {
				ret += 4;
			}
			break;
		case ID:
			break;
		case FID:
			break;
		case PRINTSTRING:
			break;
		case INITID:
			break;
		case STRING:
			break;
		case IDVEC:
			break;
		case INT:
			break;
		default:
			for(i = 0; i < p->value.sub.num; i++) {
				calc_enter(p->SUB(i));
			}
			break;
    	}
    	
    	return ret;
}
