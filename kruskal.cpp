#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <tuple>
#include <math.h>
#include <queue>
#include <algorithm>


using namespace std;
using namespace std::chrono;

vector< tuple<int, int, int> > Kruskal(vector< tuple<int,int,int> >&, int);
bool comparacion(tuple<int,int,int> x, tuple<int,int,int> y);
int find(int* padres, int nodo);
void Unir(int* padres, int* altura, int x, int y);

int BFS(vector< vector <int> >&, int, int, int*);
int Master(int*, int, int);


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

	vector< tuple<int,int,int> > aristas;

	for(int i = 0; i < n; i++){
       for(int j = 0; j < n; j++){
		tuple<int,int,int> arista = make_tuple(i, j, abs( puntos[i].first - puntos[j].first) + abs(puntos[i].second - puntos[j].second));
		aristas.push_back(arista);
        } // calculamos la distancia entre todos los puntos y los colocamos en la matriz
    }

	vector< tuple<int,int,int> > res;
	res = Kruskal(aristas, n);

	vector <pair<int,int>> ejesAnalizar;
	for(int i = 0; i < n; i++){
		ejesAnalizar.push_back(make_pair(get<0>(aristas[i]),get<1>(aristas[i]))); // Creamos un vector de aristas
	}	

	cout << "Aristas" << endl;
	for(int i =0; i <aristas.size();i++){
		cout << "(" << get<0>(aristas[i]) << "," << get<1>(aristas[i]) << ")" << " ";  // esto es para ver las aristas
	}
	cout << endl;



	return 0;
}

vector< tuple <int, int, int> > Kruskal(vector< tuple<int,int,int> >& Aristas, int cantNodos){

	int* Padres = new int[cantNodos];
	int* Altura = new int[cantNodos];

	for(int i = 0; i < cantNodos; i++){
		Padres[i] = i;
		Altura[i] = 1;
	}

	vector< tuple<int,int,int> > Sol;
	sort(Aristas.begin(), Aristas.end(), comparacion); //O(m log m) = O(m log n)

	for(int i = 0; i < Aristas.size(); i++){
		if(find(Padres, get<0>(Aristas[i])) != find(Padres, get<1>(Aristas[i]))){
			tuple<int, int, int> arista = make_tuple(get<0>(Aristas[i]), get<1>(Aristas[i]), get<2>(Aristas[i]));
			Sol.push_back(arista);
			Unir(Padres, Altura, get<0>(Aristas[i]), get<1>(Aristas[i]));
		}
	}

	delete[] Padres;
	delete[] Altura;

	return Sol;
}

bool comparacion(tuple<int,int,int> x, tuple<int,int,int> y){
	return (get<2>(x) < get<2>(y));
}

int find(int* padres, int nodo){
	if(nodo != padres[nodo]){
		padres[nodo] = find(padres, padres[nodo]);
	}
	return padres[nodo];
}

void Unir(int* padres, int* altura, int x, int y){
	int nodo1 = find(padres, x);
	int nodo2 = find(padres, y);

	if(altura[nodo1] < altura[y]){
		padres[nodo1] = nodo2;
	}else{
		padres[nodo2] = nodo1;
	}

	if(altura[nodo1] == altura[nodo2]){
		altura[nodo1] = altura[nodo1] + 1; 
	}
}
