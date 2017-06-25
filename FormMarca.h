void showFormMarca() {
	system("cls");
	printf("--------------------\n");
	printf("|       MARCA      |\n");
	printf("--------------------\n");
	printf("1. INSERIR\n");
	printf("2. BUSCAR\n");
	printf("3. LISTAR\n");
	printf("4. REMOVER\n");
	printf("5. SALVAR\n");
	printf("0. SAIR\n");
	printf("--------------------\n");
}

void insertFormMarca(TNoMarca ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  INSERIR MARCA   |\n");
	printf("--------------------\n");
	
	TMarca * marca = (TMarca *) malloc(sizeof(TMarca));
	marca->descricao = (char *) malloc(sizeof(char)*100);

	printf("Entre com o id: ");
	scanf("%d",&marca->id);
	while( (findMarca(*head,marca->id) != NULL) )
    { 
		printf("ID ja esta em uso !!\n");
		printf("Entre com o id: ");
	    scanf("%d",&marca->id);
    }   
	fflush(stdin);
	
	printf("Entre com a descricao: ");
	gets(marca->descricao);
	while( (strlen(marca->descricao) < 3) )
    { 
		printf("Descricao invalida !!\n");
		printf("Entre com a descricao: ");
		gets(marca->descricao);
    }   
	fflush(stdin);
	insertOrderedMarca(head,marca);
	
	destroyMarca(marca);
	
	printf("Marca inserida com sucesso!");
	getch();
}

void findFormMarca(TNoMarca * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   BUSCAR MARCA   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id: ");
	scanf("%d",&id);
	fflush(stdin);
	
	TMarca * marca = findMarca(head,id);
	if (marca != NULL) {
		printMarca(marca);
		free(marca);
	} else {
		printf("Marca nao encontrada!");
	}
	
	getch();	
}

void listFormMarca(TNoMarca * head) {
	system("cls");
	printf("--------------------\n");
	printf("|  LISTAR MARCA    |\n");
	printf("--------------------\n");
	printAllMarca(head);
	getch();	
}

void removeFormMarca(TNoMarca ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  REMOVER MARCA   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id da marca: ");
	scanf("%d",&id);
	fflush(stdin);
	
	if (removeMarca(head,id)) {
		printf("Marca removida com sucesso!");
	} else {
		printf("Marca nao encontrada!");
	}
	
	getch();
}

void saveFormMarca(TNoMarca * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   SALVAR MARCA   |\n");
	printf("--------------------\n");
	if (saveToFileMarca(head,"marca.txt")) {
		printf("Arquivo salvo com sucesso!");
	} else {
		printf("Erro ao salvar arquivo!");
	}
	getch();
}

TMarca * selectMarca() {
	TNoMarca * head = NULL;
	loadFromFileMarca(&head,"marca.txt");
	if (head != NULL) {
		listFormMarca(head);
		
		int id;
		printf("Entre com o id da marca: ");
		scanf("%d",&id);
		fflush(stdin);
		
		TMarca * marca = findMarca(head,id);
		while (marca == NULL) {
			printf("Marca nao encontrada!\n");
			printf("\n===== Pressione 0 para sair! =========\n");
			printf("Entre com o id: ");
			scanf("%d",&id);
			if ( id == 0 )
			{
				break;
			}
			fflush(stdin);
			marca = findMarca(head,id);
		}
		return marca;
	}
	return createMarca(0,"");
}

void loadFormMarca(TNoMarca ** head) {
	loadFromFileMarca(head,"marca.txt");
}

void executeFormMarca() {
	TNoMarca * head = NULL;
	loadFormMarca(&head);
	showFormMarca();
	printf("Entre com a opcao: ");
	char ch = getche();
	while (ch != '0') {
		switch(ch) {
			case '1' : insertFormMarca(&head); break;
			case '2' : findFormMarca(head); break;
			case '3' : listFormMarca(head); break;
			case '4' : removeFormMarca(&head); break;
			case '5' : saveFormMarca(head); break;
			default  : printf("\nOpcao invalida"); getch(); break;
		}
		showFormMarca();
		printf("Entre com a opcao: ");
		ch = getche();
	}
	destroyListMarca(&head);
}
