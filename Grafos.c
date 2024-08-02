#include <stdlib.h>
#include <stdio.h>
#define TAM 5

typedef struct lista
{
    int destino;
    int custo;
    struct lista *prox;
} lista;

void inicializar(lista** g, int x)
{
    for (int i = 0; i <= x; i++)
    {
        g[i] = NULL;
    }
}

lista *inserirNalista(lista* l, int destino, int custo)
{
    lista *no = (lista *)malloc(sizeof(lista));

    no->destino = destino;
    no->custo = custo;
    no->prox = l;

    return no;
}

void inserirAresta(lista** g, int tam)
{
    int origem, destino, custo;
    printf("Origem: ");
    scanf("%d", &origem);
    if (origem < 1 || origem > tam)
    {
        printf("\nOrigem invalida\n");
        return;
    }
    printf("Destino: ");
    scanf("%d", &destino);
    printf("Custo: ");
    scanf("%d", &custo);

    g[origem] = inserirNalista(g[origem], destino, custo);
}

void imprimirLista(lista* l, int i){
    if(l == NULL){
        return;
    }
    else{
        printf("\nOrigem: %d Destino: %d Custo: %d", i, l->destino, l->custo);
        imprimirLista(l->prox, i);
    }
}

void imprimirGrafo(lista** g, int tam){
    for(int i = 1; i <= tam; i++){
        imprimirLista(g[i], i);
        //printf("\n");
    }
    printf("\n");
}

lista* removerNalista(lista* l, int destino, int custo)
{

    if (l == NULL){
        printf("\nNao existe\n");
        return l;
    }
    else if(l->custo == custo && l->destino == destino){
        lista* aux = l;
        l = l->prox;
        free(aux);
        printf("\nRemovido\n");
        return l;
    }
    else{
        l->prox = removerNalista(l->prox, destino, custo);
        return l;
    }

}

void removerAresta(lista** g, int tam)
{
    int origem, destino, custo;
    printf("Origem: ");
    scanf("%d", &origem);
    if (origem < 1 || origem > tam)
    {
        printf("\nOrigem invalida\n");
        return;
    }
    printf("Destino: ");
    scanf("%d", &destino);
    printf("Custo: ");
    scanf("%d", &custo);

    g[origem] = removerNalista(g[origem], destino, custo);
}

int contarGrauE(lista* l, int vertice){
    if(l == NULL){
        return 0;
    }
    else if(l->destino == vertice){
        return 1 + contarGrauE(l->prox, vertice);
    }
    
    return contarGrauE(l->prox, vertice);
    
}

int contarGrauS(lista* l){
    if(l == NULL){
        return 0;
    }
    else{
        return 1 + contarGrauS(l->prox);
    }
}

void imprimirGraus(lista** g, int tam){
    int grauS = 0;
    int grauE = 0;
    int vertice;
    printf("Vertice: ");
    scanf("%d", &vertice);
    if (vertice < 1 || vertice > tam)
    {
        printf("\nvertice invalida\n");
        return;
    }

    for(int i = 1; i<=tam; i++){
        grauE += contarGrauE(g[i], vertice);
    }
    grauS = contarGrauS(g[vertice]);

    printf("Grau de Saida = %d \tGrau de Entrada = %d\n", grauS, grauE);
}

void verificaGrafoCompleto(lista **g, int tam){
    int aux =0;
    for (int i = 1; i <=tam; i++)
    {
        aux += contarGrauS(g[i]);
    }
    printf("\n%d\n", aux);
    if(aux == tam*(tam-1)){
        printf("Eh completo!");
    }
    else{
        printf("Nao eh completo!");
    }
    
}

int main()
{
    int opc = 0;
    lista *g[TAM];

    inicializar(g, TAM);

    while (opc != 9)
    {
        printf("\n1-Inserir aresta no grafo\n2-Remover aresta no grafo\n3-Imprime o grafo\n4-Imprime os graus de entrada e de saida de um vertice\n5-Verificar se um grafo e completo\n9-Sair\n:");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            inserirAresta(g, TAM-1);
            break;
        case 2:
            removerAresta(g, TAM-1);
            break;
        case 3:
            imprimirGrafo(g, TAM-1);
            break;
        case 4:
            imprimirGraus(g, TAM-1);
            break;
        case 5:
            verificaGrafoCompleto(g, TAM-1);
        default:
            break;
        }
    }
}