#include "saisie.h"


void print(char * msg){
    int c;
    printf("\n%s\n\n",msg);
    fflush(stdout);
    while((c=getchr())!=10);
}


int saisie(int nb,char * buff,const char * intro,int flag){
    char c;
    buff[nb]='\0';
    memset(buff,'_',nb);
    int i=0;
    int ok=1;
    while(ok){
        system("clear");
        printf("%s\n",intro);
        printf("%s\n",buff);
        c=getchr();
        if((int)c==127 && i>0 && (flag!=IPV4 || (flag==IPV4 && i!= 4 && i!= 8 && i!= 12))){//ya un truc a faire sur les if de ipv4
            buff[--i]='_';
            continue;
        }
        if((int)c==127 && flag==IPV4 &&( i== 4|| i== 8 || i== 12)){
            buff[--i]='_';
            buff[--i]='_';
        }
        if(i==nb){
            if(c==10)ok=0;
        }else{
            switch(flag){
                case ALPHANUMERIC :
                    if(c=='#' || (c==10 && i>0)){
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
                case IPV4:
                    if(isdigit(c) && (i==2 || i==6 ||i==10)){
                        buff[i++]=c;
                        buff[i++]='.';
                    }else if(isdigit(c)){
                        buff[i++]=c;
                    }
                    break;
                case ALNU_SIZELESS :
                    if(c==10 && i>0){
                        ok=0;
                        break;
                    }
                    if(isalnum(c) || c=='/' || c=='.' || c=='~'){
                        buff[i++]=c;
                    }
                    break;
                default:
                    buff[i++]=c;
                    break;
            }
        }
        fflush(stdout);
    }
    return i;
}
