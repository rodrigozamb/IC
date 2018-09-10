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

bool meuSort(Bit a,Bit b){
    return avalia(binTOdec(a))>avalia(binTOdec(b));
}

void mostraPopulacao(vector<Bit>colonia){
    for(int i=0;i<colonia.size();i++){
            cout<<"Individuo["<<i<<"] = [";
            for(int j=0;j<4;j++){
                cout<<colonia[i].cadeia[j];
                if(j<3)cout<<",";
            }
            cout<<"] - dec = "<<binTOdec(colonia[i])<<" - nota :"<<100 - avalia(binTOdec(colonia[i]))<<endl;
        }
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
            cout<<"] - dec = "<<binTOdec(colonia[i])<<" - nota :"<<100 - avalia(binTOdec(colonia[i]))<<endl;
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
            cout<<"] - dec = "<<binTOdec(filho[i])<<" - nota :"<<100 - avalia(binTOdec(filho[i]))<<endl;
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
            cout<<"] - dec = "<<binTOdec(filho[i])<<" - nota :"<<100 - avalia(binTOdec(filho[i]))<<endl;
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
            cout<<"] - dec = "<<binTOdec(colonia[i])<<" - nota :"<<100 - avalia(binTOdec(colonia[i]))<<endl;
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
            cout<<"] - dec = "<<binTOdec(colonia[i])<<" - nota :"<<100 - avalia(binTOdec(colonia[i]))<<endl;
        }
        */
    }

    cout<<endl<<"Populacao Final = "<<endl<<endl;
    mostraPopulacao(colonia);

return 0;
}
