#include "gestionnaire.h"


int recup_port(){
    char buff[5];
    buff[4]='\0';
    saisie(4, buff, "Veillez entrer le port du gestionnaire : ",NUMERIC);
    return atoi(buff);
}

void recup_ip(char * ip){
    char * ch_ip[3];
    ip[15]='\0';
    ch_ip[0]="Localhost";
    ch_ip[1]="Entrez un nom de machine : ";
    ch_ip[2]="Entrer une IPv4";
    switch (menu_simple("Choisir ip : ",ch_ip,2)) {
        case 0:
            sprintf(ip,"localhost");
            break;
        case 1:
            break;
        case 2:
            saisie(15, ip, "Entrez une IPv4 de la forme : XXX.XXX.XXX.XXX : ", IPV4);
            break;
    }
}
/*
int connexion2(int port, char * ip){
    struct sockaddr_in adress_sock;
    adress_sock.sin_family = AF_INET;
    adress_sock.sin_port = htons(port);
    inet_aton(ip,&adress_sock.sin_addr);
    int descr=socket(PF_INET,SOCK_STREAM,0);
    printf("\nConnexion en cours...\n\n");
    int r=connect(descr,(struct sockaddr *)&adress_sock,sizeof(struct sockaddr_in));
    printf("R : %d\n",r);
    return (r==-1)?r:descr;
}*/

int connexion(int port, char * ip){
    int sock=socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in *addressin;
    struct addrinfo *first_info;
    struct addrinfo hints;
    bzero(&hints,sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype=SOCK_STREAM;
    char tmp[5];
    tmp[4]='\0';
    snprintf(tmp,5,"%d",port);
    int r=getaddrinfo("ip","5566",&hints,&first_info);
    if(r==0){
        if(first_info!=NULL){
            addressin=(struct sockaddr_in *)first_info->ai_addr;
            int ret=connect(sock,(struct sockaddr *)addressin,(socklen_t)sizeof(struct sockaddr_in));
            if(ret==0){
                return sock;            }
            else{
                print("Probleme de connexion!\n");
            }
            close(sock);
        }
    }
    return -1;
}




void connexion_gestionnaire(){
    char ip[16];
    int port=recup_port();
    recup_ip(ip);
    printf("\nIP : %s : PORT  : %d\n",ip,port);
    int sock=connexion(port, ip);
    if(sock==-1){
        print("Connexion au gestionnaire impossible.");
        return;
    }
    printf("Connexion Réussi\n");
    fflush(stdout);
    lecture_gestionnaire(sock);
    close(sock);
}
