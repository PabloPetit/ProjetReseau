package pr6_projet;
import java.net.*;
import java.io.*;

public class threadGestion implements Runnable {

	Socket service;
	BufferedReader bf;
	PrintWriter pw;
	int port = 5566;
	annuaire bottin;
	
	public threadGestion(Socket service, annuaire bottin){
		this.bottin = bottin;
		this.service = service;
	}
	
	public void run(){
			try{
				bf = new BufferedReader(new InputStreamReader(service.getInputStream()));
				pw = new PrintWriter(new OutputStreamWriter(service.getOutputStream()));
				String read="";
				String[] req;
				while(true){
					read = bf.readLine();
					System.out.println("gestion lit -> "+read);
					if(read == null) break;
					req = read.split(" ");
				
				//requete inscription
					if(req[0].equals("REGI")){
						if(req.length == 6){
							IDdiff diffuseur = new IDdiff(req, service);
							if(bottin.add(diffuseur)){
								pw.print("REOK\r\n");
								pw.flush();
								System.out.println("REGI -> Le diffuseur : "+diffuseur.toString()+" enregistre");
							}
						}else{
							pw.print("RENO\r\n");
							pw.flush();
							System.out.println("REGI -> Impossible d'enregistrer le diffuseur");
							//service.close();
							break;
					}
				//requete lister les diffuseurs
					}else if(req[0].equals("LIST")){
						System.out.println("LIST -> envoi du nombre d'elements");
						pw.print("LINB "+bottin.length()+"\r\n");
						pw.flush();
						String[] listDiff = bottin.lister();
						System.out.println("LIST -> envoi des elements");
						for(int i=0; i<listDiff.length; i++){
							pw.print("ITEM "+listDiff[i]+"\r\n");
							pw.flush();
						}
						//service.close();
						//break;
					}
					
				} 	bf.close(); pw.close(); service.close();
			}
			catch(SocketTimeoutException st){
				System.out.println("timeout");
			}
			catch(Exception e){
				e.printStackTrace();
			}
	}
}
