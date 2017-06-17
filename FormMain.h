void showFormMain() {
	system("cls");
	printf("--------------------\n");
	printf("|   MENU PRINCIPAL |\n");
	printf("--------------------\n");
	printf("1. MARCA\n");
	printf("2. MODELO\n");
	printf("3. CLIENTE\n");
	printf("4. VEICULO\n");
	printf("5. PRODUTO\n");
	printf("6. SERVICO\n");
	printf("0. SAIR\n");
	printf("--------------------\n");
}

void executeFormMain() {
	showFormMain();
	printf("Entre com a opcao: ");
	char ch = getche();
	while (ch != '0') {
		switch(ch) {
			case '1' : executeFormMarca(); break;
			case '2' : executeFormModelo(); break;
			case '3' : executeFormCliente(); break;
			case '4' : executeFormVeiculo(); break;
			case '5' : executeFormProduto(); break;
			case '6' : executeFormServico(); break;
			default  : printf("\nOpcao invalida"); break;
		}
		showFormMain();
		printf("Entre com a opcao: ");
		ch = getche();
	}
	
}
