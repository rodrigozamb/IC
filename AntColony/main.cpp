#include<bits/stdc++.h>
#include"AntColony.h"
#define linhas 3
#define colunas 3
using namespace std;


int main(){

    srand(time(NULL));



    Grafo *G = cria_grafo(6);
    insere_arestaN(G,0,1,0.1);
    insere_arestaN(G,0,2,0.2);
    insere_arestaN(G,0,3,0.3);
    insere_arestaN(G,0,4,0.4);
    insere_arestaN(G,0,5,0.5);
    insere_arestaN(G,1,2,1.2);
    insere_arestaN(G,1,3,1.3);
    insere_arestaN(G,1,4,1.4);
    insere_arestaN(G,1,5,1.5);
    insere_arestaN(G,2,3,2.3);
    insere_arestaN(G,2,4,2.4);
    insere_arestaN(G,2,5,2.5);
    insere_arestaN(G,3,4,3.4);
    insere_arestaN(G,3,5,3.5);
    insere_arestaN(G,4,5,4.5);


    float **matriz;
    matriz = cria_matriz(G->qtde_vertices,G->qtde_vertices);
    //for(int i=0;i<G->qtde_vertices;i++)cout<<CalculaProbabilidade(G,matriz,1,i)<<endl;

    int *visitados;
    No* resp;
    visitados =(int*)calloc(G->qtde_vertices,sizeof(int));
    resp = sorteio_triplo(G,0,matriz,visitados);

    cout<<"resp na main -- vert ganhador = "<<resp->vertice<<endl;

    //DPS(G,0);
/*
  vector<int> caminho;
    printf("##### 0 #####\n");
    printf("Caminho Profundidade Comecando em 0: \n");
    ACO(G,4,matriz,caminho);
*/


/*

    int *visitados,pos=0;
         visitados=(int*)calloc(G->qtde_vertices,sizeof(int));

    int g=20;
    while(g--){
            No * aux2= sorteio_triplo(G,0,matriz,visitados);
            cout<<aux2->vertice<<endl;

    }
*/
return 0;
}
