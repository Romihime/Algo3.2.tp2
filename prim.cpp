#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <tuple>
#include <math.h>
#include <queue>


using namespace std;
using namespace std::chrono;

#define INFINITO 21474836


void Prim(int** ,int, int, int*);
float desvio(vector <int> vector);
vector <int> calcAdyacentesA(int nodoInicial, int d, int* padres, int **matriz, int n);
vector <int> calcAdyacentesB(int nodoInicial, int a, int d, int* padres, int **matriz, int n);
float promedio(vector <int> vector);
vector<int> clusterizar(vector <bool> inconsistentes, int* padres, int **matriz, vector <tuple<int,int> > aristas, int n);



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

    
	for(int i =0; i <n;i++){
		for(int j= 0; j<n; j++ ){
			cout << matriz[i][j] << " "; // esto es para chekear que hay dentro de la matriz
		}
	cout << endl;
	}
	cout << endl;


    int* padres = new int[n];
    Prim(matriz, 0, n, padres); // AGM


     for(int i =0; i <n;i++){
		cout << padres[i] << " ";  // esto es para ver quienes quedaron en el AGM // 0 0 1 6 6 3 2 2 5 4
	}
	cout << endl;

	vector <tuple<int,int>> aristas;
	for(int i = 0; i < n; i++){
		if(i != padres[i]) aristas.push_back(make_tuple(i,padres[i]));
	}

	for(int i =0; i <aristas.size();i++){
		cout << "(" << get<0>(aristas[i]) << "," << get<1>(aristas[i]) << ")" << " ";  // esto es para ver los puntos
	}
	cout << endl;



	vector <bool> inconsistentes(aristas.size(),0);
    vector <tuple<int,int>> candidatos;
    int d = 2;

    for(int p = 0; p < aristas.size(); p++){
        int a = (int)get<0>(aristas[p]);
        int b = (int)get<1>(aristas[p]);

        int PesoDeAristaAAnalizar = matriz[a][b];

        vector <int> adyA = calcAdyacentesA(a,2,padres,matriz,n);
        vector <int> adyB = calcAdyacentesB(b,a,2,padres,matriz,n);

        float promA = promedio(adyA);
        float promB = promedio(adyB);

       	//inconsistentes[p] = (((PesoDeAristaAAnalizar / promA) > 2*desvio(adyA))  && ((PesoDeAristaAAnalizar / promB) > 2*desvio(adyB))) ? 1 : 0;
       	inconsistentes[p] = (((PesoDeAristaAAnalizar / promA) > 1)  && ((PesoDeAristaAAnalizar / promB) > 1)) ? 1 : 0;
	}

	cout << "aristas inconsistentes?" << endl;
	for(int i =0; i < inconsistentes.size();i++){
		cout << inconsistentes[i] << " ";  // esto es para ver quienes quedaron en el AGM // 0 0 1 6 6 3 2 2 5 4
	}
	cout << endl;


    vector<int> resultados = clusterizar(inconsistentes, padres, matriz,aristas, n);
    cout << "Resultado" << endl;
    for(int i =0; i < n;i++){
    	cout << resultados[i] << endl;
    }
    //delete[] matriz;
    //delete[] padres;
    return 0;
}


vector<int> clusterizar(vector <bool> inconsistentes, int* padres, int **matriz, vector <tuple<int,int> > aristas, int n){

	vector <int> resultado(n,-1);	 
	for(int i =0; i < inconsistentes.size();i++){
		if(inconsistentes[i]) padres[(int)get<0>(aristas[i])] = (int)get<0>(aristas[i]);
	} //cortamos las insconsistentes

	cout << "padres con aristas cortadas" << endl;
	for(int i =0; i <n;i++){
		cout << padres[i] << " "; 
	}
	cout << endl;

	int contador = 0;
	for(int i =0; i < n;i++){
		if(resultado[i] == -1) resultado[i] = contador;

		for(int j =0; j < n;j++){
			if (padres[j] == i && padres[j] != j){
				resultado[j] = resultado[i];
			}
		}
	contador++;
	}

	return resultado;
}




vector <int> calcAdyacentesA(int nodoInicial, int d, int* padres, int **matriz, int n){

		queue< tuple <int,int>> cola; // nodo, altura
	 	cola.push(make_tuple(nodoInicial,0));
	 	vector <int> aux;

	 	while(!cola.empty()){

	 		tuple <int, int> nodo = cola.front();
			cola.pop();

		    for(int j =0; j < n;j++){
		        if (padres[j] == (int)get<0>(nodo) && j != (int)get<0>(nodo)){
		        	if((int)get<1>(nodo) + 1 <= d) {
		        		cola.push(make_tuple(j, (int)get<1>(nodo) + 1));
		        		aux.push_back(matriz[(int)get<0>(nodo)][j]);
		        	}
		        }

		    }
		}

		cout << "[" ;
	  	for(int i =0; i <aux.size();i++){
			cout << aux[i] << " ";  // pesos adyacentes por d
		}
		cout << "]" << endl;
		return aux;
}


vector <int> calcAdyacentesB(int nodoInicial,int a, int d, int* padres, int **matriz, int n){


	 	queue< tuple <int,int>> cola; // nodo, altura
	 	cola.push(make_tuple(nodoInicial,0));
	 	vector <int> aux;

	 	while(!cola.empty()){

	 		tuple <int, int> nodo = cola.front();
			cola.pop();

		    for(int j =0; j < n;j++){
		        if (padres[j] == (int)get<0>(nodo) && j != a  && j != (int)get<0>(nodo)){
		        	if((int)get<1>(nodo) + 1 <= d) {
		        		cola.push(make_tuple(j, (int)get<1>(nodo) + 1));
		        		aux.push_back(matriz[(int)get<0>(nodo)][j]);
		        	}
		        }

		    }
		}

		queue< tuple <int,int>> cola2; // nodo, altura
	 	cola2.push(make_tuple(nodoInicial,0));

	 	while(!cola2.empty()){

	 		tuple <int, int> nodo = cola2.front();
			cola2.pop();


		    if((int)get<1>(nodo) + 1 <= d) {
		       	if (padres[(int)get<0>(nodo)] != (int)get<0>(nodo) ){

			       	if((int)get<1>(nodo) + 1 < d){
			       		cola2.push(make_tuple(padres[(int)get<0>(nodo)], (int)get<1>(nodo) + 1));// agregue el 3
		        		aux.push_back(matriz[(int)get<0>(nodo)][padres[(int)get<0>(nodo)]]);
			        	//cout << "agregue a la cola1 al " << padres[(int)get<0>(nodo)] << "," << (int)get<1>(nodo) + 1 << endl;
			        }

					for(int j =0; j < n;j++){
			        	if (padres[j] == padres[(int)get<0>(nodo)] && j != (int)get<0>(nodo) && j != padres[(int)get<0>(nodo)]){
			        		if((int)get<1>(nodo) + 1 <= d) {
			        			cola2.push(make_tuple(j, (int)get<1>(nodo) + 2));
			        			//cout << "agregue a la cola2 al " << j << "," << padres[(int)get<1>(nodo)] + 1 << endl;
			        			aux.push_back(matriz[j][padres[j]]);
			        		}
			        	}
			        }
			    }
		    }




	    }
	
		cout << "[" ;
	  	for(int i =0; i <aux.size();i++){
			cout << aux[i] << " ";  // pesos adyacentes por d
		}
		cout << "]" << endl;
		return aux;
}



float desvio(vector <int> vector){
	float suma;
	int n = vector.size();
	for(int i = 0; i < n; i++){
		suma = suma + vector[i];
	}
	float promedio = suma/n;
	float sigma;
	for(int i = 0; i < n; i++){
		sigma = sigma + ((vector[i] - promedio)*(vector[i] - promedio));
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

