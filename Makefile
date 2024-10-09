default: main.c
	gcc main.c -o hexpro

test: main.cpp
	g++ main.cpp -o hexpro
	./hexpro main.cpp

htest: main.cpp
	g++ main.cpp -o hexpro
	./hexpro -h

ltest: main.cpp
	g++ main.cpp -o hexpro
	./hexpro main.cpp -l 4

otest: main.cpp
	g++ main.cpp -o hexpro
	./hexpro main.cpp -o out.txt

clean:
	rm hexpro
