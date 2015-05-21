
import java.net.*;
import java.io.*;

public class threadGestion implements Runnable {

	Socket service;
	BufferedReader bf;
	PrintWriter pw;
	int port = 5566;
	annuaire bottin;
	screen out;
	
	public threadGestion(Socket service, annuaire bottin, screen out){
		this.bottin = bottin;
		this.service = service;
		this.out = out;
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
					//out.print("gestion lit -> "+read);
					if(read == null) break;
					req = read.split(" ");
				
				//requete inscription
					if(req[0].equals("REGI")){
						if(verifIns(req)){
							diffuseur = new IDdiff(req, service,pw);
							if(bottin.add(diffuseur)){
								pw.print("REOK\r\n");
								//pw.flush();
								out.print("Le diffuseur : "+diffuseur.getId()+" est enregistré");
							}else{
								pw.print("RENO\r\n");
								pw.flush();
								out.print("Erreur le diffuseur "+req[1]+" est déjà enregistré");
								break;
							}
						}else{
							pw.print("RENO\r\n");
							pw.flush();
							out.print("Impossible d'enregistrer le diffuseur "+req[1]);
							//service.close();
							break;
					}
				//requete lister les diffuseurs
					}else if(req[0].equals("LIST")){
						out.print("Envoi du nombre d'elements à l'adresse "+service.getInetAddress());
						if (bottin.length() < 10){
							pw.print("LINB 0"+bottin.length()+"\r\n");
						}else{ 
							pw.print("LINB "+bottin.length()+"\r\n");
							}
						pw.flush();
						String[] listDiff = bottin.lister();
						out.print("Envoi des elements  à l'adresse "+service.getInetAddress());
						for(String Diff : listDiff){
							pw.print("ITEM "+Diff+"\r\n");
							pw.flush();
						}
					}
					//requete test
					else if(req[0].equals("IMOK")){
						//if(diffuseur != null)
						diffuseur.setTestOK();
					}
					
					else break;
					
				} 	bf.close(); pw.close(); service.close();
			}
			catch(SocketTimeoutException st){
				out.print("timeout");
			}
			catch(Exception e){
				e.printStackTrace();
			}
	}
		
	private boolean verifIns(String tab[]){
		if(tab.length != 6 ) return false;
		if(tab[1].length() > 8 || tab[0].length() == 0 ) return false;
		if(!estPort(tab[3]) || !estPort(tab[5])) return false;// test si les ports sont compris entre 0 et 9999
		if(!rescueIp(tab)) return false; //verifie si les ip font 15 char
		return true;
	}
	
	private boolean rescueIp(String tab[]){
		
		String [] tmp;
		
		if(tab[2].length()<15){
			tmp = tab[2].split("\\.");
			if(tmp.length < 4){ 
				out.print("Diffuseur "+tab[1] +" ip1 non valide");
				return false;
			}else{
				out.print("Diffuseur "+tab[1] +" correction de ip1");
				for(int i=0; i<4; i++){
					if(Integer.parseInt(tmp[i])>256){
						out.print("Diffuseur "+tab[1] +" erreur ip1");
						return false;
					}
					switch (tmp[i].length()){
					case 1 : 
						tmp[i] = "00"+tmp[i];
						break;
					case 2 :
						tmp[i] = "0"+ tmp[i];
						break;
					}
				}
				tab[2] = tmp[0]+"."+tmp[1]+"."+tmp[2]+"."+tmp[3];
			}
		}if(tab[4].length()<15){
			tmp = tab[4].split("\\.");
			if(tmp.length < 4){ 
				out.print("Diffuseur "+tab[1] +" ip2 non valide");
				return false;
			}else{
				out.print("Diffuseur "+tab[1] +" correction de ip2");
				for(int i=0; i<4; i++){
					if(Integer.parseInt(tmp[i])>256){
						out.print("Diffuseur "+tab[1] +" erreur ip2 "+tab[4]);
						return false;
					}
					switch (tmp[i].length()){
					case 1 : 
						tmp[i] = "00"+tmp[i];
						break;
					case 2 :
						tmp[i] = "0"+ tmp[i];
						break;
					}
				}
				tab[4] = tmp[0]+"."+tmp[1]+"."+tmp[2]+"."+tmp[3];		
		}
			return true;
	}
		return true;
}
	

	private static boolean estPort(String s) {
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
