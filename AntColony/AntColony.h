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



struct no2
{
    int vertice;
    float peso;
};
typedef struct no2 No2;

struct grafo2
{
    int qtde_vertices, qtde_arestas;
    vector<int>grau;
    vector< vector<No2> >aresta;
};
typedef struct grafo2 Grafo2;


Grafo* cria_grafo(int ver);
Grafo* cria_grafo2(int ver);
float** cria_matriz(int L,int C);
void libera_grafo(Grafo **G);
void mostra_grafo(Grafo *G);
int insere_arestaN(Grafo *G,int v1,int v2,float peso);
int insere_arestaN2(Grafo *G,int v1,int v2,float peso);
int verifica_aresta(Grafo *G,int v1,int v2);
void busca_profundidade(Grafo *G,int v,int *visitados,vector<int> &caminho,int pos);
void DPS(Grafo *gr,int v);
void ACO(Grafo *G,int v,float **m,vector<int> &caminho);
No* sorteio_triplo(Grafo *G,int v,float** m,int *visitados);
float floatrand();
float geraFloat(float m);
void busca_formiga(Grafo *G,int v,float **m,int *visitados,int f,int pos,vector <int> &caminho);
float CalculaProbabilidade(Grafo *G,float** m,int v1,int v2);
void mostra_matriz(float **m,int n);
bool ehCaminho(vector<int> caminho,int x,int y);
void atualizaMatriz(vector< vector<int> > formigas, vector<float>valor_caminhos,float** matriz,int nro_vertices);
void ACO_Geral(Grafo* G, float** mat);
No* randomNo(Grafo* G,int v);
//----------------------------------------------------

void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont);

float valorCaminho(Grafo *G,vector<int>caminho);
float achaDist(Grafo *G,int v1,int v2);



#endif // ANTCOLONY_H_INCLUDED
