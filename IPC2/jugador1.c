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
	int 	jug1,llegeix;
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
		jug1 = open("./jugador1.txt", O_WRONLY|O_RDONLY, 0700);
		llegeix = read(jug1, &jugador1, sizeof(jugador1));
		llegeix = read(jug1, &jugador2, sizeof(jugador2));
		if (jugador1 >= 3 || jugador2 >= 3) exit(0);
		do{
			printf("Escriu el valor que creguis convenient:\n(0-3)\n");
			scanf("%d",&tirada);

		}while(tirada>3 && tirada < 0);

		write(jug1,&tirada,sizeof(tirada));

		do {
			printf("Quina es la teva suma:\n(0-6)\n");
			scanf("%d",&suma);
		}while (suma < 0 && suma > 6);
		
		write(jug1,&suma,sizeof(int));
		
		close(jug1);

		sem_post(JA1);
	}

	if (close(jug1)!=0) err_sys("error close write");
	if (sem_close(AJ1)!=0) err_sys("error eliminacio semafor");
	if (sem_close(JA1)!=0) err_sys("error eliminacio semafor");
	
	exit(0);
	return 0;
}