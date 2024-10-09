default: main.c
	gcc main.c -o hexpro

test: main.c
	gcc main.c -o hexpro -g2
	rm -f out.txt
	./hexpro main.c
	vim out.txt

clean:
	rm hexpro
