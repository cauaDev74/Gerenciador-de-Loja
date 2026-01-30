#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"

int main(){
    int indiceP = 0;
    char produto[MAX_PRODUTOS][LENGTH];
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