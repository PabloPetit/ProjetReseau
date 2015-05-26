#include "diffuseur.h"

diffuseur * diff;
extern int out;
void * diffuseur_run(void * arg){
    extern liste_msg * lt_at;
    extern liste_msg * lt_df;
    
    int sock=socket(PF_INET,SOCK_DGRAM,0);
    struct addrinfo *first_info;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype=SOCK_DGRAM;
    int r=getaddrinfo(diff->ipv4,diff->port_multi,NULL,&first_info);
    char * tmp="Message envoye : \n";
    if(r==0){
        if(first_info!=NULL){
            
            message * msg;
            struct sockaddr *saddr=first_info->ai_addr;
            
            while(42){
                msg=transfert();
                if(msg==NULL){
                    sleep(1);
                    continue;
                }
                
                //Bricolage :
                /*
                char mess_tmp[141];
                int i;
                
                for( i = 0;i<141;i++){
                    mess_tmp[i]='#';
                }
                mess_tmp[140]='\0';
                
                snprintf(mess_tmp, strlen(msg->message)+1,"%s",msg->message);
                
                if(strlen(msg->message)<140){
                    mess_tmp[strlen(msg->message)+1]='#';
                }
                */
                
                // /Bricole
                
                char buff[1024];
                sprintf(buff,"DIFF %s %s %s\r\n",msg->num_mess,msg->id,msg->message);
                write(out,tmp,strlen(tmp));
                write(out,buff,strlen(buff));
                sendto(sock,buff,strlen(buff),0,saddr,(socklen_t)sizeof(struct sockaddr_in));
                sleep(diff->interval);
            }
        }
    }
    return NULL;
}

diffuseur * make_diffuseur(char * id,char* portR,char * portM,char * ipv4,int interval){
    int i;
    diffuseur * dif = malloc(sizeof(diffuseur));
    dif->ipv4=malloc(sizeof(char)*16);
    dif->port_multi=malloc(sizeof(char)*5);
    dif->port_tcp=malloc(sizeof(char)*5);
    dif->id=malloc(sizeof(char)*9);
    
    dif->ipv4[15]='\0';
    dif->port_multi[4]='\0';
    dif->port_tcp[4]='\0';
    dif->id[8]='\0';
    dif->interval = interval;
    
    for(i=0;i<15;i++){
        dif->ipv4[i]=ipv4[i];
    }
    for(i=0;i<4;i++){
        dif->port_multi[i]='0';
        dif->port_tcp[i]='0';
    }
    
    sprintf((dif->port_multi+(4-strlen(portM))),"%s",portM);
    sprintf((dif->port_tcp+(4-strlen(portR))),"%s",portR);
    
    for(i=0;i<8;i++){
        if(i<strlen(id)){
            dif->id[i]=id[i];
        }else{
            dif->id[i]='#';
        }
    }
    return dif;
}

void print_diffuseur(diffuseur* dif){
    printf("\nInformations sur le Diffuseur : \n\n");
    printf("Id : %s\n",dif->id);
    printf("Port de Diffusion : %s\n",dif->port_multi);
    printf("Port de Reception : %s\n",dif->port_tcp);
    printf("Addresse de Diffusion : %s\n\n",dif->ipv4);
} 
