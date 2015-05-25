//
//  lecteur.c
//  Client
//
//  Created by Pablo Petit on 11/05/2015.
//  Copyright (c) 2015 Pablo Petit. All rights reserved.
//

#include "lecteur.h"

char * message_intro="\n\n\nRecepteur de messages activer : \n\n\n";

void * run_lecture(void * arg){
    diffuseur * diff = (diffuseur *)arg;
    extern int out;
    write(out,message_intro,strlen(message_intro));
    while(42==42){
        long lus;
        char buff[143];
        lus = recv(diff->sockUDP,buff,142,0);
        if(lus>=0){
            buff[lus]='\0';
            write(out,buff,lus);
        }
    sleep(1);
    }
}