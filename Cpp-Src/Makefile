default: main.o layer.o network.o node.o pipe.o state.o
	g++ -std=c++17 *.o

layer.o: egghead_comp.hpp
	g++ -std=c++17 -c layer.cpp

network.o: egghead_comp.hpp
	g++ -std=c++17 -c network.cpp

node.o: egghead_comp.hpp
	g++ -std=c++17 -c node.cpp

pipe.o: egghead_comp.hpp
	g++ -std=c++17 -c pipe.cpp

state.o: egghead_comp.hpp
	g++ -std=c++17 -c state.cpp

main.o: main.cpp
	clear
	g++ -std=c++17 -c main.cpp

clear:
	rm *.o
	rm a.out