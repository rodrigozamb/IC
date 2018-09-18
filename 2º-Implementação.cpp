#include<bits/stdc++.h>
#include<math.h>
using namespace std;

#define nmrsEmX 5
long double a,b;





typedef struct individuo{
    float cadeia[nmrsEmX];
}Individuo;

vector<Individuo> colonia;

Individuo geraX(){
    float HI=b,LO=a;
    Individuo ser;
    for(int i=0;i<nmrsEmX;i++){
        float r = (rand() / (float)RAND_MAX * HI) + LO;
        ser.cadeia[i]=r;
    }
    return ser;
}


float funcaoY(Individuo ser){
    float sum=0;
    for(int i=0;i<nmrsEmX;++i){
        sum+=(ser.cadeia[i]*ser.cadeia[i]);
    }
    float x=0,y;
    for(int i=0;i<nmrsEmX;++i){
        x+=(ser.cadeia[i]*(i+1));
    }
    x=x/2.00;
    y=x*x*x*x;
    x=x*x;
    sum+=(y+x);

    return sum;
}


void mostraPopulacao(vector<Individuo>colonia){
    for(int i=0;i<colonia.size();i++){
            cout<<"Individuo["<<i<<"] = [";
            for(int j=0;j<nmrsEmX;j++){
                cout<<colonia[i].cadeia[j];
                if(j<nmrsEmX-1)cout<<" , ";
            }
            cout<<"] - Y = "<<funcaoY(colonia[i])<<endl;
        }

}

/*
int CrossBlend(int P1,int P2){

    Individuo f1;
    Individuo f2;
    float gama = 0.1;
    float LO = -gama;
    float HI=gama+1;
    float B = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    cout<<gama <<" "<<LO <<" "<<HI <<" "<<B<<" "<<endl;
    for(int i=0;i<nmrsEmX;++i){


        f1.cadeia[i]=colonia[P1].cadeia[i] + B*(colonia[P2].cadeia[i]-colonia[P1].cadeia[i]);
        f2.cadeia[i]=colonia[P2].cadeia[i] + B*(colonia[P1].cadeia[i]-colonia[P2].cadeia[i]);
    }

    colonia.push_back(f1);
    colonia.push_back(f2);

}

*/

void selecao(vector<Individuo> colonia,int tam,Individuo *a,Individuo *b){

    vector<Individuo> filhos;
    Individuo f1,f2;
    int p2,p1;
    while(p1==p2){
        p1=(rand()%tam);
        p2=(rand()%tam);
    }
    float gama = 0.1;
    float LO = -gama;
    float HI=gama+1;
    float B = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    cout<<"asdas"<<endl;

    for(int i=0;i<nmrsEmX;++i){
        f1.cadeia[i]= colonia[p1].cadeia[i] + B*(colonia[p2].cadeia[i]-colonia[p1].cadeia[i]);
        f2.cadeia[i]= colonia[p2].cadeia[i] + B*(colonia[p1].cadeia[i]-colonia[p2].cadeia[i]);
    }
    mostraPopulacao(filhos);

}



int main(){
    a=-5.00;
    b=10.00;
    int nmr;
    cout<<"Digite a qnt de indivíduos da colonia"<<endl;
    cin>>nmr;


    srand (time(NULL));


    Individuo p;
    srand (time(NULL));


    for(int i=0;i<nmr;i++){
        p=geraX();
        colonia.push_back(p);
    }
    mostraPopulacao(colonia);


    int g=10;
    while(g--){
        Individuo i1,i2;
        selecao(colonia,colonia.size(),&i1,&i2);


    }








return 0;
}

