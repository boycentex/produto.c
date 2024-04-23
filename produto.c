#include<stdio.h> 
#include<math.h> 
#include<string.h> 
#include<locale.h> 
#include<stdlib.h> 
#include<ctype.h>
#include "produto.h"

#define USUARIO "vicente123"
#define SENHA "123456"
#define EMAIL "vicenteneto159@gmail.com"


struct Login{
    char usuario[50];
    char senha[15];
    char email[80];
};

int VerificacaoLogin(char usuario[50], char senha[15]){    
	if(strcmp(USUARIO, usuario) != 0 || strcmp(SENHA, senha) != 0){ 
		return 1;
	}
else{ 
	return 0;
	} 
}

int VerificacaoEmail(char email[80]) {
    int i = 0;
    while (email[i] != '\0' && i < 80) {
        if (email[i] == '@') {
            if (strcmp(EMAIL, email) == 0) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}

struct produto { 
	char nome[50]; 
	char tipo[50];
	float peso; 
	float preco; 
	int quantidade;  
	int codigo;  
	float avaliacao; // uma media das avaliações dos clientes do produto, vai de 0 até 10 // 
};

typedef struct No {
    Produto dado;
    struct No* prox;
};

struct lista{ 
	No* inicio;
};

/*void FimLista(Lista *lista, Produto x) {
    No* novo = (No*) calloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: não foi possível alocar memória para um novo nó.\n");
        return 1;
    }
    novo->dado = x;
    novo->prox = NULL;
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        No* ptr;
        for (ptr = lista->inicio; ptr->prox != NULL; ptr = ptr->prox);
        ptr->prox = novo;
    }
}*/

/*void mostrar(Lista lista) {
    No* ptr;
    for(ptr = lista.inicio; ptr != NULL; ptr = ptr->prox) {
        Produto n = ptr->dado;
        printf("Nome: %s\nTipo: %s\nPreço: %.2f\nPeso: %.2f\nQuantidade: %d\nCódigo: %d\nAvaliações: %.1f\n\n",
               n.nome, n.tipo, n.preco, n.peso, n.quantidade, n.codigo, n.avaliacao);
    }
}*/

void editarPreco(Lista* lista, int codigo, float preco) {
  if (lista->inicio == NULL) {
    printf("Lista vazia\n");
  }
  else {
    No* ptr;
    for (ptr = lista->inicio; ptr != NULL; ptr = ptr->prox);
    if (ptr == NULL) {
      printf("Produto não encontrado\n");
    }
    else {
      ptr->dado.preco = preco;
    }
  }  
} 

void deletar(Lista *lista, int codigo) {
  if (lista->inicio == NULL) {
    printf("Lista vazia\n");
  }
  else {
      No* pa = NULL;
      No* ptr;
      for (ptr = lista->inicio; ptr->prox != NULL && ptr->dado.codigo != codigo; ptr = ptr->prox) {
        pa = ptr;
      }
      if (pa == NULL) {
        if (ptr->dado.codigo == codigo) {
          lista->inicio = ptr->prox;
          free(ptr);
        }
        else {
          printf("Produto não encontrado\n");
        }
      }
      else {
        if (ptr->dado.codigo == codigo) {
          pa->prox = ptr->prox;
          free(ptr);
        }
        else {
          printf("Produto não encontrado\n");
        }
      }
  }
}

void ler(Produto *x) {
    printf("Informe os dados do produto:\n");
    scanf("%s %s %f %f %d %d %f", x->nome, x->tipo, &x->preco, &x->peso, &x->quantidade, &x->codigo, &x->avaliacao);
}

void BoasVindas(){ 
printf("Seja muito bem vindo a loja de suplementos Suplementa Plus.\nAqui voce encontra uma variedade de suplementos para de ajudar na sua meta.\n");
printf("Seja ela perda de peso ou ganha de massa muscular.\nTambem temos produtos para de ajudar no seu rendimento durante o treino.\n"); 
printf("Contamos com preços totalmente em conta para todo tipo de pessoa.\nTambem temos otimas promoções em quase todos os nossos produtos.\n");
printf("venha conferir!\n");

}

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

void cadastrar() {
    FILE *arq = fopen("produto.b", "ab");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
    Produto n;
    printf("Informe os dados do novo produto:\n");
    printf("Nome: ");
    scanf(" %[^\n]", n.nome);
    printf("Tipo: "); // uma opção seria suplemento
    scanf(" %[^\n]", n.tipo);
    printf("Preço: ");
    scanf("%f", &n.preco);
    printf("Peso em gramas do Produto:\n");
    scanf("%f", &n.peso);
    printf("Quantidade disponivel no estoque:\n");
    scanf("%d", &n.quantidade);
    printf("Informe o codigo do produto:\n");
    scanf("%d", &n.codigo);
    printf("Informe a media de avaliacoes dos clientes pelo produto:\n");
    scanf("%f", &n.avaliacao);
    fwrite(&n, sizeof(Produto), 1, arq);
    printf("Produto cadastrado com sucesso!\n");
    fclose(arq);
}

void listar() {
    FILE *arq = fopen("produto.b", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
    Produto n;
    while (fread(&n, sizeof(Produto), 1, arq)) {
        printf("Nome: %s\nTipo: %s\nPreço: %.2f\nPeso: %.2f\nQuantidade: %d\nCódigo: %d\nAvaliações: %.1f\n\n",
               n.nome, n.tipo, n.preco, n.peso, n.quantidade, n.codigo, n.avaliacao);
    }
    fclose(arq);
}

int tamanho() {
    FILE *arq = fopen("produto.b", "rb");
	Produto n;
    int cont = 0;
    while (fread(&n, sizeof(Produto), 1, arq)) {
        cont++;
    }
    fclose(arq);
    return cont;
}

void lerLista(Lista *lista) {
  FILE *arq = fopen("produto.b", "rb");
  Produto n;
  while (fread(&n, sizeof(Produto), 1, arq)) {
      adicionaFim(lista, n);
  }
  fclose(arq);
}

void salvaLista(Lista *lista) {
  FILE *arq = fopen("produto.b", "wb");
  No* ptr;
  for (ptr = lista->inicio; ptr != NULL; ptr = ptr->prox) {
    fwrite(&ptr->dado, sizeof(Produto), 1, arq);
  }
  fclose(arq);
}

void ordenar(){ 
	Lista lista;
	lista.inicio = NULL;
	lerlista(&lista);
	No *p1;
	No *p2;
	No *fim = NULL;
	if(lista.inicio == NULL){ 
		return;
	}
	for(p1 = lista.inicio; p1->prox != NULL; p1 = p1->prox){ 
	
		for(p2 = lista.inicio; p2->prox != NULL; p2 = p2->prox){ 
			if(p2->dado.codigo > p2->prox->dado.codigo){ 
				produto temp = p2->dado;
				p2->dado = p2->prox->dado;
				p2->prox->dado = temp;
			}			
		}
	}
salvaLista(&lista);	
}

void excluir(int codigo) {
    Lista lista;
    lista.inicio = NULL;
    lerLista(&lista);
    deletar(&lista, codigo);
    salvaLista(&lista);
}

void editar(int codigo) {
    Lista lista;
    lista.inicio = NULL;
    lerLista(&lista);
    float preco;
    printf("Informe o novo preço do produto:\n");
    scanf("%f", &n.preco);
    editarMedia(&lista, codigo, preco);
    salvaLista(&lista);
}

void calcularValorTotal(char tipo[]) {
    FILE *arq = fopen("produto.b", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
	Produto n;
    int valor = 0;
    while (fread(&n, sizeof(Produto), 1, arq)) {
        if (strcmp(n.tipo, tipo) == 0) {
            valor = n.quantidade;
        }
    }
    printf("O valor total em estoque do tipo %s é: %d unidades\n", tipo, valor);
	fclose(arq);
}

void promocao(int codigo){ 
	FILE *arq = fopen("produto.b", "rb");
	if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
	Produto n;
	float valor;
	while (fread(&n, sizeof(Produto), 1, arq)){
		if(n.codigo == codigo){ 
		valor = n.preco - (0.2*n.preco);
		} 
	}	
	printf("o valor do produto na promoção é de %.2f reais\n", valor);
	fclose(arq); 
}

void MediaDosClientes(int codigo){  // media dos clientes sobre um determinado produto//
	FILE *arq = fopen("produto.b", "rb");
	if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
	Produto n;
    float media;
	while(fread(&n, sizeof(produto), 1, arq)){ 
		if(n->codigo == codigo){ 
          media = n->avaliacao;
		}	
	} 
	printf("a media de avaliações de 0 a 5 desse produto é de %.1f\n", media);
	fclose(arq);
}
 
void procurarPorPeso(float peso) {
    FILE *arq = fopen("produto.b", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    Produto n;
    int encontrado = 0; 
    while (fread(&n, sizeof(produto), 1, arq)) {
        if (n->peso == peso){ 
            
			encontrado = 1;
            printf("um produto com esse peso foi encontrado seu nome é %s do tipo %s\n", n.nome, n.tipo);
        }
    }
    if (!encontrado) {
    printf("Nenhum produto encontrado com o peso especificado.\n");
    }
    fclose(arq);
} 
 
void buscar (int codigo) {
    FILE *arq = fopen("produto.b", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
	Produto n;
    int dx = 0;
    while (fread(&n, sizeof(Produto), 1, arq)) {
        if (n.codigo == codigo) {
            printf("nome:%s\ntipo:%s\npreço:%.2f reais\npeso:%.2f gramas\nquantidade:%d\ncodigo:%d\nmedia de avaliações dos clientes:%.2f\n", n.nome, n.tipo, n.peso, n.preco, n.quantidade, n.codigo, n.avaliacao);
            dx = 1;
        }
    }
    if (dx == 0) {
        printf("Produto não Encontrado\n");
    }
    fclose(arq);
}

void ComprarMaisDe1(int codigo, int x) {
    FILE *arq = fopen("produto.b", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
    Produto n;
    float soma = 0;
    int encontrado = 0; // Variável para verificar se o produto foi encontrado
    while (fread(&n, sizeof(Produto), 1, arq)) {
        if (n.codigo == codigo) {
            soma = x * n.preco;
            encontrado = 1;
            break; 
        }
    }

    if (encontrado) {
        printf("O valor final da compra vai ser igual a %.2f reais\n", soma);
    } else {
        printf("Produto não encontrado.\n");
    }

    fclose(arq);
}

void excluir(int codigo) {
    int v = tamanho();
	Produto n[v];
    FILE *arq = fopen("produto.b", "rb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
	int i = 0;
    while (fread(&n[i], sizeof(Produto), 1, arq)) {
        i++;
    }
    fclose(arq);
    arq = fopen("produto.b", "wb");
    for (i = 0; i < v; i++) {
        if (n[i].codigo != codigo) {
            fwrite(&n[i], sizeof(produto), 1, arq);
        }
    }
    fclose(arq);
}


int main() {
    setlocale(LC_ALL, "portuguese");

	BoasVindas();

	char usuario[50];
    char senha[15];
    char email[80];

    printf("Digite o nome de usuário: ");
    scanf("%s", usuario);
    printf("Digite a sua senha: ");
    scanf("%s", senha);

    int x = VerificacaoLogin(usuario, senha);
    while (x != 0) {
        printf("Nome de usuário ou senha incorreto. Tente novamente.\n");
        printf("Digite o nome de usuário novamente: ");
        scanf("%s", usuario);
        printf("Digite a sua senha novamente: ");
        scanf("%s", senha);
        x = VerificacaoLogin(usuario, senha);
    }
    printf("Verificação do login concluída com sucesso.\n\n");

    printf("Agora vamos verificar o seu email.\n");
    printf("Por favor, informe seu email: ");
    scanf("%s", email);
    int y = VerificacaoEmail(email);
    while (y == 0) {
        printf("Email inválido. Por favor, insira novamente: ");
        scanf("%s", email);
        y = VerificacaoEmail(email);
    }
    printf("Email válido.\n\n");

	Lista lista; 
	lista.inicio = NULL;
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
        } else if( opcao == 11){ 
			ordenar(&lista);
		} else if (opcao == 0) {
            printf("Encerrando o programa...\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);


    return 0;
}

