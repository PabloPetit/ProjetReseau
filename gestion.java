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
			this.port = port;
			this.maxDiff = maxDiff;
			server = new ServerSocket(port);
			Runtime.getRuntime().exec("clear");
			System.out.println("Serveur Gestionnaire créé sur le port "+port);
			bottin = new annuaire(maxDiff);
		}catch(Exception e){ e.printStackTrace();}
	}
	
	public void serviceGestion(){
		try{
			
			threadTest test = new threadTest(bottin);
			Thread threadTest = new Thread(test);
			threadTest.start();
		
		while(true){
			Socket serv = server.accept();
			System.out.println("Connection établie avec l'addresse "+serv.getInetAddress());
			threadGestion ges = new threadGestion(serv,bottin);
			Thread threadGes = new Thread(ges);
			threadGes.start();
		}
		
		}catch(Exception e){
			e.printStackTrace();
			
		}	
	}
	
	public static void main(String[] args){
		
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
		}while((max<0) || (max>99));
		
		
		scan.close();
		gestion ges = new gestion(port, max);
		ges.serviceGestion();
	}
}
