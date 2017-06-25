void showFormModelo() {
	system("cls");
	printf("--------------------\n");
	printf("|       MODELO      |\n");
	printf("--------------------\n");
	printf("1. INSERIR\n");
	printf("2. BUSCAR\n");
	printf("3. LISTAR\n");
	printf("4. REMOVER\n");
	printf("5. SALVAR\n");
	printf("0. SAIR\n");
	printf("--------------------\n");
}

void insertFormModelo(TNoModelo ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  INSERIR MODELO   |\n");
	printf("--------------------\n");
	
	TModelo * modelo = (TModelo *) malloc(sizeof(TModelo));
	modelo->descricao = (char *) malloc(sizeof(char)*100);

	printf("Entre com o id do modelo: ");
	scanf("%d",&(modelo->id));
	while( (findModelo(*head,modelo->id) != NULL) )
    { 
		printf("ID ja esta em uso !!\n");
		printf("Entre com o id: ");
	    scanf("%d",&modelo->id);
    }   
	fflush(stdin);
	printf("Entre com a descricao: ");
	gets(modelo->descricao);
	while( (strlen(modelo->descricao) < 3) )
    { 
		printf("Descricao invalida !!\n");
		printf("Entre com a descricao: ");
		gets(modelo->descricao);
    }   
	
	fflush(stdin);
	
	modelo->marca = selectMarca();
	if ( modelo->marca == NULL )
	{
		printf("\n Nao foi possivel cadastrar a marca, Erro!!");
    	getch();
	}
	else
	{
		insertOrderedModelo(head,modelo);
		destroyModelo(modelo);
		printf("Modelo inserido com sucesso!");
		getch();
	}
}

void findFormModelo(TNoModelo * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   BUSCAR MODELO   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do modelo: ");
	scanf("%d",&id);
	fflush(stdin);
	
	TModelo * modelo = findModelo(head,id);
	if (modelo != NULL) {
		printModelo(modelo);
		free(modelo);
	} else {
		printf("Modelo nao encontrado!");
	}
	
	getch();	
}

void listFormModelo(TNoModelo * head) {
	system("cls");
	printf("--------------------\n");
	printf("|  LISTAR MODELO    |\n");
	printf("--------------------\n");
	printAllModelo(head);
	getch();	
}

void removeFormModelo(TNoModelo ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  REMOVER MODELO   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do modelo: ");
	scanf("%d",&id);
	fflush(stdin);
	
	if (removeModelo(head,id)) {
		printf("Modelo removido com sucesso!");
	} else {
		printf("Modelo nao encontrado!");
	}
	
	getch();
}

void saveFormModelo(TNoModelo * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   SALVAR MODELO   |\n");
	printf("--------------------\n");
	if (saveToFileModelo(head,"modelo.txt")) {
		printf("Arquivo salvo com sucesso!");
	} else {
		printf("Erro ao salvar arquivo!");
	}
	getch();
}

TModelo * selectModelo() {
	TNoModelo * head = NULL;
	loadFromFileModelo(&head,"modelo.txt");
	if (head != NULL) {
		listFormModelo(head);
		
		int id;
		printf("Entre com o id do modelo: ");
		scanf("%d",&id);
		fflush(stdin);
		
		TModelo * modelo = findModelo(head,id);
		while ( (modelo == NULL) ) {
			printf("Modelo nao encontrado!\n");
			printf("\n===== Pressione 0 para sair! =========\n");
			printf("Entre com o id: ");
			scanf("%d",&id);
			if ( id == 0 ) 
			{
				break;
			}
			fflush(stdin);
			modelo = findModelo(head,id);
		}
		return modelo;
	}
	return NULL;
}

void loadFormModelo(TNoModelo ** head) {
	loadFromFileModelo(head,"modelo.txt");
}

void executeFormModelo() {
	TNoModelo * head = NULL;
	loadFormModelo(&head);
	showFormModelo();
	printf("Entre com a opcao: ");
	char ch = getche();
	while (ch != '0') {
		switch(ch) {
			case '1' : insertFormModelo(&head); break;
			case '2' : findFormModelo(head); break;
			case '3' : listFormModelo(head); break;
			case '4' : removeFormModelo(&head); break;
			case '5' : saveFormModelo(head); break;
			default  : printf("\nOpcao invalida"); getch(); break;
		}
		showFormModelo();
		printf("Entre com a opcao: ");
		ch = getche();
	}
	destroyListModelo(&head);
}
