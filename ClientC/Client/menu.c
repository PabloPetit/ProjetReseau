#include "menu.h"

int capture_select_simple(int i,int max){// BAS = 0 ; HAUT = 1 ; ENTER = -1 ; ELSE = -2
    char c1,c3;
    c1=getchr();
    if(c1==10){//trouver le code entrer
        return -1;
    }else if(c1==27){
        getchr();
        c3=getchr();
        if(c3==65 ){//HAUT
            return 1;
        }else if(c3==66){//BAS<
            return 0;
        }else{
            return -2;
        }
    }else{
        return -2;
    }
    return -2;
}

int menu_simple(char * intro, char * args[],int length){
    int selected,ok,i;
    selected=0,ok=0;
    while(!ok){
        system("clear");
        printf("%s\n\n",intro);
        for(i=0;i<length;i++){
            if(i==selected){
                printf("\e[1;34m-> %s\e[0m\n",args[i]);
            }else{
                printf("   %s\n",args[i]);
            }
        }
        int tmp = capture_select_simple(selected,length);
        if(tmp==-1){
            return selected;
        }else if(tmp==0){
            selected = (selected+1<length)?selected+1:selected;
        }else if(tmp==1){
            selected = (selected-1>=0)?selected-1:selected;
        }
    }
    return selected;
}
