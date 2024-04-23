#include<stdio.h>
#include "produto.h" 

void menu(){
	printf("escolha um dos itens abaixo\n");
	printf("1 - Cadastrar\n");
	printf("2 - Listar\n"); 
	printf("3 - Buscar\n");  
	printf("4 - Calcular valor total em estoque de um tipo de produto\n"); 
	printf("5 - Valor do Item com Promoção\n"); 
	printf("6 - Media de Avaliações de um Produto Especifico\n"); 
	printf("7 - Procurar Produto com um Peso Espesifico\n");
	printf("8 - Comprar Mais de 1 Produto\n"); 
	printf("9 - Editar\n"); 
	printf("10 - excluir\n");
	printf("0 - sair\n");
} 

int main(){ 

int opcao;

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            cadastrar();
        } else if (opcao == 2) {
            listar();
        } else if (opcao == 9) {
            int codigo;
            printf("Informe o código do produto que deseja editar:\n");
            scanf("%d", &codigo);
            editar(codigo);
        } else if (opcao == 10) {
            int codigo;
            printf("Informe o código do produto que deseja excluir:\n");
            scanf("%d", &codigo);
            excluir(codigo);
        } else if (opcao == 3) {
            int codigo;
            printf("Informe o código do produto que deseja buscar:\n");
            scanf("%d", &codigo);
            buscar(codigo);
        } else if (opcao == 4) {
            char tipo[50];
            printf("Informe o tipo do produto para calcular o valor total em estoque:\n");
            scanf(" %[^\n]", tipo);
            calcularValorTotal(tipo);
        } else if (opcao == 5) {
            int codigo;
            printf("Informe o código do produto para aplicar a promoção:\n");
            scanf("%d", &codigo);
            promocao(codigo);
        } else if (opcao == 6) {
            int codigo;
            printf("Informe o código do produto para calcular a média de avaliações:\n");
            scanf("%d", &codigo);
            MediaDosClientes(codigo);
        } else if (opcao == 7) {
            float peso;
            printf("Informe o peso específico que deseja procurar:\n");
            scanf("%f", &peso);
            procurarPorPeso(peso);
        } else if (opcao == 8) {
            int codigo; 
            int x;
            printf("Informe o codigo do produto que deseja procurar:\n");
            scanf("%d", &codigo); 
            printf("informe a quantidade que deseja comprar desse produto:\n");
            scanf("%d", &x);
			ComprarMaisDe1(codigo, x);
        } else if (opcao == 0) {
            printf("Encerrando o programa...\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);


    return 0;

}
