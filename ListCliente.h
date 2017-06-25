struct TCliente 
{
	int id;
	char * nome;
	char * rg;
	char * cpf;
	char * cnpj;
	char * logradouro;
	char * numero;
	char * bairro;
	char * cidade;
	char * estado;
};

struct TNoCliente 
{
	TCliente * cliente;
	TNoCliente * prox;
};

TCliente * createCliente(int id, char * nome, char * rg, char * cpf, char * cnpj, char * logradouro, char * numero, char * bairro, char * cidade, char * estado) 
{
	TCliente * cliente = (TCliente *) malloc(sizeof(TCliente));
	cliente -> id = id;
	cliente->nome = (char *) malloc(sizeof(char)*100);
	cliente->rg =   (char *) malloc(sizeof(char)*100);
	cliente->cpf =  (char *) malloc(sizeof(char)*100);
	cliente->cnpj = (char *) malloc(sizeof(char)*100);
	cliente->logradouro = (char *) malloc(sizeof(char)*100);
	cliente->numero = (char *) malloc(sizeof(char)*100);
	cliente->bairro = (char *) malloc(sizeof(char)*100);
	cliente->cidade = (char *) malloc(sizeof(char)*100);
	cliente->estado = (char *) malloc(sizeof(char)*100);
	if (nome != NULL) 
	{
		strcpy(cliente->nome,nome);
	}
	else 
	{
		cliente->nome[0] = '\0';
	}
	if (rg != NULL) 
	{
		strcpy(cliente->rg,rg);
	}
	else 
	{
		cliente->rg[0] = '\0';
	}
	if (cpf != NULL) 
	{
		strcpy(cliente->cpf,cpf);
	}
	else 
	{
		cliente->cpf[0] = '\0';
	}
	if (cnpj!= NULL) 
	{
		strcpy(cliente->cnpj,cnpj);
	}
	else 
	{
		cliente->cnpj[0] = '\0';
	}
	if (logradouro != NULL) 
	{
		strcpy(cliente->logradouro,logradouro);
	}
	else 
	{
		cliente->logradouro[0] = '\0';
	}
	if (numero != NULL) 
	{
		strcpy(cliente->numero,numero);
	}
	else 
	{
		cliente->numero[0] = '\0';
	}
	if (bairro != NULL) 
	{
		strcpy(cliente->bairro,bairro);
	}
	else 
	{
		cliente->bairro[0] = '\0';
	}
	if (cidade != NULL) 
	{
		strcpy(cliente->cidade,cidade);
	}
	else 
	{
		cliente->cidade[0] = '\0';
	}
	if (estado != NULL) 
	{
		strcpy(cliente->estado,estado);
	}
	else 
	{
		cliente->estado[0] = '\0';
	}
	
	return cliente;
}

TCliente * cloneCliente(TCliente * cliente) 
{
	if (cliente != NULL) 
	{
		return createCliente(
			cliente->id,
			cliente->nome,
			cliente->rg,
			cliente->cpf,
			cliente->cnpj,
			cliente->logradouro,
			cliente->numero,
			cliente->bairro,
			cliente->cidade,
			cliente->estado);
	}
	return createCliente(0,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

TNoCliente * createNoCliente(TCliente * cliente) 
{
	TNoCliente * no = (TNoCliente *) malloc(sizeof(TNoCliente));
	no->cliente = cloneCliente(cliente);
	no->prox = NULL;
	return no;
}

void destroyCliente(TCliente * cliente) 
{
	if (cliente != NULL) 
	{	
		free(cliente->nome);
		free(cliente->rg);
		free(cliente->cpf);
		free(cliente->cnpj);
		free(cliente->logradouro);
		free(cliente->numero);
		free(cliente->bairro);
		free(cliente->cidade);
		free(cliente->estado);
		free(cliente);
	}
}

void destroyNoCliente(TNoCliente * no) 
{
	if (no != NULL) 
	{	
		destroyCliente(no->cliente);
		free(no);
	}
}

void printCliente(TCliente * cliente) 
{
	printf("Id do cliente: %d\n",cliente->id);
	printf("Nome: %s\n",cliente->nome);
	printf("RG: %s\n",cliente->rg);
	printf("CPF: %s\n",cliente->cpf);
	printf("CNPJ: %s\n",cliente->cnpj);
	printf("Logradouro: %s\n",cliente->logradouro);
	printf("Numero: %s\n",cliente->numero);
	printf("Bairro: %s\n",cliente->bairro);
	printf("Cidade: %s\n",cliente->cidade);
	printf("Estado: %s\n",cliente->estado);
}

void insertCliente(TNoCliente ** head, TCliente * cliente) 
{
	if (cliente != NULL) 
	{
		TNoCliente * newNo = createNoCliente(cliente);
		
		if (*head == NULL) 
		{
			*head = newNo;
		} 
		else 
		{
			TNoCliente * pAux = *head;
			while (pAux->prox != NULL) 
			{
				pAux = pAux->prox;
			}
			pAux->prox = newNo;
		}	
	}
}

void insertOrderedCliente(TNoCliente ** head, TCliente * cliente) 
{
	if (cliente != NULL) 
	{
		TNoCliente * newNo = createNoCliente(cliente);
		
		if (*head == NULL) 
		{
			*head = newNo;
		} 
		else 
		{
			TNoCliente * pAnt = *head;
			TNoCliente * pProx = *head;
			while ((pProx != NULL) && (strcmp(pProx->cliente->nome,newNo->cliente->nome) < 0)) 
			{
				pAnt = pProx;
				pProx = pProx->prox;			
			}
			
			if (pProx == *head) 
			{
				newNo->prox = *head;
				*head = newNo;
			} else 
			{
				pAnt->prox = newNo;
				newNo->prox = pProx;
			}
		}
	}
}

TCliente * findCliente(TNoCliente * head, int id) 
{
	TNoCliente * pAux = head;
	while ((pAux != NULL) && (pAux->cliente->id != id)) 
	{
		pAux = pAux->prox;
	}	
	if (pAux != NULL) 
	{
		return cloneCliente(pAux->cliente);
	}
	return NULL;
}

void printAllCliente(TNoCliente * head) 
{
	TNoCliente * pAux = head;
	while (pAux != NULL) 
	{
		printCliente(pAux->cliente);
		printf("-------------------\n");
		pAux = pAux->prox;
	}	
}

int removeCliente(TNoCliente ** head, int id) 
{
	TNoCliente * pAnt = *head;
	TNoCliente * pProx = *head;
	
	while ((pProx != NULL) && (pProx->cliente->id != id)) 
	{
		pAnt = pProx;
		pProx = pProx->prox;
	}
	
	if (pProx != NULL) 
	{
		if (pProx == *head) 
		{
			*head = pProx->prox;
		} else 
		{
			pAnt->prox = pProx->prox;
		}
		destroyNoCliente(pProx);
		return 1;
	}
	return 0;
}

int saveToFileCliente(TNoCliente * head, char * path) 
{
	FILE * f = fopen(path,"w");
	if (f != NULL) 
	{
		TNoCliente * pAux = head;
		while (pAux != NULL) 
		{
			fputs("\n",f);
			
			char * strId = IntToStr(pAux->cliente->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
			
			fputs(pAux->cliente->nome,f);
			fputs("\n",f);	
			fputs(pAux->cliente->rg,f);
			fputs("\n",f);	
			fputs(pAux->cliente->cpf,f);
			fputs("\n",f);	
			fputs(pAux->cliente->cnpj,f);
			fputs("\n",f);	
			fputs(pAux->cliente->logradouro,f);
			fputs("\n",f);	
			fputs(pAux->cliente->numero,f);
			fputs("\n",f);	
			fputs(pAux->cliente->bairro,f);
			fputs("\n",f);	
			fputs(pAux->cliente->cidade,f);
			fputs("\n",f);	
			fputs(pAux->cliente->estado,f);
				
			
			pAux = pAux->prox;
		}
		fclose(f);
		return 1;
	}
	return 0;
}

int loadFromFileCliente(TNoCliente ** head, char * path) 
{
	FILE * f = fopen(path,"r");
	if (f != NULL) 
	{
		char str[100];
		fgets(str,100,f);
		TCliente * cliente = createCliente(0,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		while (!feof(f)) 
		{
		fgets(str,100,f);
		removeEnter(str);
		cliente->id = StrToInt(str); //converte de string para int
			
		fgets(cliente->nome,100,f);
			
		fgets(cliente->rg,100,f);
		
		fgets(cliente->cpf,100,f);
			
		fgets(cliente->cnpj,100,f);
		
		fgets(cliente->logradouro,100,f);
			
		fgets(cliente->numero,100,f);
			
		fgets(cliente->bairro,100,f);
			
		fgets(cliente->cidade,100,f);
		
		fgets(cliente->estado,100,f);
		
			
		removeEnter(cliente->nome);
		removeEnter(cliente->rg);
		removeEnter(cliente->cpf);
		removeEnter(cliente->cnpj);
		removeEnter(cliente->logradouro);
		removeEnter(cliente->numero);
		removeEnter(cliente->bairro);
		removeEnter(cliente->cidade);
		removeEnter(cliente->estado);
			
		insertOrderedCliente(head,cliente);
		}
		destroyCliente(cliente);
		fclose(f);
		return 1;
	}
	return 0;
}


void destroyListCliente(TNoCliente ** head) 
{
	TNoCliente * pAnt = *head;
	TNoCliente * pProx = *head;
	while (pProx != NULL) 
	{
		pProx = pProx->prox;
		destroyNoCliente(pAnt);
		pAnt = pProx;	
	}
	*head = NULL;
}






