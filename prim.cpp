#include "ej1.h"


int cantidadDeNodos;

void Prim (vector <vector<int>> matriz, int nodo, int cantNodos, int *res);
vector <int> calcAdyacentesA(int nodoInicial, int d, int* padres, vector <vector<int>> matriz, int n);
vector <int> calcAdyacentesB(int nodoInicial, int a, int d, int* padres, vector <vector<int>> matriz, int n);
void printVectorPadres(int*  vector);



//Parametros a modificar para experimentar:
//d, cantidad de desvios, inconsistencia doble, f sub t


int main(){
	int n ;
	cin >> n;
	cantidadDeNodos = n;
    int x;
    int y;
    vector < pair<int,int> > puntos;

    for(int i = 0; i < n; i++){
    	cin >> x;
    	cin >> y;
    	puntos.push_back(make_pair(x,y)); 
    }

	

    vector< vector<int> > matriz(n);

    for(int i = 0; i < n; i++){
        matriz[i].resize(n); // inicializamos la matriz
    }

   for(int i = 0; i < n; i++){
       for(int j = 0; j < n; j++){
            matriz[i][j] = abs( puntos[i].first - puntos[j].first) + abs(puntos[i].second - puntos[j].second);
        } // calculamos la distancia entre todos los puntos y los colocamos en la matriz
    }


    int* padres = new int[n];

    Prim(matriz, 0, n, padres); // ------------------------- PRIM ---------------------------------------------------

	cout << "Padres" << endl;
	printVectorPadres(padres);

	vector <pair<int,int>> aristas;
	for(int i = 0; i < n; i++){
		if(i != padres[i]) aristas.push_back(make_pair(i,padres[i])); // Creamos un vector de aristas
	}

	//cout << "Aristas" << endl;
	//printVectorPuntos(aristas);

	/*cout << "Pesos" << endl;
	for(int i =0; i <aristas.size();i++){
		cout << "(" << matriz[aristas[i].first][aristas[i].second] << ")" << " ";  // esto es para ver el peso de cada arista
	}
	cout << endl;*/

	vector <bool> inconsistentes(aristas.size(),0); // Creamos un vector de bools
    int d = 2;

    for(int p = 0; p < aristas.size(); p++){
        int a = aristas[p].first;
        int b = aristas[p].second;

        int PesoDeAristaAAnalizar = matriz[a][b];

        vector <int> adyA = calcAdyacentesA(a,2,padres,matriz,n); // el vector de los pesos de los adyacentes con distancia d hacia A
        vector <int> adyB = calcAdyacentesB(b,a,2,padres,matriz,n); // el vector de los pesos de los adyacentes con distancia d hacia B

        float promA = promedio(adyA);
        float promB = promedio(adyB);

       	//inconsistentes[p] = (((PesoDeAristaAAnalizar / promA) > 2*desvio(adyA))  && ((PesoDeAristaAAnalizar / promB) > 2*desvio(adyB))) ? 1 : 0; // criterio del desvio
       	inconsistentes[p] = (((PesoDeAristaAAnalizar / promA) > 1)  && ((PesoDeAristaAAnalizar / promB) > 1)) ? 1 : 0; // criterio con fsubt
	}

	/*cout << "aristas inconsistentes?" << endl;
	for(int i =0; i < inconsistentes.size();i++){
		cout << inconsistentes[i] << " ";  // esto es para ver si hay inconsistentes
	}
	cout << endl;*/


    vector<int> resultados = clusterizar(inconsistentes, padres, aristas, n);
    cout << "Resultado" << endl;
	printVector(resultados);


    delete[] padres;
    return 0;
}



void printVectorPadres(int*  vector){
    for(int i =0; i < cantidadDeNodos ;i++){
		cout << vector[i] << " ";  // este vector es el de padres de cada nodo 
	}
	cout << endl;
}


vector <int> calcAdyacentesA(int nodoInicial, int d, int* padres, vector <vector<int>> matriz, int n){

		queue< pair <int,int>> cola; // nodo, altura
	 	cola.push(make_pair(nodoInicial,0));	// coloco en la cola al nodo inicial
	 	vector <int> aux; // es el vector de pesos resultado

	 	while(!cola.empty()){

	 		pair <int, int> nodo = cola.front(); // tomo el nodo y su altura 
			cola.pop();

		    for(int j =0; j < n;j++){
		        if (padres[j] == nodo.first && j != nodo.first){ // busco a sus hijos 
		        	if(nodo.second + 1 <= d) { // si su hijo no supera d de distancia
		        		cola.push(make_pair(j, nodo.second + 1)); // lo coloco en la cola con una altura mayor
		        		aux.push_back(matriz[nodo.first][j]); // y guardo el peso de la arista padre-hijo
		        	}
		        }

		    }
		}

		/*cout << "[" ;
	  	printVector(aux); // pesos de las aristas adyacentes a A de distancia d
		cout << "]" << endl;*/
		return aux;
}


vector <int> calcAdyacentesB(int nodoInicial,int a, int d, int* padres, vector <vector<int>> matriz, int n){

 	queue< pair <int,int>> cola; // nodo, altura
 	cola.push(make_pair(nodoInicial,0));
 	vector <int> aux;

 	while(!cola.empty()){
 		pair <int, int> nodo = cola.front();
		cola.pop();

	    for(int j =0; j < n;j++){
	        if (padres[j] == nodo.first && j != a  && j != nodo.first){ //para b, por como el grafo es dirigido y 0 es la raiz siempre,
	        	if(nodo.second + 1 <= d) { //  busco los hijos de B primero, que no sean a y no superen la distancia d
	        		cola.push(make_pair(j, nodo.second + 1)); // los pusheo en la cola, y en el vector resultado
	        		aux.push_back(matriz[nodo.first][j]);
	        	}
	        }
	    }
	}

	queue< pair <int,int>> cola2; // nodo, altura
 	cola2.push(make_pair(nodoInicial,0)); // creo una 2da cola para los d padres de B y los hijos de estos ultimos

 	while(!cola2.empty()){
 		pair <int, int> nodo = cola2.front();
		cola2.pop();

		if (padres[nodo.first] != nodo.first ){
		    if(nodo.second + 1 < d) {
		       	cola2.push(make_pair(padres[nodo.first], nodo.second + 1));//  agrego a los d padres de B
	        	aux.push_back(matriz[nodo.first][padres[nodo.first]]);

				for(int j =0; j < n;j++){
		        	if (padres[j] == padres[nodo.first] && j != nodo.first && j != padres[nodo.first]){
		        		if(nodo.second + 2 >= d) { // la altura del hijo
		        			aux.push_back(matriz[j][padres[j]]); // aca agrego a los hijos de los padres de B que no sean B
		        		}else{
		        			cola2.push(make_pair(j, nodo.second + 2));
		        			aux.push_back(matriz[j][padres[j]]);
		        		}
		        	}
		        }
		    }else{
	    		aux.push_back(matriz[nodo.first][padres[nodo.first]]);
		    }
	    }
    }

	/*cout << "[" ;
  	printVector(aux); // Esto nos muestra los pesos de los adyacentes de distancia d a B 
	cout << "]" << endl;*/
	return aux;
}






void Prim (vector <vector<int>> matriz, int nodo, int cantNodos, int *res){
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
        res[i] = padres[i];
        i++;
    }
}




