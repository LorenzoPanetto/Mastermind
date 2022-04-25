#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std;
// g++ mastermind.cpp -o mastermind.exe

const int dim=4; // Costante per la dimensione degli array
void main1();
void main2();

void SetColor(short Color) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,Color);
}


struct Variabile{
	int numeri;
	int colori;
};


//controllo valori doppi PC @@panetto
bool duplicates(int sec[], int dim) {
    for (int i=0; i<dim; i++) {
        for (int j=0; j<dim; j++) {
            if (sec[i]==sec[j]&&i!=j)
                return true;
        }
    }
    return false;
}


//controllo valori doppi PC @@panetto
bool duplicatesColor(Variabile sec[], int dim) {
    for (int i=0; i<dim; i++) {
        for (int j=0; j<dim; j++) {
            if ((sec[i].colori==sec[j].colori&&i!=j)||(sec[i].numeri==sec[j].numeri&&i!=j))
                return true;
        }
    }
    return false;
}


//creazione codice segreto PC @@bulfoni
void secretCode(int sec[], int dim) {
    for (int i=0; i<dim; i++) {
        sec[i]=rand()%10;
    }
    while (duplicates(sec, dim)==true) {
        for (int i=0; i<dim; i++)
            sec[i]=rand()%10;
    }
 
    //cout codice segreto
    for (int i=0; i<dim; i++) 
        cout << sec[i] << " ";
    cout << endl;
}


void secretCodeColor(Variabile sec[], int dim) {
    for (int i=0; i<dim; i++) {
        sec[i].numeri=rand()%10;
        sec[i].colori=rand()%8;
    }
    while (duplicatesColor(sec, dim)==true) {
        for (int i=0; i<dim; i++) {
            sec[i].numeri=rand()%10;
			sec[i].colori=rand()%8;      	
        }
    }
    
    for (int k=0; k<dim; k++) {
    	SetColor(sec[k].colori);
    	cout << sec[k].numeri << " " << endl;
	}
    SetColor(7);
}
 

//controllo se il valore inserito dall'utente è già presente nell'array @@panetto
bool containes(int arr[], int val, int end) {
    for (int j=0; j<end; j++) {
        if (arr[j] == val)
            return true;
    }
    return false;
}


bool containesColor(Variabile arr[], int val, int end) {
    for (int j=0; j<end; j++) {
        if (arr[j].numeri == val)
            return true;
    }
    return false;
}


//input codice utente @@bulfoni
void inputCode(int code[], int dim) {
	//num++;
    for (int i=0; i<dim; i++){
        cin >> code[i];
        while(code[i]<0||code[i]>9) {
            cout<<"il numero deve essere compreso tra 0 e 9"<<endl;
            cin >> code[i];
        }
        while (containes(code, code[i], i)) {
            cout << "inserisci un array di 4 cifre diverse. Ora sostituisci solo la cifra doppia" << endl;
    		cin >> code[i];
        }
    }
}


void inputCodeColor(Variabile code[], int dim) {
	//num++;
    for (int i=0; i<dim; i++){
        cin >> code[i].numeri;
        cin >> code[i].colori;
        while((code[i].numeri<0||code[i].numeri>9)||(code[i].colori<0||code[i].colori>8)) {
            cout<<"il numero deve essere compreso tra 0 e 9"<<endl;
            cin>>code[i].numeri;
            cout<<"il colore deve essere compreso tra 0 e 8"<<endl;
            cin>>code[i].colori;
        }
        while (containesColor(code, code[i].numeri, i)) {
            cout << "inserisci un array di 4 cifre diverse. Ora sostituisci solo la cifra doppia" << endl;
    		cin >> code[i].numeri;
        }
        while (containesColor(code, code[i].colori, i)) {
            cout << "inserisci un array di 4 cifre diverse. Ora sostituisci solo la cifra doppia" << endl;
    		cin >> code[i].colori;
        }
    }
}


//output codice utente
void outputcode (int code[], int dim) {
	for (int i=0; i<dim; i++)
		cout << code[i];
}


//controlla se tutti i valori inseriti dall'utente sono uguali al codice del computer
bool check (int code[], int sec[], int dim) {
	for (int i=0; i<dim; i++) {
		if (code[i]!=sec[i])
			return false;
	}
	return true;
}


//indica quanti numeri giusti in posizione sbagliata ci sono nel codice dell'utente rispetto al pc
int numGiusti (int code[], int sec[], int dim) {
	int num=0; //numeri giusti in posizione sbagliata
	for (int i=0; i<dim; i++) {
		for (int j=0; j<dim; j++) {
			if (sec[i]==code[j]&&i!=j)
				num++;
		}
	}
	return num;
}


//indica quanti numeri giusti in posizione giusta ci sono nel codice dell'utente rispetto al PC
int posGiusti (int code[], int sec[], int dim) {
	int pos=0; //numeri giusti in posizione giusta
	for (int i=0; i<dim; i++) {
		for (int j=0; j<dim; j++) {
			if (sec[i]==code[j]&&i==j)
				pos++;
		}
	}
	return pos;
}


void table (int a[], int num, int pos) {
	cout<<endl;
	cout<<" _____ _____ _____ _____ _____ _____ _____ "<<endl;
	cout<<"|     |     |     |     |     |     |     |"<<endl;
	cout<<"|  "<<a[0]<<"  |  "<<a[1]<<"  |  "<<a[2]<<"  |  "<<a[3]<<"  |"<<"     |  "<<num<<"  |  "<<pos<<"  |  " << endl;
	cout<<"|_____|_____|_____|_____|_____|_____|_____|"<<endl;
}


int main () {
	int mod;
	cout << "Inserisci la modalita' di gioco: " << endl;
	cout << "MOD 1: solo numeri tutti diversi tra loro" << endl;
	cout << "MOD 2: numeri diversi tra loro + colori" << endl;
	cin >> mod;
	if (mod==1)
		main1();
	if (mod==2)
		main2();
}


void main1() {
	system("cls");
    srand(time(0));
    int prove=7;
    int secret[dim];
    cout << "codice segreto generato dal PC: ";
    secretCode(secret, dim);
    int codeut[dim];
	cout<<"inserire il codice"<<endl;
    inputCode(codeut, dim);
    system("CLS");
    table(codeut, numGiusti(codeut, secret, dim), posGiusti(codeut, secret, dim));
    while (check(codeut, secret, dim) == false && prove>0) {
    	inputCode(codeut, dim);
    	table(codeut, numGiusti(codeut, secret, dim), posGiusti(codeut, secret, dim));
    	prove--;
	}
}


void main2() {
	system("cls");
    srand(time(0));
    int prove=7;
    Variabile secret[dim];
    
    cout << "codice segreto generato dal PC: " << endl;
    secretCodeColor(secret, dim);
    
    /*   
    Variabile codeut[dim];
	cout<<"inserire il codice"<<endl;
    inputcodecolor(codeut, dim);
    system("CLS");
    table(codeut, numgiusti(codeut, secret, dim), posgiusti(codeut, secret, dim));
    while (check(codeut, secret, dim)==false&&prove>0)
    {
    	inputcode(codeut, dim);
    	system("CLS");
    	table(codeut, numgiusti(codeut, secret, dim), posgiusti(codeut, secret, dim));
    	prove--;
	}
    return 0;
    */	
}