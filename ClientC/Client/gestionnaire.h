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
#include "menu.h"
#include "saisie.h"
#include "diffuseur.h"

int recup_port();
void recup_ip(char *);
int connexion(int, char *);
void connexion_gestionnaire();

#endif /* defined(__Client__gestionnaire__) */
