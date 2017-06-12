#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "ListMarca.h"
#include "ListModelo.h"
#include "ListCliente.h"
#include "FormMarca.h"
#include "FormModelo.h"
#include "FormMain.h"

int main() {
	executeFormMain();
/*	//MODOS DE ABERTURA - TEXTO
	//w - write ou escrita
	//Cria um novo arquivo vazio e permite a escrita
	//Se o arquivo já existir, zera o tamanho dele
	
	//a - append ou concatenar
	//Abre um arquivo existente em modo de escrita,
	//porem escreve no fim do arquivo
	
	//r - read ou leitura
	//Abre um arquivo existente em modo leitura
	
	//MODES DE ABERTURA - BINARIO
	//Mesma coisa mas acrescenta um b: wb, rb, ab
	
	
	//fopen - file open
	//p1 path - onde esta o arquivo
	//p2 modo de abertura
	FILE * f = fopen("d:\\temp\\teste.txt","r");
	if (f != NULL) {
		//MODO TEXTO
		//fputs - file put string
		//p1 o que gravar
		//p2 onde gravar
		//fputs("\nOla Kaneko!",f);
		
		//fgets - file get string
		//p1 - onde voce vai ler (variavel)
		//p2 - quantos caracteres. 
	    //     Vai ler a quantidade de caracteres ou até encontar um enter, 
		//     o que acontecer primeiro.
	    //p3 de onde vou ler
	    char str[100];
	    
	    //feof - file end of file    
	    while (!feof(f)) { //enquanto nao for final de arquivo
	    	fgets(str,100,f);
			printf("%s",str);
		}
	
		//fclose - file close
		fclose(f);
	}*/
}




