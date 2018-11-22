#include<bits/stdc++.h>
#include"AntColony.h"
#define linhas 3
#define colunas 3
using namespace std;


int main(){

    Grafo *G = cria_grafo(5);
    insere_arestaN(G,0,1,0.1);
    insere_arestaN(G,0,2,0.2);
    insere_arestaN(G,0,3,0.3);
    insere_arestaN(G,0,4,0.4);
    insere_arestaN(G,1,2,1.2);
    insere_arestaN(G,1,3,1.3);
    insere_arestaN(G,1,4,1.4);
    insere_arestaN(G,2,3,2.3);
    insere_arestaN(G,2,4,2.4);
    insere_arestaN(G,3,4,3.4);

    //mostra_grafo(G);
    //DPS(G,1);
    float **matriz;
    matriz = cria_matriz(5,5);
/*
    vector<int> fila1;
    printf("##### 0 #####\n");
    printf("Caminho Profundidade Comecando em 0: \n");
    ACO(G,0,matriz,fila1);
    printf("\n");
*/


    int *visitados;
    visitados=(int*)calloc(G->qtde_vertices,sizeof(int));


    srand (time(NULL));
    int r=20;
    while(r--){
        No* queijo = sorteio_triplo(G,0,matriz,visitados);
        cout<<queijo->vertice<<endl;
    }


return 0;
}
