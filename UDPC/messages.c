#include "messages.h"


liste_msg * lt_at;
liste_msg * lt_df;
int cmp_msg = 0;
pthread_mutex_t verrou= PTHREAD_MUTEX_INITIALIZER;


void print_liste(liste_msg * liste){
    pthread_mutex_lock(&verrou);
    liste_msg * lt = liste;
    if(lt==NULL){
        printf("\nListe vide.\n\n");
        pthread_mutex_unlock(&verrou);
        return;
    }
    printf("\nListe des messages :\n\n");
    while(lt->suivant != NULL){
        printf("\n---N° %s Type : %s Identifiant : %s---\n\n",lt->msg->num_mess,lt->msg->type,lt->msg->id);
        printf("%s\n",lt->msg->message);
        lt=lt->suivant;
    }
    printf("\n---N° %s Type : %s Identifiant : %s---\n\n",lt->msg->num_mess,lt->msg->type,lt->msg->id);
    printf("%s\n",lt->msg->message);
    printf("\n--Fin de la liste --\n\n");
    print("");
    pthread_mutex_unlock(&verrou);
}

void format_mess(char * src,char * dest){
    memset(dest,'#',140);
    if(strlen(dest)<141){
        dest[sprintf(dest,"%s",src)]='#';
    }
    else{
         snprintf(dest,141,"%s",src);
    }
    dest[140]='\0';
}

void format_id(char * src,char * dest){
    memset(dest,'#',8);
    if(strlen(dest)<9){
        dest[sprintf(dest,"%s",src)]='#';
    }
    else{
        snprintf(dest,9,"%s",src);
    }
    dest[8]='\0';
}

void format_type(char * src,char * dest){
    memset(dest,'#',4);
    if(strlen(dest)<5){
        dest[sprintf(dest,"%s",src)]='#';
    }
    else{
        snprintf(dest,5,"%s",src);
    }
    dest[4]='\0';
}

void format_index(int src,char * dest){
    char tmp[4];
    sprintf(tmp,"%d",src);
    memset(dest,'0',4);
    sprintf((dest+(4-strlen(tmp))),"%d",src);
}

void maj_cmp(){
    cmp_msg=(cmp_msg<9999)?cmp_msg+1:0;
}

message * make_msg(char * id,char * type,char * mess){
    message * msg = malloc(sizeof(message));
    format_mess(mess,msg->message);
    format_id(id,msg->id);
    format_type(type,msg->type);
    format_index(cmp_msg,msg->num_mess);
    maj_cmp();
    return msg;
}

liste_msg * make_list(message * msg){
    liste_msg * lt = malloc(sizeof(liste_msg));
    lt->msg=msg;
    lt->suivant=NULL;
    return lt;
}

void add_msg(message * msg){
    pthread_mutex_lock(&verrou);
    liste_msg * lt = lt_at;
    
    if(lt==NULL || lt==0){
        lt_at=make_list(msg);
        pthread_mutex_unlock(&verrou);
        return;
    }
    while(lt->suivant!=NULL)lt=lt->suivant;
    lt->suivant=make_list(msg);
    pthread_mutex_unlock(&verrou);
}

message * transfert(){
    pthread_mutex_lock(&verrou);
    if(lt_at==NULL ||lt_at==0){
        pthread_mutex_unlock(&verrou);
        return NULL;
    }
    liste_msg * lt = lt_at;
    message * msg =lt->msg;
    
    lt_at=(lt_at->suivant==NULL)?NULL:lt->suivant;
    lt->suivant=lt_df;//Si ça merde, ça vient d'ici
    lt_df=lt;
    pthread_mutex_unlock(&verrou);
    return msg;
}

void charger_fichier(char * path){
    int fic,i;
    long lus;
    printf("%s\n",path );
    extern diffuseur * diff;
    char * buff = malloc(sizeof(char)*1025);
    buff[1024]='\0';
    
    if((fic=open(path,O_RDONLY))==-1){
        print("Impossible de lire le fichier\n");
        return;
    }else{
      while((lus=read(fic,buff,1024))!=0){
            int index_point=0;
            for(i=0;i<lus;i++){
                if(buff[i]=='.' || i-index_point==140 || i==lus-1){//Decoupage par phrase, si possible
                    char * str = malloc(sizeof(char)*((i-index_point)+2));
                    snprintf(str,(i-index_point+2),"%s",(buff+index_point));
                
                    add_msg(make_msg(diff->id, "DIFF", str));
                
                    index_point=i+1;
                    free(str);
                }
            }
        }
    }
}
