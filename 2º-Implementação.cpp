#include<bits/stdc++.h>
#include<math.h>
using namespace std;
#define Ngama 0.01
#define nmrsEmX 5
long double a,b;

typedef struct individuo{
    float cadeia[nmrsEmX];
}Individuo;


Individuo geraX(){
    float HI=b,LO=a;
    Individuo ser;
    for(int i=0;i<nmrsEmX;i++){
        float r = (rand() / (float)RAND_MAX * HI) + LO;
        char n[20];
        sprintf(n, "%.3f", r);
        r = atof(n);
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


void mutar(Individuo *a){
    float LO = -Ngama;
    float HI = Ngama;
    float B = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));

    for(int i=0;i<nmrsEmX;i++){
        float resp1 = a->cadeia[i]*(1+B);

        char n[20];
        sprintf(n, "%.3f", resp1);
        resp1 = atof(n);
        a->cadeia[i]=resp1;


    }

}

void selecao(vector<Individuo> &colonia,Individuo *a,Individuo *b){

    vector<Individuo> filhos;
    Individuo f1,f2;
    int p2=0,p1=0;

    while(p1==p2){
        p1=(rand()%colonia.size());
        p2=(rand()%colonia.size());
    }
    float gama = Ngama;
    float LO = -gama;
    float HI=gama+1;
    float B = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));

    for(int i=0;i<nmrsEmX;i++){
        float resp1,resp2;

        resp1 = colonia[p1].cadeia[i] + B*(colonia[p2].cadeia[i] - colonia[p1].cadeia[i]);
        char n[20];
        sprintf(n, "%.3f", resp1);
        resp1 = atof(n);
        f1.cadeia[i]=resp1;

        resp2 = colonia[p2].cadeia[i] + B*(colonia[p1].cadeia[i] - colonia[p2].cadeia[i]);
        char m[20];
        sprintf(m, "%.3f", resp2);
        resp2 = atof(m);
        f2.cadeia[i]=resp2;

    }
    mutar(&f1);
    mutar(&f2);
    colonia.push_back(f1);
    colonia.push_back(f2);
}


bool meuSort(Individuo a,Individuo b){

    return funcaoY(a)>funcaoY(b);
}

int main(){
    a=-5.00;
    b=10.00;
    int nmr;
    cout<<"Digite a qnt de indivíduos da colonia"<<endl;
    cin>>nmr;
    vector<Individuo> colonia;

    srand (time(NULL));

    Individuo p;
    srand (time(NULL));


    for(int i=0;i<nmr;i++){
        p=geraX();
        colonia.push_back(p);
    }
    mostraPopulacao(colonia);
    cout<<"Tamanho da colonia Inicial = "<<colonia.size()<<endl;



    int g=3000;
    while(g--){
        Individuo i1,i2;
        selecao(colonia,&i1,&i2);
        sort(colonia.begin(),colonia.end(),meuSort);
        colonia.erase(colonia.begin(),colonia.begin()+2);
    }
    mostraPopulacao(colonia);






return 0;
}

