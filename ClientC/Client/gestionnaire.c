#include "gestionnaire.h"


int recup_port(){
    char buff[5];
    buff[4]='\0';
    saisie(4, buff, "Veillez entrer le port du diffuseur : ",NUMERIC);
    return atoi(buff);
}

void connexion_gestionnaire(){
    int port=recup_port();
    printf("PORT : %d\n",port);
}