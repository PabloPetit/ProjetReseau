#include "menu_principal.h"



int menu_principal(){
    
    extern liste_msg * lt_at;
    extern liste_msg * lt_at;
    extern diffuseur * diff;
    extern int out;
    char mess[141];
    char fic_name[35];
    int ok=0;
    char * intro, *args[7];
    intro = "Menu Principal du Diffuseur:";
    args[0]="Envoyer un message";
    args[1]="Charger fichier";
    args[2]="Afficher la liste d'attente";
    args[3]="S'enregistrer a un gestionnaire";
    args[4]="Afficher les informations du diffuseur";
    args[5]="Changer le fichier de sortie du mode verbeux";
    args[6]="Quitter";
    
    while(!ok){
        switch(menu_simple(intro,args,7)){
            case 0:
                saisie(140,mess,"Entrer un message",ALPHANUMERIC);//Bug par la, surement une histoire de verrou
                add_msg(make_msg(diff->id, "DIFF", mess));
                print_liste(lt_at);
                break;
            case 1:
                printf("Entrer l'adresse du fichier\n");
                fic_name[saisie(35, fic_name, "Entrer l'adresse du fichier", ALNU_SIZELESS)]='\0';
                charger_fichier(fic_name);
                print_liste(lt_at);
                break;
            case 2:
                print_liste(lt_at);
                break;
            case 3:
                connexion_gestionnaire();
                break;
            case 4:
                print_diffuseur(diff);
                print("");
                break;
            case 5:
                out = saisie_tty_out();
                break;
            case 6:
                ok=1;
                break;
        }
    }
    return 0;
}
