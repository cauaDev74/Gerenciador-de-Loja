#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUTO 10
#define LENGTH 20

void clearInputBuffer() {
    //Limpa caracteres restantes no buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarProduto(char produto[][LENGTH], float preco[], int* contaP, int quantidadeNoEstoque[]){
    /*  ¬» Essa função tem como objetivo cadastrar o produto recebendo: nome, preço e quantidade.
            Utilizei uma matriz 10x20 para registrar os nomes dos produtos, essa função vai receber
            apenas o nome do produto que está sendo registrado no momento e isso serve para os outros parâmetros.
        ¬» Sugestão de melhora seria utilizar structs para que apenas uma variável receba todos os parâmetros.
    */
    if(*contaP >= MAX_PRODUTO){
        //Verifica se já atingiu o limite de produtos
        printf("Limite de produtos registrados atingido.\n");
        return;
    }

    char nomeDoProduto[LENGTH];
    float precoUnitario;
    int quantidade;

    printf("Informe o nome do produto: ");
    if(fgets(nomeDoProduto, LENGTH, stdin) == NULL){
        printf("Erro ao ler o nome.\n");
        return;
    }
    nomeDoProduto[strcspn(nomeDoProduto, "\n")] = 0;
    strcpy(produto[*contaP], nomeDoProduto);
    
    printf("Insira o valor: R$");
    if(scanf("%f", &precoUnitario) != 1){
        printf("Valores inválidos.\n");
        clearInputBuffer();
        return;
    }
    
    preco[*contaP] = precoUnitario;
    
    printf("Insira a quantidade no estoque: ");
    if(scanf("%d", &quantidade) != 1){
        printf("Quantidade inválida.\n");
        clearInputBuffer();
        return;
    }
    
    quantidadeNoEstoque[*contaP] = quantidade;

    clearInputBuffer();

    (*contaP)++;

    printf("Produto cadastrado com sucesso.\n");
}

void venderProduto(char M[][LENGTH], int Q[], float P[], int total) {

    char nome[LENGTH];              
    int quantia, encontrado= 0;
    int i;

    printf("Nome do produto: ");
    fgets(nome, LENGTH, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Quantidade desejada: ");
    if(scanf("%d", &quantia) != 1 || quantia <= 0){
        printf(" Quantidade inválida.\n");
        clearInputBuffer();
        return;
    }

    for (i = 0; i<total; i++) {

        if (strcmp(M[i], nome) == 0) { 

            encontrado = 1;

            if (Q[i] >= quantia) { // verifica se tem estoque

                float totalPagar = quantia * P[i];

                Q[i] -= quantia; // att estoque se 

                printf("Produto: %s\n", M[i]);
                printf("Total a pagar: R$ %.2f\n", totalPagar);
                printf("Estoque restante: %d\n", Q[i]);

            } else {
                printf("Estoque insuficiente!\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado!\n");
    }
    clearInputBuffer();
}

void pesquisarProduto();

void imprimirEstoque();

int main(){
    int indiceP = 0;
    char produto[MAX_PRODUTO][LENGTH];
    int Q[10];
    float P[10];

    int totalProdutos = 0; 
    int escolha;
    
    do{
    printf("\tSISTEMA ABERTO!\t\n\n");   
    printf(" 1 - CADASTRAR PRODUTO\n");
    printf(" 2 - VENDER\n");
    printf(" 3 - PESQUISAR PRODUTO\n");
    printf(" 4 - IMPRIMIR ESTOQUE\n");
    printf(" 5 - SAIR\n");
    printf("ESCOLHA UMA OPÇÃO:\n");
    scanf("%d", &escolha);
    
    switch (escolha){
        case 1:
        clearInputBuffer();
        cadastrarProduto(produto, P, &indiceP, Q);
        break;
    case 2:
        clearInputBuffer();
        venderProduto(produto, Q, P, totalProdutos);
        break;
    case 3: 
        clearInputBuffer();
        printf("OPÇÃO DE PESQUISA ESCOLHIDA\n");
        break;
    case 4: 
        clearInputBuffer();
        printf("OPÇÃO DE IMPRIMIR ESCOLHIDA\n");
        break;
    case 5:
        clearInputBuffer();
        printf("SAINDO...\n");
        break;
    default:
        printf("OPÇÃO INVÁLIDA!!\n");
        break;
    }
        
    } while(escolha != 5);

    return 0;

}