#include "diffuseur.h"

liste_dif * liste;
liste_dif * liste_tmp;
pthread_mutex_t verrou= PTHREAD_MUTEX_INITIALIZER;

liste_dif * make_list(diffuseur * diff){
    liste_dif * lt = malloc(sizeof(liste_dif));
    lt->diff=diff;
    lt->suivant=NULL;
    return lt;
}

diffuseur * make_diff(char * id,char * port1,char * ip1,char * port2, char * ip2){
    diffuseur * diff=malloc(sizeof(diffuseur));
    snprintf(diff->id,8,"%s",id);
    snprintf(diff->port1, 5, "%s",port1);
    snprintf(diff->port2, 5, "%s",port2);
    snprintf(diff->ip1,16,"%s",ip1);
    snprintf(diff->ip2,16,"%s",ip2);
    return diff;
}

void add_diff(liste_dif * liste,diffuseur * diff){
    pthread_mutex_lock(&verrou);
    liste_dif * lt = liste;
    if(lt==NULL || lt==0){
        liste=make_list(diff);
        pthread_mutex_unlock(&verrou);
        return;
    }
    while(lt->suivant!=NULL)lt=lt->suivant;
    lt->suivant=make_list(diff);
    pthread_mutex_unlock(&verrou);
}

void clear_liste(liste_dif * liste){
    pthread_mutex_lock(&verrou);
    liste_dif * next;
    if(liste==NULL || liste==0){
        pthread_mutex_unlock(&verrou);
        return;
    }
    if(liste->diff==NULL){
        free(liste);
        return;
    }
    while( (next=liste->suivant)!=NULL){
        free(liste->diff);
        free(liste);
        liste=next;
    }
    free(next->diff);
    free(next);
    liste=NULL;
}

int verif_ip(char * ip){
    int i,ok=1;
    for(i=0;i<15;i++){
        if(i==3||i==7||i==11)ok=ip[i]=='.';
        else ok = isdigit(ip[i]);
    }
    return ok;
}

int verif_port(char * port){
    int a = atoi(port);
    return  a>0 && a<9999;
}

int genere_diff(int sock,int nb){
    long lus;
    int i;
    char buff[57];
    buff[56]='\0';
    for(i=0;i<nb;i++){
        char type[5];
        char id[9];
        char ip1[16];
        char port1[5];
        char ip2[16];
        char port2[5];
        lus=recv(sock, buff, 56, 0);//4+1+8+1+4+1+15+1+4+15+2
        if(lus!=56){
            print("Erreur de format -5-, fin de la connexion au gestionnaire.");
            return 0;
        }
        snprintf(type,5,"%s",buff);
        if(strcmp("ITEM",type)){
            print("Erreur de format -6-, fin de la connexion au gestionnaire.");
            return 0;
        }
        snprintf(id,9,"%s",(buff+5));//des milliards de test a faire bien sur ...
        snprintf(port1, 5, "%s",(buff+14));
        snprintf(ip1,16,"%s",(buff+19));
        snprintf(port2, 5, "%s",(buff+35));
        snprintf(ip2,16,"%s",(buff+40));
        if(strlen(id)!=8 || !verif_ip(ip1) || !verif_ip(ip2) || !verif_port(port1) || !verif_port(port2)){
            print("Erreur de format -7-, fin de la connexion au gestionnaire.");
            return 0;
        }
        add_diff(liste_tmp, make_diff(id, port1, ip1, port2, ip2));
    }
    return 1;
}


void lecture_gestionnaire(int sock){
    long lus;
    char buff[1025];
    char type[5];
    int nb;
    buff[1024]='\0';
    type[4]='\0';
    
    lus=recv(sock, buff, 7, 0);
    printf("LUS : %lu",lus);
    if(lus!=6){
        print("Erreur de format -1-, fin de la connexion au gestionnaire.");
        return;
    }
    snprintf(type,5,"%s",buff);
    if(strcmp("LINB", type)){
        print("Erreur de format -2-, fin de la connexion au gestionnaire.");
        return;
    }
    nb=atoi((buff+5));// a verif pour \r\n
    printf("nb : %d\n",nb);
    
    if(nb<0 || nb>99){
        print("Erreur de format -3-, fin de la connexion au gestionnaire.");
        return;
    }
    if (!genere_diff(sock, nb)){
        clear_liste(liste_tmp);
    }
}