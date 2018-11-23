#include "AntColony.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <math.h>
#include <bits/stdc++.h>


using namespace std;

float** cria_matriz(int L,int C){

    float **M = (float**)malloc(L*sizeof(float*));

    for(int i=0;i<L;i++){
        M[i] = (float*)calloc(C,sizeof(float));
        for(int j=0;j<C;j++)M[i][j]=0.0;
    }
    return M;
}

Grafo* cria_grafo(int ver){

    if(ver<=0)return NULL;

    Grafo *gr = (Grafo*)malloc(sizeof(Grafo));
    if(gr==NULL){
        free(gr);
        return NULL;
    }

    gr->qtde_vertices = ver;
    gr->qtde_arestas = 0;

    gr->grau = (int*)calloc(ver,sizeof(int));
    if(gr->grau==NULL){
        free(gr->grau);
        free(gr);
        return NULL;
    }

    gr->aresta = (No**)calloc(ver,sizeof(No));
    for(int i=0;i<ver;i++){
        gr->aresta[i]=NULL;
    }

    if(gr->aresta == NULL){
        free(gr->aresta);
        free(gr->grau);
        free(gr);
        return NULL;
    }
    return gr;

}

void libera_grafo(Grafo **G){
    if((*G)!=NULL)
    {
        int i;
        No *aux,*ant;
        for(i=0; i<(*G)->qtde_vertices; i++)
        {
            aux=(*G)->aresta[i];
            ant=NULL;
            while(aux!=NULL)
            {
                ant=aux;
                aux=aux->prox;
                free(ant);
            }
        }

        free((*G)->grau);
        free(*G);
        *G=NULL;
    }


}

int insere_arestaN(Grafo *G,int v1,int v2,float peso){
    if(G==NULL || (v1<0 || v2<0)){
        return -1;
    }

    No *aux;

    aux=G->aresta[v1];
    while(aux!=NULL && aux->vertice!=v2)
    {
        aux=aux->prox;
    }
    if(aux!=NULL)
    {
        return 0;
    }

    No* novo = (No*)malloc(sizeof(No));
    if(novo!=NULL)
    {
        novo->vertice=v2;
        novo->peso=peso;
        novo->prox=G->aresta[v1];
        G->aresta[v1]=novo;
    }

    G->qtde_arestas++;
    G->grau[v1]++;

    No *aux2;

    aux2=G->aresta[v2];
    while(aux2!=NULL && aux2->vertice!=v1)
    {
        aux2=aux2->prox;
    }
    if(aux2!=NULL)
    {
        return 0;
    }

    No *novo2=(No*)malloc(sizeof(No));
    if(novo2!=NULL)
    {
        novo2->vertice=v1;
        novo2->peso=peso;
        novo2->prox=G->aresta[v2];
        G->aresta[v2]=novo2;
    }
    G->grau[v2]++;

    return 1;
}

void mostra_grafo(Grafo *G){
    if(G==NULL)
    {
        printf("Grafo não existe");
    }
    else if(G->qtde_arestas==0)
    {
        printf("Grafo Vazio");
    }
    No *aux;
    int i;
    for(i=0; i< G->qtde_vertices; i++)
    {
        aux=G->aresta[i];
        printf("Vertice[%d]:\n",i);
        while(aux!=NULL)
        {
            printf(" %d - Peso: %f\n",aux->vertice,aux->peso);
            aux=aux->prox;
        }
        printf("\n\n");
    }

}

int verifica_aresta(Grafo *G,int v1,int v2){
    if(G==NULL || (v1<0 || v2<0))
    {
        return -1;
    }
    No *aux;
    aux=G->aresta[v1];
    while(aux!=NULL && aux->vertice!=v2)
    {
        aux=aux->prox;
    }
    if(aux==NULL)
    {
        return 0;
    }
    return 1;
}

void busca_profundidade(Grafo *G,int v,int *visitados,vector<int> &caminho){


    visitados[v]=1;

    caminho.push_back(v);
    //printf("  %d  ",v);

    No *aux;
    aux=G->aresta[v];


    while(aux!=NULL)
    {
        if(visitados[aux->vertice]==0)
        {
            busca_profundidade(G,aux->vertice,visitados,caminho);
        }

        aux=aux->prox;
    }

}

void DPS(Grafo *gr,int v){

    int *visitados = (int*)calloc(gr->qtde_vertices,sizeof(int));
    vector<int> caminho;

    busca_profundidade(gr,v,visitados,caminho);

    for(int i=0;i<gr->qtde_vertices;i++){
        cout<<caminho[i]<<" ";
    }
    cout<<endl;

}

void ACO(Grafo *G,int v,float **m,vector<int> &caminho){

    int *visitados,pos=0;

    visitados=(int*)calloc(G->qtde_vertices,sizeof(int));

    busca_formiga(G,v,m,visitados,v,pos,caminho);
    caminho.push_back(v);

    cout<<"caminho : \n";
    for(int i=0;i<caminho.size();i++){
        cout<<caminho[i]<<" ";
    }
    cout<<endl;


}

float geraFloat(float m){

    float HI=m,LO=0.0;
    float r = (rand() / (float)RAND_MAX * HI) + LO;
    return r;
}

No* sorteio_triplo(Grafo *G,int v,float** m,int *visitados){
    No *aux0;
    float ps[G->qtde_vertices];
    int candidatos[G->qtde_vertices];
    for(int p=0;p<G->qtde_vertices;p++){
        ps[p]=-1.0;
        candidatos[p]=-1;
    }

    aux0 = G->aresta[v];

    float t=1.0,tt=1.0;
    while(aux0->prox!=NULL){

        if(visitados[(aux0->vertice)]==0){

            ps[aux0->vertice] = geraFloat(tt);
            t=ps[aux0->vertice];

            tt-=t;
            candidatos[aux0->vertice]= aux0->vertice;


            if(aux0->prox->prox==NULL){
                ps[aux0->prox->vertice]=tt;
                candidatos[aux0->prox->vertice] = aux0->prox->vertice;
                break;
            }
        }
        aux0= aux0->prox;
    }

    float x = geraFloat(1.0);
    int y=0;
    int escolhido=0;
    while(1){
        if(ps[y]!=-1.00){
            if(x<=ps[y]){
                escolhido=candidatos[y];
                break;
            }
            else{
                x-=ps[y];
                y++;
            }
        }
        else
            y++;
    }


    No* aux1 = G->aresta[v];
    while(aux1->vertice!=escolhido)aux1= aux1->prox;
    return aux1;
}

float CalculaProbabilidade(Grafo *G,float** m,int v1,int v2){

    No *aux;
    float p=0,f1=0,f2=0;
    float a=floatrand(),b=floatrand();

    aux = G->aresta[v1];

    while(aux!=NULL)
    {
        if(aux->vertice == v2)
        {
            f1 = pow(m[v1][v2],a)*pow(aux->peso,b);
        }
        f2 += pow(m[v1][aux->vertice],a)*pow(aux->peso,b);
        aux = aux->prox;
    }

    if(f2 == 0){
        p = 0;
    }else{

    p = f1/f2;

    }


    return p;

}

float floatrand(){

    float HI=1.0,LO=0.0;
    float r = (rand() / (float)RAND_MAX * HI) + LO;
    return r;
}

void busca_formiga(Grafo *G,int v,float **m,int *visitados,int f,int pos,vector <int> &caminho){
     // 'v'-> vertice inicial   'F'-> vertice final
  /*
    if(pos==G->qtde_vertices-1){

        //tenho que pegar o primeiro do vector
        vector<int>::iterator it = caminho.begin();
        cout<<*it<<endl;
        visitados[*it]=0;
        visitados[v]=1;
    }
    else{
        visitados[v] = 1;
    }

*/
    visitados[v] = 1;

    caminho.push_back(v);
    //printf("  %d  ",v);

    No *aux;
    aux=G->aresta[v];

    while(aux!=NULL && visitados[aux->vertice]!=1)
    {
        No* aux2 = sorteio_triplo(G,v,m,visitados);
        if(visitados[aux2->vertice]==0)busca_formiga(G,aux2->vertice,m,visitados,f,pos+1,caminho);

        aux=aux->prox;
    }

}

float valorCaminho(Grafo *G,vector<int>caminho){
    float dist=0.0;
    for(int i=0;i<caminho.size()-1;i++){
        dist+=achaDist(G,caminho[i],caminho[i+1]);
    }
    return dist;
}

float achaDist(Grafo *G,int v1,int v2){

        No* aux = G->aresta[v1];
        while(aux->vertice!=v2 && aux!=NULL)aux = aux->prox;
        return aux->peso;
}












