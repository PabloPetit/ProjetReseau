#include "server_tcp.h"

void post_old_msg(int sock,int nb){
    extern liste_msg * lt_df;
    liste_msg * lt=lt_df;
    int i=0;
    
    if(lt==NULL || lt==0) return;
    
    while(i<nb && lt->suivant != NULL){
        char buff[164];
        sprintf(buff,"OLDM %s %s %s\r\n",lt->msg->num_mess,lt->msg->id,lt->msg->message);
        send(sock,buff,strlen(buff),0);
        lt=lt->suivant;
        i++;
    }
    send(sock,"ENDM\r\n",(sizeof(char)*6),0);
}

int match_message(char * msg,long size,int sock){
    char type[5];
    if(size<8||size>156){
        return 1;
    }
    snprintf(type,5,"%s",msg);
    if(strcmp("MESS",type)==0){
        if(size<15)return 1;
        char id[9],mess[141];
        
        snprintf(id,9,"%s",(msg+5));
        snprintf(mess, size-15,"%s",(msg+14));
        
        add_msg(make_msg(id, "DIFF", mess));
        
        char tmp[9]="ACKM\r\n";
        tmp[8]='\0';
        send(sock,tmp,9,0);
    }else if(strcmp("LAST",type)==0){
        if(size!=10)return 1;
        int nb;
        if((nb=atoi((msg+5)))<0)return 2;
        post_old_msg(sock,nb);
    }
    return 0;
}

void * run_client(void * arg){
    long recu;
    int sock= *((int *)arg);
    char buff[1025];
    buff[1024]='\0';
   
    
    printf("\nUn nouveau client c'est connecter.\n\n");
    
    recu=recv(sock,buff,1024*sizeof(char),0);
    
    if(!match_message(buff,recu,sock)){
        printf("La demande du client ne respecte pas le format, connexion fermée.\n");
    }
    
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
