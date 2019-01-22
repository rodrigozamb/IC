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

Grafo* cria_grafo2(int ver){
    if(ver<=0)return NULL;

    Grafo2 *gr = (Grafo2*)malloc(sizeof(Grafo2));
    if(gr==NULL){
        free(gr);
        return NULL;
    }

    gr->qtde_vertices = ver;
    gr->qtde_arestas = 0;

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

int insere_arestaN2(Grafo2 *G,int v1,int v2,float peso){
    No2 aux1,aux2;
    aux1.peso = peso;
    aux1.vertice = v2;

    aux2.peso = peso;
    aux2.vertice = v1;

    G->aresta[v1].push_back(aux1);
    G->aresta[v2].push_back(aux2);

    G->grau[v1]++;
    G->grau[v2]++;
    G->qtde_arestas++;

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

void ACO(Grafo *G,int v,float **m,vector<int> &caminho){

    int *visitados,pos=0;

    visitados=(int*)calloc(G->qtde_vertices,sizeof(int));

    busca_formiga(G,v,m,visitados,v,pos,caminho); // O PRBLEMA VEM DE AQUI

    caminho.push_back(v);
/*
    cout<<"caminho : \n";
    for(int i=0;i<caminho.size();i++){
        cout<<caminho[i]<<" ";
    }
    cout<<endl;
*/
}

float geraFloat(float m){

    float HI=m,LO=0.0;
    float r = (rand() / (float)RAND_MAX * HI) + LO;
    return r;
}

No* sorteio_triplo(Grafo *G,int v,float** m,int *visitados){
    int i;
    No *aux0;
    float ps[G->qtde_vertices]; // vetor das probabilidades / tamanho = nro de vertices do grafo
    float candidatos[G->qtde_vertices];

    // setando os vetores de probabilidade e de candidatos
    for(int p=0;p<G->qtde_vertices;p++){
        ps[p]=-1.0;
        candidatos[p]=-1.0;
    }

    aux0 = G->aresta[v];

    float som=0.0;
    while(aux0 != NULL){

        if(visitados[(aux0->vertice)]==0){

            ps[aux0->vertice] = CalculaProbabilidade(G,m,v,aux0->vertice);

            som+=ps[aux0->vertice];
            candidatos[aux0->vertice] = ps[aux0->vertice];


        }
        else
            ps[aux0->vertice] = 0.0;

        aux0 = aux0->prox;
    }

    sort(ps,ps+G->qtde_vertices);

    float x = geraFloat(1.0);

    int y=0;
    float escolhido=0.0;
    while(1){

        if(ps[y]!=-1.00){

            if(ps[y]>=x){
                escolhido = ps[y];

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

    int pos=0;
    for(i=0;i<G->qtde_vertices;i++)
        if(candidatos[i]==escolhido){
            pos=i;
        }

    No* aux1 = G->aresta[v];
    while(aux1->vertice != pos && aux1->prox != NULL){ // ESSE aux1->prox != NULL CONCERTOU O PROBLEMA
        aux1 = aux1->prox;
    }

    return aux1;

}

No* randomNo(Grafo* G,int v){

    int a = rand() % G->qtde_vertices;
    No* aux = G->aresta[v];
    for(int i=0;i<a;i++)aux=aux->prox;

    return aux;

}

float CalculaProbabilidade(Grafo *G,float** m,int v1,int v2){

    No *aux;
    float p=0.0,f1=0.0,f2=0.0;
    float a=floatrand(),b=floatrand();

    aux = G->aresta[v1];

    while(aux!=NULL)
    {
        if(aux->vertice == v2)
        {
            f1 = pow(m[v1][v2],a)*pow(1.0/aux->peso,b);
        }
        f2 += pow(m[v1][aux->vertice],a)*pow(1.0/aux->peso,b);
        aux = aux->prox;
    }

    if(f2 == 0.0)
        //aqui ta dando merda pq n dá pra dividir por 0, , sugestao p = 1.0
        p = 1.0;
    else
        p = f1/f2;

    return p;
}

int verificaA(int tam,int *visitados){
    for(int i=0;i<tam;i++){
        if(visitados[i]==0)return 0;
    }
    return 1;
}

void busca_formiga(Grafo *G,int v,float **m,int *visitados,int f,int pos,vector <int> &caminho){
     // 'v'-> vertice inicial   'F'-> vertice final
    visitados[v] = 1;

    caminho.push_back(v);

    No *aux;
    aux=G->aresta[v];

    while(verificaA(G->qtde_vertices,visitados)==0)
    {
        No* aux2;

        do{
            aux2 = sorteio_triplo(G,v,m,visitados);


        }while(visitados[aux2->vertice]==1);

        busca_formiga(G,aux2->vertice,m,visitados,f,pos+1,caminho);
    }
}

void buscaProfundidade(Grafo *G, int ini, int *visitado, int cont){

    visitado[ini] = cont;
    No *aux = G->aresta[ini];

    while(aux != NULL){
        if(visitado[aux->vertice] == -1)
             buscaProfundidade(G,aux->vertice,visitado,cont+1);

        aux = aux->prox;
    }
}

void DPS(Grafo *gr,int v){

    int *visitados = (int*)calloc(gr->qtde_vertices,sizeof(int));

    for(int i=0;i<gr->qtde_vertices;i++)visitados[i]=-1;

    buscaProfundidade(gr,v,visitados,0);
    cout<<endl;

    for(int i=0;i<gr->qtde_vertices;i++){
        cout<<visitados[i]<<" ";
    }
    cout<<endl;

}

float floatrand(){
    double HI=1.0,LO=0.0;
    double r = (rand() / (double)RAND_MAX * HI) + LO;
    return r;
}

void mostra_matriz(float **m,int n){

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //cout<<m[i][j]<<" ";
            printf("%.3f ",m[i][j]);
        }
        cout<<endl;
    }

}

float valorCaminho(Grafo* G,vector<int>caminho){
    float total=0.0;

    for(int i=0;i<caminho.size()-1;i++){

        No* aux = G->aresta[caminho[i]];
        while(aux->vertice != caminho[i+1])aux = aux->prox;
        total += aux->peso;
    }
    return total;
}

bool ehCaminho(vector<int> caminho,int x,int y){
    for(int i=0;i<caminho.size()-1;i++){
        if(caminho[i]==x && caminho[i+1]==y)return true;
        if(caminho[i]==y && caminho[i+1]==x)return true;
    }

    return false;
}

void atualizaMatriz(vector< vector<int> > formigas, vector<float>valor_caminhos,float** matriz,int nro_vertices){
    float q=1.0;//FORÇA DO FEROMÕNIO
    float fi = 0.5; //FORÇA DA EVAPORAÇÃO

    for(int i=0;i<nro_vertices;i++){
        for(int j=0;j<nro_vertices;j++){

            float soma=0.0;

            for(int k=0;k<formigas.size();k++){
                if(ehCaminho(formigas[k],i,j)==true){
                    soma+=(q/valor_caminhos[k]);
                }
            }

            if(i!=j)matriz[i][j] = ( (1.0 - fi) * matriz[i][j] ) + soma;

        }
    }
}

void ACO_Geral(Grafo* G, float** mat){

    vector< vector<int> > formigas;
    vector<float> valor_caminhos;

    for(int i=0;i<G->qtde_vertices;i++){
        vector<int> caminho;

        ACO(G,i,mat,caminho); //O PROBLEMA ACONTECE AQUI

        formigas.push_back(caminho);
        valor_caminhos.push_back(valorCaminho(G,caminho));
    }

    atualizaMatriz(formigas,valor_caminhos,mat,G->qtde_vertices);

}
