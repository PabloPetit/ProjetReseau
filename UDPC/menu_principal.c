#include "menu_principal.h"



int menu_principal(){
    
    extern liste_msg * lt_at;
    extern liste_msg * lt_at;
    char *fic_name, *msg;
    fic_name = malloc(sizeof(char)*20);
    //message msg = malloc(sizeof(message));
    int ok=0;
    char * intro, *args[4];
    intro = "Menu Principal du Diffuseur:";
    args[0]="Envoyer un message";
    args[1]="Charger fichier";
    args[2]="Afficher la liste d'attente";
    args[3]="S'enregistrer a un gestionnaire";
    args[4]="Quitter";
    
    while(!ok){
        switch(menu_simple(intro,args,5)){
            case 0:
                //envoyer un message ;
                printf("Entrer un message\n");
                //saisie(140,msg,"Entrer un message",0);
                //add_msg(msg);
                sleep(3);
                break;
            case 1:
                //system("clear");
                printf("Entrer l'adresse du fichier\n");
                scanf("%20s",fic_name);
                charger_fichier(fic_name);
                print_liste(lt_at);
                sleep(3);
                break;
            case 2:
                print_liste(lt_at);
                sleep(3);
                break;
            case 4:
                ok=1;
                break;
        }
    }
    return 0;
}
