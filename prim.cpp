#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <tuple>

using namespace std;
using namespace std::chrono;

#define INFINITO 21474836


void Prim(int** ,int, int, int*);
void PintandoRutas(int,int*, int**);





int main(){
int n ;
cin >> n;
    if (n != 0){
    int x;
    int y;
    vector < tuple<int,int> > puntos;

    for(int i = 0; i < n; i++){
    	cin >> x;
    	cin >> y;
    	puntos.push_back(make_tuple(x,y));
    }

    for(int i =0; i <n;i++){
		cout << "(" << get<0>(puntos[i]) << "," << get<1>(puntos[i]) << ")" << " "; 
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

    


	for(int i =0; i <n;i++){
		for(int j= 0; j<n; j++ ){
			cout << matriz[i][j] << " "; // esto es para chekear que hay dentro de la matriz
		}
	cout << endl;
	}
	cout << endl;

    int* Padres = new int[n];


    //high_resolution_clock::time_point t1 = high_resolution_clock::now();

    Prim(matriz, 0, n, Padres);


     for(int i =0; i <n;i++){
		cout << Padres[i] << " "; 
	}
	cout << endl;
    
    //PintandoRutas(cantFabricas, Padres, Aristas);
    //high_resolution_clock::time_point t4 = high_resolution_clock::now();
    //duration<double> time_span1 = duration_cast<duration<double>>(t4 - t1);
    //cout << time_span1.count() << endl; 
	}

/*
    int res = 0;
    int contador = 0;
    i = 0;
    while(i < cantNodos){
        if(Padres[i] != -1){
            res += Aristas[i][Padres[i]];
            contador++;
        }
        i++;
    }

    cout << res << " " << contador << " ";
    i = 0;
    while(i < cantNodos){
        if(Padres[i] != -1){
            cout << Padres[i] << " " << i << " ";
        }
        i++;
    }
    cout << endl;
    i = 0;
    while(i < cantNodos){
        delete[] Aristas[i];
        i++;
    }

    delete[] matriz;
    delete[] Padres;

cin >> aux;
}*/
    return 0;
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
