#include "gestionnaire.h"

extern int out;

int recup_port(){
    char buff[5];
    buff[4]='\0';
    saisie(4, buff, "Veillez entrer le port du gestionnaire : ",NUMERIC);
    return atoi(buff);
}

int recup_ip(char * ip){
    char * ch_ip[3];
    int c;
    ip[15]='\0';
    ch_ip[0]="Localhost";
    ch_ip[1]="Entrer un nom de machine";
    ch_ip[2]="Entrer une IPv4";
    switch (c=menu_simple("Choisir ip : ",ch_ip,3)) {
        case 0:
            sprintf(ip,"localhost");
            break;
        case 1:
            ip[saisie(15, ip, "Entrez un nom de machine (max 15) : ", ALNU_SIZELESS)]='\0';
            break;
        case 2:
            saisie(15, ip, "Entrez une IPv4 de la forme : XXX.XXX.XXX.XXX : ", IPV4);
            break;
    }
    return c;
}

int connexion2(int port, char * ip){// Pour choix : localhost
    struct sockaddr_in adress_sock;
    adress_sock.sin_family = AF_INET;
    adress_sock.sin_port = htons(port);
    inet_aton(ip,&adress_sock.sin_addr);
    int descr=socket(PF_INET,SOCK_STREAM,0);
    printf("\nConnexion en cours...\n\n");
    int r=connect(descr,(struct sockaddr *)&adress_sock,sizeof(struct sockaddr_in));
    return (r==-1)?r:descr;
}

int connexion(int port, char * ip){//Pour choix : machine || ip
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
    int r=getaddrinfo("ip",tmp,&hints,&first_info);
    if(r==0){
        if(first_info!=NULL){
            addressin=(struct sockaddr_in *)first_info->ai_addr;
            int ret=connect(sock,(struct sockaddr *)addressin,(socklen_t)sizeof(struct sockaddr_in));
            if(ret==0){
                return sock;
            }
            else{
                print("Probleme de connexion!\n");
            }
            close(sock);
        }
    }
    return -1;
}

void get_ip(char * ip){
    
    int fd[2];
   	pipe(fd);
    char * argv[3];
    argv[0]="java";
    argv[1]="Ip";
    argv[2]=NULL;
    int pid = fork();
    
    if(pid==-1){
        print("Recuperation de l'ip impossible");
    }else if(pid==0){
        dup2(fd[1],1);
        execvp(argv[0],argv);
        exit(1);
    }else{
        wait(NULL);
        read(fd[0],ip,15);
    }
    ip[15]='\0';
}

int regi(int sock){//[REGI␣id␣ip1␣port1␣ip2␣port2]4+1+8+1+15+1+4+1+15+1+4+2
    extern diffuseur * diff;
    long lus;
    char mess[58];
    char ip[16];
    char ret[7];
    ret[6]='\0';
    get_ip(ip);
    snprintf(mess,58,"REGI %s %s %s %s %s\r\n",diff->id,diff->ipv4,diff->port_multi,ip,diff->port_tcp);
    send(sock, mess, 57, 0);
    lus=recv(sock, ret,6, 0);
    if(lus==6 && strcmp("REOK\r\n",ret)==0){
        int * tmp = malloc(sizeof(int));
        *tmp=sock;
        pthread_t th;
        pthread_create(&th,NULL,run_gestionnaire,tmp);
    }else{
        return 0;
    }
    return 1;
}

void * run_gestionnaire(void * arg){
    int sock = *((int*)arg);
    long lus;
    char buff[7];
    buff[6]='\0';
    while(42){
        lus=recv(sock,buff,6,0);
        if (lus==6 && strcmp("RUOK\r\n",buff)==0){
            send(sock,"IMOK\r\n",6,0);
        }else{
            break;
        }
    }
    close(sock);
    free(arg);
    
    write(out,"Connexion interrompu avec un des gestionnaire.",strlen("Connexion interrompu avec un des gestionnaire."));
    return NULL;
}

void connexion_gestionnaire(){
    char ip[16];
    int port=recup_port();
    int c=recup_ip(ip);
    int sock;
    printf("\nIP : -%s- : PORT  : -%d-\n",ip,port);
    if(c==0)sock=connexion2(port, ip);
    else sock=connexion(port, ip);
    if(sock==-1){
        print("Connexion au gestionnaire impossible.");
        return;
    }
    fflush(stdout);
    if(!regi(sock)){
        close(sock);
        print("Un probleme de connexion a eu lieu, abandon.");
    }else{
        print("La connexion a ete etablie.");
    }
}
