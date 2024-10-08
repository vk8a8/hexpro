default: main.cpp
	g++ main.cpp -o hexpro

test: main.cpp
	g++ main.cpp -o hexpro -g2

clean:
	rm hexpro
