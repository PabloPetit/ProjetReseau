#include "menu.h"

//Potentiel equivalent a clear : printf("\033[H\033[2J");
void breakpoint(){
}
int capture_select_simple(int i){// BAS = 0 ; HAUT = 1 ; ENTER = -1 ; ELSE = -2
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

/*
liste_dif ** menu_diffuseurs(liste_dif * lst,int nb){//La liste tmp
    int selected,ok,i;
    selected=0,ok=0,i=0;
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
            if(tab_select[i] && i==selected){
                printf("-> \e[1;31m%s\e[0m\n",tabList[i]->diff->id);
            }
            else if(tab_select[i]){
                printf("\e[1;31m   %s\e[0m\n",tabList[i]->diff->id);
            }
            else if (i==selected){
                printf("-> \e[1;34m%s\e[0m\n",tabList[i]->diff->id);
            }
            else{
                printf("   %s\n",tabList[i]->diff->id);
            }
        }
        
        if (selected==nb) {
            printf("-> \e[1;34mReinitialiser\e[0m\n");
        }else{
            printf("   Reinitialiser\n");
        }
        if (selected==nb+1) {
            printf("-> \e[1;34mValider\e[0m\n");
        }else{
            printf("   Valider\n");
        }
        
        if(selected==nb+2){
            printf("-> \e[1;34mQuitter\e[0m\n");
        }
        else{
            printf("   Quitter\n");
        }
        
        int tmp = capture_select_simple(selected);// BAS = 0 ; HAUT = 1 ; ENTER = -1 ; ELSE = -2
        
        if(tmp==-1){
            if(selected<nb) tab_select[selected]=!tab_select[selected];
            else if (selected==nb){
                memset(tab_select,0,sizeof(int)*nb);
            }else if(selected==nb+1){
                ok = 1;
            }else{
                return NULL;
            }
        }else if(tmp==0){
            selected = (selected+1<nb+3)?selected+1:selected;
        }else if(tmp==1){
            selected = (selected-1>=0)?selected-1:selected;
        }
        
    }
    liste_dif ** retour = malloc(sizeof(liste_dif*));
    for(i=0;i<nb;i++){
        if (tab_select[i]){
            add_diff(retour, tabList[i]->diff);
        }
    }
    
    return retour;
}*/

int menu_simple(char * intro, char * args[],int length){
    int selected,ok,i;
    selected=0,ok=0;
    while(!ok){
        system("clear");
        printf("%s\n\n",intro);
        for(i=0;i<length;i++){
            if(i==selected){
                printf("-> \e[1;34m%s\e[0m\n",args[i]);
            }else{
                printf("   %s\n",args[i]);
            }
        }
        int tmp = capture_select_simple(selected);
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


