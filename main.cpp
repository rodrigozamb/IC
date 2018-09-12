#include<bits/stdc++.h>
#include<math.h>
using namespace std;

long double a,b;

typedef struct bit{
    int cadeia[4];
}Bit;

long double binTOdec(Bit aa){
    double sum=0;
    if(aa.cadeia[0]==1)sum+=pow(2,3);
    if(aa.cadeia[1]==1)sum+=pow(2,2);
    if(aa.cadeia[2]==1)sum+=pow(2,1);
    if(aa.cadeia[3]==1)sum+=1;

    return ((b - a) * sum) /  (pow(2,4)- 1) + a;
}

long double avalia(long double x){
    return x*x;
}

int torneio(vector<Bit> colonia,set<int> filhos){
    set<int>::iterator it;
    it=filhos.begin();
    int winner=*it;

    while(!filhos.empty()){
        it=filhos.begin();

        /*
        cout<<"Ind - ["<<*it<<"] = [";
        for(int j=0;j<4;j++){
            cout<<colonia[*it].cadeia[j];
            if(j<3)cout<<",";
        }
        cout<<"]"<<endl;
        */
        if(avalia(binTOdec(colonia[*it])) < avalia(binTOdec(colonia[winner])))winner=*it;
        filhos.erase(it);
    }
    /*
    cout<<"Vencedor - ["<<winner<<"] = [";
    for(int j=0;j<4;j++){
            cout<<colonia[winner].cadeia[j];
            if(j<3)cout<<",";
        }

    cout<<"]"<<endl;
    */
    return winner;
}

Bit selecao(vector<Bit> colonia,int tam){
    set<int>filhos;

    while(filhos.size()!=3){

        filhos.insert(rand()%tam);
    }

    int x = torneio(colonia,filhos);
    //cout<<"vencedor do trio = "<<x<<endl;

    return colonia[x];

}

void mutacao(vector<Bit> &filho){

    for(int i=0;i<filho.size();i++){
        int x = rand()%4;
        //cout<<x<<endl;
        if(filho[i].cadeia[x]==1)filho[i].cadeia[x]=0;
        else filho[i].cadeia[x]=1;
    }

}

bool meuSort(Bit aaa,Bit bbb){
    return avalia( binTOdec(aaa)) > avalia(binTOdec(bbb));
}

void mostraPopulacao(vector<Bit>colonia){
    for(int i=0;i<colonia.size();i++){
            cout<<"Individuo["<<i<<"] = [";
            for(int j=0;j<4;j++){
                cout<<colonia[i].cadeia[j];
                if(j<3)cout<<",";
            }
            cout<<"] - X = "<<fixed<<setprecision(3)<<binTOdec(colonia[i])<<" - Y ="<<avalia(binTOdec(colonia[i]))<<endl;
        }
}

int main(){
    a=-10.00;
    b=10.00;
    int nmr;
    cout<<"Digite a qnt de indivíduos da colonia"<<endl;
    cin>>nmr;

    srand (time(NULL));

    vector<Bit> colonia;
    Bit p;
    srand (time(NULL));
    for(int i=0;i<nmr;i++){
        for(int j=0;j<4;j++){
            p.cadeia[j]=rand()%2;
        }
        colonia.push_back(p);
    }
    int ger=10;

    mostraPopulacao(colonia);

    while(ger--){
            /*
        for(int i=0;i<nmr;i++){
            cout<<"Individuo["<<i<<"] = [";
            for(int j=0;j<4;j++){
                cout<<colonia[i].cadeia[j];
                if(j<3)cout<<",";
            }
            cout<<"] - dec = "<<binTOdec(colonia[i],a,b)<<" - nota :"<<100 - avalia(binTOdec(colonia[i],a,b))<<endl;
        }
    */

        vector<Bit>filho;
        for(int i=0;i<(int)(nmr/4);i++){   //SELECIONANDO OS PAIS PARA REPRODUÇÃO
            filho.push_back(selecao(colonia,nmr));

        }
        /*
        for(int i=0;i<(int)(nmr/4);i++){
            cout<<"Filho["<<i<<"] = [";
            for(int j=0;j<4;j++){
                cout<<filho[i].cadeia[j];
                if(j<3)cout<<",";
            }
            cout<<"] - X = "<<binTOdec(filho[i],a,b)<<" - Y = "<<avalia(binTOdec(filho[i],a,b))<<endl;
        }
        */
        mutacao(filho);
    /*
        cout<<endl<<endl<<"Pos-mutacao"<<endl<<endl;

        for(int i=0;i<(int)(nmr/4);i++){
            cout<<"Filho["<<i<<"] = [";
            for(int j=0;j<4;j++){
                cout<<filho[i].cadeia[j];
                if(j<3)cout<<",";
            }
            cout<<"] - dec = "<<binTOdec(filho[i],a,b)<<" - nota :"<<100 - avalia(binTOdec(filho[i],a,b))<<endl;
        }
        */

        for(int i=0;i<filho.size();i++){
            colonia.push_back(filho[i]);
        }
        //cout<<colonia.size()<<endl;

        sort(colonia.begin(),colonia.end(),meuSort);
    /*
        for(int i=0;i<colonia.size();i++){
            cout<<"Individuo["<<i<<"] = [";
            for(int j=0;j<4;j++){
                cout<<colonia[i].cadeia[j];
                if(j<3)cout<<",";
            }
            cout<<"] - X = "<<binTOdec(colonia[i],a,b)<<" - Y :"<<avalia(binTOdec(colonia[i],a,b))<<endl;
        }
    */
        colonia.erase(colonia.begin(),colonia.begin()+(int)(nmr/4));
    /*
        cout<<endl<<"eliminando piores"<<endl<<endl;

        for(int i=0;i<colonia.size();i++){
            cout<<"Individuo["<<i<<"] = [";
            for(int j=0;j<4;j++){
                cout<<colonia[i].cadeia[j];
                if(j<3)cout<<",";
            }
            cout<<"] - X = "<<binTOdec(colonia[i],a,b)<<" - Y = "<<avalia(binTOdec(colonia[i],a,b))<<endl;
        }
        */
    }

    cout<<endl<<"Populacao Final = "<<endl<<endl;
    mostraPopulacao(colonia);

return 0;
}
