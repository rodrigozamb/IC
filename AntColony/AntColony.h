#ifndef ANTCOLONY_H_INCLUDED
#define ANTCOLONY_H_INCLUDED
#include<bits/stdc++.h>
using namespace std;
struct no
{
    int vertice;
    float peso;
    struct no *prox;
};
typedef struct no No;

struct grafo
{
    int qtde_vertices, qtde_arestas;
    int *grau;
    No**aresta;
};

typedef struct grafo Grafo;


Grafo* cria_grafo(int ver);
float** cria_matriz(int L,int C);
void libera_grafo(Grafo **G);
void mostra_grafo(Grafo *G);
int insere_arestaN(Grafo *G,int v1,int v2,float peso);
int verifica_aresta(Grafo *G,int v1,int v2);
void busca_profundidade(Grafo *G,int v,int *visitados,vector<int> &caminho,int pos);
void DPS(Grafo *gr,int v);
void ACO(Grafo *G,int v,float **m,vector<int> &caminho);
No* sorteio_triplo(Grafo *G,int v,float** m,int *visitados);
float floatrand();
float geraFloat(float m);
void busca_formiga(Grafo *G,int v,float **m,int *visitados,int f,int pos,vector <int> &caminho);
float CalculaProbabilidade(Grafo *G,float** m,int v1,int v2);





#endif // ANTCOLONY_H_INCLUDED
