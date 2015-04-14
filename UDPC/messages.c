#include "messages.h"


liste_msg * lt_at;
liste_msg * lt_df;

pthread_mutex_t verrou= PTHREAD_MUTEX_INITIALIZER;

void init_list_msg(){
	lt_at = malloc(sizeof(liste_msg));
	lt_at->index = 0;
	lt_at->msg=NULL;
	lt_at->suivant=NULL;
	
	lt_df = malloc(sizeof(liste_msg));
	lt_df->index = 0;
	lt_df->msg=NULL;
	lt_df->suivant=NULL;
}

liste_msg * make_list_msg(int index,message * msg){
	liste_msg * res = malloc(sizeof(liste_msg));
	res->index = index;
	res->msg=msg;
	res->suivant=NULL;
	return res;
}

message * init_msg(){
	message* msg = malloc(sizeof(message));

	msg->type = malloc(sizeof(char)*5);
	msg->num_mess = malloc(sizeof(char)*5);
	msg->id = malloc(sizeof(char)*9);
	msg->message = malloc(sizeof(char)*141);

	msg->type[4]='\0';
	msg->num_mess[4]='\0';
	msg->id[8]='\0';
	msg->message[140]='\0';

	return msg;
}

message * make_msg(char * type,char * id, char * mess){
	message * msg = init_msg();

	sprintf(msg->type,type);

	memset(msg->message,'#',140);
	msg->message[sprintf(msg->message,"%s",mess)]='#';

	sprintf(msg->id,"%s",id);
	return msg;
}
/*
void add_msg_df(message * msg){
	liste_msg * lt = lt_df;
	if(lt->mg==NULL){
		lt->msg=msg;
		return;
	}
	while(lt->suivant!=NULL)lt=lt->suivant;
	lt->suivant = make_list_msg//c'est nul faut passer direct les pointeur de listes
}*/

void add_msg(liste_msg * liste,message * msg){
	//pthread_mutex_lock(&verrou);
	int index=0;
	liste_msg * lt = liste;
	if(lt->msg==NULL){
		printf("IF 1\n");
		lt->msg=msg;
		sprintf(msg->num_mess,"0000");
		return;
	}
	index++;
	while(lt->suivant!=NULL){
		lt = lt->suivant;
		index = (index<9999)?index+1:0;
	}

	char tmp[4];
	sprintf(tmp,"%d",index);
	memset(msg->num_mess,'0',4);
	sprintf((msg->num_mess+(4-strlen(tmp))),"%d",index);

	lt->suivant = make_list_msg(index,msg);
	//pthread_mutex_unlock(&verrou);
}

void free_msg(message * msg){
	//pthread_mutex_lock(&verrou);
	free(msg->type);
	free(msg->num_mess);
	free(msg->id);
	free(msg->message);
	free(msg);
	//pthread_mutex_unlock(&verrou);
}


message * transfert_msg(){
	//pthread_mutex_lock(&verrou);
	liste_msg * lt=lt_at;
	if(lt==NULL || lt->msg==NULL){
		//pthread_mutex_unlock(&verrou);
		return NULL;
	}
	if(lt->suivant== NULL){
		message * mess = lt->msg;
		add_msg(lt_df,mess);
		lt->msg=NULL;
		pthread_mutex_unlock(&verrou);
		return mess;
	}
	lt_at = lt->suivant;
	message * mess = lt->msg;
	liste_msg * tmp=lt_df;
	lt_df=lt;
	lt_df->suivant=tmp;
	//pthread_mutex_unlock(&verrou);
	return mess;
}

int get_last_index(liste_msg * liste){
	//pthread_mutex_lock(&verrou);
	liste_msg * lt=liste;
	while(lt->suivant != NULL)lt=lt->suivant;
	//pthread_mutex_unlock(&verrou);
	return lt->index;
}

void print_liste(liste_msg * liste){
	//pthread_mutex_lock(&verrou);
	liste_msg * lt = liste;
	
	if(lt==NULL || lt->msg==NULL){
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
}

void charger_fichier(char * path){
	//pthread_mutex_lock(&verrou);
	int fic,lus,i;
	extern diffuseur * diff;
	char * buff = malloc(sizeof(char)*1025);
	buff[1024]='\0';

	if((fic=open(path,O_RDONLY))==-1){
		printf("Impossible de lire le fichier\n");
		//pthread_mutex_unlock(&verrou);
	}
	while((lus=read(fic,buff,1024))!=0){
		int index_point=0;
		for(i=0;i<lus;i++){
			if(buff[i]=='.' || i-index_point==140 || i==lus-1){
				char * str = malloc(sizeof(char)*((i-index_point)+2));
				snprintf(str,(i-index_point+2),"%s",(buff+index_point));
				message * mess = make_msg("DIFF",diff->id,str);
				add_msg(lt_at,mess);
				index_point=i+1;
				free(str);
			}
		}
	}
	//pthread_mutex_unlock(&verrou);
}
