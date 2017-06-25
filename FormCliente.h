void showFormCliente() {
	system("cls");
	printf("--------------------\n");
	printf("|       CLIENTE      |\n");
	printf("--------------------\n");
	printf("1. INSERIR\n");
	printf("2. BUSCAR\n");
	printf("3. LISTAR\n");
	printf("4. REMOVER\n");
	printf("5. SALVAR\n");
	printf("0. SAIR\n");
	printf("--------------------\n");
}

void insertFormCliente(TNoCliente ** head) {
	system("cls");
	printf("--------------------\n");
	printf("|  INSERIR CLIENTE   |\n");
	printf("--------------------\n");
	
	TCliente * cliente = (TCliente *) malloc(sizeof(TCliente));
	
	cliente->nome = (char *) malloc(sizeof(char)*100);
	cliente->rg =   (char *) malloc(sizeof(char)*8);
	cliente->cpf =  (char *) malloc(sizeof(char)*11);
	cliente->cnpj = (char *) malloc(sizeof(char)*14);
	cliente->logradouro = (char *) malloc(sizeof(char)*100);
	cliente->numero = (char *) malloc(sizeof(char)*100);
	cliente->bairro = (char *) malloc(sizeof(char)*100);
	cliente->cidade = (char *) malloc(sizeof(char)*100);
	cliente->estado = (char *) malloc(sizeof(char)*100);

	printf("Entre com o id: ");
	scanf("%d",&(cliente->id));
	while( (findCliente(*head,cliente->id) != NULL) )
    { 
		printf("ID ja esta em uso !!\n");
		printf("Entre com o id: ");
	    scanf("%d",&cliente->id);
    }   
	fflush(stdin);	
	printf("Entre com a nome: ");
	gets(cliente->nome);
	while( (strlen(cliente->nome) < 3) )
    { 
		printf("Nome invalido !!\n");
		printf("Entre com o nome: ");
		gets(cliente->nome);
    }   
	
	fflush(stdin);	
	printf("Entre com o RG: ");
	gets(cliente->rg);
    while (strlen(cliente->rg) != 8 )
	{
		printf("RG Invalido(o numero do RG deve conter 8 caracteres)");
		printf("\nEntre com o RG: ");
		gets(cliente->rg);
	}
	fflush(stdin);
	
	char tipo;
	printf("FISICA OU JURIDICA(f/j) :");
	scanf("%c",&tipo);
	fflush(stdin);
    while (((tipo != 'j') && (tipo != 'J')) &&  ((tipo != 'f') && (tipo != 'F')))
    {
	    printf("tipo invalido:");
		printf("\nFISICA OU JURIDICA(f/j) :");
		scanf("%c",&tipo);
	}
	if ((tipo == 'f') || (tipo == 'F'))
	{
		printf("Entre com o CPF: ");
		gets(cliente->cpf);
		cliente->cnpj=NULL;
		while (strlen(cliente->cpf) != 11 )
		{	
			printf("\nCPF Invalido(o numero do CPF deve conter 11 caracteres)");
			printf("\nEntre com o CPF: ");
			gets(cliente->cpf);
	    }
    }  
    fflush(stdin);
 
    if ((tipo == 'J') || (tipo == 'j'))
	{	
	fflush(stdin);	
	printf("Entre com o CNPJ: ");
	gets(cliente->cnpj);
	cliente->cpf=NULL;
	while (strlen(cliente->cnpj) != 14  )
	{
		printf("CNPJ Invalido(o numero do CNPJ deve conter 14 caracteres)\n");
		printf("\nEntre com o CNPJ: ");
		gets(cliente->cnpj);
	}
	} 
    fflush(stdin);
    
	printf("Entre com o logradouro: ");
	gets(cliente->logradouro);
	while (strlen(cliente->logradouro) < 3  )
	{
		printf("Logradouro Invalido\n");
		printf("\nEntre com o logradouro: ");
		gets(cliente->logradouro);
	}
	fflush(stdin);
	
	printf("Entre com a numero: ");
	gets(cliente->numero);
	while (cliente->numero < 0  )
	{
		printf("Numero Invalido");
		printf("Entre com o Numero: ");
		gets(cliente->numero);
	}
	fflush(stdin);
	
	printf("Entre com a bairro: ");
	gets(cliente->bairro);
	while (strlen(cliente->bairro) < 3  )
	{
		printf("Bairro Invalido");
		printf("\nEntre com o bairro: ");
		gets(cliente->bairro);
	}
	fflush(stdin);
	
	printf("Entre com a cidade: ");
	gets(cliente->cidade);
	while (strlen(cliente->cidade) < 3  )
	{
		printf("Cidade Invalida");
		printf("\nEntre com a Cidade: ");
		gets(cliente->cidade);
	}
	fflush(stdin);
	
	printf("Entre com a estado: ");
	gets(cliente->estado);
	while (strlen(cliente->estado) < 3   )
	{
		printf("Estado Invalido");
		printf("\nentre com o estado: ");
		gets(cliente->estado);
	}
	fflush(stdin);
	
	insertOrderedCliente(head,cliente);	
	destroyCliente(cliente);	
	printf("Cliente inserido com sucesso!");
	getch();
}

void findFormCliente(TNoCliente * head) {
	system("cls");
	printf("--------------------\n");
	printf("|   BUSCAR CLIENTE   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do cliente: ");
	scanf("%d",&id);
	fflush(stdin);
	
	TCliente * cliente = findCliente(head,id);
	if (cliente != NULL) {
		printCliente(cliente);
		free(cliente);
	} else {
		printf("Cliente nao encontrado!");
	}
	
	getch();	
}

void listFormCliente(TNoCliente * head) {
	system("cls");
	printf("--------------------\n");
	printf("|  LISTAR CLIENTE    |\n");
	printf("--------------------\n");
	printAllCliente(head);
	getch();	
}

void removeFormCliente(TNoCliente ** head) 
{
	system("cls");
	printf("--------------------\n");
	printf("|  REMOVER CLIENTE   |\n");
	printf("--------------------\n");
	
	int id;
	printf("Entre com o id do cliente: ");
	scanf("%d",&id);
	fflush(stdin);
	
	if (removeCliente(head,id)) 
	{
		printf("Cliente removido com sucesso!");
	} else 
	{
		printf("Cliente nao encontrado!");
	}
	
	getch();
}

void saveFormCliente(TNoCliente * head) 
{
	system("cls");
	printf("--------------------\n");
	printf("|   SALVAR CLIENTE   |\n");
	printf("--------------------\n");
	if (saveToFileCliente(head,"cliente.txt")) 
	{
		printf("Arquivo salvo com sucesso!");
	} else 
	{
		printf("Erro ao salvar arquivo!");
	}
	getch();
}

TCliente * selectCliente() 
{
	TNoCliente * head = NULL;
	loadFromFileCliente(&head,"cliente.txt");
	if (head != NULL) 
	{
		listFormCliente(head);
		
		int id;
		printf("Entre com o id do cliente: ");
		scanf("%d",&id);
		fflush(stdin);
		
		TCliente * cliente = findCliente(head,id);
		while (cliente == NULL) 
		{
			printf("Cliente nao encontrado!\n");
			printf("\n===== Pressione 0 para sair! =========\n");
			printf("Entre com o id do cliente: ");
			scanf("%d",&id);
			if ( id == 0 ) 
			{
				break;
			}
			fflush(stdin);
			cliente = findCliente(head,id);
		}
		return cliente;
	}
	return createCliente(0,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
}

void loadFormCliente(TNoCliente ** head) 
{
	loadFromFileCliente(head,"cliente.txt");
}

void executeFormCliente() 
{
	TNoCliente * head = NULL;
	loadFormCliente(&head);
	showFormCliente();
	printf("Entre com a opcao: ");
	char ch = getche();
	while (ch != '0') 
	{
		switch(ch) {
			case '1' : insertFormCliente(&head); break;
			case '2' : findFormCliente(head); break;
			case '3' : listFormCliente(head); break;
			case '4' : removeFormCliente(&head); break;
			case '5' : saveFormCliente(head); break;
			default  : printf("\nOpcao invalida"); getch(); break;
		}
		showFormCliente();
		printf("Entre com a opcao: ");
		ch = getche();
	}
	destroyListCliente(&head);
}



