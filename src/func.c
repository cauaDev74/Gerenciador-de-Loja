#include <stdio.h>
#include <string.h>
#include "func.h"

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

void venderProduto(char M[][20], int Q[], float P[], int total) {

    char nome[20];              
    int quantia, encontrado= 0;
    int i;

    printf("Nome do produto: ");
    scanf("%s", nome);

    printf("Quantidade desejada: ");
    scanf("%d", &quantia);

    for (i = 0; i<total; i++) {

        if (strcmp(M[i], nome) == 0) { 

            encontrado = 1;

            if (Q[i] >= quantia) { // verifica se tem estoque

                float totalPagar = quantia * P[i];

                Q[i] -= quantia; // att estoque se 

                printf("Produto: %s\n", M[i]);
                printf("Total a pagar: R$ %.2f\n", totalPagar);

            } else {
                printf("Estoque insuficiente!\n");
            }
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado!\n");
    }
}

void pesquisarProduto();

void imprimirEstoque();

void salvarArquivo();

void menu();