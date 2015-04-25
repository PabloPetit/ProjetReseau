import java.io.*;
import java.net.*;


public class MenuPrincipal {

    public static void changerId(){
        System.out.println("Identifiant Actuel : "+Main.ID);
        Main.ID=Main.saisieId();
        System.out.println("\nVotre nouvel identifiant est : " + Main.ID + "\n");
    }


    public static void run(){
        boolean ok=false;
        while(!ok)
        switch(new MenuSimple("Menu Principal : ",new String[]{"Changer d'id","Se connecter à un gestionnaire","Parcourir Diffuseur","Quitter"}).run()){
            case 0://Change id
                    changerId();
                break;
            case 1://Connection gestionnaire
                Gestionnaire.connexionGestionnaire();
                break;
            case 2://Parcourir diffuseeur
                break;
            case 3://Quit
                ok = true;
                break;
        }

    }
}
