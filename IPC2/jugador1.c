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
	int 	jug1;
	sem_t* 	JA1;
	sem_t*	AJ1;	
	int 	jugador1, jugador2;
	int     tirada, suma;


	if ((JA1 = (sem_t*)sem_open("/JA1", 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}
  	if ((AJ1 = (sem_t*)sem_open("/AJ1", 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}

  	if ((jug1=open("./jugador1.txt",O_WRONLY|O_CREAT|O_TRUNC,0700)) < 0)
		err_sys("error de fitxer sortida");

	sem_post(JA1);

	close(jug1);


	while(1){
		sem_wait(AJ1);
		jug1 = open("./jugador1.txt",O_RDONLY, 0);
		read(jug1, &jugador1, sizeof(jugador1));
		read(jug1, &jugador2, sizeof(jugador2));
		printf("Marcador: %i - ",jugador1);
		printf("%i\n",jugador2);
		close(jug1);
		if (jugador1 >= 3 || jugador2 >= 3) exit(0); //Final
		jug1 = open("./jugador1.txt",O_WRONLY, 0700);
		do{
			printf("Escriu el valor de la teva tirada:\n(0-3)\n");
			scanf("%i",&tirada);

		}while(tirada>3 || tirada < 0);

		write(jug1,&tirada,sizeof(tirada));

		do {
			printf("Quina es la teva suma/aposta:\n(0-6)\n");
			scanf("%i",&suma);
		}while (suma < 0 || suma > 6);
		
		write(jug1,&suma,sizeof(suma));

		printf("Tirada: %i - Suma: %i\n", tirada, suma);
		
		close(jug1);

		sem_post(JA1);
	}

	if (close(jug1)!=0) err_sys("error close write");
	if (sem_close(AJ1)!=0) err_sys("error eliminació semàfor");
	if (sem_close(JA1)!=0) err_sys("error eliminació semàfor");
	
	exit(0);
}