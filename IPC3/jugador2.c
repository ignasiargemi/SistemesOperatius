#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define BUFFSIZE 20

void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
    int sock3, sock4;
    struct sockaddr_in jug2A;
    struct sockaddr_in jug2B;

    char buffer[BUFFSIZE];
    char buffer2[BUFFSIZE];
    unsigned int echolen, clientlen, echolen2;
    int received = 0, received2 = 0;
    int contador, tirada;

    int marcadorJug1 = 0;
    int marcadorJug2 = 0;

    if (argc != 4) {
        fprintf(stderr, "US: %s <ip_servidor> <port1> <port2>\n", argv[0]);
        exit(1);
    }
    //Creem el socket UDP
    if ((sock3 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        err_sys("error crear socket");
    }
    if ((sock4 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        err_sys("error crear socket");
    }
    /* preparamos sockaddr_in para servidor */
    memset(&jug2A, 0, sizeof(jug2A));       /* borramos la zona de memoria */
    jug2A.sin_family = AF_INET;                  /* Internet/IP */
    jug2A.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
    jug2A.sin_port = htons(atoi(argv[2]));       /* server port */

    memset(&jug2B, 0, sizeof(jug2B));       /* borramos la zona de memoria */
    jug2B.sin_family = AF_INET;                  /* Internet/IP */
    jug2B.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
    jug2B.sin_port = htons(atoi(argv[3]));       

    contador = 0;
    while(1) {
        ++contador;
        //Enviem les dades a l'arbitre
        tirada = -1;
        do {
            printf("Ronda %d: quin número vols posar?(0,1,2,3)\n", contador);
            fgets(buffer,BUFFSIZE-1,stdin);
            tirada = atoi(buffer);
        } while(tirada>3 || tirada < 0);

        echolen = strlen(buffer)+1;
        if (sendto(sock3, buffer, echolen, 0,(struct sockaddr *) &jug2A,sizeof(jug2A)) != echolen) {
            err_sys("error en escriptura1");
        }

        //Aposta
        buffer2[0] = '\0';        /* \0 */
        tirada = -1;
        do {
            printf("Ronda %d: quina és la vostra aposta?(0,1,2,3,4,5,6)\n", contador);
            fgets(buffer2,BUFFSIZE-1,stdin);
            tirada = atoi(buffer2);
        } while(tirada>6 || tirada < 0);
        echolen2 = strlen(buffer2)+1;
        if (sendto(sock4, buffer2, echolen2, 0,(struct sockaddr *) &jug2B,sizeof(jug2B)) != echolen2) {
            err_sys("error en escriptura");
        }

        //Rebem les dades de l'arbitre
        clientlen = sizeof(jug2A);
        if ((received = recvfrom(sock3, buffer, BUFFSIZE, 0,(struct sockaddr *) &jug2A,&clientlen)) != echolen) {
            err_sys("error en lectura2A");
        }
        buffer[received] = '\0';
        marcadorJug1 = atoi(buffer);     
        
        clientlen = sizeof(jug2B);
        if ((received2 = recvfrom(sock4, buffer2, BUFFSIZE, 0,(struct sockaddr *) &jug2B,&clientlen)) != echolen2) {
            err_sys("error en lectura2B");
        }
        buffer2[received2] = '\0';        
        marcadorJug2 = atoi(buffer2);       
    
        printf("Marcador: %i - %i \n", marcadorJug1, marcadorJug2);
        if (marcadorJug1>= 3 || marcadorJug2>=3) break;
    }
    printf("Final de la partida\n");
    if (marcadorJug1 == marcadorJug2) printf("Hi ha hagut un empat.\n");
    else if (marcadorJug1 < marcadorJug2) printf("Heu guanyat!\n");
    else printf("Heu perdut!\n");
    close(sock3);
    close(sock4);
    exit(0);
}