int power(int b, int a) {
	
	int ret = a, i;
	if(b == 0) {
		return 1;
	}
	if(b < 0) {
		return 0;
	}
	for(i = b-1; i > 0; i--) {
		ret *= a;
	}
	
	return ret;
}
