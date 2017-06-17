struct TServico {
	int id;
	int qtdHrs;
	int valor;
	char * descricao;
};

struct TNoServico{
	TServico * Servico;
	TNoServico * prox;
};

TServico * createServico(int id,int qtdHrs,int valor ,char * descricao) {
	TServico * Servico = (TServico *) malloc(sizeof(TServico));
	Servico->id = id;
	Servico->qtdHrs=qtdHrs;
	Servico->valor=valor;
	Servico->descricao = (char *) malloc(sizeof(char)*100);
	if (descricao != NULL) 
	{
		strcpy(Servico->descricao,descricao);
	} else {
		Servico->descricao[0] = '\0';
	}
	return Servico;
}

TServico * cloneServico(TServico * Servico) {
	if (Servico != NULL) 
	{
		return createServico(Servico->id,Servico->qtdHrs,Servico->valor,Servico->descricao);
	}
	return createServico(0,0,0,NULL);
}

TNoServico* createNoServico(TServico * Servico) {
	TNoServico * no = (TNoServico *) malloc(sizeof(TNoServico));
	no->Servico = cloneServico(Servico);
	no->prox = NULL;
	return no;
}

void destroyServico(TServico * Servico) {
	if (Servico != NULL) {
	  	
		free(Servico->descricao);
		free(Servico);
	}
}

void destroyNoServico(TNoServico * no) {
	if (no != NULL) {	
		destroyServico(no->Servico);
		free(no);
	}
}

void printServico(TServico * Servico) {
	printf("Id do Produto: %d\n",Servico->id);
	printf("quantidade de horas: %d\n",Servico->qtdHrs);
	printf("valor: %d\n",Servico->valor);
	printf("Descricao: %s\n",Servico->descricao);
}

void insertServico(TNoServico ** head, TServico * Servico) {
	if (Servico != NULL) {
		TNoServico * newNo = createNoServico(Servico);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoServico * pAux = *head;
			while (pAux->prox != NULL) {
				pAux = pAux->prox;
			}
			pAux->prox = newNo;
		}	
	}
}

void insertOrderedServico(TNoServico ** head, TServico * Servico) {
	if (Servico != NULL) {
		TNoServico * newNo = createNoServico(Servico);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoServico * pAnt = *head;
			TNoServico * pProx = *head;
			while ((pProx != NULL) && (strcmp(pProx->Servico->descricao,newNo->Servico->descricao) < 0)) {
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

TServico * findServico(TNoServico* head, int id) {
	TNoServico * pAux = head;
	while ((pAux != NULL) && (pAux->Servico->id != id)) {
		pAux = pAux->prox;
	}	
	if (pAux != NULL) {
		return cloneServico(pAux->Servico);
	}
	return NULL;
}

void printAllServico(TNoServico * head) {
	TNoServico * pAux = head;
	while (pAux != NULL) {
		printServico(pAux->Servico);
		printf("-------------------\n");
		pAux = pAux->prox;
	}	
}

int removeServico(TNoServico ** head, int id) {
	TNoServico * pAnt = *head;
	TNoServico * pProx = *head;
	
	while ((pProx != NULL) && (pProx->Servico->id != id)) {
		pAnt = pProx;
		pProx = pProx->prox;
	}
	
	if (pProx != NULL) {
		if (pProx == *head) {
			*head = pProx->prox;
		} else {
			pAnt->prox = pProx->prox;
		}
		destroyNoServico(pProx);
		return 1;
	}
	return 0;
}

int saveToFileServico(TNoServico * head, char * path) {
	FILE * f = fopen(path,"w");
	if (f != NULL) {
		TNoServico * pAux = head;
		while (pAux != NULL) {
			fputs("\n",f);
			
			char * strId = IntToStr(pAux->Servico->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
		    
			 char *strqtd = IntToStr(pAux->Servico->qtdHrs); //converte o id para string
			fputs(strqtd,f); 
			free(strqtd);
			fputs("\n",f);
			
			char *  strval = IntToStr(pAux->Servico->valor); //converte o id para string
			fputs(strval,f); 
			free(strval);
			fputs("\n",f);
			
			fputs(pAux->Servico->descricao,f);
			pAux = pAux->prox;
		}
		fclose(f);
		return 1;
	}
	return 0;
}

int loadFromFileServico(TNoServico ** head, char * path) {
	FILE * f = fopen(path,"r");
	if (f != NULL) {
		char str[100];
		fgets(str,100,f);
		TServico * Servico = createServico(0,0,0,NULL);
		while (!feof(f)) {
			fgets(str,100,f);
			removeEnter(str);
			Servico->id = StrToInt(str); //converte de string para int
		
		
		
		    fgets(str,100,f);
			removeEnter(str);
			Servico->qtdHrs = StrToInt(str);
		
		    fgets(str,100,f);
			removeEnter(str);
			Servico->valor = StrToInt(str); 
			
			fgets(Servico->descricao,100,f);
			removeEnter(Servico->descricao);
			
			
			insertOrderedServico(head,Servico);
		}
		destroyServico(Servico);
		fclose(f);
		return 1;
	}
	return 0;
}

void destroyListServico(TNoServico** head) {
	TNoServico * pAnt = *head;
	TNoServico * pProx = *head;
	while (pProx != NULL) {
		pProx = pProx->prox;
		destroyNoServico(pAnt);
		pAnt = pProx;	
	}
	*head = NULL;
}

