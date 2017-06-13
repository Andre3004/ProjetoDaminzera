struct Tveiculo {
	int id;
	char[7] placa;
	char[15] cor;
    char[25] chassie;
    TMarca * marca;
	tmodelo * modelo;
};

struct TNoveiculo {
	Tveiculo * veiculo;
	TNoveiculo * prox;
}

Tveiculo * createveiculo(int id,char chassie,char placa,char cor,TMarca * marca,tmodelo * modelo) {
	Tveiculo * veiculo = (Tveiculo *) malloc(sizeof(Tveiculo));
	veiculo->id = id;
	veiculo->placa = placa;
	veiculo->cor = cor;
	veiculo->chassie = chassie;	
	veiculo->marca = cloneMarca(marca);
	veiculo->modelo =clonemodelo(modelo)
	
	return veiculo;
}

Tveiculo * cloneveiculo(Tveiculo * veiculo) {
	if (veiculo != NULL) {
		return createveiculo(veiculo->id,veiculo->placa,veiculo->cor,veiculo->chassie,veiculo->marca,veiculo->modelo);
	}
	return createveiculo(0,NULL,NULL,NULL,NULL,NULL);
}

TNoveiculo * createNoveiculo(Tveiculo * veiculo) {
	TNoModelo * no = (TNoveiculo *) malloc(sizeof(TNoveiculo));
	no->veiculo = cloneveiculo(veiculo);
	no->prox = NULL;
	return no;
}

void destroyveiculo(Tveiculo * veiculo) {
	if (veiculo != NULL) {	
		free(veiculo->placa);
		free(veiculo->cor);
		free(veiculo->chassie);
		destroyMarca(veiculo->marca);
		destroymodelo(veiculo->modelo)
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
	printf("id.......: %d\n",veiculo->id);
	printf("placa.......: %d\n",veiculo->placa);
	printf("cor.......: %d\n",veiculo->cor);
	printf("chassie.......: %d\n",veiculo->chassie);
	printf("Marca\n");
	printMarca(veiculo->marca);
	printf("modelo\n");
	printMarca(veiculo->modelo);
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

TModelo * findveiculo(TNoveiculo * head, int id) {
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

int removeModelo(TNoveiculo ** head, int id) {
	TNoveiculo * pAnt = *head;
	TNoveiculo * pProx = *head;
	
	while ((pProx != NULL) && (pProx->veiculo->modelo->id != id)) {
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
			
			fputs(pAux->veiculo->cor,f);
			fputs("\n",f);	
			fputs(pAux->veiculo->placa,f);
			fputs("\n",f);
			fputs(pAux->veiculo->chassie,f);
			fputs("\n",f);
			
			strId = IntToStr(pAux->veiculo->marca->id); //converte o id para string
			fputs(strId,f); 
			free(strId);
			fputs("\n",f);			
			
			fputs(pAux->veiculo->marca->descricao,f);
				
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
			
			fgets(veiculo-> ->descricao,100,f);
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

void destroyListveiculo(TNoveiculo ** head) {
	TNoveiculo * pAnt = *head;
	TNo * pProx = *head;
	while (pProx != NULL) {
		pProx = pProx->prox;
		destroyNoveiculo(pAnt);
		pAnt = pProx;	
	}
	*head = NULL;
}
