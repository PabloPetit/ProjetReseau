//
//  lecteur.c
//  Client
//
//  Created by Pablo Petit on 11/05/2015.
//  Copyright (c) 2015 Pablo Petit. All rights reserved.
//

#include "lecteur.h"

void * run_lecture(void * arg){
    int  sock= *(int *)arg;
    extern int out;
    while(42==42){
        long lus;
        char buff[143];
        lus = recv(sock,buff,142,0);
        if(lus>=0){
            buff[lus]='\0';
            write(out,buff,lus);
        }
    sleep(1);
    }
}
/*
void * run_lecteur(void * arg){
    extern liste_dif * liste;
    extern pthread_mutex_t verrou;
    int out = *((int*)arg);//Out = descipteur du fichier de sortie
    
    while(42){
       // pthread_mutex_lock(&verrou);
        fd_set rdfs;
        int max = 0;
        liste_dif * lst=liste;
        
        while(lst!=NULL){//On ajoute toutes les sockets a l'ensemble
            printf("HEY\n");
            if(lst->diff->sockUDP>-1){
                printf("lst!=NULL && sock !=-1\n");
                FD_SET(lst->diff->sockUDP,&rdfs);
                if(max<lst->diff->sockUDP){
                    max=lst->diff->sockUDP;
                }
            }
            lst=lst->suivant;
        }
        int ret=select(max+1, &rdfs, NULL, NULL, NULL);
        while(ret>0){
            lst=liste;
            while(lst!=NULL){
                if(FD_ISSET(lst->diff->sockUDP,&rdfs)){
                    //Gestion mess
                    long lus;
                    char buff[143];
                    lus = recv(lst->diff->sockUDP,buff,142,0);
                    if(lus>=0){
                        buff[lus]='\0';
                        write(out,buff,lus);
                    }
                    //Fin
                    ret--;
                }
                lst=lst->suivant;
            }
            
        }
       // pthread_mutex_unlock(&verrou);
        sleep(1);
    }
    return NULL;
}*/