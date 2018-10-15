all: 
	g++ -g -std=c++11 -o tp2prim prim.cpp
	g++ -g -std=c++11 -o tp2kruskal kruskal.cpp
	g++ -g -std=c++11 -o tp2kruskalpc kruskalpc.cpp

	#python generador.py > in
	./tp2prim < in
	./tp2kruskal < in
	./tp2kruskalpc < in
	
clean:
	rm tp2prim
	rm tp2kruskal
	rm tp2kruskalpc





