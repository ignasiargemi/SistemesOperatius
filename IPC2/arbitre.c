#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <string.h>

void err_sys(const char* cadena)
{
	perror(cadena);
	exit(1);
} 

int main() {
	int 	jug1, jug2;
	char 	buffer[10+2];
	int 	numero_linea_entrada=0;
	sem_t* 	AJ1;
	sem_t*	AJ2;
	sem_t* 	JA1;
	sem_t*	JA2;
	int jugador1=0;
	int jugador2=0;

	if ((AJ1 = (sem_t*)sem_open("/AJ1", O_CREAT, 0644, 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}
 	if ((JA1 = (sem_t*)sem_open("/JA1", O_CREAT, 0644, 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}
  	if ((AJ2 = (sem_t*)sem_open("/AJ2", O_CREAT, 0644, 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}
 	if ((JA2 = (sem_t*)sem_open("/JA2", O_CREAT, 0644, 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}
  	printf("Inicialitzat\n");

  	sem_wait(JA1);
  	printf("Jugador 1 a punt\n");

  	jug1 = open("jug1.txt", O_WRONLY|O_TRUNC, 0644);

  	sem_wait(JA2);
  	printf("Jugador 2 a punt\n");

  	jug2 = open("jug2.txt", O_WRONLY|O_TRUNC, 0644);

  	write(jug1, &jugador1, jugador1);
  	write(jug1, &jugador2, jugador2);

  	write(jug2, &jugador1, jugador1);
  	write(jug2, &jugador2, jugador2);

  	close(jug1);
  	close(jug2);

  	sem_post(AJ1);
  	sem_post(AJ2);

  	while (1) {
  		if (jugador1 >= 3 || jugador2 >= 3) exit(0);
  		sem_wait(JA1);
  		//Read
  		sem_wait(JA2);
  		//Read


  	}

	//Close
	if (sem_close(AJ1)!=0) err_sys("error eliminacio semafor");
	if (sem_close(AJ2)!=0) err_sys("error eliminacio semafor");
	if (sem_close(JA1)!=0) err_sys("error eliminacio semafor");
	if (sem_close(JA2)!=0) err_sys("error eliminacio semafor");
	printf("Final\n");
}