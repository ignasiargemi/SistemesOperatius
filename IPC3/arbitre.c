#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 5
#define MAXPENDING 5    /* numero maximo de connexiones simultaneas */

void err_sys(const char* cadena){perror(cadena);exit(1);} 

void HandleJugador(int sock) {/*REBEM MISSATGE, QUAN JUGADOR ENTRA A JUGAR*/
char buffer[BUFFSIZE];
int received = -1;

/* recibimos mensahe */
if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
  err_sys("error recepcion");
}
/* enviamos echo */
while (received > 0) {
  /* enviamos echo */
  if (send(sock, buffer, received, 0) != received) {
      err_sys("error escriptura");}

    /* quedan datos por recibir */
  if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
      err_sys("error lectura addicional");
  }
}
close(sock);
}

int main(int argc, char *argv[]) {


  int   jug1sock, jug2sock, arbitresock;
  struct sockaddr_in echoArbitre, echoJug1, echoJug2;


  int jugador1=0;
  int jugador2=0;
  int suma1, tirada1;
  int suma2, tirada2;
  //int r;

  
  if (argc != 2) {err_sys("US: server <port>\n");}

  /* creamos socket TCP */
  if ((arbitresock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
  err_sys("error creacion socket");}

   /* preparamos sockaddr_in */
  memset(&echoArbitre, 0, sizeof(echoArbitre));       /* borra memoria */
  echoArbitre.sin_family = AF_INET;                  /* Internet/IP */
  echoArbitre.sin_addr.s_addr = htonl(INADDR_ANY);   /* cualquier addr */
  echoArbitre.sin_port = htons(atoi(argv[1]));       /* server port */

  /* Bind -->enlazamos */
  if (bind(arbitresock, (struct sockaddr *) &echoArbitre,sizeof(echoArbitre)) < 0) {
    err_sys("error bind");
  }


  printf("Inicialitzat\n");

  // sem_wait(JA1);

  /* Listen --> El jugador1 ens avisa si ha entrat */
  if (listen(arbitresock, MAXPENDING) < 0) {
    err_sys("error listen");
  }


  while (1) {
    unsigned int jug1len = sizeof(echoJug1);
    /* esperamso conexion por parte del cliente */
    if ((jug1sock =
      accept(arbitresock, (struct sockaddr *) &echoJug1,&jug1len)) < 0) {
    err_sys("error accept");
    }
    fprintf(stdout, "Jugador: %s\n",inet_ntoa(echoJug1.sin_addr));
    HandleJugador(jug1sock);
  }

  printf("Jugador 1 a punt\n");

  //sem_wait(JA2);

  /* Listen --> El jugador2 ens avisa si ha entrat */
  if (listen(arbitresock, MAXPENDING) < 0) {
    err_sys("error listen");
  }

  while (1) {
    unsigned int jug2len = sizeof(echoJug2);
    /* esperando conexion por parte del cliente */
    if ((jug2sock =
      accept(arbitresock, (struct sockaddr *) &echoJug2,&jug2len)) < 0) {
    err_sys("error accept");
    }
    fprintf(stdout, "Jugador2: %s\n",inet_ntoa(echoJug2.sin_addr));
    HandleJugador(jug2sock);
  }

  printf("Jugador 2 a punt\n");



  if (write(jug1sock, &jugador1, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor "); }

  if (write(jug1sock, &jugador2, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");}

  if (write(jug2sock, &jugador1, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");}

  if (write(jug2sock, &jugador2, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");}


  //sem_post(AJ1);
  //sem_post(AJ2);




  
  //******************************************************
    
  while (1) {
    printf("El marcador és de %i a %i\n",jugador1,jugador2);
    if (jugador1 >= 3 || jugador2 >= 3) break;

    //sem_wait(JA1);
    

    //Read
    if ((read(jug1sock, &tirada1, sizeof(tirada1))) < 0) {
    err_sys("error recepcion");}
    if ((read(jug1sock, &suma1, sizeof(suma1))) < 0) {
    err_sys("error recepcion");}
    
    printf("Jugador 1: %i - %i\n", tirada1,suma1);


    //sem_wait(JA2);
    



    //Read
    if ((read(jug2sock, &tirada2, sizeof(tirada2))) < 0) {
    err_sys("error recepcion");}
    if ((read(jug2sock, &suma2, sizeof(suma2))) < 0) {
    err_sys("error recepcion");}

    printf("Jugador 2: %i - %i\n", tirada2,suma2);

    if ((tirada1+tirada2) == suma1) ++jugador1;
    if ((tirada1+tirada2) == suma2) ++jugador2;

    if (write(jug1sock, &jugador1, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");}
    if (write(jug1sock, &jugador2, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");}
    if (write(jug2sock, &jugador1, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");}
    if (write(jug2sock, &jugador2, sizeof(int)) != sizeof(int)) {
            err_sys("error al enviar la informacio a servidor ");}
    
    //sem_post(AJ1);
    //sem_post(AJ2);

  
  }

  //Enunci del guanyador
  if (jugador1 == 3 && jugador2 == 3) printf("Hi ha hagut un empat!\n");
  else if (jugador1 > jugador2) printf("Ha guanyat el jugador 1!\n");
  else printf("Ha guanyat el jugador 2!\n");

  //Close sockets

  if (close(jug1sock)<0)
  err_sys("error en close jug1sock");

  if (close(jug2sock)<0)
    err_sys("error en close jug2sock");


  if (close(arbitresock)<0)
    err_sys("error en close arbitresock");



  printf("Final de l'arbitre!\n");
  exit(0);
}