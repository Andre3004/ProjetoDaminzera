struct Tveiculo {
	int id;
	char * placa;
	char * cor;
    char * chassie;
	TModelo * modelo;
	TCliente * cliente;
};

struct TNoveiculo {
	Tveiculo * veiculo;
	TNoveiculo * prox;
};

Tveiculo * createveiculo(int id,char * placa,char * cor,char * chassie,TModelo * modelo,TCliente * cliente) {
	Tveiculo * veiculo = (Tveiculo *) malloc(sizeof(Tveiculo));
	veiculo->id     = id;
	veiculo->placa  = (char *) malloc(sizeof(char)*20);
	veiculo->cor    = (char *) malloc(sizeof(char)*20);
	veiculo->chassie= (char *) malloc(sizeof(char)*17);
	if (placa != NULL) 
	{
		strcpy(veiculo->placa,placa);
	}
	else 
	{
		veiculo->placa[0] = '\0';
	}
	if (cor != NULL) 
	{
		strcpy(veiculo->cor,cor);
	}
	else 
	{
		veiculo->cor[0] = '\0';
	}
	if (chassie != NULL) 
	{
		strcpy(veiculo->chassie,chassie);
	}
	else 
	{
		veiculo->chassie[0] = '\0';
	}
	veiculo->modelo= cloneModelo(modelo);
	veiculo->cliente= cloneCliente(cliente);
	return veiculo;
}

Tveiculo * cloneveiculo(Tveiculo * veiculo) {
	if (veiculo != NULL)
    {
		return createveiculo(veiculo->id,veiculo->placa,veiculo->cor,veiculo->chassie,veiculo->modelo,veiculo->cliente);
	}
	return createveiculo(0,NULL,NULL,NULL,NULL,NULL);
}

TNoveiculo * createNoveiculo(Tveiculo * veiculo) {
	TNoveiculo * no = (TNoveiculo *) malloc(sizeof(TNoveiculo));
	no->veiculo = cloneveiculo(veiculo);
	no->prox = NULL;
	return no;
}

void destroyveiculo(Tveiculo * veiculo) {
	if (veiculo != NULL) {	
		free(veiculo->placa);
		free(veiculo->cor);
		free(veiculo->chassie);
		destroyModelo(veiculo->modelo);
		destroyCliente(veiculo->cliente);
		free(veiculo);
	}
}

void destroyNoveiculo(TNoveiculo * no) {
	if (no != NULL) {	
		destroyveiculo(no->veiculo);
		free(no);
	}
}

void printveiculo(Tveiculo * veiculo) {
	printCliente(veiculo->cliente);
	printModelo(veiculo->modelo);
	printf("id do veiculo: %d\n",veiculo->id);
	printf("placa........: %s\n",veiculo->placa);
	printf("cor..........: %s\n",veiculo->cor);
	printf("chassie......: %s\n",veiculo->chassie);
	
	
}

void insertveiculo(TNoveiculo ** head, Tveiculo * veiculo) {
	if (veiculo != NULL) {
		TNoveiculo  * newNo = createNoveiculo (veiculo);
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoveiculo  * pAux = *head;
			while (pAux->prox != NULL) {
				pAux = pAux->prox;
			}
			pAux->prox = newNo;
		}	
	}
}

void insertOrderedveiculo (TNoveiculo  ** head, Tveiculo  * veiculo ) {
	if (veiculo  != NULL) {
		TNoveiculo  * newNo = createNoveiculo (veiculo );
		
		if (*head == NULL) {
			*head = newNo;
		} else {
			TNoveiculo  * pAnt = *head;
			TNoveiculo  * pProx = *head;
			while ((pProx != NULL) && (strcmp(pProx->veiculo->modelo->descricao,newNo->veiculo->modelo->descricao) < 0)) {
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

Tveiculo * findveiculo(TNoveiculo * head, int id) {
	TNoveiculo * pAux = head;
	while ((pAux != NULL) && (pAux->veiculo->id != id)) {
		pAux = pAux->prox;
	}	
	if (pAux != NULL) {
		return cloneveiculo(pAux->veiculo);
	}
	return NULL;
}

void printAllveiculo(TNoveiculo * head) {
	TNoveiculo * pAux = head;
	while (pAux != NULL) {
		printveiculo(pAux->veiculo);
		printf("-------------------\n");
		pAux = pAux->prox;
	}	
}

int removeVeiculo(TNoveiculo ** head, int id) {
	TNoveiculo * pAnt = *head;
	TNoveiculo * pProx = *head;
	
	while ((pProx != NULL) && (pProx->veiculo->id != id)) {
		pAnt = pProx;
		pProx = pProx->prox;
	}
	
	if (pProx != NULL) {
		if (pProx == *head) {
			*head = pProx->prox;
		} else {
			pAnt->prox = pProx->prox;
		}
		destroyNoveiculo(pProx);
		return 1;
	}
	return 0;
}

int saveToFileveiculo(TNoveiculo * head, char * path) {
	FILE * f = fopen(path,"w");
	if (f != NULL) {
		TNoveiculo * pAux = head;
		while (pAux != NULL) {
			fputs("\n",f);
			
			char * strId = IntToStr(pAux->veiculo->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
			
			fputs(pAux->veiculo->placa,f);
			fputs("\n",f);	
			fputs(pAux->veiculo->cor,f);
			fputs("\n",f);
			fputs(pAux->veiculo->chassie,f);
			fputs("\n",f);
			
			strId = IntToStr(pAux->veiculo->modelo->marca->id ); //converte o id do modelo para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);	
			
			fputs(pAux->veiculo->modelo->marca->descricao,f); 
			fputs("\n",f);	
			
			strId = IntToStr(pAux->veiculo->modelo->id); //converte o id do modelo para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);	
			
			fputs(pAux->veiculo->modelo->descricao,f); 
			fputs("\n",f);	
			
				strId = IntToStr(pAux->veiculo->cliente->id); //converte o id do modelo para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);
			
			fputs(pAux->veiculo->cliente->nome,f); 
			fputs("\n",f);
			fputs(pAux->veiculo->cliente->rg,f); 
			fputs("\n",f);
			fputs(pAux->veiculo->cliente->cpf,f ); 
			fputs("\n",f);
			fputs(pAux->veiculo->cliente->cnpj,f ); 
			fputs("\n",f);
			fputs(pAux->veiculo->cliente->logradouro,f ); 
			fputs("\n",f);
			
		    fputs(pAux->veiculo->cliente->numero,f); 
			fputs("\n",f);
			
			fputs(pAux->veiculo->cliente->bairro,f); 
			fputs("\n",f);
			fputs(pAux->veiculo->cliente->cidade,f ); 
			fputs("\n",f);
			fputs(pAux->veiculo->cliente->estado,f ); 	
			
			pAux = pAux->prox;
		}
		fclose(f);
		return 1;
	}
	return 0;
}

int loadFromFileveiculo(TNoveiculo ** head, char * path) {
	FILE * f = fopen(path,"r");
	if (f != NULL) {
		char str[100];
		fgets(str,100,f);
		Tveiculo  * veiculo  = createveiculo (0,NULL,NULL,NULL,NULL,NULL);
		while (!feof(f)) {
			fgets(str,100,f);
			removeEnter(str);
			veiculo->id = StrToInt(str); //converte de string para int
			
	        fgets(veiculo->placa,100,f);
			removeEnter(veiculo->placa);
			
			fgets(veiculo->cor,100,f);
			removeEnter(veiculo->cor);
			
			fgets(veiculo->chassie,100,f);
			removeEnter(veiculo->chassie);
			
		
			fgets(str,100,f);
			removeEnter(str);
			veiculo->modelo->marca->id = StrToInt(str); //converte de string para int
			
			fgets(veiculo->modelo->marca->descricao,100,f);
			removeEnter(veiculo->modelo->marca->descricao);
			
			fgets(str,100,f);
			removeEnter(str);
			veiculo->modelo->id = StrToInt(str); //converte de string para int
			
			fgets(veiculo->modelo->descricao,100,f);
			removeEnter(veiculo->modelo->descricao);
			
			//le as informacoes do Cliente
			fgets(str,100,f);
			removeEnter(str);
			veiculo->cliente->id = StrToInt(str); //converte de string para int
			
			fgets(veiculo->cliente->nome,100,f);
			removeEnter(veiculo->cliente->nome);
			
			fgets(veiculo->cliente->rg,100,f);
			removeEnter(veiculo->cliente->rg);
			
			fgets(veiculo->cliente->cpf,100,f);
			removeEnter(veiculo->cliente->cpf);
			
			fgets(veiculo->cliente->cnpj,100,f);
			removeEnter(veiculo->cliente->cnpj);
			
			fgets(veiculo->cliente->logradouro,100,f);
			removeEnter(veiculo->cliente->logradouro);
			
			fgets(str,100,f);
			removeEnter(str);
		
			fgets(veiculo->cliente->numero,100,f);
			removeEnter(veiculo->cliente->numero);
			
			fgets(veiculo->cliente->bairro,100,f);
			removeEnter(veiculo->cliente->bairro);
			
			fgets(veiculo->cliente->cidade,100,f);
			removeEnter(veiculo->cliente->cidade);
			
			fgets(veiculo->cliente->estado,100,f);
			removeEnter(veiculo->cliente->estado);			
			
			
			insertOrderedveiculo(head,veiculo);
		}
		destroyveiculo(veiculo);
		fclose(f);
	}
	return 0;
}

void destroyListveiculo(TNoveiculo ** head) {
	TNoveiculo * pAnt = *head;
	TNoveiculo * pProx = *head;
	while (pProx != NULL) {
		pProx = pProx->prox;
		destroyNoveiculo(pAnt);
		pAnt = pProx;	
	}
	*head = NULL;
}

