#define _REENTRANT
#include<stdio.h>
#include<ncurses.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
struct Competidor {
	char caracter[2];
	int linea;	
};

void* jugarCarrera(void*);

char* ganador = "-";

int main() {
	srand(time(NULL));
	initscr();
	raw();
	struct Competidor competidor[8];
	int i;
	char competidores[8] = {'a','b','c','d','z','x','y','0'}; // Arreglo con los posibles competidores de la carrera.
	pthread_t id[8];
	int tamanoLinea = 30;
	int numeroCompetidores = 2 + rand()%7; // Generar una cantidad aleatoria de jugadores entre 0 y 8
	for(i = 0; i < tamanoLinea; i++) {
		mvprintw(i,0,"| |"); // Se imprime la linea de meta.
	}
	for(i = 1; i <= numeroCompetidores*2;i+=2) mvprintw(i,3,"-------------------------------------------------------------------------------------------");
	int inicioTexto = tamanoLinea/3;
	mvprintw(inicioTexto,1,"M");
	mvprintw(inicioTexto+2,1,"E");
	mvprintw(inicioTexto+4,1,"T");
	mvprintw(inicioTexto+6,1,"A");
	refresh();
	for(i = 0; i < numeroCompetidores; i++) {
		competidor[i].caracter[0] = competidores[rand()%8];
		competidor[i].caracter[1] = '\0';
		competidor[i].linea = i*2;
		if(pthread_create(&id[i],NULL,jugarCarrera,(void*)&competidor[i]) != 0) {
			fprintf(stderr,"Error al crear el hilo");
		}
	}
	printf("\n");
	while(*ganador == '-'); // esperar a que haya un ganador en la carrera.
	mvprintw(tamanoLinea,0,"Felicidades el ganador fue %s!!\n",ganador);
	refresh();
	endwin();
	return 0;
}

void* jugarCarrera(void* jugador) {
	struct Competidor *competidor = (struct Competidor*) jugador;
	int pos = 80,posAnterior=pos+1;
	while(pos > 0) {
		mvprintw(competidor->linea,pos,competidor->caracter); // imprime el caracter en la posicion actual.
		posAnterior = pos;
		refresh();
		pos -= 1 + rand()%15;
		sleep(1+rand()%5);
		mvprintw(competidor->linea,posAnterior," "); // borra el caracter de la iteracion anterior.
	}
	mvprintw(competidor->linea,0,competidor->caracter);
	ganador = (char*) competidor->caracter;
	return (void*) NULL;
}
