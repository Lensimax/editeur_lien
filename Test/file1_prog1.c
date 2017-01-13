int factoriel(int i){
	if(i<0){
		return -1;
	} else if(i == 0){
		return 0;
	} else if(i == 1){
		return 1;
	} else {
		return i*factoriel(i-1);
	}
}