#include<bits/stdc++.h>
#include<math.h>
using namespace std;
#define taxaRep 0.6
#define nmrsEmX 10


typedef struct individuo{
    float cadeia[nmrsEmX];
}Individuo;

Individuo geraX(){

    // D E M N O R S Y
    // 0 1 2 3 4 5 6 7

    Individuo pessoa;
    vector <int> lista;
    for(int i=0;i<10;i++)lista.push_back(i);


    for(int i=0;i<10;i++){
        int pos = rand()% lista.size();
        pessoa.cadeia[i]=lista[pos];
        lista.erase(lista.begin()+pos);
    }


    return pessoa;
}

int funcaoY(Individuo ser){

    int send = ser.cadeia[0]+10*ser.cadeia[3]+100*ser.cadeia[1]+1000*ser.cadeia[6];
    int more = ser.cadeia[2]+10*ser.cadeia[4]+100*ser.cadeia[5]+1000*ser.cadeia[1];
    int money = ser.cadeia[2]+10*ser.cadeia[4]+100*ser.cadeia[3]+1000*ser.cadeia[1]+10000*ser.cadeia[7];

    int sum = abs (money - (send+more));
    return sum;
}

void mostraPopulacao(vector<Individuo>colonia){
    for(int i=0;i<colonia.size();i++){
            cout<<"Individuo["<<i<<"] = [";
            for(int j=0;j<nmrsEmX;j++){
                cout<<colonia[i].cadeia[j];
                if(j==7)cout<<" |";
                if(j<nmrsEmX-1)cout<<" , ";
            }
            cout<<"]";
            cout<<" - Y = "<<funcaoY(colonia[i])<<endl;
        }
}

int func (int gen,Individuo pai){

    for(int i=0;i<8;i++){
        if(pai.cadeia[i]==gen)return i;
    }
    return -1;
}

void gerarFilhos(Individuo pai1, Individuo pai2, Individuo *F1, Individuo *F2){

    int pos = rand()%8; //gera um valor random de 0 a 8

	for(int i=0;i<10;i++){
		F1->cadeia[i]=-1;
		F2->cadeia[i]=-1;
	}

    int gen = pai2.cadeia[pos];

    while(F1->cadeia[pos]==-1 && pos!=-1){

		gen = pai2.cadeia[pos];
		F1->cadeia[pos] = pai2.cadeia[pos];
		F2->cadeia[pos] = pai1.cadeia[pos];
		pos = func(gen,pai1);
		if(pos==-1)break;

	}

	for(int i=0;i<10;i++){
		if(F1->cadeia[i]==-1)F1->cadeia[i]=pai1.cadeia[i];
		if(F2->cadeia[i]==-1)F2->cadeia[i]=pai2.cadeia[i];
	}


}

void mutar(Individuo *ind){
    int pos1 = rand()%8;
    int pos2;
    do{
        pos2 = rand()%10;
    }while(pos1==pos2);
    int aux1 = ind->cadeia[pos1];
    int aux2 = ind->cadeia[pos2];
    ind->cadeia[pos1] = aux2;
    ind->cadeia[pos2] = aux1;
}

void selecao(vector<Individuo> colonia,int *pai1,int *pai2){
    //cout<<"tam = "<<colonia.size()<<" rand = "<<rand()% colonia.size()<<endl;
    int Pai1,Pai2;
    for(int i=0;i<2;i++){
        int posP1=0,posP2=0,posP3=0;
        while(posP1==posP2 || posP2==posP3 || posP1 == posP3){
            posP1 = rand()%colonia.size();
            posP2 = rand()%colonia.size();
            posP3 = rand()%colonia.size();
        }

        if(i==0){
            if(funcaoY(colonia[posP1]) >= funcaoY(colonia[posP2]) && funcaoY(colonia[posP1])>=funcaoY(colonia[posP3])) Pai1 = posP1;
            if(funcaoY(colonia[posP2]) >= funcaoY(colonia[posP1]) && funcaoY(colonia[posP2])>=funcaoY(colonia[posP3])) Pai1 = posP2;
            if(funcaoY(colonia[posP3]) >= funcaoY(colonia[posP2]) && funcaoY(colonia[posP3])>=funcaoY(colonia[posP1])) Pai1 = posP3;
        }
        else if(i==1){
            if(funcaoY(colonia[posP1]) >= funcaoY(colonia[posP2]) && funcaoY(colonia[posP1])>=funcaoY(colonia[posP3])) Pai2 = posP1;
            if(funcaoY(colonia[posP2]) >= funcaoY(colonia[posP1]) && funcaoY(colonia[posP2])>=funcaoY(colonia[posP3])) Pai2 = posP2;
            if(funcaoY(colonia[posP3]) >= funcaoY(colonia[posP2]) && funcaoY(colonia[posP3])>=funcaoY(colonia[posP1])) Pai2 = posP3;
        }
    }

    *pai1 = Pai1;
    *pai2 = Pai2;
}

bool meuSort(Individuo a,Individuo b){

    return funcaoY(a)>funcaoY(b);
}

int main(){
    double a=-5.00;
    double b=10.00;
    int nmr;
    cout<<"Digite a qnt de indivíduos da colonia"<<endl;
    cin>>nmr;
    vector<Individuo> colonia;

    srand (time(NULL));

    Individuo p;

    for(int i=0;i<nmr;i++){
        p=geraX();
        colonia.push_back(p);
    }
    mostraPopulacao(colonia);
    cout<<"Tamanho da colonia Inicial = "<<colonia.size()<<endl;

    int g=500;
    while(g--){
        //ESTA REPETINDO ALGUNS NUMEROS NO SEND+MORE=MONEY
        for(int i=0;i<(int)(nmr*taxaRep);i++){
            Individuo i1,i2;
            int p1,p2;
            selecao(colonia,&p1,&p2);
            gerarFilhos(colonia[p1],colonia[p2],&i1,&i2);
            mutar(&i1);
            mutar(&i2);
            colonia.push_back(i1);
            colonia.push_back(i1);
        }
        sort(colonia.begin(),colonia.end(),meuSort);
        colonia.erase(colonia.begin(),colonia.begin()+(colonia.size()-nmr));
    }
    mostraPopulacao(colonia);


return 0;
}

