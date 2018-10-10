makefilemake: 
	g++ -g -std=c++11 -o tp2prim prim.cpp
	
clean:
	rm tp2prim

test:
	#python generador.py > in
	./tp2prim < in

