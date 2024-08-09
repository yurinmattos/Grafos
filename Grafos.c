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

int existe(int* vet, int valor, int pos){
    int i;
    for (i = 0; i < pos; i++)
    {
        if(vet[i] == valor){
            return 1;
        }
    }
    return 0;
}

void imprimirCaminhos(lista** g, int destino, int* vet, int pos){
    if (vet[pos-1] == destino)
    {
        int i;
        printf("\n");
        for (i = 0; i < pos; i++)
        {
            printf("%d-", vet[i]);
        }
    }
    else{
        lista *p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                imprimirCaminhos(g, destino, vet, pos+1);
            }
            p = p->prox;
        }        
    }   
}

void imprimirMenorCaminho(lista** g, int destino, int* vet, int* vetAux, int pos, int* tamMax){
    if (vet[pos-1] == destino)
    {
        int cont = pos;
        if(cont < *tamMax){
            *tamMax = cont;
            for (int i = 0; i < cont; i++)
            {
                vetAux[i] = vet[i];
            }
        }
    }
    else{
        lista *p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                imprimirMenorCaminho(g, destino, vet, vetAux, pos+1, tamMax);
            }
            p = p->prox;
        }        
    }    
}

void imprimirMenorCusto(lista** g, int destino, int* vet, int* vetAux, int pos, int* custo, int custoAtual){
    if (vet[pos-1] == destino)
    {
        if(custoAtual < *custo){
            *custo = custoAtual;
            for (int i = 0; i < pos; i++)
            {
                vetAux[i] = vet[i];
            }
            //custoAtual = 0;
        }
    }
    else{
        lista *p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                imprimirMenorCusto(g, destino, vet, vetAux, pos + 1, custo, custoAtual + p->custo);
            }
            p = p->prox;
        }        
    }    
}



int main()
{
    int opc = 0;
    int origem, destino;
    lista *g[TAM];

    inicializar(g, TAM);

    while (opc != 9)
    {
        printf("\n1-Inserir aresta no grafo\n2-Remover aresta no grafo\n3-Imprime o grafo\n4-Imprime os graus de entrada e de saida de um vertice\n5-Verificar se um grafo e completo\n6-Imprimir caminhos de origem ao destino\n7-Menor caminho:\n9-Sair\n:");
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
            break;
        case 6:
            printf("Insira a origem e o destino:\n");
            scanf("%d\n%d", &origem, &destino);
            int* vet = (int*) malloc(TAM * sizeof(int));
            vet[0] = origem;
            imprimirCaminhos(g, destino, vet, 1);
            free(vet);
            break;
        case 7:
            printf("Insira a origem e o destino:\n");
            scanf("%d\n%d", &origem, &destino);
            int custo = TAM;
            int* vetAux = (int*) malloc(TAM * sizeof(int));
            int* vet1 = (int*) malloc(TAM * sizeof(int));
            for (int i = 0; i < TAM; i++) {
                vet1[i] = -1;
            }
            vet1[0] = origem;
            imprimirMenorCaminho(g, destino, vet1, vetAux, 1, &custo);

            for(int i = 0; i < custo; i++){
                if (vetAux[i] != -1) {
                    printf("%d-", vetAux[i]);
                }
            }
            free(vet1);
            free(vetAux);
            break;
        case 8:
            printf("Insira a origem e o destino:\n");
            scanf("%d\n%d", &origem, &destino);
            int custo2 = 100000;
            int* vetAux2 = (int*) malloc(TAM * sizeof(int));
            int* vet2 = (int*) malloc(TAM * sizeof(int));
            for (int i = 0; i < TAM; i++) {
                vetAux2[i] = -1;
            }
            vet2[0] = origem;
            imprimirMenorCusto(g, destino, vet2, vetAux2, 1, &custo2, 0);

            for(int i = 0; i < TAM; i++){
                if (vetAux2[i] != -1) {
                    printf("%d-", vetAux2[i]);
                }
                printf("\nCusto: %d\n\n", custo2);
            }
            free(vet2);
            free(vetAux2);
            break;

        default:
            break;
        }
    }
}