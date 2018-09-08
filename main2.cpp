#include<bits/stdc++.h>
using namespace std;


typedef struct bit{
    int cadeia[4];
}Bit;


int binTOdec(Bit a){
    int sum=0;
    if(a.cadeia[0]==1)sum+=pow(2,3);
    if(a.cadeia[1]==1)sum+=pow(2,2);
    if(a.cadeia[2]==1)sum+=pow(2,1);
    if(a.cadeia[3]==1)sum+=1;
    return sum;
}

int avalia(int x){
    return x*x;
}

int torneio(vector<Bit> colonia,set<int> filhos){
    set<int>::iterator it;
    it=filhos.begin();
    int winner=*it;

    while(!filhos.empty()){
        it=filhos.begin();


        cout<<"Ind - ["<<*it<<"] = [";
        for(int j=0;j<4;j++){
            cout<<colonia[*it].cadeia[j];
            if(j<3)cout<<",";
        }
        cout<<"]"<<endl;
        if(avalia(binTOdec(colonia[*it])) < avalia(binTOdec(colonia[winner])))winner=*it;
        filhos.erase(it);
    }
    cout<<"Vencedor - ["<<winner<<"] = [";
    for(int j=0;j<4;j++){
            cout<<colonia[winner].cadeia[j];
            if(j<3)cout<<",";
        }

    cout<<"]"<<endl;
    return winner;
}

Bit selecao(vector<Bit> colonia,int tam){
    set<int>filhos;

    while(filhos.size()!=3){

        filhos.insert(rand()%tam);
    }

    int x = torneio(colonia,filhos);
    cout<<"vencedor do trio = "<<x<<endl;

    return colonia[x];

}



int main(){
    int nmr;
    cout<<"Digite a qnt de indivíduos da colonia"<<endl;
    cin>>nmr;

    srand (time(NULL));

    vector<Bit> colonia;
    Bit a;
    srand (time(NULL));
    for(int i=0;i<nmr;i++){
        for(int j=0;j<4;j++){
            a.cadeia[j]=rand()%2;
        }
        colonia.push_back(a);
    }

    for(int i=0;i<nmr;i++){
        cout<<"Individuo["<<i<<"] = [";
        for(int j=0;j<4;j++){
            cout<<colonia[i].cadeia[j];
            if(j<3)cout<<",";
        }
        cout<<"] - dec = "<<binTOdec(colonia[i])<<" - nota :"<<100 - avalia(binTOdec(colonia[i]))<<endl;
    }


    vector<Bit>filho;
    for(int i=0;i<(int)(nmr/4);i++){   //SELECIONANDO OS PAIS PARA REPRODUÇÃO
        filho.push_back(selecao(colonia,nmr));

    }

    for(int i=0;i<(int)(nmr/4);i++){
        cout<<"Filho["<<i<<"] = [";
        for(int j=0;j<4;j++){
            cout<<filho[i].cadeia[j];
            if(j<3)cout<<",";
        }
        cout<<"] - dec = "<<binTOdec(filho[i])<<" - nota :"<<100 - avalia(binTOdec(filho[i]))<<endl;
    }






return 0;
}
