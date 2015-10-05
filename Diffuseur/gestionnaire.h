#ifndef __Client__gestionnaire__
#define __Client__gestionnaire__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "menu.h"
#include "saisie.h"
#include "main.h"

int recup_port();
int recup_ip(char *);
char * convert(char *);
int connexion(int, char *);
int connexion2(int, char *);
void connexion_gestionnaire();
void get_ip();
void * run_gestionnaire(void * arg);

#endif /* defined(__Client__gestionnaire__) */
