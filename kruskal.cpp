#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector< tuple<int, int, int> > Kruskal(vector< tuple<int,int,int> >&, int);
bool comparacion(tuple<int,int,int> x, tuple<int,int,int> y);
int find(int* padres, int nodo);
void Unir(int* padres, int* altura, int x, int y);

int BFS(vector< vector <int> >&, int, int, int*);
int Master(int*, int, int);


int main(){
int auxBienPeola;
cin >> auxBienPeola;
    while( auxBienPeola != 0){
		int cantNodos;
		int cantAristas;
		cantNodos = auxBienPeola;
		cin >> cantAristas;


		vector< tuple<int,int,int> > Aristas;

		int i = 0;
		while(i < cantAristas){
			int nodo1, nodo2, peso;
			cin >> nodo1;
			cin >> nodo2;
			cin >> peso;
			tuple<int,int,int> arista = make_tuple(nodo1, nodo2, peso);
			Aristas.push_back(arista);
			i++;
		}

		vector< tuple<int,int,int> > res;
		int res1 = 0;
		int res2 = 0;
		int res3 = 0;
		
		vector< vector<int> > lista;
		for(int j = 0; j < cantNodos; j++){
			vector<int> aux;
			lista.push_back(aux);
		}	

		high_resolution_clock::time_point t1 = high_resolution_clock::now();

		res = Kruskal(Aristas, cantNodos);

		for(int i = 0; i < res.size(); i++){
			int padre = (int)get<0>(res[i]);
			int hijo = (int)get<1>(res[i]);
			lista[padre].push_back(hijo);
			lista[hijo].push_back(padre);
		}

		int* padres = new int[cantNodos];
		res1 = BFS(lista,0, cantNodos, padres);
		res2 = BFS(lista,res1,cantNodos,padres);
		
		res3 = Master(padres, res1, res2);
		
		int aux = 0;
		for(int i = 0; i<res.size();i++){
			aux = aux + get<2>(res[i]);
		}
		
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
		//cout << time_span1.count() << endl; 

		cout << aux << " " << res3 << " " <<res.size() << " ";

		for(int i = 0; i<res.size();i++){	
			cout << get<0>(res[i]) << " " << get<1>(res[i]) << " ";
		}
		cout << endl;
		cin >> auxBienPeola;
    }
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


int BFS(vector< vector <int> >& lista, int nodoInicio, int cantNodos, int* padres){
	queue<int> cola;
	int visitados[cantNodos];
	int i =0;
	int res = 0;

	while(i < cantNodos){
		visitados[i] = false;
		i++;
	}

	cola.push(nodoInicio);
	visitados[nodoInicio] = true;
	padres[nodoInicio] = 0;

	while(!cola.empty()){
		int aux = cola.front();
		cola.pop();
		if(cola.empty()){
			res = aux;
		}
		int i = 0;
		while(i < lista[aux].size()){
			if(visitados[lista[aux][i]] == false){
				visitados[lista[aux][i]] = true;
				cola.push(lista[aux][i]);
				padres[lista[aux][i]] = aux;
			}
			i++;
		}
	}
	return res;
}

int Master(int* padres, int e1, int e2){
	int aux = e2;
	int contador = 1;
	while (aux != e1){
		aux = padres[aux];
		contador++;
	}

	aux = e2;
	int i = 1;
	if(contador%2 == 0){
		contador = contador/2;
	}else{
		contador = (contador+1)/2;
	}
	while(i < contador){
		aux = padres[aux];
		i++;
	}
	return aux;
}

    © 2018 GitHub, Inc.
    Terms
    Privacy
    Security
    Status
    Help

    Contact GitHub
    Pricing
    API
    Training
    Blog
    About

Press h to open a hovercard with more details.
