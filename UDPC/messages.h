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
#include "saisie.h"
#include "diffuseur.h"

typedef struct message{
    char type[5];
    char num_mess[5];
    char id[9];
    char message[141];
}message;

typedef struct liste_msg{
    message * msg;
    struct liste_msg * suivant;
}liste_msg;

void print_liste(liste_msg *);
void format_mess(char *,char *);
void format_id(char *,char *);
void format_type(char *,char *);
void format_index(int,char *);
void maj_cmp();
message * make_msg(char *,char *,char *);
liste_msg * make_list(message *);
void add_msg(message *);
message * transfert();
void charger_fichier(char *);

#endif
