#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void err_sys(const char* cadena){ 
    perror(cadena); 
    exit(1);
} 

int main () {
    int bytesLeidos;
    int a, b, can[2], can2[2], can3[2];
    char buffer [100], entrada [80];
    pid_t pid;
    int resposta;

    

    pipe(can);
    pipe(can2);
    pipe(can3);

    if((pid = fork()) == -1) {
        perror("error en el fork");
        exit(1);
    }

    if(pid != 0) {
        printf ("Introdueix el nom del fitxer d'escritura:\n(Cal posar format)\n");  
        scanf("%s%*c", entrada);
        write(can[1],entrada, sizeof(entrada));
        while (read(can2[0],&resposta,sizeof(resposta)) == 0);
        while (resposta == -1) {
            printf("Aquest fitxer no existeix. Torna a escriure un altre nom.\n");
            scanf("%s%*c", entrada);
            write(can[1],entrada, sizeof(entrada));
            while (read(can2[0],&resposta,sizeof(int)) == 0);
        }
        printf("Escriu el nom per l'arxiu de sortida.\n");
        scanf("%s%*c", entrada);
        int b = open(entrada,O_WRONLY|O_CREAT|O_TRUNC,0777);
        int red;
        do {
            red = read(can3[0],buffer,sizeof(buffer));
            write(b,buffer,red);
        } while (red == sizeof(buffer));
        printf("He escrit tot\n");
        close(b);
    }

    else {
        read(can[0],buffer, sizeof(buffer));
        int f = open(buffer, O_RDONLY);
        while (f == -1) {
            int r = -1;
            write(can2[1],&r,sizeof(r));
            while (read(can[0],buffer, sizeof(buffer)) == 0);
            f = open(buffer, O_RDONLY);
        }
        
        int r = 2;
        write(can2[1],&r,sizeof(r));
        bytesLeidos = read(f, &buffer, sizeof(buffer));
        while(bytesLeidos!= 0) {
            write(can3[1], &buffer, bytesLeidos);
            bytesLeidos = read(f, &buffer, sizeof(buffer));
        }
        close(f);
    }

    return 0;
    exit (0);
}