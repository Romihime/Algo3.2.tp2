makefilemake: 
	g++ -g -std=c++11 -o tp2prim prim.cpp
	g++ -g -std=c++11 -o tp2kruskalcomun kruskalcomun.cpp
	
clean:
	rm tp2prim
	rm tp2kruskalcomun

test:
	#python generador.py > in
	./tp2prim < in
	./tp2kruskalcomun < in


