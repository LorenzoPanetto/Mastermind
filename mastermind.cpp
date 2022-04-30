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


void secretCodeColor(int sec[], int dim) {
    for (int i=0; i<dim; i++) {
        sec[i]=rand()%8;
    }
    while (duplicates(sec, dim)==true) {
        for (int i=0; i<dim; i++) {
			sec[i]=rand()%8;      	
        }
    }
    
    for (int k=0; k<dim; k++) {
    	SetColor(sec[k]);
    	cout << "#" << " ";
	}
	cout << endl;
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


void inputCodeColor(int code[], int dim) {
    for (int i=0; i<dim; i++){
        cin >> code[i];
        while(code[i]<0||code[i]>8) {
            cout<<"il colore deve essere compreso tra 0 e 8"<<endl;
            cin>>code[i];
        }
        while (containes(code, code[i], i)) {
            cout << "inserisci un array di 4 cifre diverse. Ora sostituisci solo la cifra doppia" << endl;
    		cin >> code[i];
        }
    }
}


//output codice utente
void outputcode (int code[], int dim) {
	for (int i=0; i<dim; i++)
		cout << code[i];
}


void outputCodeColor (int code[], int dim) {
    for (int k=0; k<dim; k++) {
    	SetColor(code[k]);
    	cout << "#" << " ";
	}
    SetColor(7);
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




void table(int a[][6], int num) {
    system("cls");
    cout<<" _____ _____ _____ _____       _____ _____ "<<endl;
    for (int i=0; i<num; i++) {
        cout<<"|     |     |     |     |     |     |     |"<<endl;
        cout<<"|  "<<a[i][0]<<"  |  "<<a[i][1]<<"  |  "<<a[i][2]<<"  |  "<<a[i][3]<<"  |"<<"     |  "<<a[i][4]<<"  |  "<<a[i][5]<<"  |  " << endl;
        cout<<"|_____|_____|_____|_____|     |_____|_____|"<<endl;
    }
}


void tableColor(int a[][6], int num) {
    system("cls");
    cout<<" _____ _____ _____ _____       _____ _____ "<<endl;
    for (int i=0; i<num; i++) {
        cout<<"|     |     |     |     |     |     |     |"<<endl;
        cout<<"|  "; 
		SetColor(a[i][0]);
		cout<<"#";
		SetColor(7);
		cout<<"  |  ";
		SetColor(a[i][1]);
		cout << "#";
		SetColor(7);
		cout<<"  |  ";
		SetColor(a[i][2]);
		cout << "#";
		SetColor(7);
		cout<<"  |  ";
		SetColor(a[i][3]);
		cout << "#";
		SetColor(7);
		cout<<"  |"<<"     |  "<<a[i][4]<<"  |  "<<a[i][5]<<"  |  " << endl;
        cout<<"|_____|_____|_____|_____|     |_____|_____|"<<endl;
    }
}


int main () {
	ifstream fin;
	string testo;
	fin.open("ii.txt", ios::in);
	
	if (fin) 
	{
		while(getline(fin,testo))
			cout << testo << endl;
	}
	else
		cout << "errore apertura file indicazioni iniziali.txt" << endl;
	
	fin.close();
		
		
	int mod;
	cout << "Inserisci la modalita' di gioco: " << endl;
	cin >> mod;
	if (mod==1)
		main1();
	if (mod==2)
		main2();
}


void main1() {
	system("cls");
    srand(time(0));
    int prove=7, fatte=0;
    int tentativi[prove][6]; // Matrice dei tentativi
    int secret[dim];
    cout << "codice segreto generato dal PC: ";
    secretCode(secret, dim);
    int codeut[dim];
	cout<<"inserire il codice"<<endl;
    inputCode(codeut, dim);
    system("CLS");
    for (int i=0; i<dim; i++) {
        tentativi[0][i]=codeut[i]; // Inserisco il codice utente nelle prime dim colonne della matrice
    }
    tentativi[0][4] = numGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti nelle prime dim colonne della matrice
    tentativi[0][5] = posGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti in posizione giusta nelle prime dim colonne della matrice
    table(tentativi, 1); // 2, numero di righe da stampare 
    while (check(codeut, secret, dim) == false && prove>0) {
    	inputCode(codeut, dim);
        fatte++;
        for (int i=0; i<dim; i++) {
            tentativi[fatte][i]=codeut[i]; // Inserisco il codice utente nelle prime dim colonne della matrice
        }
        tentativi[fatte][4] = numGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti nelle prime dim colonne della matrice
        tentativi[fatte][5] = posGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti in posizione giusta nelle prime dim colonne della matrice
    	table(tentativi, fatte+1); // fatte+1 è il numero di righe da stampare 
        prove--;
	}
}


void main2() {
	system("cls");
    srand(time(0));
    int prove=7, fatte=0;
    int tentativi[prove][6];
    int secret[dim];
    
    cout << "codice segreto generato dal PC: " << endl;
    secretCodeColor(secret, dim);
    int codeut[dim];
	cout<<"inserire il codice"<<endl;
    inputCodeColor(codeut, dim);
    system("CLS");
    for (int i=0; i<dim; i++) {
        tentativi[0][i]=codeut[i]; // Inserisco il codice utente nelle prime dim colonne della matrice
    }
    tentativi[0][4] = numGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti nelle prime dim colonne della matrice
    tentativi[0][5] = posGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti in posizione giusta nelle prime dim colonne della matrice
    tableColor(tentativi, 1); // 2, numero di righe da stampare 
    while (check(codeut, secret, dim) == false && prove>0) {
    	inputCodeColor(codeut, dim);
        fatte++;
        for (int i=0; i<dim; i++) {
            tentativi[fatte][i]=codeut[i]; // Inserisco il codice utente nelle prime dim colonne della matrice
        }
        tentativi[fatte][4] = numGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti nelle prime dim colonne della matrice
        tentativi[fatte][5] = posGiusti(codeut, secret, dim); // Inserisco il numero di numeri giusti in posizione giusta nelle prime dim colonne della matrice
    	tableColor(tentativi, fatte+1); // fatte+1 è il numero di righe da stampare 
        prove--;
	}
}