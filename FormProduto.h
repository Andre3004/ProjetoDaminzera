void showFormProduto() {
	system("cls");
	printf("--------------------\n");
	printf("|      PRODUTO     |\n");
	printf("--------------------\n");
	printf("1. INSERIR\n");
	printf("2. BUSCAR\n");
	printf("3. LISTAR\n");
	printf("4. REMOVER\n");
	printf("5. SALVAR\n");
	printf("0. SAIR\n");
	printf("--------------------\n");
}

void insertFormProduto(TNoProduto ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  INSERIR PRODUTO  |\n");
	printf("--------------------\n");
	
	TProduto * Produto = (TProduto *) malloc(sizeof(TProduto));
	Produto->descricao = (char *) malloc(sizeof(char)*100);

	printf("Entre com o id: ");
	scanf("%d",&Produto->id);
	while( (findProduto(*head,Produto->id) != NULL) )
    { 
		printf("ID ja esta em uso !!\n");
		printf("Entre com o id: ");
	    scanf("%d",&Produto->id);
    }   
	fflush(stdin);
	
	printf("Entre com a quantidade: ");
	scanf("%d",&Produto->quantidade);
	while ((Produto->quantidade) <= 0)
	{
		printf("quantidade invalido");	
		fflush(stdin);
		printf("\nEntre com a quantidade: ");
		scanf("%d",&Produto->quantidade);
    }

	printf("Entre com o valor: ");
	scanf("%d",&Produto->valor);
    while ((Produto->valor) < 0)
	{
		printf("valor invalido");	
		printf("\nEntre com o valor: ");
		scanf("%d",&Produto->valor);
    }
    
    printf("Entre com a descricao: ");
	scanf("%s",Produto->descricao);
    while (strlen(Produto->descricao) < 3)
	{
		printf("descricao invalida");	
		printf("\nEntre com a descricao: ");
		scanf("%s",Produto->descricao);
    }
	
	insertOrderedProduto(head,Produto);	
	destroyProduto(Produto);
	
	printf("Produto inserido com sucesso!");
	getch();
}

void findFormProduto(TNoProduto * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   BUSCAR PRODUTO   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do Produto: ");
	scanf("%d",&id);
	fflush(stdin);
	
	TProduto * Produto = findProduto(head,id);
	if (Produto != NULL) {
		printProduto(Produto);
		free(Produto);
	} else {
		printf("Produto nao encontrado!");
	}
	
	getch();	
}

void listFormProduto(TNoProduto* head) {
	system("cls");
	printf("--------------------\n");
	printf("|  LISTAR PRODUTO   |\n");
	printf("--------------------\n");
	printAllProduto(head);
	getch();	
}

void removeFormProduto(TNoProduto ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  REMOVER PRODUTO  |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do Produto: ");
	scanf("%d",&id);
	fflush(stdin);
	
	if (removeProduto(head,id)) {
		printf("Produto removida com sucesso!");
	} else {
		printf("Produto nao encontrada!");
	}	
	getch();
    }
void saveFormProduto(TNoProduto * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   SALVAR PRODUTO  |\n");
	printf("--------------------\n");
	if (saveToFileProduto(head,"Produto.txt")) {
		printf("Arquivo salvo com sucesso!");
	} else {
		printf("Erro ao salvar arquivo!");
	}
	getch();
}

TProduto * selectProduto() {
	TNoProduto * head = NULL;
	loadFromFileProduto(&head,"Produto.txt");
	if (head != NULL) {
		listFormProduto(head);
		
		int id;
		printf("Entre com o id da Produto: ");
		scanf("%d",&id);
		fflush(stdin);
		
		TProduto * Produto = findProduto(head,id);
		while (Produto == NULL) {
			printf("Produto nao encontrada!\n");
			printf("Entre com o id: ");
			scanf("%d",&id);
			fflush(stdin);
			Produto = findProduto(head,id);
		}
		return Produto;
	}
	return createProduto(0,0,0,NULL);
}

void loadFormProduto(TNoProduto ** head) {
	loadFromFileProduto(head,"Produto.txt");
}

void executeFormProduto() {
	TNoProduto * head = NULL;
	loadFormProduto(&head);
	showFormProduto();
	printf("Entre com a opcao: ");
	char ch = getche();
	while (ch != '0') {
		switch(ch) {
			case '1' : insertFormProduto(&head); break;
			case '2' : findFormProduto(head); break;
			case '3' : listFormProduto(head); break;
			case '4' : removeFormProduto(&head); break;
			case '5' : saveFormProduto(head); break;
			default  : printf("\nOpcao invalida"); getch(); break;
		}
		showFormProduto();
		printf("Entre com a opcao: ");
		ch = getche();
	}
	destroyListProduto(&head);
}

