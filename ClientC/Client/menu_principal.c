#include "menu_principal.h"


int menu_principal(){
    int ok=0;
    char * intro, *args[4];
    intro = "Menu Principal du Client:";
    args[0]="Changer d'identifiant.";
    args[1]="Consulter un gestionnaire";
    args[2]="Liste des diffuseurs";
    args[3]="Quitter";
    
    while(!ok){
        switch(menu_simple(intro,args,4)){
            case 0:
                saisie_id();
                break;
            case 1:
                connexion_gestionnaire();
                break;
            case 2:
                break;
            case 3:
                ok=1;
                break;
        }
    }
    return 0;
}
