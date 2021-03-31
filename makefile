carrera: carrera.c
	gcc $(CFLAGS) -o carrera carrera.c -lpthread -lncurses
clear:
	rm *.o carrera
