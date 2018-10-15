#ifndef EJ1_H
#define EJ1_H

#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <tuple>
#include <math.h>
#include <queue>
#include <algorithm>


 
#define INFINITO 21474836 

using namespace std;
using namespace std::chrono;

float promedio(vector <int> vector);
float desvio(vector <int> vector);
void printVectorPuntos(vector < pair<int,int> >  vector);
void printVector(vector < int >  vector);
void printMatriz(vector< vector<int> >  matriz);
void pasarMatriz( vector< vector<int> > res, int* padres, int n);
vector<int> clusterizar(vector <bool> inconsistentes, int* padres, vector <pair<int,int> > aristas, int n);


float desvio(vector <int> vector){
	int n = vector.size();
	float promedio1 = promedio(vector);
	float sigma;
	for(int i = 0; i < n; i++){
		sigma = sigma + ((vector[i] - promedio1)*(vector[i] - promedio1)); // calculamos el desvio
	}
	return sqrt(sigma/(n));
}

float promedio(vector <int> vector){
	float suma;
	int n = vector.size();
	for(int i = 0; i < n; i++){
		suma = suma + vector[i];
	}
	float promedio = suma/n;
	return promedio;
}


void printMatriz(vector< vector<int> >  matriz){
    for(int i = 0; i < matriz[0].size(); i++){
       for(int j = 0; j < matriz[0].size(); j++){
            cout << matriz[i][j] << " " ;
        }
        cout << endl;
    }
    cout << endl;
}

void printVectorPuntos(vector < pair<int,int> >  vector){
    for(int i =0; i <vector.size();i++){
		cout << "(" << vector[i].first << "," << vector[i].second << ")" << " ";  // esto es para ver los puntos
	}
	cout << endl;
}

void printVector(vector < int >  vector){
    for(int i =0; i <vector.size();i++){
		cout << vector[i] << " ";  // este vector es el de padres de cada nodo 
	}
	cout << endl;
}


void pasarMatriz( vector< vector<int> > res, int* padres, int n){

    for(int i = 0; i < n; i++){
        padres[i] = -1;
    }
    padres[0] = 0;
    queue <int> cola;
    cola.push(0); // la raiz es el 0

    while(!cola.empty()){
        int nodo = cola.front();
        cola.pop();

        for(int i = 0; i < n; i++){
            if (res[nodo][i] != 0 && padres[i] == -1){
                padres[i] = nodo;
                cola.push(i);
            } 
        }          
    }
}



vector<int> clusterizar(vector <bool> inconsistentes, int* padres, vector <pair<int,int> > aristas, int n){

    vector <int> resultado(n,-1);    
    for(int i =0; i < inconsistentes.size();i++){
        if(inconsistentes[i]) padres[aristas[i].first] = aristas[i].first;
    } //cortamos las insconsistentes del arreglo de padres

    cout << endl;

    queue <int> cola; 
    cola.push(0);
    int contador = 0;

    while(!cola.empty()){
        int nodo = cola.front();
        cola.pop();
        if(resultado[nodo] == -1) resultado[nodo] = contador; // ponele un numero al primer nodo, si no lo visite

        for(int j =0; j < n;j++){
            if (padres[j] == nodo && padres[j] != j){
                resultado[j] = resultado[nodo]; // y a los hijos poneles el mismo
                cola.push(j);
            }
        }

        if (cola.empty()){
            int i = 0;
            while( i < n){
                i++;
                if (resultado[i] == -1){
                    cola.push(i); // si ya vi toda la componente conexa, busca otra
                    contador++;
                    break;
                }
            }       
        }              
    }
    return resultado;
}





#endif