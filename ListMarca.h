struct TMarca {
	int id;
	char * descricao;
};

struct TNoMarca {
	TMarca * marca;
	TNoMarca * prox;
};

TMarca * createMarca(int id, char * descricao) {
	TMarca * marca = (TMarca *) malloc(sizeof(TMarca));
	marca->id = id;
	marca->descricao = (char *) malloc(sizeof(char)*100);
	if (descricao != NULL) {
		strcpy(marca->descricao,descricao);
	} else {
		marca->descricao[0] = '\0';
	}
	return marca;
}

TMarca * cloneMarca(TMarca * marca) {
	if (marca != NULL) {
		return createMarca(marca->id,marca->descricao);
	}
	return createMarca(0,NULL);
}

TNoMarca * createNoMarca(TMarca * marca) {
	TNoMarca * no = (TNoMarca *) malloc(sizeof(TNoMarca));
	no->marca = cloneMarca(marca);
	no->prox = NULL;
	return no;
}

void destroyMarca(TMarca * marca) {
	if (marca != NULL) {	
		free(marca->descricao);
		free(marca);
	}
}

void destroyNoMarca(TNoMarca * no) {
	if (no != NULL) {	
		destroyMarca(no->marca);
		free(no);
	}
}

void printMarca(TMarca * marca) {
	printf("Id.......: %d\n",marca->id);
	printf("Descricao: %s\n",marca->descricao);
}

void insertMarca(TNoMarca ** head, TMarca * marca) {
	if (marca != NULL) {
		TNoMarca * newNo = createNoMarca(marca);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoMarca * pAux = *head;
			while (pAux->prox != NULL) {
				pAux = pAux->prox;
			}
			pAux->prox = newNo;
		}	
	}
}

void insertOrderedMarca(TNoMarca ** head, TMarca * marca) {
	if (marca != NULL) {
		TNoMarca * newNo = createNoMarca(marca);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoMarca * pAnt = *head;
			TNoMarca * pProx = *head;
			while ((pProx != NULL) && (strcmp(pProx->marca->descricao,newNo->marca->descricao) < 0)) {
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

TMarca * findMarca(TNoMarca * head, int id) {
	TNoMarca * pAux = head;
	while ((pAux != NULL) && (pAux->marca->id != id)) {
		pAux = pAux->prox;
	}	
	if (pAux != NULL) {
		return cloneMarca(pAux->marca);
	}
	return NULL;
}

void printAllMarca(TNoMarca * head) {
	TNoMarca * pAux = head;
	while (pAux != NULL) {
		printMarca(pAux->marca);
		printf("-------------------\n");
		pAux = pAux->prox;
	}	
}

int removeMarca(TNoMarca ** head, int id) {
	TNoMarca * pAnt = *head;
	TNoMarca * pProx = *head;
	
	while ((pProx != NULL) && (pProx->marca->id != id)) {
		pAnt = pProx;
		pProx = pProx->prox;
	}
	
	if (pProx != NULL) {
		if (pProx == *head) {
			*head = pProx->prox;
		} else {
			pAnt->prox = pProx->prox;
		}
		destroyNoMarca(pProx);
		return 1;
	}
	return 0;
}

int saveToFileMarca(TNoMarca * head, char * path) {
	FILE * f = fopen(path,"w");
	if (f != NULL) {
		TNoMarca * pAux = head;
		while (pAux != NULL) {
			fputs("\n",f);
			
			char * strId = IntToStr(pAux->marca->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
			
			fputs(pAux->marca->descricao,f);
			pAux = pAux->prox;
		}
		fclose(f);
		return 1;
	}
	return 0;
}

int loadFromFileMarca(TNoMarca ** head, char * path) {
	FILE * f = fopen(path,"r");
	if (f != NULL) {
		char str[100];
		fgets(str,100,f);
		TMarca * marca = createMarca(0,NULL);
		while (!feof(f)) {
			fgets(str,100,f);
			removeEnter(str);
			marca->id = StrToInt(str); //converte de string para int
			
			fgets(marca->descricao,100,f);
			removeEnter(marca->descricao);
			
			insertOrderedMarca(head,marca);
		}
		destroyMarca(marca);
		fclose(f);
		return 1;
	}
	return 0;
}

void destroyListMarca(TNoMarca ** head) {
	TNoMarca * pAnt = *head;
	TNoMarca * pProx = *head;
	while (pProx != NULL) {
		pProx = pProx->prox;
		destroyNoMarca(pAnt);
		pAnt = pProx;	
	}
	*head = NULL;
}
