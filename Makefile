CFLAGS = -Og -g

all: wol

wol: obj/main.o obj/networking.o
	gcc $(CFLAGS) obj/main.o obj/networking.o -o wol

obj/main.o: src/main.c
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

obj/networking.o: src/networking.c
	gcc $(CFLAGS) -c src/networking.c -o obj/networking.o


clean:
	rm *.o
