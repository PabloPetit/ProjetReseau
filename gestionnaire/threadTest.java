package pr6_projet;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.concurrent.TimeUnit;

public class threadTest implements Runnable {
	
	annuaire bottin;
	int frequence = 1;
	
	public threadTest(annuaire bottin){
		this.bottin = bottin;
	}
	
	public void run(){
		
		while(true){
		
			try {
				if(bottin.length() > 0){
					TimeUnit.SECONDS.sleep(frequence);
					IDdiff test = bottin.getRandom();
				
					if(test!=null){
						if(test.socket.isClosed()){
							bottin.supp(test.ID);
						}else{
							test.socket.setSoTimeout(10000);
							BufferedReader bf = new BufferedReader(new InputStreamReader(test.socket.getInputStream()));
							PrintWriter pw = new PrintWriter(new OutputStreamWriter(test.socket.getOutputStream()));
					
							System.out.println("Test du diffuseur "+test.ID);
			
							pw.print("RUOK\r\n");
							pw.flush();
							String rep ="";
							try{
							rep = bf.readLine();
							System.out.println("rep -> "+rep);
							if(rep.equals("IMOK")){
							System.out.println("Diffuseur "+test.ID+" est OK");
							}
							}catch(Exception e){
								//e.printStackTrace();
								System.out.println("Le diffuseur "+test.ID+" ne repond pas");
								System.out.println("Supression de l'annuaire du diffuseur "+test.ID);
								bottin.supp(test.ID);
							}
							//System.out.println("rep -> "+rep);
						
						}
					}	
				}			
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("timeout");
			}
			
			
		}
	}
}
