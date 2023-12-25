output: main.o
	gcc main.o -o wol

main.o: main.c
	gcc -c main.c

clean:
	rm *.o
