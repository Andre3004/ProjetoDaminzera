struct TModelo {
	int id;
	char * descricao;
	TMarca * marca;
};

struct TNoModelo {
	TModelo * modelo;
	TNoModelo * prox;
};

TModelo * createModelo(int id, char * descricao,TMarca * marca) {
	TModelo * modelo = (TModelo *) malloc(sizeof(TModelo));
	modelo->id = id;
	modelo->descricao = (char *) malloc(sizeof(char)*100);
	if (descricao != NULL) {
		strcpy(modelo->descricao,descricao);
	}
	modelo->descricao[0] = '\0';
	
	modelo->marca = cloneMarca(marca);
	
	return modelo;
}

TModelo * cloneModelo(TModelo * modelo) {
	if (modelo != NULL) {
		return createModelo(modelo->id,modelo->descricao,modelo->marca);
	}
	return createModelo(0,NULL,NULL);
}

TNoModelo * createNoModelo(TModelo * modelo) {
	TNoModelo * no = (TNoModelo *) malloc(sizeof(TNoModelo));
	no->modelo = cloneModelo(modelo);
	no->prox = NULL;
	return no;
}

void destroyModelo(TModelo * modelo) {
	if (modelo != NULL) {	
		free(modelo->descricao);
		destroyMarca(modelo->marca);
		free(modelo);
	}
}

void destroyNoModelo(TNoModelo * no) {
	if (no != NULL) {	
		destroyModelo(no->modelo);
		free(no);
	}
}

void printModelo(TModelo * modelo) {
	printf("Id.......: %d\n",modelo->id);
	printf("Descricao: %s\n",modelo->descricao);
	printf("Marca\n");
	printMarca(modelo->marca);
}

void insertModelo(TNoModelo ** head, TModelo * modelo) {
	if (modelo != NULL) {
		TNoModelo * newNo = createNoModelo(modelo);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoModelo * pAux = *head;
			while (pAux->prox != NULL) {
				pAux = pAux->prox;
			}
			pAux->prox = newNo;
		}	
	}
}

void insertOrderedModelo(TNoModelo ** head, TModelo * modelo) {
	if (modelo != NULL) {
		TNoModelo * newNo = createNoModelo(modelo);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoModelo * pAnt = *head;
			TNoModelo * pProx = *head;
			while ((pProx != NULL) && (strcmp(pProx->modelo->descricao,newNo->modelo->descricao) < 0)) {
				pAnt = pProx;
				pProx = pProx->prox;			
			}
			
			if (pProx == *head) {
				newNo->prox = *head;
				*head = newNo;
			} else {
				pAnt->prox = newNo;
				newNo->prox = pProx;
			}
		}	
	}
}

TModelo * findModelo(TNoModelo * head, int id) {
	TNoModelo * pAux = head;
	while ((pAux != NULL) && (pAux->modelo->id != id)) {
		pAux = pAux->prox;
	}	
	if (pAux != NULL) {
		return cloneModelo(pAux->modelo);
	}
	return NULL;
}

void printAllModelo(TNoModelo * head) {
	TNoModelo * pAux = head;
	while (pAux != NULL) {
		printModelo(pAux->modelo);
		printf("-------------------\n");
		pAux = pAux->prox;
	}	
}

int removeModelo(TNoModelo ** head, int id) {
	TNoModelo * pAnt = *head;
	TNoModelo * pProx = *head;
	
	while ((pProx != NULL) && (pProx->modelo->id != id)) {
		pAnt = pProx;
		pProx = pProx->prox;
	}
	
	if (pProx != NULL) {
		if (pProx == *head) {
			*head = pProx->prox;
		} else {
			pAnt->prox = pProx->prox;
		}
		destroyNoModelo(pProx);
		return 1;
	}
	return 0;
}

int saveToFileModelo(TNoModelo * head, char * path) {
	FILE * f = fopen(path,"w");
	if (f != NULL) {
		TNoModelo * pAux = head;
		while (pAux != NULL) {
			fputs("\n",f);
			
			char * strId = IntToStr(pAux->modelo->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
			
			fputs(pAux->modelo->descricao,f);
			fputs("\n",f);	
			
			strId = IntToStr(pAux->modelo->marca->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
			
			fputs(pAux->modelo->marca->descricao,f);
				
			pAux = pAux->prox;
		}
		fclose(f);
		return 1;
	}
	return 0;
}

int loadFromFileModelo(TNoModelo ** head, char * path) {
	FILE * f = fopen(path,"r");
	if (f != NULL) {
		char str[100];
		fgets(str,100,f);
		TModelo * modelo = createModelo(0,NULL,NULL);
		while (!feof(f)) {
			fgets(str,100,f);
			removeEnter(str);
			modelo->id = StrToInt(str); //converte de string para int
			
			fgets(modelo->descricao,100,f);
			removeEnter(modelo->descricao);
			
			fgets(str,100,f);
			removeEnter(str);
			modelo->marca->id = StrToInt(str); //converte de string para int
			
			fgets(modelo->marca->descricao,100,f);
			removeEnter(modelo->marca->descricao);
			
			insertOrderedModelo(head,modelo);
		}
		destroyModelo(modelo);
		fclose(f);
		return 1;
	}
	return 0;
}

void destroyListModelo(TNoModelo ** head) {
	TNoModelo * pAnt = *head;
	TNoModelo * pProx = *head;
	while (pProx != NULL) {
		pProx = pProx->prox;
		destroyNoModelo(pAnt);
		pAnt = pProx;	
	}
	*head = NULL;
}
