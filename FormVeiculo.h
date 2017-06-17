void showFormVeiculo() {
	system("cls");
	printf("--------------------\n");
	printf("|       VEICULO      |\n");
	printf("--------------------\n");
	printf("1. INSERIR\n");
	printf("2. BUSCAR\n");
	printf("3. LISTAR\n");
	printf("4. REMOVER\n");
	printf("5. SALVAR\n");
	printf("0. SAIR\n");
	printf("--------------------\n");
}

void insertFormVeiculo(TNoveiculo ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  INSERIR VEICULO   |\n");
	printf("--------------------\n");
	
	Tveiculo * veiculo = (Tveiculo *) malloc(sizeof(Tveiculo));
	veiculo->placa = (char *) malloc(sizeof(char)*100);
	veiculo->cor =   (char *) malloc(sizeof(char)*8);
	veiculo->chassie =  (char *) malloc(sizeof(char)*11);
	
    fflush(stdin);
    printf("Entre com o id do veiculo: ");
	scanf("%d",&veiculo->id);
	while( (findveiculo(*head,veiculo->id) != NULL) )
    { 
		printf("ID ja esta em uso !!\n");
		printf("Entre com o id: ");
	    scanf("%d",&veiculo->id);
    }   
	fflush(stdin);	
	printf("Entre com a placa: ");
	gets(veiculo->placa);	
	while (strlen(veiculo->placa) != 8 )
	{
		fflush(stdin);
		printf("Numero da placa Invalido");
		printf("\nEntre com a placa(EX: abc-1234): ");
		gets(veiculo->placa);
	}
	
	printf("Entre com a cor: ");
	gets(veiculo->cor);
	
	printf("Entre com o chassie: ");
	gets(veiculo->chassie);
	while (strlen(veiculo->chassie) != 17 ) 
	{
		printf("Numero de chassie Invalido(o numero do chassie deve conter 17 caracteres)");
		printf("\nEntre com o chassie: ");
		gets(veiculo->chassie);
	}
	
   
    	veiculo->modelo = selectModelo();
    	if ( veiculo->modelo == NULL )
    	{
    		printf("\n Nao foi possivel cadastrar o veiculo, Erro!!");
    		getch();
		}
		else
		{
			veiculo->cliente= selectCliente();
			if ( veiculo->cliente == NULL )
	    	{
	    		printf("\n Nao foi possivel cadastrar o veiculo, Erro!!");
	    		getch();
			}
			else
			{
				insertOrderedveiculo(head,veiculo);	
		  		destroyveiculo(veiculo);	
			}
		}
    	

	getch();
}

void findFormVeiculo(TNoveiculo * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   BUSCAR VEICULO   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id: ");
	scanf("%d",&id);
	fflush(stdin);
	
	Tveiculo * veiculo = findveiculo(head,id);
	if (veiculo != NULL) {
		printveiculo(veiculo);
		free(veiculo);
	} else {
		printf("veiculo nao encontrado!");
	}
	
	getch();	
}

void listFormVeiculo(TNoveiculo * head) {
	system("cls");
	printf("--------------------\n");
	printf("|  LISTAR VEICULO    |\n");
	printf("--------------------\n");
	printAllveiculo(head);
	getch();	
}

void removeFormVeiculo(TNoveiculo ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  REMOVER VEICULO   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id: ");
	scanf("%d",&id);
	fflush(stdin);
	
	if (removeVeiculo(head,id)) {
		printf("Veiculo removido com sucesso!");
	} else {
		printf("Veiculo nao encontrado!");
	}
	
	getch();
}

void saveFormVeiculo(TNoveiculo * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   SALVAR VEICULO   |\n");
	printf("--------------------\n");
	if (saveToFileveiculo(head,"Veiculo.txt")) {
		printf("Arquivo salvo com sucesso!");
	} else {
		printf("Erro ao salvar arquivo!");
	}
	getch();
}

Tveiculo * selectVeiculo() {
	TNoveiculo * head = NULL;
	loadFromFileveiculo(&head,"Veiculo.txt");
	if (head != NULL) {
		listFormVeiculo(head);
		
		int id;
		printf("Entre com o id: ");
		scanf("%d",&id);
		fflush(stdin);
		
		Tveiculo * veiculo = findveiculo(head,id);
		while (veiculo == NULL) {
			printf("veiculo nao encontrado!\n");
			printf("Entre com o id: ");
			scanf("%d",&id);
			fflush(stdin);
			veiculo = findveiculo(head,id);
		}
		return veiculo;
	}
	return createveiculo(0,NULL,NULL,NULL,NULL,NULL);
}

void loadFormVeiculo(TNoveiculo ** head) {
	loadFromFileveiculo(head,"Veiculo.txt");
}

void executeFormVeiculo() {
	TNoveiculo * head = NULL;
	loadFormVeiculo(&head);
	showFormVeiculo();
	printf("Entre com a opcao: ");
	char ch = getche();
	while (ch != '0') {
		switch(ch) {
			case '1' : insertFormVeiculo(&head); break;
			case '2' : findFormVeiculo(head); break;
			case '3' : listFormVeiculo(head); break;
			case '4' : removeFormVeiculo(&head); break;
			case '5' : saveFormVeiculo(head); break;
			default  : printf("\nOpcao invalida"); getch(); break;
		}
		showFormVeiculo();
		printf("Entre com a opcao: ");
		ch = getche();
	}
	destroyListveiculo(&head);
}
