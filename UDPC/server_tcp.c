#include "server_tcp.h"

void bre(){}

int ajout_msg(char * id,char * mess){
    extern liste_msg * lt_at;
    if(strlen(id)!=8 || strlen(mess)>140)return 0;
    message * msg = make_msg("DIFF",id,mess);
    bre();
    add_msg(lt_at,msg);
    print_liste(lt_at);// C'est par la que ça déconne
    return 1;
}

void post_old_msg(int sock,int nb){
    extern liste_msg * lt_df;
    liste_msg * lt=lt_df;
    int i=0;
    
    if(lt==NULL || lt->msg==NULL) return;
    
    while(i<nb && lt->suivant != NULL){
        char buff[164];
        sprintf(buff,"OLDM %s %s %s\r\n",lt->msg->num_mess,lt->msg->id,lt->msg->message);
        send(sock,buff,strlen(buff),0);
        lt=lt->suivant;
        i++;
    }
    send(sock,"ENDM\r\n",(sizeof(char)*6),0);
}

void * run_client(void * arg){
    int recu;
    int sock= *((int *)arg);
    char buff[1025];
    buff[1024]='0';
    printf("NEW CLIENT \n");
    char type[5],id[9],mess[141],nb_mess[4];
    
    recu=recv(sock,buff,1023*sizeof(char),0);
    
    if(recu<5 || recu>=164){
        printf("\nMessage erroné reçu -Mauvais format- connexion fermé\n\n");
        close(sock);
        return NULL;
    }
    
    snprintf(type,5,"%s",buff);
    if(strcmp("MESS",type)==0 && recu >15){
        snprintf(id,9,"%s",(buff+5));
        snprintf(mess,141,"%s",(buff+14));
        mess[strlen(mess)-1]='\0';//-----
        if(ajout_msg(id,mess)){
            printf("Message de %s ajouté à la liste de diffusion.\n",id);
            char tmp[9]="ACKM\r\n";
            tmp[6]='\0';
            send(sock,tmp,7*sizeof(char),0);
            
        }else{
            printf("\nMessage erroné reçu -Mauvais format- connexion fermé\n\n");
        }
    }else if(strcmp("LAST",type)==0){
        int nb;
        snprintf(nb_mess,3,"%s",buff+5);
        if((nb=atoi(nb_mess))>0){
            post_old_msg(sock,nb);
        }else{
            printf("\nMessage erroné reçu -Valeur nb_mess incorrect- connexion fermé\n\n");
        }
    }else{
        printf("\nMessage erroné reçu -Type inconnu- connexion fermé\n\n");
    }
    printf("END OF RECV\n");
    close(sock);
    //free(sock);
    return NULL;
}


void *run_server_tcp(void *arg){
    extern diffuseur * diff;
    
    int sock=socket(PF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in sockaddress;
    sockaddress.sin_family=AF_INET;
    sockaddress.sin_port=htons(atoi(diff->port_tcp));
    sockaddress.sin_addr.s_addr=htonl(INADDR_ANY);
    
    int r=bind(sock,(struct sockaddr *)&sockaddress,sizeof(struct sockaddr_in));
    if(r==0){
        r=listen(sock,0);
        if(r==0){
            struct sockaddr_in caller;
            socklen_t si=sizeof(caller);
            while(1){
                int *sock2=(int *)malloc(sizeof(int));
                *sock2=accept(sock,(struct sockaddr *)&caller,&si);
                if(*sock2>=0){
                    pthread_t thread;
                    pthread_create(&thread,NULL,run_client,sock2);
                }
            }
        }
    } 
    return NULL;
}
