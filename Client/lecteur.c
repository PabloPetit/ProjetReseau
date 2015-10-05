//
//  lecteur.c
//  Client
//
//  Created by Pablo Petit on 11/05/2015.
//  Copyright (c) 2015 Pablo Petit. All rights reserved.
//

#include "lecteur.h"


char * getTime(void){
    
    time_t seconde;
    struct tm instant;
    
    char * heure = malloc(sizeof(char)*8);
    
    time(&seconde);
    instant=*localtime(&seconde);
    
    snprintf(heure, 9,"%d:%d:%d", instant.tm_hour, instant.tm_min, instant.tm_sec);
    return heure;
    //return 0;
}

void * run_lecture(void * arg){
    extern int out;
    diffuseur * diff = (diffuseur *)arg;
    char * tmp2 = "\n          ----------          \n";
    while(42==42){
        long lus;
        char buff[162];
        lus = recv(diff->sockUDP,buff,161,0);
        if(lus>=0){
            buff[lus]='\0';
            char tmp1[100];
            snprintf(tmp1,100,"\nMessage reçu de : %s a %s:\n",diff->id,getTime());
            write(out,tmp1,strlen(tmp1));
            write(out,(buff+5),lus-5);
            write(out,tmp2,strlen(tmp2));
        }
    sleep(1);
    }
}