#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <string.h>

int main() {
	int 	file_write,file_read,n;
	int 	input;
	char 	buffer[10+2];
	int 	numero_linea_entrada=0;
	sem_t* 	e1;
	sem_t*	e2;
	sem_t* 	l1;
	sem_t*	l2;
	int jugador1=0;
	int jugador2=0;

	



}