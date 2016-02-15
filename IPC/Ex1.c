#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() 
{
    int a, b[2], b2[2], nbytes;
    char string [100], buffer [100], entrada [80];
	pid_t pid; 
	char fin[5] = "FINAL";
    int marca=0;
	

	a = open("entrada.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);

    pipe(b);
    
    if((pid = fork()) == -1) {
        perror("error en el fork");
        exit(1);
    }

    if(pid != 0){
        
		printf("Escriu un text:\n");
        fgets(string, sizeof(string), stdin);
        //scanf("%s", string);


		while (strncmp(string,fin,5) != 0) {
            //strcat(string," ");
			write(b[1], &string, strlen(string)); 
			//scanf("%s", string);
            fgets(string, 100, stdin);
		}
          
    }
    else {
        do {
            nbytes = read(b[0], &buffer, sizeof(buffer));
            write(a, &buffer, nbytes);
        } while (strncmp(buffer,fin,5) != 0);
        
	  
    }

    close(a);
    return 0;
    exit(0);
}