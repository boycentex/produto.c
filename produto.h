#ifndef H_PRODUTO
#define H_PRODUTO 

typedef struct produto Produto;
typedef struct lista Lista;
typedef struct no No; 

void FimLista(Lista *lista, Produto x);

void mostrar(Lista lista);

void editarPreco(Lista* lista, int codigo, float preco); 

void deletar(Lista *lista, int codigo); 

void ler(Produto *x); 

void cadastrar(); 

void buscar (int codigo); 

void listar();

int tamanho(); 

void excluir(int codigo); 

void editar(int codigo); 

void salvaLista(Lista *lista); 

void calcularValorTotal(char tipo[]);

void promocao(int codigo);

void MediaDosClientes(int codigo);

void procurarPorPeso(float peso);

void ComprarMaisDe1(int codigo, int x);

#endif
