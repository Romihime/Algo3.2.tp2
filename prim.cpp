#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <tuple>
#include <math.h>

using namespace std;
using namespace std::chrono;

#define INFINITO 21474836


void Prim(int** ,int, int, int*);
void PintandoRutas(int,int*, int**);
float desvio(vector <int> vector);




int main(){
	int n ;
	cin >> n;
    int x;
    int y;
    vector < tuple<int,int> > puntos;

    for(int i = 0; i < n; i++){
    	cin >> x;
    	cin >> y;
    	puntos.push_back(make_tuple(x,y));
    }

    for(int i =0; i <n;i++){
		cout << "(" << get<0>(puntos[i]) << "," << get<1>(puntos[i]) << ")" << " ";  // esto es para ver los puntos
	}
	cout << endl;


    int **matriz;
    matriz = new int*[n];

    for(int x = 0; x < n; x++){
        matriz[x] = new int[n];
    }

   for(int i = 0; i < n; i++){
       for(int j = 0; j < n; j++){
            matriz[i][j] = abs( (int)get<0>(puntos[i]) - (int)get<0>(puntos[j])) + abs((int)get<1>(puntos[i]) - (int)get<1>(puntos[j]));
        }
    }

    
	/*for(int i =0; i <n;i++){
		for(int j= 0; j<n; j++ ){
			cout << matriz[i][j] << " "; // esto es para chekear que hay dentro de la matriz
		}
	cout << endl;
	}
	cout << endl;*/


    int* Padres = new int[n];
    Prim(matriz, 0, n, Padres); // AGM


     for(int i =0; i <n;i++){
		cout << Padres[i] << " ";  // esto es para ver quienes quedaron en el AGM
	}
	cout << endl;



    // encontrar las aristas cercanas con d = 2
    //sacarles el promedio al peso y eso es la esperanza

    vector <tuple<int,int>> candidatos;

    for(int a = 0; a < n; a++){
        int b = Padres[a];
        int PesoDeAristaAAnalizar = matriz[a][b];
        //int cercanas = 1;

        vector <int> adyacentesAa;
        for(int j =0; j <n;j++){
            if (Padres[j] == a) adyacentesAa.push_back(j);
        }
        
        float esperanzaA = 0;
        for(int j =0; j < adyacentesAa.size();j++){
            esperanzaA = esperanzaA + matriz[a][adyacentesAa[j]];
        }

    }

        vector <int> lista;
        lista.push_back(21);
        lista.push_back(22);
        lista.push_back(19);
        lista.push_back(15);

     	for(int i =0; i < lista.size() ;i++){
			cout << lista[i] << " ";  // esto es para ver quienes quedaron en el AGM
		}
		cout << endl;	
        cout << desvio( lista) << endl;


    //delete[] matriz;
    //delete[] Padres;
    return 0;
}


float desvio(vector <int> vector){
	float suma;
	int n = vector.size();
	cout << n << endl;
	for(int i = 0; i < n; i++){
		suma = suma + vector[i];
	}
	float promedio = suma/n;
	cout << promedio << endl;
	float sigma;
	for(int i = 0; i < n; i++){
		sigma = sigma + ((vector[i] - promedio)*(vector[i] - promedio));
	}
	return sqrt(sigma/(n-1));
}


void Prim (int** matriz, int nodo, int cantNodos, int *Padres){
    int nodosVisitados = 0;
    bool visitados[cantNodos]; 
    int i = 0;
    int pesos[cantNodos];
    int padres[cantNodos];

    while(i < cantNodos){
        pesos[i] = INFINITO;
        visitados[i] = false;
        padres[i] = -1;
        i++;
    }

    i = 0;
    while(i< cantNodos){
        if(matriz[nodo][i] != INFINITO){
            pesos[i] = matriz[nodo][i];
            padres[i] = nodo;
        }
        i++;
    }

    pesos[nodo] = 0;
    visitados[nodo] = true;
    nodosVisitados++;

    while(nodosVisitados < cantNodos){
        int nodoAAgregar = 0;
        int peso = INFINITO+1;
        int j = 0;
        while(j < cantNodos){
            if((peso > pesos[j]) && (visitados[j] == false)){
                peso = pesos[j];
                nodoAAgregar = j;
            }
            j++;
        }
        visitados[nodoAAgregar] = true;
        nodosVisitados++;
        int k = 0;
        while(k < cantNodos){
            if((pesos[k] > matriz[nodoAAgregar][k]) && (visitados[k] == false)){
                pesos[k] = matriz[nodoAAgregar][k];
                padres[k] = nodoAAgregar;
            }
            k++;
        }       
    }

    i = 0;
    while(i < cantNodos){
        Padres[i] = padres[i];
        i++;
    }
}
