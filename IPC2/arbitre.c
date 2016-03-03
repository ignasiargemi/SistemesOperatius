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
	sem_t* 	psemafor_anada;
	sem_t*	psemafor_tornada;	
	int 	valor_semaforo;



}