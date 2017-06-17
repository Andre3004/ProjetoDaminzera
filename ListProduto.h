struct TProduto {
	int id;
	int quantidade;
	int valor;
	char * descricao;
};

struct TNoProduto{
	TProduto * Produto;
	TNoProduto * prox;
};

TProduto * createProduto(int id,int quantidade,int valor ,char * descricao) {
	TProduto * Produto = (TProduto *) malloc(sizeof(TProduto));
	Produto->id = id;
	Produto->quantidade=quantidade;
	Produto->valor=valor;
	Produto->descricao = (char *) malloc(sizeof(char)*100);
	if (descricao != NULL) 
	{
		strcpy(Produto->descricao,descricao);
	} else {
		Produto->descricao[0] = '\0';
	}
	return Produto;
}

TProduto * cloneProduto(TProduto * Produto) {
	if (Produto != NULL) {
		return createProduto(Produto->id,Produto->quantidade,Produto->valor,Produto->descricao);
	}
	return createProduto(0,0,0,NULL);
}

TNoProduto* createNoProduto(TProduto * Produto) {
	TNoProduto * no = (TNoProduto *) malloc(sizeof(TNoProduto));
	no->Produto = cloneProduto(Produto);
	no->prox = NULL;
	return no;
}

void destroyProduto(TProduto * Produto) {
	if (Produto != NULL) {
	  	
		free(Produto->descricao);
		free(Produto);
	}
}

void destroyNoProduto(TNoProduto * no) {
	if (no != NULL) {	
		destroyProduto(no->Produto);
		free(no);
	}
}

void printProduto(TProduto * Produto) {
	printf("Id do Produto: %d\n",Produto->id);
	printf("quantidade: %d\n",Produto->quantidade);
	printf("valor: %d\n",Produto->valor);
	printf("Descricao: %s\n",Produto->descricao);
}

void insertProduto(TNoProduto ** head, TProduto * Produto) {
	if (Produto != NULL) {
		TNoProduto * newNo = createNoProduto(Produto);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoProduto * pAux = *head;
			while (pAux->prox != NULL) {
				pAux = pAux->prox;
			}
			pAux->prox = newNo;
		}	
	}
}

void insertOrderedProduto(TNoProduto ** head, TProduto * Produto) {
	if (Produto != NULL) {
		TNoProduto * newNo = createNoProduto(Produto);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoProduto * pAnt = *head;
			TNoProduto * pProx = *head;
			while ((pProx != NULL) && (strcmp(pProx->Produto->descricao,newNo->Produto->descricao) < 0)) {
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

TProduto * findProduto(TNoProduto* head, int id) {
	TNoProduto * pAux = head;
	while ((pAux != NULL) && (pAux->Produto->id != id)) {
		pAux = pAux->prox;
	}	
	if (pAux != NULL) {
		return cloneProduto(pAux->Produto);
	}
	return NULL;
}

void printAllProduto(TNoProduto * head) {
	TNoProduto * pAux = head;
	while (pAux != NULL) {
		printProduto(pAux->Produto);
		printf("-------------------\n");
		pAux = pAux->prox;
	}	
}

int removeProduto(TNoProduto ** head, int id) {
	TNoProduto * pAnt = *head;
	TNoProduto * pProx = *head;
	
	while ((pProx != NULL) && (pProx->Produto->id != id)) {
		pAnt = pProx;
		pProx = pProx->prox;
	}
	
	if (pProx != NULL) {
		if (pProx == *head) {
			*head = pProx->prox;
		} else {
			pAnt->prox = pProx->prox;
		}
		destroyNoProduto(pProx);
		return 1;
	}
	return 0;
}

int saveToFileProduto(TNoProduto * head, char * path) {
	FILE * f = fopen(path,"w");
	if (f != NULL) {
		TNoProduto * pAux = head;
		while (pAux != NULL) {
			fputs("\n",f);
			
			char * strId = IntToStr(pAux->Produto->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
		    
			 char *strqtd = IntToStr(pAux->Produto->quantidade); //converte o id para string
			fputs(strqtd,f); 
			free(strqtd);
			fputs("\n",f);
			
			char *  strval = IntToStr(pAux->Produto->valor); //converte o id para string
			fputs(strval,f); 
			free(strval);
			fputs("\n",f);
			
			fputs(pAux->Produto->descricao,f);
			pAux = pAux->prox;
		}
		fclose(f);
		return 1;
	}
	return 0;
}

int loadFromFileProduto(TNoProduto ** head, char * path) {
	FILE * f = fopen(path,"r");
	if (f != NULL) {
		char str[100];
		fgets(str,100,f);
		TProduto * Produto = createProduto(0,0,0,NULL);
		while (!feof(f)) {
			fgets(str,100,f);
			removeEnter(str);
			Produto->id = StrToInt(str); //converte de string para int
		
		
		
		    fgets(str,100,f);
			removeEnter(str);
			Produto->quantidade = StrToInt(str);
		
		    fgets(str,100,f);
			removeEnter(str);
			Produto->valor = StrToInt(str); 
			
			fgets(Produto->descricao,100,f);
			removeEnter(Produto->descricao);
			
			
			insertOrderedProduto(head,Produto);
		}
		destroyProduto(Produto);
		fclose(f);
		return 1;
	}
	return 0;
}

void destroyListProduto(TNoProduto** head) {
	TNoProduto * pAnt = *head;
	TNoProduto * pProx = *head;
	while (pProx != NULL) {
		pProx = pProx->prox;
		destroyNoProduto(pAnt);
		pAnt = pProx;	
	}
	*head = NULL;
}

