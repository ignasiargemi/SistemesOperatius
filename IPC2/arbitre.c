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
	sem_t* 	AJ1;
	sem_t*	AJ2;
	sem_t* 	JA1;
	sem_t*	JA2;
	int jugador1=0;
	int jugador2=0;
	int suma1, tirada1;
	int suma2, tirada2;

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
  		printf("El marcador és de %i a %i\n",jugador1,jugador2);
  		if (jugador1 >= 3 || jugador2 >= 3) exit(0);
  		jug1 = open("jug1.txt", O_WRONLY|O_RDONLY, 0644);
		jug2 = open("jug2.txt", O_WRONLY|O_RDONLY, 0644);
  		sem_wait(JA1);
  		//Read
  		read(jug1, &tirada1, sizeof(tirada1));
		read(jug1, &suma1, sizeof(suma1));
		printf("Jugador 1: %i - %i\n", &tirada1,&suma1);
  		sem_wait(JA2);
  		//Read
  		read(jug2, &tirada2, sizeof(tirada2));
		read(jug2, &suma2, sizeof(suma2));
		printf("Jugador 2: %i - %i\n", &tirada2,&suma2);

  		if ((tirada1+tirada2) == suma1) ++jugador1;
  		if ((tirada1+tirada2) == suma2) ++jugador2;

		write(jug1, &jugador1, jugador1);
		write(jug1, &jugador2, jugador2);
		write(jug2, &jugador1, jugador1);
		write(jug2, &jugador2, jugador2);

		close(jug1);
	  	close(jug2);

	  	sem_post(AJ1);
	  	sem_post(AJ2);
  	}

  	//Enunci del guanyador
  	if (jugador1 == 3 && jugador2 == 3) printf("Hi ha hagut un empat!\n");
  	else if (jugador1 > jugador2) printf("Ha guanyat el jugador 1!\n");
  	else printf("Ha guanyat el jugador 2!\n");

	//Close
	if (sem_close(AJ1)!=0) err_sys("error eliminacio semafor");
	if (sem_close(AJ2)!=0) err_sys("error eliminacio semafor");
	if (sem_close(JA1)!=0) err_sys("error eliminacio semafor");
	if (sem_close(JA2)!=0) err_sys("error eliminacio semafor");
	printf("Final\n");
	exit(0);
}