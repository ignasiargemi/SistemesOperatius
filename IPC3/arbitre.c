#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 255
void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
  int sock1, sock2, sock3, sock4;
  struct sockaddr_in jug1A;
  struct sockaddr_in jug1B;
  struct sockaddr_in jug2A;
  struct sockaddr_in jug2B;

  char buffer[BUFFSIZE];
  char buffer2[BUFFSIZE];
  char buffer3[BUFFSIZE];
  char buffer4[BUFFSIZE];
  unsigned int jug1Alen, jug1Blen, jug2Alen, jug2Blen;
  int received1 = 0;
  int received2 = 0;
  int received3 = 0;
  int received4 = 0;

  int marcadorJug1 = 0;
  int marcadorJug2 = 0;
  int numJug1;
  int numJug2;
  int apostaJug1;
  int apostaJug2;

  if (argc != 5) {
    fprintf(stderr, "US: %s <portJugador1A> <portJugador1B> <portJugador2A> <portJugador2B>\n", argv[0]);
    exit(1);
  }
  /* creamos socket UDP */
  if ((sock1 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    err_sys("error crear socket");
  }
  if ((sock2 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    err_sys("error crear socket");
  }
  if ((sock3 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    err_sys("error crear socket");
  }
  if ((sock4 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    err_sys("error crear socket");
  }
  /* preparamos estructura sockaddr_in */
  memset(&jug1A, 0, sizeof(jug1A));       /* borramos memoria */
  jug1A.sin_family = AF_INET;                  /* Internet/IP */
  jug1A.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address tomara cualquiera de les IP del servidor*/
  jug1A.sin_port = htons(atoi(argv[1]));       /* server port */

  memset(&jug1B, 0, sizeof(jug1B));       /* borramos memoria */
  jug1B.sin_family = AF_INET;                  /* Internet/IP */
  jug1B.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address tomara cualquiera de les IP del servidor*/
  jug1B.sin_port = htons(atoi(argv[2]));       /* server port */

  memset(&jug2A, 0, sizeof(jug2A));       /* borramos memoria */
  jug2A.sin_family = AF_INET;                  /* Internet/IP */
  jug2A.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address tomara cualquiera de les IP del servidor*/
  jug2A.sin_port = htons(atoi(argv[3]));       /* server port */

  memset(&jug2B, 0, sizeof(jug2B));       /* borramos memoria */
  jug2B.sin_family = AF_INET;                  /* Internet/IP */
  jug2B.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address tomara cualquiera de les IP del servidor*/
  jug2B.sin_port = htons(atoi(argv[4]));       /* server port */
  
  //Fem bind per poder llegir la informació dels ports
  jug1Alen = sizeof(jug1A);
  if (bind(sock1, (struct sockaddr *) &jug1A, jug1Alen) < 0) {
    err_sys("error bind jug1A");
  }

  jug1Blen = sizeof(jug1B);
  if (bind(sock2, (struct sockaddr *) &jug1B, jug1Blen) < 0) {
    err_sys("error bind jug1B");
  }

  jug2Alen = sizeof(jug2A);
  if (bind(sock3, (struct sockaddr *) &jug2A, jug2Alen) < 0) {
    err_sys("error bind jug2A");
  }

   jug2Blen = sizeof(jug2B);
  if (bind(sock4, (struct sockaddr *) &jug2B, jug2Blen) < 0) {
    err_sys("error bind jug2B");
  }

  /* bucle infinit */
  while (1) {
    //Rebem missatges dels jugadors
    jug1Alen = sizeof(jug1A);
    if ((received1 = recvfrom(sock1, buffer, BUFFSIZE, 0,(struct sockaddr *) &jug1A,&jug1Alen)) < 0) {
      err_sys("error lectura");
    }
    jug1Blen = sizeof(jug1B);
    if ((received2 = recvfrom(sock2, buffer2, BUFFSIZE, 0,(struct sockaddr *) &jug1B,&jug1Blen)) < 0) {
      err_sys("error lectura");
    }

    jug2Alen = sizeof(jug2A);
    if ((received3 = recvfrom(sock3, buffer3, BUFFSIZE, 0,(struct sockaddr *) &jug2A,&jug2Alen)) < 0) {
      err_sys("error lectura");
    }
    jug2Blen = sizeof(jug2B);
    if ((received4 = recvfrom(sock4, buffer4, BUFFSIZE, 0,(struct sockaddr *) &jug2B,&jug2Blen)) < 0) {
      err_sys("error lectura");
    }
    numJug1 = atoi(buffer);
    apostaJug1 = atoi(buffer2);
    numJug2 = atoi(buffer3);
    apostaJug2 = atoi(buffer4);

    printf("Jugador 1:\nnúmero: %i, aposta: %i\n", numJug1, apostaJug1);
    printf("Jugador 2:\nnúmero: %i, aposta: %i\n", numJug2, apostaJug2);

    if ((numJug1+numJug2) == apostaJug1) ++marcadorJug1;
    if ((numJug1+numJug2) == apostaJug2) ++marcadorJug2;

    fprintf(stderr, "Marcador del joc: %i - %i\n", marcadorJug1,marcadorJug2);
  
    //Retorn del marcador als jugadors
    sprintf(buffer, "%d", marcadorJug1);
    if (sendto(sock1, buffer, received1, 0,(struct sockaddr *) &jug1A,sizeof(jug1A)) != received1) {
      err_sys("error escriptura");
    }

    sprintf(buffer2, "%d", marcadorJug2);
    if (sendto(sock2, buffer2, received2, 0,(struct sockaddr *) &jug1B,sizeof(jug1B)) != received2) {
      err_sys("error escriptura");
    }

    sprintf(buffer3, "%d", marcadorJug1);
    if (sendto(sock3, buffer3, received3, 0,(struct sockaddr *) &jug2A,sizeof(jug2A)) != received3) {
      err_sys("error escriptura");
    }

    sprintf(buffer4, "%d", marcadorJug2);
    if (sendto(sock4, buffer4, received4, 0,(struct sockaddr *) &jug2B,sizeof(jug2B)) != received4) {
      err_sys("error escriptura");
    }
    if (marcadorJug1>= 3 || marcadorJug2>=3) break;
  }
  printf("Final de la partida\n");
  if (marcadorJug1 == marcadorJug2) printf("Hi ha hagut un empat.\n");
  else if (marcadorJug1 > marcadorJug2) printf("Ha guanyat el jugador 1.\n");
  else printf("Ha guanyat el jugador 2.\n");
  close(sock1);
  close(sock2);
  close(sock3);
  close(sock4);
  exit(0);
}