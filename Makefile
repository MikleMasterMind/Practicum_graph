a.out: main.o algorithm.o graph.o
	gcc main.o algorithm.o graph.o

main.o: main.c
	gcc -c main.c

algorithm.o: ./sourse/algorithm.c
	gcc -c ./sourse/algorithm.c

graph.o: ./sourse/graph.c
	gcc -c ./sourse/graph.c

clean:
	rm -rf *.o a.out