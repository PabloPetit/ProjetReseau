//
//  lecteur.c
//  Client
//
//  Created by Pablo Petit on 11/05/2015.
//  Copyright (c) 2015 Pablo Petit. All rights reserved.
//

#include "lecteur.h"


void * run_lecture(void * arg){
    extern int out;
    diffuseur * diff = (diffuseur *)arg;
    char * tmp2 = "\n          ----------          \n";
    while(42==42){
        long lus;
        char buff[143];
        lus = recv(diff->sockUDP,buff,142,0);
        if(lus>=0){
            buff[lus]='\0';
            char tmp1[31];
            snprintf(tmp1,31,"\nMessage reçu de : %s :\n",diff->id);
            write(out,tmp1,31);
            write(out,buff,lus);
            write(out,tmp2,strlen(tmp2));
        }
    sleep(1);
    }
}