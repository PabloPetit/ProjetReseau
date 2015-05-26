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
#include <fcntl.h>
#include "lecteur.h"
#include "saisie.h"


#define REUSE 15
#define MENU_PRINCIPAL 0
#define LECTURE_GEST 1

typedef struct diffuseur{
    char id[9];
    char ip1[16];
    char port1[5];
    char ip2[16];
    char port2[5];
    int sockUDP;
    pthread_t * th;
}diffuseur;

typedef struct liste_dif{
    struct liste_dif * suivant;
    diffuseur * diff;
}liste_dif;

#include "menu.h"

void  suppression(liste_dif *);
liste_dif * make_list(diffuseur *);
diffuseur * make_diff(char * ,char *,char *,char *, char * );
void add_diff(liste_dif **,diffuseur *);
void print_liste(liste_dif *);
void clear_liste(liste_dif **);
int verif_ip(char * );
int verif_port(char *);
int genere_diff(int,int);
void transfert_liste(liste_dif *, liste_dif **);
void lecture_gestionnaire(int);
int init_sockUDP(diffuseur *);
int connect_liste_diff(liste_dif *);
int menu_action_diff();
int send_msg(int , char *, char *);
void diffuser_message(liste_dif * );
int check_old_mess(char *);
void display_old_mess(liste_dif * lst);
void reception_old_mess(int ,int);
void gestion_menu_diff(liste_dif*,int);
#endif /* defined(__Client__diffuseur__) */
