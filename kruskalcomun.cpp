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

using namespace std;
using namespace std::chrono;

vector< vector<int> > kruskal(vector< vector<int> > ady, int cn);
void printMatriz(vector< vector<int> >  matriz);



int main(){
    int n ;
    cin >> n;
    int x;
    int y;
    vector < pair<int,int> > puntos;

    for(int i = 0; i < n; i++){
        cin >> x;
        cin >> y;
        puntos.push_back(make_pair(x,y));
    }

    cout << "Puntos" << endl;
    for(int i =0; i <n;i++){
        cout << "(" << puntos[i].first << "," << puntos[i].second << ")" << " ";  // esto es para ver los puntos
    }
    cout << endl;

    //ya cargue la entrada 

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
    
    vector< vector<int> > res  = kruskal(matriz, n);

    printMatriz(res);

    return 0;
}



//matriz de adyacencia - > padres


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


void printMatriz(vector< vector<int> >  matriz){
    for(int i = 0; i < matriz[0].size(); i++){
       for(int j = 0; j < matriz[0].size(); j++){
            cout << matriz[i][j] << " " ;
        }
        cout << endl;
    }
    cout << endl;
}