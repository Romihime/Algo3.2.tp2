#include "ej1.h"
 
#define edge pair<int,int>

void printVectorPadres(int*  vector);
vector <int> calcAdyacentesA(int nodoInicial, int d, int* padres, vector <vector <int>> matriz, int n);
vector <int> calcAdyacentesB(int nodoInicial, int a, int d, int* padres, vector <vector <int>> matriz, int n);
int cantidadDeNodos;


 
class Graph {
private:
    vector<pair<int, edge>> G; // graph
    vector<pair<int, edge>> T; // mst
    int *parent;
    int V; // number of vertices/nodes in graph
public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
    void pasarAPadres(int* padres);
};






Graph::Graph(int V) {
    parent = new int[V];
 
    //i 0 1 2 3 4 5
    //parent[i] 0 1 2 3 4 5
    for (int i = 0; i < V; i++)
        parent[i] = i;
 
    G.clear();
    T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent
        return find_set(parent[i]);
}
 
void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}
void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end()); // increasing weight
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]); // add to tree
            union_set(uRep, vRep);
        }
    }
}
void Graph::print() {
    cout << "Edge :" << " Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : " << T[i].first << endl;
    }
}


void Graph::pasarAPadres(int* padres){

    for(int i = 0; i < cantidadDeNodos; i++){
        padres[i] = -1;
    }
    padres[0] = 0;
    queue <int> cola;
    cola.push(0); // la raiz es el 0

    while(!cola.empty()){
        int nodo = cola.front();  //  peso arista1 arista2
        cola.pop();

        for(int i = 0; i < cantidadDeNodos; i++){
            if (T[i].second.first == nodo && padres[T[i].second.second] == -1){
                padres[T[i].second.second] = nodo;
                cola.push(T[i].second.second);
            }

            if (T[i].second.second == nodo && padres[T[i].second.first] == -1){
                padres[T[i].second.first] = nodo;
                cola.push(T[i].second.first);
            }
        }          
    }

}



int main() {

    int n ;
    cin >> n;
    cantidadDeNodos = n;
    Graph g(n);
    int x;
    int y;
    vector < pair<int,int> > puntos;

    for(int i = 0; i < n; i++){
        cin >> x;
        cin >> y;
        puntos.push_back(make_pair(x,y)); //ya cargue la entrada 
    }
    


    for(int i = 0; i < n; i++){
       for(int j = 0; j < n && j!=i; j++){
        g.AddWeightedEdge(i, j, abs( puntos[i].first - puntos[j].first) + abs(puntos[i].second - puntos[j].second));
        } // calculamos la distancia entre todos los puntos y los colocamos en la matriz
    }

    g.kruskal();
    //g.print();

    int* padres = new int[n];

    g.pasarAPadres(padres);
    printVectorPadres(padres); //----------------------------------------------------------------------------

    vector< vector<int> > matriz(n);

    for(int i = 0; i < n; i++){
        matriz[i].resize(n); // inicializamos la matriz
    }
    

   for(int i = 0; i < n; i++){
       for(int j = 0; j < n; j++){
            matriz[i][j] = abs( puntos[i].first - puntos[j].first) + abs(puntos[i].second - puntos[j].second);
        } // calculamos la distancia entre todos los puntos y los colocamos en la matriz
    }


    vector <pair<int,int>> aristas;
    for(int i = 0; i < n; i++){
        if(i != padres[i]) aristas.push_back(make_pair(i,padres[i])); // Creamos un vector de aristas
    }

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

    vector<int> resultados = clusterizar(inconsistentes, padres, aristas, n);
    cout << "Resultado" << endl;
    printVector(resultados);

    return 0;
}



void printVectorPadres(int*  vector){
    for(int i =0; i < cantidadDeNodos ;i++){
        cout << vector[i] << " ";  // este vector es el de padres de cada nodo 
    }
    cout << endl;
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
