#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_PRODUTO 10
#define LENGTH 20

void clearInputBuffer() {
    //Limpa caracteres restantes no buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void paraMinusculo(char name[]){
    for(int i; name[i] != '\0'; i++){
        name[i] = tolower(name[i]);
    }
}

void trim(char str[]){
    int inicio = 0;
    int fim = strlen(str) - 1;

    while(isspace(str[inicio])){
        inicio++;
    }

    while(fim >= inicio && isspace(str[fim])){
        fim--;
    }

    int i, j = 0;

    for(i = inicio; i <= fim; i++){
        str[j++] = str[i];
    }

    str[j] = '\0';
}

void cadastrarProduto(char produto[][LENGTH], float P[], int* indiceP, int Q[]){
    /*  ¬» Essa função tem como objetivo cadastrar o produto recebendo: nome, preço e quantidade.
            Utilizei uma matriz 10x20 para registrar os nomes dos produtos, essa função vai receber
            apenas o nome do produto que está sendo registrado no momento e isso serve para os outros parâmetros.
        ¬» Sugestão de melhora seria utilizar structs para que apenas uma variável receba todos os parâmetros.
    */
    if(*indiceP >= MAX_PRODUTO){
        //Verifica se já atingiu o limite de produtos
        printf("Limite de produtos registrados atingido.\n");
        return;
    }

    char nomeDoProduto[LENGTH];
    float precoUnitario;
    int quantidade;
    int encontrado = 0;

    printf("Informe o nome do produto: ");
    if(fgets(nomeDoProduto, LENGTH, stdin) == NULL){
        printf("Erro ao ler o nome.\n");
        return;
    } 
    if(strchr(nomeDoProduto, '\n') == NULL){
        printf("Nome muito grande.\n");
        return;
    }
    nomeDoProduto[strcspn(nomeDoProduto, "\n")] = 0;
    trim(nomeDoProduto);
    if(strlen(nomeDoProduto) == 0){
        printf("Nome invalido. Nao pode ser vazio.\n");
        return;
    }
    

    paraMinusculo(nomeDoProduto);

    for (int i = 0; i < *indiceP; i++) {

        if (strcmp(produto[i], nomeDoProduto) == 0) { 

            encontrado = 1;

            printf("Esse produto ja foi cadastrado.\n");

            return;
        }

    }
    
    
    strcpy(produto[*indiceP], nomeDoProduto);
    
    printf("Insira o valor: R$");
    if(scanf("%f", &precoUnitario) != 1){
        printf("Valores inválidos.\n");
        clearInputBuffer();
        return;
    }
    
    P[*indiceP] = precoUnitario;
    
    printf("Insira a quantidade no estoque: ");
    if(scanf("%d", &quantidade) != 1){
        printf("Quantidade inválida.\n");
        clearInputBuffer();
        return;
    }
    
    Q[*indiceP] = quantidade;

    clearInputBuffer();

    (*indiceP)++;

    printf("Produto cadastrado com sucesso.\n");
}

void venderProduto(char produto[][LENGTH], int Q[], float P[], int indiceP) {

    char nome[LENGTH];              
    int quantia, encontrado= 0;
    int i;

    printf("Nome do produto: ");
    fgets(nome, LENGTH, stdin);
    nome[strcspn(nome, "\n")] = 0;

    trim(nome);
    if(strlen(nome) == 0){
        printf("Nome invalido. Nao pode ser vazio.\n");
        return;
    }

    paraMinusculo(nome);

    printf("Quantidade desejada: ");
    if(scanf("%d", &quantia) != 1 || quantia <= 0){
        printf(" Quantidade inválida.\n");
        clearInputBuffer();
        return;
    }

    for (i = 0; i<indiceP; i++) {

        if (strcmp(produto[i], nome) == 0) { 

            encontrado = 1;

            if (Q[i] >= quantia) { // verifica se tem estoque

                float totalPagar = quantia * P[i];

                Q[i] -= quantia; // att estoque se 

                printf("Produto: %s\n", produto[i]);
                printf("Total a pagar: R$ %.2f\n", totalPagar);
                printf("Estoque restante: %d\n\n", Q[i]);

            } else {
                printf("Estoque insuficiente!\n\n");
            }
            break;
        }
    }

    if (encontrado == 0) {
        printf("Produto nao encontrado!\n");
    }
    clearInputBuffer();
}

void imprimirEstoque(char produto[][LENGTH], float P[], int Q[], int indiceP){
    if (indiceP > 0){
        for (int i = 0; i < indiceP; i++){
            printf("Produto %d:\n", i + 1);
            printf("%s\n", produto[i]);
            printf("Preco: R$%.2f\n", P[i]);
            printf("Quantidade em estoque: %d\n\n", Q[i]);
        }
    }else{
        printf("Nao ha produtos no estoque. \n");
    }
}

void pesquisarProduto(char produto[][LENGTH], float P[], int Q[], int indiceP){

    char nome[LENGTH];
    int encontrado= 0;
    int i;

    printf("Nome do produto: ");
     fgets(nome, LENGTH, stdin);
    nome[strcspn(nome, "\n")] = 0;

    trim(nome);
    if(strlen(nome) == 0){
        printf("Nome invalido. Nao pode ser vazio.\n");
        return;
    }

    paraMinusculo(nome);

    for (i = 0; i < indiceP; i++) {

        if (strcmp(produto[i], nome) == 0) { 

            encontrado = 1;

            printf("produto: %s\n", produto[i]);
            printf("Preco: R$%.2f\n", P[i]);
            printf("Quantidade: %d\n\n", Q[i]);

            break;
        }

    }
    if(encontrado == 0){
        printf("Produto não encontrado!\n\n");
    }
}

int main(){
    int indiceP = 0;
    char produto[MAX_PRODUTO][LENGTH];
    int Q[10];
    float P[10]; 
    int escolha;
    
    do{
    printf("//=====================================\\\\\n");
printf("||                                       ||\n");
printf("||           GERENCIADOR DE LOJA         ||\n");
printf("||                                       ||\n");
printf("\\\\=====================================//\n");
printf("  ||                                 ||\n");
printf("  ||   (1) ... Cadastrar produto     ||\n");
printf("  ||   (2) ... Vender                ||\n");
printf("  ||   (3) ... Pesquisar Produto     ||\n");
printf("  ||   (4) ... Imprimir estoque      ||\n");
printf("  ||   (5) ... Sair                  ||\n");
printf("  ||                                 ||\n");
printf("  ||=================================||\n");
    scanf("%d", &escolha);
    
    system("cls");
    switch (escolha){
        case 1:
        clearInputBuffer();
        cadastrarProduto(produto, P, &indiceP, Q);
        break;
    case 2:
        clearInputBuffer();
        venderProduto(produto, Q, P, indiceP);
        break;
    case 3: 
        clearInputBuffer();
        pesquisarProduto(produto, P, Q, indiceP);
        break;
    case 4: 
        clearInputBuffer();
        imprimirEstoque(produto, P, Q, indiceP);
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