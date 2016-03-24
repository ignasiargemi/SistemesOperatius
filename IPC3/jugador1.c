#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>


#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 20

void err_sys(const char* cadena){ perror(cadena);exit(1);} 


int main(int argc, char *argv[]) {

    int sock;
    struct sockaddr_in echoArbitre;
    char buffer[BUFFSIZE];
    unsigned int echolen;
    int bytes = 0;

      
    int     jugador1, jugador2;
    int     tirada, suma;

    if (argc != 3) {
    fprintf(stderr, "US: TCPecho <ip_servidor> <port>\n");
    exit(1);}
    /*Creamos socket*/

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    err_sys("errpr socket");}


    /* preparamos sockaddr_in */
    memset(&echoArbitre, 0, sizeof(echoArbitre));       /* borra memoria */
    echoArbitre.sin_family = AF_INET;                  /* Internet/IP */
    echoArbitre.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
    echoArbitre.sin_port = htons(atoi(argv[2]));       /* server port */

    //sem_post(JA1);

    /* establecemos conexion con Arbitro */
    if (connect(sock,(struct sockaddr *) &echoArbitre,sizeof(echoArbitre)) < 0) {
                  err_sys("error connect");
    }

    

    while(1){
        
        //sem_wait(AJ1);
        if ((read(sock, &jugador1, sizeof(jugador1))) < 0) {
        err_sys("error recepcion");}

        if ((read(sock, &jugador2, sizeof(jugador2))) < 0) {
        err_sys("error recepcion");}
        
        
        printf("Marcador: %i - ",jugador1);
        printf("%i\n",jugador2);
        
        if (jugador1 >= 3 || jugador2 >= 3) break; //Final
        

        do{
            printf("Escriu el valor de la teva tirada:\n(0-3)\n");
            scanf("%i",&tirada);

        }while(tirada>3 || tirada < 0);

        
        if (write(sock, &tirada, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");
        }

        do {
            printf("Quina es la teva suma/aposta:\n(0-6)\n");
            scanf("%i",&suma);
        }while (suma < 0 || suma > 6);

        if (write(sock, &suma, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");
        }
 
        printf("Tirada: %i - Suma: %i\n", tirada, suma);
        
        //sem_post(JA1);
    }

    printf("Final Jugador 1!\n");
    close(sock);
    exit(0);
}
