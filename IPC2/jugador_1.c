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
	int     tirada, suma;
	int marcador1,marcador2;


	if ((JA1 = (sem_t*)sem_open("/JA1", 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}
  	if ((AJ1 = (sem_t*)sem_open("/AJ1", 0)) == SEM_FAILED) {
    	err_sys("semaphore initilization");
  	}

  	if ((jug1=open("./jugador1.txt",O_WRONLY|O_CREAT|O_TRUNC,0700)) < 0)
		err_sys("error de fitxer sortida");

	sem_post(AJ1);


	while(1){

		do{
			printf("Escriu el valor que creguis convenient: \n");
			scanf("%d",&tirada);

		}while(tirada>3);

		write(jug1,&tirada,sizeof(tirada));
		printf("Quina es la teva suma: \n");
		scanf("%d",suma);
		write(jug1,&suma,sizeof(int));
		close(jug1);


		sem_post(JA1);

		sem_wait(AJ1);

		jug1=open("/.jugador1.txt",O_RDONLY);

		marcador1=read(jug1,&marcador1,sizeof(int));
		marcador2=read(jug1,&marcador2,sizeof(int));

		if(marcador1==3 || marcador2==3) break;	
	}

	if (close(jug1)!=0) err_sys("error close write");
	if (sem_close(JA1)!=0) err_sys("error eliminacio semafor");
	if (sem_close(AJ1)!=0) err_sys("error eliminacio semafor");
	
	exit(0);


	return 0;
}
