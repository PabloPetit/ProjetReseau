#include "server_tcp.h"

extern int out;

void post_old_msg(int sock,int nb){
    extern liste_msg * lt_df;
    extern pthread_mutex_t verrou;
    pthread_mutex_lock(&verrou);
    liste_msg * lt=lt_df;
    int i=0;
    
    if(lt==NULL || lt==0){
        send(sock,"ENDM\r\n",(sizeof(char)*6),0);
        pthread_mutex_unlock(&verrou);
        return;
    }
    
    while(i<nb && lt->suivant != NULL){
        char buff[164];
        sprintf(buff,"OLDM %s %s %s\r\n",lt->msg->num_mess,lt->msg->id,lt->msg->message);
        send(sock,buff,strlen(buff),0);
        lt=lt->suivant;
        i++;
    }
    send(sock,"ENDM\r\n",(sizeof(char)*6),0);
    pthread_mutex_unlock(&verrou);
}

int match_message(char * msg,long size,int sock){
    char type[5];
    
    if(size<9||size>156){
        write(out,"Message de taille incorrecte\n",strlen("Message de taille incorrecte\n"));
    }
    snprintf(type,5,"%s",msg);
    if(strcmp("MESS",type)==0){
        if(size<15){
            write(out,"Message de taille incorrecte(2)\n",strlen("Message de taille incorrecte(2)\n"));
            return 0;
        }
        char id[9],mess[141];
        
        snprintf(id,9,"%s",(msg+5));
        snprintf(mess, size-15,"%s",(msg+14));
        
        add_msg(make_msg(id, "DIFF", mess));
        
        char tmp[9]="ACKM\r\n";
        tmp[8]='\0';
        send(sock,tmp,9,0);
    }else if(strcmp("LAST",type)==0){
        if(size!=10){
            write(out,"Message de taille incorrecte(3)\n",strlen("Message de taille incorrecte(3)\n"));
            return 0;
        }
        int nb;
        if((nb=atoi((msg+5)))<0)return 2;
        post_old_msg(sock,nb);
    }else{
        printf("Type non reconnu\n");
        return 0;
    }
    return 1;
}

void * run_client(void * arg){
    long recu;
    int sock= *((int *)arg);
    char buff[1025];
    buff[1024]='\0';
   
    write(out,"\nUn nouveau client c'est connecter.\n\n",strlen("\nUn nouveau client c'est connecter.\n\n"));
    
    recu=recv(sock,buff,1024*sizeof(char),0);
    
    if(!match_message(buff,recu,sock)){
        write(out,"La demande du client ne respecte pas le format, connexion fermée.\n",strlen("La demande du client ne respecte pas le format, connexion fermée.\n"));
    }
    write(out,"Transmission terminee\n",strlen("Transmission terminee\n"));
    close(sock);
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
