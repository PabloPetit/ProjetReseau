#include "main.h"

int out = 1;

int  saisie_tty_out(){
    char path[35];
    path[34]='\0';
    path[saisie(34, path,"Veuillez entrer le chemin du terminal/fichier vers lequel\nsera rediriger le mode verbeux", ALNU_SIZELESS)]='\0';
    printf("PATH : -%s-\n",path);
    int d;
    d=open(path,O_WRONLY);
    if (d == -1){
        print("Vous devez entrer un chemin valide.");
        return saisie_tty_out();
    }
    return d;
}
void print_help(){
    printf("\nDiffuseur de Message - C\n\n");
    printf("La ligne de commande doit contenir : \n");
    printf("  -id suivi de l'identifient du diffuseur, de 1 a 8 characteres\n");
    printf("  -r suivi du numero de port de reception, entre 0 et 9999\n");
    printf("  -m suivi du numero de port de  multi-diffusion, entre 0 et 9999\n");
    printf("  -ip suivi de l'addresse de multi-diffusion\n\n");
    printf("  -f (optionnel) Permet de charger et découper un fichier texte a diffuser\n");
    printf("Les deux port doivent etre different.\n");
    printf("\nSinon : \n\n  -d uniquement pour lancer le diffuseur avec les paremetres par défault.\n\n");
}

int check_id_valide(char* id){
    return (strlen(id)<9 && strlen(id)>0);
}

//verification port
void check_port_valide(char* port_multi,char* port_tcp){
    int portR,portM;
    portR=atoi(port_tcp);
    portM=atoi(port_multi);
    if(portR==portM){
        printf("Les deux port doivent etre differents.\n");
        exit(1);
    }
    if(portR>9999 || portR <0 || portM>9999 || portM<0){
        printf("Les numeros de ports doivent etre compris etre 0 et 9999.\n");
        exit(1);
    }
}
//affiche les infos finales
void print_param_final(char * id,char * portR,char * portM, char * ipv4){
    printf("\nLes parametre entrés sont : \n\n");
    printf("Identifiant : %s\n",id);
    printf("Port de récéption : %s\n",portR);
    printf("Port de multi-diffusion : %s\n",portM);
    printf("Addresse IPv4 : %s\n\n",ipv4);
}

int strfd(char * src, char c){
    int i=0;
    for(i=0;i<strlen(src);i++){
        if(src[i]==c){
            break;
        }
    }
    return i;
}

//verification syntaxe ip
char* format_number_ipv4(int number){
    if(number < 0 || number > 255){
        printf("Format IPv4 incorrect.\n");
        exit(1);
    }
    char * res = calloc(sizeof(char),4);
    res[4]='\0';
    if(number <10){
        sprintf(res,"00%d",number);
    }else if(number < 100){
        sprintf(res,"0%d",number);
    }
    else{
        sprintf(res,"%d",number);
    }
    return res;
}

char * format_ipv4(char *ipv4){
    //faudrai penser a verifier si l'addresse et bien pour le multi-diff
    char *res;
    int p1,p2,p3,n1,n2,n3,n4;
    if(strlen(ipv4)>15){
        printf("Format IPv4 incorrect.\n");
        exit(1);
    }
    p1=0,p2=0,p3=0;
    p1=strfd(ipv4,'.');
    p2=strfd((ipv4+p1+1),'.')+p1+1;
    p3=strfd((ipv4+p2+1),'.')+p2+1;
    ipv4[strlen(ipv4)]='\0';
    ipv4[p1]='\0';
    ipv4[p2]='\0';
    ipv4[p3]='\0';
    n1=atoi(ipv4);
    n2=atoi(ipv4+p1+1);
    n3=atoi(ipv4+p2+1);
    n4=atoi(ipv4+p3+1);
    res = malloc(sizeof(char)*16);
    res[15]='\0';
    sprintf(res,"%s.%s.%s.%s",format_number_ipv4(n1),format_number_ipv4(n2),format_number_ipv4(n3),format_number_ipv4(n4));
    return res;
}

int main(int argc, char * argv[]){
    extern diffuseur * diff;
    extern liste_msg * lt_at;
    extern liste_msg * lt_df;
    int i,d,f;
    char *ipv4, *id, *port_multi, *port_tcp, *path;
    ipv4=NULL; id=NULL; port_multi=NULL; port_tcp=NULL; path=NULL;
    i=0, d=0, f=0;
    ipv4=malloc(sizeof(char)*(strlen(argv[i])+1));
    ipv4[strlen(argv[i])]='\0';
    port_tcp = malloc(sizeof(char)*5);
    port_multi = malloc(sizeof(char)*5);
    port_tcp[4]='\0';
    port_multi[4]='\0';
    
    //traitement des arguments
    for(i=1;i<argc;i++){
        if(strcmp("-id",argv[i])==0){
            if(++i<argc && check_id_valide(argv[i])){
                id=argv[i];
            }else{
                printf("L'argument id est invalide\n");
                exit(1);
            }
        }
        else if(strcmp("-r",argv[i])==0){
            if(++i<argc){
                sprintf(port_tcp,"%s",argv[i]);
            }else{
                printf("L'argument port de reception est invalide\n");
                exit(1);
            }
        }
        else if(strcmp("-m",argv[i])==0){
            if(++i<argc){
                sprintf(port_multi,"%s",argv[i]);
            }else{
                printf("L'argument port de multi-diffusion est invalide\n");
                exit(1);
            }
        }
        else if(strcmp("-ip",argv[i])==0){
            if(++i<argc){
                sprintf(ipv4,"%s",argv[i]);
            }else{
                printf("L'argument port de ip est invalide\n");
                exit(1);
            }
        }else if(strcmp("-h",argv[i])==0 || strcmp("-h",argv[i])==0){
            print_help();
            exit(0);
        }
        else if(strcmp("-d",argv[i])==0){
            d++;
        }
        else if(strcmp("-f",argv[i])==0){
            if(++i<argc){
                f++;
                path = malloc(sizeof(char)*1025);
                sprintf(path,"%s",argv[i]);
            }else{
                printf("L'argument port de ip est invalide\n");
                exit(1);
            }
        }
    }
    
    if(argc<9 && !d){
        printf("Il manque des arguments, -h ou -help\n");// marche pas, mettre un int pour chaque param
        exit(0);
    }else if(d){//parametre par defaut
        id="Radio";
        port_tcp="4242";
        port_multi="4272";
        char tmp[] = "237.0.0.2";
        ipv4= format_ipv4(tmp); 
    }else{
        ipv4 = format_ipv4(ipv4);
        check_port_valide(port_multi,port_tcp);
    }
    
    print_param_final(id,port_tcp,port_multi,ipv4);
    
    
    diff = make_diffuseur(id,port_tcp,port_multi,ipv4,3);
    
    print_diffuseur(diff);
    
    print("");
    
    if(path!=NULL && f){

        charger_fichier(path);
    }
    
    print_liste(lt_at);

    pthread_t thread_tcp;
    pthread_t thread_dif;
    
    pthread_create(&thread_tcp,NULL,run_server_tcp,NULL);
    pthread_create(&thread_dif,NULL,diffuseur_run,NULL);
    
    menu_principal();
    
    return 0;
}
