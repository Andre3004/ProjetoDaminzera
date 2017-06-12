char * IntToStr(int x) {
	char * str = (char *) malloc(sizeof(char)*100);
	str[0] = '\0';
	int tam = 0;
	while (x>0) {
		int unidade = x % 10;
		for (int i=tam; i>0; i--) {
			str[i] = str[i-1]; 
		}
		str[0] = '0' + unidade;
		str[tam+1] = '\0';
		
		x = (x - unidade) / 10;
		tam++;
	}
	return str;
}

int StrToInt(char * str) {
	float x = 0;
	for (int i=0; i<strlen(str); i++) {
		x += (str[i] - '0') * pow(10,strlen(str) -i -1);
	}
	return x;
}

void removeEnter(char * str) {
	if (str[strlen(str)-1] == '\n')	{
		str[strlen(str)-1] = '\0';
	}
}
