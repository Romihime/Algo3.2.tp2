#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <tuple>
#include <math.h>
#include <queue>
#include <algorithm>

#define INF 21474836 
int cantidadDeNodos;

using namespace std;
using namespace std::chrono;

vector< vector<int> > kruskal(vector< vector<int> > ady, int cn);
void pasarMatriz( vector< vector<int> > res, int* padres, int n);
vector<int> clusterizar(vector <bool> inconsistentes, int* padres, vector <pair<int,int> > aristas, int n);
vector <int> calcAdyacentesA(int nodoInicial, int d, int* padres, vector <vector <int>> matriz, int n);
vector <int> calcAdyacentesB(int nodoInicial, int a, int d, int* padres, vector <vector <int>> matriz, int n);
float desvio(vector <int> vector);
float promedio(vector <int> vector);
void printVectorPuntos(vector < pair<int,int> >  vector);
void printVector(vector < int >  vector);
void printVectorPadres(int*  vector);
void printMatriz(vector< vector<int> >  matriz);



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
        puntos.push_back(make_pair(x,y)); //Cargamos la entrada 
    }

    //cout << "Puntos" << endl;
    //printVectorPuntos(puntos);    

    vector< vector<int> > matriz(n);

    for(int i = 0; i < n; i++){
        matriz[i].resize(n); // inicializamos la matriz
    }
    

   for(int i = 0; i < n; i++){
       for(int j = 0; j < n; j++){
            matriz[i][j] = abs( puntos[i].first - puntos[j].first) + abs(puntos[i].second - puntos[j].second);
        } // calculamos la distancia entre todos los puntos y los colocamos en la matriz
    }

    printMatriz(matriz);
    vector< vector<int> > res  = kruskal(matriz, n); // ------------------------- KRUSKAL ---------------------------------------------------
    //printMatriz(res);

    int* padres = new int[n];
    pasarMatriz(res, padres, n); //lo pasamos de matriz de adyacencias a vector de padres.

    cout << "Padres" << endl;
    printVectorPadres(padres);

    vector <pair<int,int>> aristas;
    for(int i = 0; i < n; i++){
        if(i != padres[i]) aristas.push_back(make_pair(i,padres[i])); // Creamos un vector de aristas
    }

    cout << "Aristas" << endl;
    printVectorPuntos(aristas);

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

void printVectorPadres(int*  vector){
    for(int i =0; i < cantidadDeNodos;i++){
        cout << vector[i] << " ";  // este vector es el de padres de cada nodo 
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



vector< vector<int> > kruskal(vector< vector<int> > ady, int cn){
    vector< vector<int> > adyacencia = ady;
    vector< vector<int> > arbol(cn);
    vector<int> pertenece(cn); // indica a que árbol pertenece el nodo

    for(int i = 0; i < cn; i++){
        arbol[i] = vector<int> (cn, 0);
        pertenece[i] = i;
    }

    int nodoA;
    int nodoB;
    int arcos = 1;
    while(arcos < cn){
        // Encontrar  el arco mínimo que no forma ciclo y guardar los nodos y la distancia.
        int min = INF;
        for(int i = 0; i < cn; i++)
            for(int j = 0; j < cn; j++)
                if(min > adyacencia[i][j] && adyacencia[i][j]!=0 && pertenece[i] != pertenece[j]){
                    min = adyacencia[i][j];
                    nodoA = i;
                    nodoB = j;
                }

        // Si los nodos no pertenecen al mismo árbol agrego el arco al árbol mínimo.
        if(pertenece[nodoA] != pertenece[nodoB]){
            arbol[nodoA][nodoB] = min;
            arbol[nodoB][nodoA] = min;

            // Todos los nodos del árbol del nodoB ahora pertenecen al árbol del nodoA.
            int temp = pertenece[nodoB];
            pertenece[nodoB] = pertenece[nodoA];
            for(int k = 0; k < cn; k++)
                if(pertenece[k] == temp)
                    pertenece[k] = pertenece[nodoA];

            arcos++;
        }
    }
    return arbol;
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




vector <int> calcAdyacentesA(int nodoInicial, int d, int* padres, vector <vector <int>> matriz, int n){

        queue< pair <int,int>> cola; // nodo, altura
        cola.push(make_pair(nodoInicial,0));    // coloco en la cola al nodo inicial
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


vector <int> calcAdyacentesB(int nodoInicial,int a, int d, int* padres, vector <vector <int>> matriz, int n){

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