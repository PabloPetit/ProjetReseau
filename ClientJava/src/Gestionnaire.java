import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Gestionnaire {


    public static Socket recupInfo(){
        boolean ok=false;
        int port=0;
        String ip=null;
        Scanner sc = new Scanner(System.in);
        Socket sock=null;
        int i=0;


        while(!ok) {
            try {
                System.out.println("\nEntrez le port du gestionnaire :");
                port=sc.nextInt();
                System.out.println("PORT SAISI : " + port);
                if(port<0||port>9999)throw new InputMismatchException();
                System.out.println("Entrez l'ip du gestionnaire : ");
                ip=sc.nextLine();
                System.out.println("IP : -" + ip + "-");
                sock=new Socket(ip,port);
                ok=true;
            } catch (UnknownHostException e){
                System.out.println("Hote inconnu.");
            } catch (IOException e) {
                switch (new MenuSimple("Une erreur a eu lieu, recommencer ?",new String[]{"Oui","Non"}).run()){
                    case 1:
                        return null;
                }
            }catch (InputMismatchException e){
                System.out.println("Le port doit etre un entier compris entre 0 et 9999");
            }catch (NoSuchElementException e){
                System.out.println("Le port doit etre un entier compris entre 0 et 9999.");
            }catch (IllegalStateException e){
                System.out.println("Adrresse ip incorrect.");
            }
            finally {
                sc.next();
            }
        }
        return sock;
    }


    public static void connexionGestionnaire(){
        try {
            Socket socket = recupInfo();
            if(socket==null)return;
            BufferedReader br=new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter pw=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

/*

if(i++>5){
                switch (new MenuSimple("5 essais : ",new String[]{"Continuer","Quitter"}).run()){
                    case 1:
                        return null;
                }
            }
 */
