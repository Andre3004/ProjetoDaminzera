void showFormServico() {
	system("cls");
	printf("--------------------\n");
	printf("|      SERVICO     |\n");
	printf("--------------------\n");
	printf("1. INSERIR\n");
	printf("2. BUSCAR\n");
	printf("3. LISTAR\n");
	printf("4. REMOVER\n");
	printf("5. SALVAR\n");
	printf("0. SAIR\n");
	printf("--------------------\n");
}

void insertFormServico(TNoServico ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  INSERIR SERVICO  |\n");
	printf("--------------------\n");
	
	TServico * Servico = (TServico *) malloc(sizeof(TServico));
	Servico->descricao = (char *) malloc(sizeof(char)*100);

	printf("Entre com o id: ");
	scanf("%d",&Servico->id);
	while( (findServico(*head,Servico->id) != NULL) )
    { 
		printf("ID ja esta em uso !!\n");
		printf("Entre com o id: ");
	    scanf("%d",&Servico->id);
    }   
	fflush(stdin);
	
	printf("Entre com a quantidade de horas: ");
	scanf("%d",&Servico->qtdHrs);
	while ((Servico->qtdHrs) <= 0)
	{
		printf("quantidade de horas invalido");	
		fflush(stdin);
		printf("\nEntre com a quantidade de horas: ");
		scanf("%d",&Servico->qtdHrs);
    }

	printf("Entre com o valor: ");
	scanf("%d",&Servico->valor);
    while ((Servico->valor) <= 0)
	{
		printf("valor invalido");	
		printf("\nEntre com o valor: ");
		scanf("%d",&Servico->valor);
    }
    
    printf("Entre com a descricao: ");
	scanf("%s",Servico->descricao);
    while (strlen(Servico->descricao) < 2)
	{
		printf("descricao invalida");	
		printf("\nEntre com a descricao: ");
		scanf("%s",Servico->descricao);
    }
	
	insertOrderedServico(head,Servico);	
	destroyServico(Servico);
	
	printf("Servico inserido com sucesso!");
	getch();
}

void findFormServico(TNoServico * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   BUSCAR SERVICO   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do Servico: ");
	scanf("%d",&id);
	fflush(stdin);
	
	TServico * Servico = findServico(head,id);
	if (Servico != NULL) {
		printServico(Servico);
		free(Servico);
	} else {
		printf("Servico nao encontrado!");
	}
	
	getch();	
}

void listFormServico(TNoServico* head) {
	system("cls");
	printf("--------------------\n");
	printf("|  LISTAR SERVICO   |\n");
	printf("--------------------\n");
	printAllServico(head);
	getch();	
}

void removeFormServico(TNoServico ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  REMOVER SERVICO  |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do Servico: ");
	scanf("%d",&id);
	fflush(stdin);
	
	if (removeServico(head,id)) {
		printf("Servico removida com sucesso!");
	} else {
		printf("Servico nao encontrada!");
	}	
	getch();
    }
void saveFormServico(TNoServico * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   SALVAR SERVICO  |\n");
	printf("--------------------\n");
	if (saveToFileServico(head,"Servico.txt")) {
		printf("Arquivo salvo com sucesso!");
	} else {
		printf("Erro ao salvar arquivo!");
	}
	getch();
}

TServico * selectServico() {
	TNoServico * head = NULL;
	loadFromFileServico(&head,"Servico.txt");
	if (head != NULL) {
		listFormServico(head);
		
		int id;
		printf("Entre com o id da Servico: ");
		scanf("%d",&id);
		fflush(stdin);
		
		TServico * Servico = findServico(head,id);
		while (Servico == NULL) {
			printf("Servico nao encontrada!\n");
			printf("Entre com o id: ");
			scanf("%d",&id);
			fflush(stdin);
			Servico = findServico(head,id);
		}
		return Servico;
	}
	return createServico(0,0,0,NULL);
}

void loadFormServico(TNoServico ** head) {
	loadFromFileServico(head,"Servico.txt");
}

void executeFormServico() {
	TNoServico * head = NULL;
	loadFormServico(&head);
	showFormServico();
	printf("Entre com a opcao: ");
	char ch = getche();
	while (ch != '0') {
		switch(ch) {
			case '1' : insertFormServico(&head); break;
			case '2' : findFormServico(head); break;
			case '3' : listFormServico(head); break;
			case '4' : removeFormServico(&head); break;
			case '5' : saveFormServico(head); break;
			default  : printf("\nOpcao invalida"); getch(); break;
		}
		showFormServico();
		printf("Entre com a opcao: ");
		ch = getche();
	}
	destroyListServico(&head);
}

