#ifndef message_h
#define message_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <pthread.h>
#include "diffuseur.h"

typedef struct message{
    char *type;//4
    char *num_mess;//4
    char *id;//8
    char *message;//140
}message;

typedef struct liste_msg{
    int index;
    message * msg;
    struct liste_msg * suivant;
}liste_msg;


void init_list_msg();
liste_msg * make_list_msg(int,message *);
message * init_msg();
message * make_msg(char *,char *, char *);
int get_last_index(liste_msg *);
void add_msg(liste_msg *,message *);
void print_liste(liste_msg *);
message * transfert_msg();
void free_msg(message *);
void charger_fichier(char *);

#endif
