#include "menu.h"

//Potentiel equivalent a clear : printf("\033[H\033[2J");

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


int menu_diffuseurs(liste_dif * lst,int nb){//La liste tmp
    int selected,ok,i,mode_multi;
    selected=0,ok=0,i=0,mode_multi=0;
    int tab_select[nb];
    liste_dif * tabList[nb];
    memset(tab_select,0,sizeof(int)*nb);
    
    liste_dif * ld = lst;
    while(ld!=NULL){
        tabList[i++] = ld;
        ld=ld->suivant;
    }
    //printf("NB : %d i : %d\n",nb,i);
    
    while(!ok){
        system("clear");
        printf("Liste des Diffuseurs : \n\n");
        for(i=0;i<nb;i++){
            if(!mode_multi){
                if(i==selected){
                    printf("\e[1;34m-> %s\e[0m\n",tabList[i]->diff->id);
                }else{
                    printf("   %s\n",tabList[i]->diff->id);
                }
            }else{
                if(tab_select[i] && i==selected){
                    printf("\e[1;31m-> %s\e[0m\n",tabList[i]->diff->id);
                }
                else if(tab_select[i]){
                    printf("\e[1;31m   %s\e[0m\n",tabList[i]->diff->id);
                }
                else if (i==selected){
                    printf("\e[1;34m-> %s\e[0m\n",tabList[i]->diff->id);
                }
                else{
                    printf("   %s\n",tabList[i]->diff->id);
                }
            }
        }
        if(mode_multi){
            if (i==nb) {
               printf("\e[1;34mMode multi-diffuseurs.\e[0m\n");
            }else{
                printf("   Mode multi-diffuseurs.");
            }
        }else{
            if (i==nb) {
                printf("\e[1;34mMode simple\e[0m\n");
            }else{
                printf("   Mode simple.");
            }
        }
        if(i==nb+1){
            printf("\e[1;34m-> Quitter\e[0m\n");
        }
        else{
            printf("\e[1;34m   Quitter\e[0m\n");
        }
        
        int tmp = capture_select_simple(selected,nb+1);// BAS = 0 ; HAUT = 1 ; ENTER = -1 ; ELSE = -2
        
        if(tmp==-1){
            if(mode_multi){
                if(selected<nb) tab_select[selected]=!tab_select[i];
                else if (selected==nb){
                    memset(tab_select,0,sizeof(int)*nb);
                    mode_multi=0;
                }else{
                    //Quitter
                    return -1;
                }
            }else{
                if(selected<nb) return selected;
                else if (selected==nb){
                    mode_multi=1;
                }else{
                    //Quitter
                    return -1;
                }
            }
        }else if(tmp==0){
            selected = (selected+1<nb+1)?selected+1:selected;
        }else if(tmp==1){
            selected = (selected-1>=0)?selected-1:selected;
        }
        
    }
    return 1;
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


