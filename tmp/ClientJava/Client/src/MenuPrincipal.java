import java.util.Scanner;

public class MenuPrincipal {

    public static String convertId(String id) {
        String res;
        if (id.length() < 8) {
            res = id;
            for (int i = id.length(); i < 8; i++) {
                res += '#';
            }
            return res;
        } else if (id.length() > 8) {
            return id.substring(0, 8);
        } else {
            return id;
        }
    }

    public static String saisieId(){
        Scanner sc = new Scanner(System.in);
        String id=null;
        while(id==null) {
            System.out.println("Veuillez entrez un identifiant : \n");
            id = sc.nextLine();
            if (id.length() > 0) {
                id = convertId(id);
            } else {
                System.out.println("\nVous devez entrez un identifiant d'au moins un character.\nRecommencez : \n");
                continue;
            }
        }
        String intro="Vous avez saisi : "+id+"\nGarder cet identifiant ?";
        int res = new Menu(intro,new String[]{"Oui","Non"}).run();
        System.out.println("RES : "+res);
        return id;

    }

    public static void startMenu(){
        System.out.println("Client JAVA");

        if(Menu.initMenu()){
            System.out.println("Compilation du menu réussi.\n");
        }else{
            System.out.println("Erreur lors de la compilation du menu, sortie.\n");
            System.exit(1);
        }
        Main.id=saisieId();
    }
}
