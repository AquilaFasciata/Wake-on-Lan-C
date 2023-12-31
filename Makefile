
all: wol

wol: obj/main.o
	gcc obj/main.o -o wol

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

clean:
	rm *.o
