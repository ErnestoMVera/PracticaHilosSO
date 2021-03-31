#define _REENTRANT
#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

#define MAX 5
#define TRAND(limit,n) { struct timeval t; \
			gettimeofday(&t,(void *) NULL);\
			(n) = rand_r((unsigned *) &t.tv_usec) % (limit)+1; }
#include<ncurses.h>
void* say_it(void *);
int main(int argc,char* argv[])
{
	initscr();
	raw();
	int i;
	pthread_t thread_id[MAX];
	int status, *p_status = &status;
	if(argc>MAX+1) {
		fprintf(stderr, "%s arg1,arg2,arg3,arg4... arg%d\n",*argv,MAX);
		exit(1);
	}
	printf("Creando hilo\n");
	for(i=0;i<argc-1;++i) {
		if(pthread_create(&thread_id[i],NULL,say_it,(void*)argv[i+1]) > 0) {
			fprintf(stderr,"pthread_create failure");
			exit(2);
		}
		printf("Creando hilo %u",(unsigned)thread_id[i]);
	}
	sleep(5);
	printf("\nTermina\n");
	exit(0);
}
void* say_it(void *word) {
	int i,numb;
	TRAND(MAX,numb);
	initscr();
	raw();
	int j;
	for(j=0;j < 7; j++) {
		mvprintw(j+numb,10+numb,"%s",word);
		refresh();
		usleep(1000000);
	}
	endwin();
	return (void*) NULL;
}
