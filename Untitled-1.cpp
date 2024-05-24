// Esercizio 1

/*
    Supponendo di avere in input i dati relativi a tutte le vendite 
    di 5 reparti di un supermercato nei giorni della settimana, scrivi
    un programma che visualizzi i dati relativi alle vendite di ogni
    reparto e alla sua percentuale rispetto al totale.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Dichiarazione costanti 
#define N 5 // numero reparti

// Colori 
#define RESET       "\033[0m"
#define BLUE        "\033[1m\033[34m"  
#define RED         "\033[1m\033[31m"  
#define YELLOW      "\033[1m\033[33m"  
#define GREEN       "\033[1m\033[32m"  

// Protoripi
int menu();
void inserisciVendite(double vendite[7][N],string settimana[], int &inizio, int &fine);
bool controllo(int giorno);
bool controllo1(int inizio, int fine);
bool controllo2(int soldi);
void stampa(double vendite[7][N],string settimana[], int inizio, int fine);
int size(string settimana[],int inizio, int fine); // Calcolo dimensione massima della settimana
int size1(double vendite[7][N]); // Calcolo n caratteri di n max
void dati(double vendite[7][N],string settimana[], int inizio, int fine,double SommaDati[]);
void DatiSettimana(double vendite[7][N],string settimana[], int giorno);
void DatiReparto(double vendite[7][N],string settimana[], int reparto,int inizio, int fine, double SommaDati[]);
void Percentuali(double vendite[7][N],string settimana[], double SommaDati[]);
void next();


int main(){

    // Dichiarazione variabili
    int s,inizio,fine;
    double vendite[7][N];
    string settimana[7]={
        "Lunedi", "Martedi", "Mercoledi",
        "Giovedi", "Venerdi", "Sabato",
        "Domenica"
    };

    double SommaDati[N]; // Dati per ogni reparto

    do{

        system("cls");
        s=menu();

        switch(s){

            // Inserimento vendite
            case 1:{
                inserisciVendite(vendite,settimana,inizio,fine);
                next();
                break;
            }

            // Stampa vendite
            case 2:{
                stampa(vendite,settimana,inizio,fine);
                next();
                break;
            }

            // Visualizza Dati
            case 3:{
                dati(vendite,settimana,inizio,fine,SommaDati);
                next();
                break;
            }

            // Esci
            case 0:{
                cout<<GREEN<<"Arrivederci!"<<RESET;
                break;
            }

            default:{
                cout<<RED<<"Scelta non valida!"<<RESET;
                break;
            }
        }

    }while(s!=0);
    return 0;
}

int menu(){

    int s;

    cout<<BLUE<<"\t-----MENU-----\n"<<RESET;
    cout<<BLUE<<"1. "<<RESET<<"Inserisci vendite\n";
    cout<<BLUE<<"2. "<<RESET<<"Stampa vendite\n";
    cout<<BLUE<<"3. "<<RESET<<"Visualizza Dati\n";
    cout<<BLUE<<"0. "<<RESET<<"Esci\n";

    cout<<GREEN<<"\nFai una scelta: "<<RESET;
    cin>>s;

    cout<<"\n";

    return s;
}

void inserisciVendite(double vendite[][N],string settimana[], int &inizio, int &fine){

    do{
        do{
            cout<<BLUE<<"Inserisci l'inizio della settimana (1-7): "<<RESET;
            cin>>inizio;
        }while(controllo(inizio)==false);

        do{
            cout<<BLUE<<"Inserisci la fine della settimana (1-7): "<<RESET;
            cin>>fine;
        }while(controllo(fine)==false);

    }while(controllo1(inizio,fine)==false);

    cout<<"\n";

    for(int i=inizio-1;i<fine;i++){
        for(int j=0;j<N;j++){
            cout<<BLUE<<"settimana "<<settimana[i]<<", reparto "<<j+1<<": "<<RESET;
            do{
                cin>>vendite[i][j];
            }while(controllo2(vendite[i][j])==false);
        }
        cout<<"\n";
    }
}

bool controllo(int giorno){

    if(giorno<1 || giorno>7){
        cout<<YELLOW<<"\nGiorno non valido!\n"<<RESET;
        return false;
    }
    else{
        return true;
    }
}

bool controllo1(int inizio, int fine){
    
    if(inizio>fine){
        cout<<YELLOW<<"\nInizio maggiore di fine!\n"<<RESET;
        return false;
    }
    else{
        return true;
    }
}

bool controllo2(int soldi){
    
    if(soldi<0){
        cout<<YELLOW<<"\nInserisci una quantita' positiva\n"<<RESET;
        return false;
    }
    else{
        return true;
    }
}

void stampa(double vendite[][N],string settimana[], int inizio, int fine){

    // Calcolo dimensione massima della settimana
    int n=size(settimana,inizio,fine);
    // Calcolo n caratteri di n max
    int nMax=size1(vendite);

    // Stampa vendite
    for(int i=inizio-1;i<fine;i++){

        cout<<BLUE<<settimana[i]<<setw(n-settimana[i].size()+4)<<"| "<<RESET;

        for(int j=0;j<N;j++){
            cout<<setw(nMax-to_string(vendite[i][j]).size()+2)<<vendite[i][j]<<setw(2)<<" | ";
        }

        cout<<"\n";
    }

}

int size(string settimana[],int inizio, int fine){
    int size=0;

    for(int i=inizio-1;i<fine;i++){
        if(settimana[i].size()>size){
            size=settimana[i].size();
        }
    }

    return size;
}

int size1(double vendite[7][N]){
    int size=0;

    for(int i=0;i<7;i++){
        for(int j=0;j<N;j++){
            if(to_string(vendite[i][j]).size()>size){
                size=to_string(vendite[i][j]).size();
            }
        }
    }

    return size;
}

void dati(double vendite[7][N],string settimana[], int inizio, int fine, double SommaDati[]){
    for(int i=inizio-1;i<fine;i++){
        DatiSettimana(vendite,settimana,i);
        cout<<"\n";
    }

    for(int i=0;i<N;i++){
        DatiReparto(vendite,settimana,i,inizio,fine,SommaDati);
    }

    cout<<"\n";

    Percentuali(vendite,settimana,SommaDati);
}

void DatiSettimana(double vendite[7][N],string settimana[], int giorno){

    int n=0;

    for(int i=0;i<N;i++){
        n+=vendite[giorno][i];
    }
    cout<<BLUE<<settimana[giorno]<<": "<<RESET;
    cout<<"Vendite totali: "<<n<<endl;

}

void DatiReparto(double vendite[7][N],string settimana[], int reparto,int inizio, int fine, double SommaDati[]){
    int somma=0;

    for(int i=inizio-1;i<fine;i++){
        somma+=vendite[i][reparto];
    }
    cout<<BLUE<<"Reparto "<<reparto+1<<": "<<RESET;
    cout<<"Vendite totali: "<<somma<<endl;

    SommaDati[reparto]=somma;
}

void Percentuali(double vendite[7][N],string settimana[], double SommaDati[]){
    double totale=0;

    // Calcolo totale vendite
    for(int i=0;i<N;i++){
        totale+=SommaDati[i];
    }

    // Calcola e stampa le percentuali di vendite per ogni reparto
    for(int i=0;i<N;i++) {
        double percentuale=(SommaDati[i]/totale)*100;
        cout<<BLUE<<"Percentuale di vendite per Reparto "<<i+1<<": "<<RESET<<setprecision(2)<<percentuale<<"%\n";
    }
}


void next(){
    cout<<GREEN<<"\nPremi qualsiasi tasto per continuare..."<<RESET;
    cin.ignore();
    cin.get();
}