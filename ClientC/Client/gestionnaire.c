#include "gestionnaire.h"


int recup_port(){
    char buff[5];
    buff[4]='\0';
    saisie(4, buff, "Veillez entrer le port du gestionnaire : ",NUMERIC);
    return atoi(buff);
}

void recup_ip(char * ip){
    char * ch_ip[2];
    ip[15]='\0';
    ch_ip[0]="Localhost";
    ch_ip[1]="Entrer une IPv4";
    switch (menu_simple("Choisir ip : ",ch_ip,2)) {
        case 0:
            sprintf(ip,"localhost");
            break;
        case 1:
            saisie(15, ip, "Entrez une IPv4 de la forme : XXX.XXX.XXX.XXX : ", IPV4);
            break;
    }
}

int connexion(int port, char * ip){
    struct sockaddr_in adress_sock;
    adress_sock.sin_family = AF_INET;
    adress_sock.sin_port = htons(port);
    inet_aton(ip,&adress_sock.sin_addr);
    int descr=socket(PF_INET,SOCK_STREAM,0);
    printf("\nConnexion en cours...\n\n");
    int r=connect(descr,(struct sockaddr *)&adress_sock,sizeof(struct sockaddr_in));
    printf("R : %d\n",r);
    return (r==-1)?r:descr;
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
    printf("SOCK close");
    close(sock);
}
