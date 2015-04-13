#ifndef diffuseur_h
#define diffuseur_h

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
#include <pthread.h>
#include <sys/types.h>

#include "messages.h"

typedef struct diffuseur{
	char* ipv4;//15
	char* port_multi;//4
	char* port_tcp;//4
	char* id;//8
	int interval;
}diffuseur;

void * diffuseur_run(void * );
void print_diffuseur(diffuseur*);
diffuseur * make_diffuseur(char *,char *,char *,char *,int);

#endif
