default: main.cpp
	g++ main.cpp -o hexpro

test: main.cpp
	g++ main.cpp -o hexpro
	./hexpro main.cpp

htest: main.cpp
	g++ main.cpp -o hexpro
	./hexpro -h
