#include "saisie.h"

void saisie(int nb,char * buff,const char * intro){
    char c;
    buff[nb]='\0';
    memset(buff,'_',8);
    int i=0;
    while(i<nb){
        system("clear");
        printf("%s\n",intro);
        printf("%s\n",buff);
        c=getchr();
        if(isalnum(c) || c=='#'){
            buff[i++]=c;
        }
    }
}
