
all: wol

wol: main.o networking.o
	gcc obj/main.o obj/networking.o -o wol

main.o: src/main.c
	gcc -c src/main.c -o obj/main.o

networking.o: src/networking.c
	gcc -c src/networking.c -o obj/networking.o


clean:
	rm *.o
