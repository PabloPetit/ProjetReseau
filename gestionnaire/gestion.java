

import java.net.*;

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
			System.out.println("Serveur Gestionnaire créé");
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
		gestion ges = new gestion();
		
		ges.serviceGestion();
	}
}
