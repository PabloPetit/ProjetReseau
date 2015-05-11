
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
				IDdiff diffuseur = null;
				while(true){
					read = bf.readLine();
					System.out.println("gestion lit -> "+read);
					if(read == null) break;
					req = read.split(" ");
				
				//requete inscription
					if(req[0].equals("REGI")){
						if(verifIns(req)){
							diffuseur = new IDdiff(req, service);
							if(bottin.add(diffuseur)){
								diffuseur.send("REOK\r\n");
								//pw.flush();
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
					//requete test
					else if(req[0].equals("IMOK")){
						//if(diffuseur != null)
						diffuseur.setTestOK();
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
	public static boolean verifIns(String tab[]){
		if(tab.length != 6 ) return false;
		if(tab[1].length() > 8 || tab[0].length() == 0 ) return false;
		if(!estPort(tab[3]) || !estPort(tab[5])) return false;// test si les ports sont compris entre 0 et 9999
		if(tab[2].length() != 15 || tab[4].length() != 15 ) return false; //verifie si les ip font 15 char
		return true;
	}
	
	public static boolean estPort(String s) {
	    int port;
		try { 
	        port = Integer.parseInt(s); 
	    } catch(NumberFormatException e) { 
	        return false; 
	    } catch(NullPointerException e) {
	        return false;
	    }
		if (port>=0 && port <= 9999) return true;
		else return false;
	}
}
