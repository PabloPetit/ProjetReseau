#include "saisie.h"



void saisie(int nb,char * buff,const char * intro,int flag){
    char c;
    buff[nb]='\0';
    memset(buff,'_',nb);
    int i=0;
    while(i<nb){
        system("clear");
        printf("%s\n",intro);
        printf("%s\n",buff);
        c=getchr();
        if((int)c==127 && i>0){
            buff[--i]='_';
            continue;
        }
        switch(flag){
            case ALPHANUMERIC :
                if(c=='#'){
                    while(i<nb)buff[i++]='#';
                    break;
                }
                if(isalnum(c)){
                    buff[i++]=c;
                }
                break;
            case NUMERIC :
                if(isdigit(c)){
                    buff[i++]=c;
                }
                break;
            default:
                buff[i++]=c;
                break;
        }
    }
}
