#include "main.h"

char id[9];


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
    saisie(8, id, "Veuiller saisir un identifiant :\n");
}

int main(int argc, const char * argv[]) {
    system("clear");
    saisie_id();
    menu_principal();
    return 0;
}

