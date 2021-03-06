#include "diffuseur.h"

liste_dif * liste=NULL;
liste_dif * liste_tmp=NULL;
pthread_mutex_t verrou= PTHREAD_MUTEX_INITIALIZER;


liste_dif * make_list(diffuseur * diff){
    liste_dif * lt = malloc(sizeof(liste_dif));
    lt->diff=diff;
    lt->suivant=NULL;
    return lt;
}

diffuseur * make_diff(char * id,char * port1,char * ip1,char * port2, char * ip2){
    diffuseur * diff=malloc(sizeof(diffuseur));
    snprintf(diff->id,9,"%s",id);
    snprintf(diff->port1, 5, "%s",port1);
    snprintf(diff->port2, 5, "%s",port2);
    snprintf(diff->ip1,16,"%s",ip1);
    snprintf(diff->ip2,16,"%s",ip2);
    diff->sockUDP = -1;
    diff->th=NULL;
    return diff;
}

void add_diff(liste_dif ** liste,diffuseur * diff){
    pthread_mutex_lock(&verrou);
    liste_dif * lt = *liste;
    if(lt==NULL || lt==0 ){//Passe toujours par ici
        *liste = make_list(diff);//faut
        pthread_mutex_unlock(&verrou);
        return;
    }
    while(lt->suivant!=NULL)lt=lt->suivant;
    lt->suivant=make_list(diff);
    pthread_mutex_unlock(&verrou);
}

void clear_liste(liste_dif ** liste){
    *liste=NULL;

    /*
    pthread_mutex_lock(&verrou);
    liste_dif * next;
    liste_dif * temp = *liste;
    if(*liste==NULL || *liste==0){
        pthread_mutex_unlock(&verrou);
        return;
    }
    if((*liste)->diff==NULL){
        free(*liste);
        *liste = NULL;
        pthread_mutex_unlock(&verrou);
        return;
    }
    while ((*liste)->suivant!=NULL) {
        next = (*liste)->suivant;
        free(*liste);
        liste = &next;
    }
    *liste=NULL;
    temp=NULL;
    pthread_mutex_unlock(&verrou);
     */
}

char * convert(char * ip){
    char a[4];
    char b[4];
    char c[4];
    char d[4];
    printf("IP : -%s-",ip);
    
    snprintf(a,4,"%s",ip);
    snprintf(b,4,"%s",ip+4);
    snprintf(c,4,"%s",ip+8);
    snprintf(d,4,"%s",ip+12);
    
    int a1 =atoi(a);
    int b1 =atoi(b);
    int c1 =atoi(c);
    int d1 =atoi(d);
    
    char * ret=malloc(sizeof(char)*16);
    sprintf(ret,"%d.%d.%d.%d",a1,b1,c1,d1);
    printf("RETOUR IP : -%s-\n",ret);
    return  ret;
}

void print_liste(liste_dif * liste){
    liste_dif * lst = liste;
    printf("Liste des Diffuseurs : \n\n");
    while (lst!=NULL) {
        printf("ID : %s\n",lst->diff->id);
        printf("Ip 1 : %s\n",lst->diff->ip1);
        printf("Port 1: %s\n",lst->diff->port1);
        printf("Ip 2 : %s\n",lst->diff->ip2);
        printf("Port 2 : %s\n\n",lst->diff->port2);
        lst = lst -> suivant;
    }
    printf("Fin de la liste.\n\n");
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

int init_sockUDP(diffuseur * diff){
    int sock=socket(PF_INET,SOCK_DGRAM,0);
    sock=socket(PF_INET,SOCK_DGRAM,0);
    int ok=1;
    int r=setsockopt(sock,SOL_SOCKET,REUSE,&ok,sizeof(ok));
    struct sockaddr_in address_sock;
    address_sock.sin_family=AF_INET;
    address_sock.sin_port=htons(atoi(diff->port1));
    address_sock.sin_addr.s_addr=htonl(INADDR_ANY);
    r=bind(sock,(struct sockaddr *)&address_sock,sizeof(struct sockaddr_in));
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr=inet_addr(diff->ip1);
    mreq.imr_interface.s_addr=htonl(INADDR_ANY);
    r=setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));
    if (r!=-1){
        fcntl( sock, F_SETFL, O_NONBLOCK);
        diff->sockUDP=sock;
    }
    printf("display old : %s : %s : %s : %d\n",diff->id,diff->port1,diff->ip1, diff->sockUDP);
    return r!=-1;
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
        lus=recv(sock, buff, 57, 0);//4+1+8+1+15+1+4+1+15+1+4+2
        //
        printf("LUS : %lu -%s-\n",lus,buff);
        if(lus!=57){
            print("Erreur de format -5-, fin de la connexion au gestionnaire.");
            return 0;
        }
        snprintf(type,5,"%s",buff);
        if(strcmp("ITEM",type)){
            print("Erreur de format -6-, fin de la connexion au gestionnaire.");
            return 0;
        }
        snprintf(id,9,"%s",(buff+5));
        snprintf(ip1,16,"%s",(buff+14));
        snprintf(port1, 5, "%s",(buff+30));
        snprintf(ip2,16,"%s",(buff+35));
        snprintf(port2, 5, "%s",(buff+51));
        
        
        if(strlen(id)!=8 || !verif_ip(ip1) || !verif_ip(ip2) || !verif_port(port1) || !verif_port(port2)){
            print("Erreur de format -7-, fin de la connexion au gestionnaire.");
            return 0;
        }
        printf("GENERE LIST : \n");
        printf("id : -%s-\n p1 : -%s-\n ip1 : -%s-\n p2 : -%s-\n ip2 : -%s-\n",id,port1,ip1,port2,ip2);
        add_diff(&liste_tmp, make_diff(id, port1, ip1, port2, ip2));
    }
    return 1;
}

void transfert_liste(liste_dif * src, liste_dif ** cible){
    while(src!=NULL){
        add_diff(cible, src->diff);
        src = src->suivant;
    }
}

int connect_liste_diff(liste_dif * lst){
    int res = 1;
    while (lst!=NULL) {
        if(init_sockUDP(lst->diff)==-1){
            res = -1;
            char ch[46];
            snprintf(ch,46,"Connexion au diffuseur : %s impossible.",lst->diff->id);
            print(ch);
        }
    }
    return res;
}

int menu_action_diff(int flag){
    char * intro = "Choisissez une option : ";
    char * args[4];
    if(flag==LECTURE_GEST){
        args[0]="Ajouter a la liste de lecture";
    }else{
        args[0]="Supprimer de la liste de lecture";
    }
    args[1]="Diffuser un message";
    args[2]="Demander la liste des derniers messages";
    args[3]="Quitter";
    
    return menu_simple(intro,args,4);
}

/*
int send_msg(int port, char * addr, char * mess){
    
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
    int r=getaddrinfo(addr,tmp,&hints,&first_info);
    if(r==0){
        while(first_info!=NULL){
            addressin=(struct sockaddr_in *)first_info->ai_addr;
            int ret=connect(sock,(struct sockaddr *)addressin,(socklen_t)sizeof(struct sockaddr_in));
            if(ret==0){
                send(sock,mess,strlen(mess),0);
                close(sock);
                return 0;
            }
            else{
                print("Probleme de connexion!\n");
            }
            close(sock);
            first_info=first_info->ai_next;
        }
    }
    return -1;

}*/

int send_msg(int port, char * addr, char * mess){//A faire peut etre avec gettaddrinfo
    struct sockaddr_in adress_sock;
    adress_sock.sin_family = AF_INET;
    adress_sock.sin_port = htons(port);
    inet_aton(convert(addr),&adress_sock.sin_addr);
    int descr=socket(PF_INET,SOCK_STREAM,0);
    int r=connect(descr,(struct sockaddr *)&adress_sock,sizeof(struct sockaddr_in));
    if(r!=-1){
        send(descr,mess,strlen(mess),0);
        close(descr);
    }
    return r!=-1;
}

void diffuser_message(liste_dif * lst){
    extern char id[9];
    char texte[141];
    saisie(140, texte, "Entrez le message : ", ALPHANUMERIC);
    char mess [157];
    snprintf(mess, 157,"MESS %s %s\r\n",id,texte);
    while(lst!=NULL){
        printf("diff mess : %s\n",lst->diff->id);
        if(!send_msg(atoi(lst->diff->port2), lst->diff->ip2, mess)){
            char tmp[52];
            snprintf(tmp,52,"Envoie du message au diffuseur %s impossible.",lst->diff->id);
            
        }
        lst=lst->suivant;
    }
}

int check_old_mess(char * buff){
    int res=1,i;
    res = !memcmp("OLDM",buff,4);
    for(i=5;i<9;i++) res=isdigit(buff[i]);
    return res;
}

void reception_old_mess(int sock,int nb){
    char tmp[162];//161
    extern int out;
    long lus=-1;
    int nb_recu = 0;
    tmp[161]='\0';
    char * tmp0="OLD MESS : \n";
    char * tmp2 = "\n          ----------          \n";

    while((lus=recv(sock, tmp, 161, 0))!=-1  && nb_recu<nb){
        if(lus == 6 && !strcmp(tmp,"ENDM\r\n")){//Ptite correction a faire
            return;
        }
        if(lus != 161){
            printf("Format errone, abandon.\n");
            return;
        }
        if(!check_old_mess(tmp)){
            printf("Format errone, abandon.-1-");
            return;
        }
        
        write(out,tmp0,strlen(tmp0));
        write(out,tmp,strlen(tmp));
        write(out,tmp2,strlen(tmp2));
        
        nb_recu++;
    }
}
/*
void display_old_mess(liste_dif * lst){
    char tmp [3];
    saisie(2, tmp,"Combien de message a recuperer ? : ", NUMERIC);
    int nb = atoi (tmp);
    
    char oldMess[9];
    snprintf(oldMess, 9, "LAST %s\r\n",tmp);
    while(lst!=NULL){
        
        int sock=socket(PF_INET,SOCK_STREAM,0);
        struct sockaddr_in *addressin;
        struct addrinfo *first_info;
        struct addrinfo hints;
        bzero(&hints,sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype=SOCK_STREAM;
        char tmp[5];
        tmp[4]='\0';
        snprintf(tmp,5,"%s",lst->diff->port2);
        int r=getaddrinfo(lst->diff->ip2,tmp,&hints,&first_info);
        if(r==0){
            if(first_info!=NULL){
                addressin=(struct sockaddr_in *)first_info->ai_addr;
                int ret=connect(sock,(struct sockaddr *)addressin,(socklen_t)sizeof(struct sockaddr_in));
                if(ret==0){
                    send(sock,oldMess,9,0);
                    reception_old_mess(sock,nb);
                }else{
                    char tmp[56];
                    snprintf(tmp,56,"Envoie de la demande au diffuseur %s impossible.",lst->diff->id);
                    print(tmp);
                }
            }
        }
        close(sock);
        lst=lst->suivant;
    }
}
*/


void display_old_mess(liste_dif * lst){
    char tmp [4];
    saisie(3, tmp,"Combien de message a recuperer ? : ", NUMERIC);
    int nb = atoi (tmp);
    
    char oldMess[11];//CHANGEMENT
    snprintf(oldMess, 11, "LAST %s\r\n",tmp);//CHANGEMENT
    while(lst!=NULL){
        struct sockaddr_in adress_sock;
        adress_sock.sin_family = AF_INET;
        adress_sock.sin_port = htons(atoi(lst->diff->port2));
        inet_aton(convert(lst->diff->ip2),&adress_sock.sin_addr);
        int descr=socket(PF_INET,SOCK_STREAM,0);
        int r=connect(descr,(struct sockaddr *)&adress_sock,sizeof(struct sockaddr_in));
        if(r==-1){
            char tmp[56];
            snprintf(tmp,56,"Envoie de la demande au diffuseur %s impossible.",lst->diff->id);
            
        }
        send(descr,oldMess,10,0);//CHANGEMENT
        reception_old_mess(descr,nb);
        close(descr);
        lst=lst->suivant;
    }
}

int length(liste_dif * lst){
    int nb=0;
    while(lst!=NULL){
        nb++;
        lst=lst->suivant;
    }
    return nb;
}

void  suppression(liste_dif * lst){
    if(liste == NULL || liste==0 || lst == NULL || lst==0){
        return;
    }
    if(liste==lst){
        liste=NULL;
        return;
    }
    liste_dif * tmp = liste;
    while(tmp != NULL){
        if(tmp->suivant==lst){
            tmp->suivant=lst->suivant;
            return;
        }
        tmp=tmp->suivant;
    }
    
}

void breakpointe(){};

void gestion_menu_diff(liste_dif * tmp,int flag){
    printf("ETAPE 1");
    int nb=length(tmp);
    liste_dif ** selection = (menu_diffuseurs(tmp,nb));
    printf("ETAPE 2");
    
    liste_dif * lst;
    
    if(selection !=NULL){
        clear_liste(&liste_tmp);
       lst=*selection;
    }else{
        return;
    }
    breakpointe();
    
    switch (menu_action_diff(flag)) {
        case 0:
            while(lst!=NULL) {// ajout a la liste de lecture
                init_sockUDP(lst->diff);
                pthread_t * th = malloc(sizeof(pthread_t));
                lst->diff->th=th;
                pthread_create(th, NULL, run_lecture, lst->diff);
                lst=lst->suivant;
            }
            transfert_liste(*selection, &liste);
            break;
        case 1:
            diffuser_message(*selection);//pas tester
            break;
        case 2:
            display_old_mess(*selection);//pas tester
            break;
        case 3:
            break;
    }
     clear_liste(&liste_tmp);
}


void lecture_gestionnaire(int sock){
    long lus;
    char buff[1025];
    char type[5];
    int nb;
    buff[1024]='\0';
    type[4]='\0';
    
    send(sock, "LIST\r\n", 6, 0);
    
    lus=recv(sock, buff, 9, 0);
    buff[lus]='\0';
    printf("-%s-\n",buff);
    if(lus!=9){
        print("Erreur de format -1-, fin de la connexion au gestionnaire.");
        return;
    }
    snprintf(type,5,"%s",buff);
    if(strcmp("LINB", type)){
        print("Erreur de format -2-, fin de la connexion au gestionnaire.");
        return;
    }
    nb=atoi((buff+5));
    printf("nb : %d\n",nb);
    
    if(nb<0 || nb>99){
        print("Erreur de format -3-, fin de la connexion au gestionnaire.");
        return;
    }
    if (!genere_diff(sock, nb)){
        clear_liste(&liste_tmp);
        return;
    }
    
    gestion_menu_diff(liste_tmp,LECTURE_GEST);
}

















