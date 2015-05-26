import java.io.*;
import java.net.*;
import java.util.InputMismatchException;
import java.util.Scanner;

public class gestion {

	ServerSocket server;
	int port = 5566;
	int maxDiff = 10;
	annuaire bottin;
	
	public gestion(){
		try{
			server = new ServerSocket(port);
			System.out.println("Serveur Gestionnaire créé");
			bottin = new annuaire(maxDiff);
		}catch(Exception e){ e.printStackTrace();}
	}
	
	public gestion(int port, int maxDiff){
		try{
			this.port = (port<0 || port>9999)?5566:port;
			this.maxDiff =  (maxDiff<0 || maxDiff>99)?10:maxDiff;
			server = new ServerSocket(port);
			clear();
			System.out.println("Serveur Gestionnaire créé sur le port "+port);
			bottin = new annuaire(maxDiff);
		}catch(Exception e){ e.printStackTrace();}
	}
	
	public static void clear(){
		final String ESC = "\033[";
		System.out.print (ESC + "2J");
		System.out.print (ESC + "0;0H");
		System.out.flush();
	}
	
	public void serviceGestion(){
		try{
			InetAddress address = InetAddress.getLocalHost(); 
		    String ip = address.getHostAddress() ;
		    String hostname = address.getHostName(); 
		    //String hostname = address.getCanonicalHostName(); 
			screen out = new screen(25,60, bottin, hostname, ip, port);
			out.print("Serveur Gestionnaire créé sur le port "+port);
			threadTest test = new threadTest(bottin, out);
			Thread threadTest = new Thread(test);
			threadTest.start();
		
		while(true){
			Socket serv = server.accept();
			out.print("Connection établie avec l'addresse "+serv.getInetAddress());
			threadGestion ges = new threadGestion(serv,bottin, out);
			Thread threadGes = new Thread(ges);
			threadGes.start();
		}
		
		}catch(Exception e){
			e.printStackTrace();
			
		}	
	}
	
	public static void main(String[] args){
		clear();
		
		if(args.length == 1){
			if(args[0].equals("d")){
				gestion ges = new gestion(5566, 15);
				ges.serviceGestion();
			}else if(args.length == 2){
				try{
					gestion ges = new gestion(Integer.parseInt(args[0]),Integer.parseInt( args[1]));
					ges.serviceGestion();
				}catch(Exception e){
					System.err.println("Arguments errone, lancement par default.");
					gestion ges = new gestion(5566, 15);
					ges.serviceGestion();
				}
			}
		}else{
		
		Scanner scan = new Scanner(System.in);
		int port , max =-1;
		
		//lecture du port
		System.out.println("Veuillez entrez un numero de port compris entre 0 et 9999");
			do{
				try{
					port = scan.nextInt();
				}catch(InputMismatchException e){
					System.out.println("Attention le numero de port doit être UNIQUEMENT des entiers");
					System.out.println("Veuillez recommencer");
					scan.next();
					port =-1;
				}
			}while((port<0) || (port>9999));
		
		//lecture du maximun diffuseur
		System.out.println("Veuillez entrez un nombre maximun de diffuseurs (maximun 99)");
		do{
			try{
				max = scan.nextInt();
			}catch(InputMismatchException e){
				System.out.println("Attention le numero de port doit être UNIQUEMENT des entiers");
				System.out.println("Veuillez recommencer");
				scan.next();
				max =-1;
			}
			clear();
		}while((max<0) || (max>99));
		
		
		scan.close();
		
		gestion ges = new gestion(port, max);
		ges.serviceGestion();
		}
	}
}
