#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/types.h>


int main() {
	int sock=socket(PF_INET,SOCK_DGRAM,0);
	sock=socket(PF_INET,SOCK_DGRAM,0);
	int ok=1;
	int r=setsockopt(sock,SOL_SOCKET,SO_REUSEPORT,&ok,sizeof(ok));
	struct sockaddr_in address_sock;
	address_sock.sin_family=AF_INET;
	address_sock.sin_port=htons(4272);
	address_sock.sin_addr.s_addr=htonl(INADDR_ANY);
	r=bind(sock,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in));
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr=inet_addr("237.0.0.2");
	mreq.imr_interface.s_addr=htonl(INADDR_ANY);
	r=setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
	char tampon[1024];
	while(1){
		int rec=recv(sock,tampon,1024,0);
		tampon[rec]='\0';
		printf("Message recu : %s\n",tampon);
	}
	return 0;
}