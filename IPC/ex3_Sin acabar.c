
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# define SIZE 100

int main(){
 	
	pid_t pid;
	int a[2], b[2],f, nbytes,s;
	char buffer[SIZE], entrada[SIZE], sortida[SIZE];
	pipe(a);
	pipe(b);

	printf("Digam el nom de fitxer\n");
	scanf("%s", entrada);
	strcat(entrada,".txt");

	if ((pid=fork())==-1)
	{
		perror("Error en el fork");
		exit(0);
	}

	if (pid==0)
	{//Hijo
		close(a[1]);//Cerramos el lado de escritura del hijo
		close(b[0]);//Cerramos el lado de lectura del padre
		if(access(entrada)!= -1){

			f= open(entrada, O_RDONLY| O_CREAT| O_TRUNC, 0644);

			//Si no da error ira leyendo por bloques i le enviara al proceso padre
			while (nbytes = read(a[0],entrada,SIZE)>0)
				write(1,buffer,nbytes);
			close(a[0]);

			write(b[1],buffer,strlen(buffer));
			close(b[1]);
		}
		//Demanarà que li envii un nou nom del fitxer
		else{
			do{
				strcpy(buffer,"Error");
				write(a[1],buffer,strlen(buffer));
				close(a[1]);
		   }while(access(entrada)== -1);

		}
		
	*********************************
	}
	else{//Padre
		//Demanarà un segon nom pel fitxer de escritura
		
		printf("Digam el nom de sortida del fitxer\n");
		scanf("%s", sortida);
		strcat(sortida,".txt");
		s= open(entrada, O_WRONLY| O_CREAT| O_TRUNC, 0644);
		
		close(a[0]);//cerramos lectura
		close(b[1]);//cerramos escritura
		
		while((nbytes= read(b[0],buffer,SIZE))>0){
			write(s,buffer,nbytes);
		close(b[0]);
		}
	}

	waitpid(pid,NULL,0);
	exit(0);
	return 0;
}
