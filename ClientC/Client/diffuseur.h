//
//  diffuseur.h
//  Client
//
//  Created by Pablo Petit on 26/04/2015.
//  Copyright (c) 2015 Pablo Petit. All rights reserved.
//

#ifndef __Client__diffuseur__
#define __Client__diffuseur__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "menu.h"
#include "saisie.h"

typedef struct diffuseur{
    char id[9];
    char ip1[16];
    char port1[5];
    char ip2[16];
    char port2[5];
}diffuseur;

typedef struct liste_dif{
    struct liste_dif * suivant;
    diffuseur * diff;
}liste_dif;

liste_dif * make_list(diffuseur *);
diffuseur * make_diff(char * ,char *,char *,char *, char * );
void add_diff(liste_dif *,diffuseur *);
void clear_liste(liste_dif *);
int verif_ip(char * );
int verif_port(char *);
int genere_diff(int,int);
void lecture_gestionnaire(int);
#endif /* defined(__Client__diffuseur__) */
