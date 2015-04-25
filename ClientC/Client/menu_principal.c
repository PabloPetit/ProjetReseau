#include "menu_principal.h"


int menu_principal(){
    int ok=0;
    char * intro, *args[5];
    intro = "Menu Principal :";
    args[0]="Changer d'identifiant.";
    args[1]="Consulter un gestionnaire";
    args[2]="Se connecter à un gestionnaire";
    args[3]="Liste des diffuseurs";
    args[4]="Quitter";
    
    while(!ok){
        switch(menu_simple(intro,args,5)){
            case 0:
                saisie_id();
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                ok=1;
                break;
        }
    }
    return 0;
}
