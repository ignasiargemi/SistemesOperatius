#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>


void err_sys(const char* cadena)
{
	perror(cadena);
	exit(1);
} 


int main()
{
	int 	jug2;
	sem_t* 	JA2;
	sem_t*	AJ2;	
	int 	jugador1, jugador2;
	int     tirada, suma;


	if ((JA2 = (sem_t*)sem_open("/JA2", 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}
  	if ((AJ2 = (sem_t*)sem_open("/AJ2", 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}

  	if ((jug2=open("./jugador2.txt",O_WRONLY|O_CREAT|O_TRUNC,0700)) < 0)
		err_sys("error de fitxer sortida");

	sem_post(JA2);

	close(jug2);


	while(1){
		sem_wait(AJ2);
		jug2 = open("./jugador2.txt", O_WRONLY|O_RDONLY, 0700);
		read(jug2, &jugador1, sizeof(jugador1));
		read(jug2, &jugador2, sizeof(jugador2));
		printf("Marcador: %i - ",&jugador1);
		printf("%i\n",&jugador2);
		if (jugador1 >= 3 || jugador2 >= 3) exit(0);
		do{
			printf("Escriu el valor de la teva tirada:\n(0-3)\n");
			scanf("%i",&tirada);

		}while(tirada>3 || tirada < 0);

		write(jug2,&tirada,sizeof(tirada));

		do {
			printf("Quina es la teva suma:\n(0-6)\n");
			scanf("%i",&suma);
		}while (suma < 0 || suma > 6);
		
		write(jug2,&suma,sizeof(suma));

		printf("Tirada: %i - Suma: %i\n", tirada, suma);
		
		close(jug2);

		sem_post(JA2);
	}

	if (close(jug2)!=0) err_sys("error close write");
	if (sem_close(AJ2)!=0) err_sys("error eliminacio semafor");
	if (sem_close(JA2)!=0) err_sys("error eliminacio semafor");
	
	exit(0);
}