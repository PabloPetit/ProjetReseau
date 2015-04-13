#ifndef server_tcp_h
#define server_tcp_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

#include "messages.h"
#include "diffuseur.h"

typedef struct args_tcp{
	int portR;
	char *ipv4;
}args_tcp;

int ajout_msg(char *,char *);
void * run_client(void *);
void *run_server_tcp(void *);
void post_old_msg(int,int);

#endif
