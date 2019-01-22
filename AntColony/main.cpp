#include<bits/stdc++.h>
#include"AntColony.h"
#define linhas 3
#define colunas 3
using namespace std;


int main(){
    cout<<"amigos para sempre"<<endl<<endl;

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



    int g=9000;
    while(g--){
        //mostra_matriz(matriz,G->qtde_vertices);
        ACO_Geral(G,matriz);
        //cout<<endl;
    }
    mostra_matriz(matriz,G->qtde_vertices);




return 0;
}
