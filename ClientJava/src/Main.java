import java.util.Scanner;

public class Main {

    public static String ID;

    public static String convertId(String id) {
        System.out.println("CONVERT DE : -"+id+"-");
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
            if(sc.hasNextLine()){
                id = sc.nextLine();
            }else{
                sc.nextLine();
                id=null;
            }
            if (id.length() > 0) {
                id = convertId(id);
            } else {
                System.out.println("\nVous devez entrez un identifiant d'au moins un character.\nRecommencez : \n");
                id=null;
            }
        }
        return id;
    }


    public static void main(String[] args){
      //MenuFleche.initMenu();
        Main.ID=saisieId();
        MenuPrincipal.run();
    }
}
