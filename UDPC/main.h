#ifndef main_h
#define main_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include "diffuseur.h"
#include "messages.h"
#include "server_tcp.h"
#include "menu_principal.h"

void printHelp();
int check_id_valide(char*);
void check_port_valide(char *,char *);
char * format_ipv4(char *);

#endif
