#include "main.h"

char id[9];
int out;

void format_id(char * src,char * dest){
    memset(dest,'#',8);
    if(strlen(dest)<9){
        dest[sprintf(dest,"%s",src)]='#';
    }
    else{
        snprintf(dest,9,"%s",src);
    }
    dest[8]='\0';
}

void saisie_id(){
    saisie(8, id, "Veuiller saisir un identifiant :\n",ALPHANUMERIC);
}

int  saisie_tty_out(){
    char path[35];
    path[34]='\0';
    path[saisie(34, path,"Veuillez entrer le chemin du terminal/fichier vers lequel\nsera rediriger l'entre UDP", ALNU_SIZELESS)]='\0';
    printf("PATH : -%s-\n",path);
    int d;
    d=open(path,O_WRONLY);
    if (d == -1){
        print("Vous devez entrer un chemin valide.");
        return saisie_tty_out();
    }
    return d;
}

char * intro = "\n\n\nRecepteur de messages : \n\n";

int main(int argc, const char * argv[]) {
    system("clear");
    saisie_id();
    out = saisie_tty_out();
    write(out,intro,strlen(intro));
    menu_principal();
    return 0;
}

