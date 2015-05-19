
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.concurrent.TimeUnit;

public class threadTest implements Runnable {
	
	annuaire bottin;
	screen out;
	int frequence = 20;
	
	
	public threadTest(annuaire bottin, screen out){
		this.bottin = bottin;
		this.out = out;
	}
	
	public void run(){
		
		while(true){
		
			try {
				TimeUnit.SECONDS.sleep(frequence);
				if(bottin.length() > 0){
					
					//IDdiff test = bottin.getRandom();
				for ( IDdiff test : bottin.getList()){
					if(test!=null){
						if(test.socket.isClosed()){
							bottin.supp(test.ID);
						}else{
							//test.socket.setSoTimeout(10000);
							//BufferedReader bf = new BufferedReader(new InputStreamReader(test.socket.getInputStream()));
							//PrintWriter pw = new PrintWriter(new OutputStreamWriter(test.socket.getOutputStream()));
					
							out.print("Test du diffuseur "+test.ID);
			
							test.send("RUOK\r\n");
							//pw.flush();
							
							try{
							//rep = bf.readLine();
						//	System.out.println("rep -> "+rep);
								TimeUnit.SECONDS.sleep(3);	
							if(test.getTest()){
								out.print("Diffuseur "+test.ID+" est OK");
								test.resetTest();
							}else{
								out.print("Supression de l'annuaire du diffuseur "+test.ID);
								bottin.supp(test);
							}
							}catch(Exception e){
								//e.printStackTrace();
								out.print("Le diffuseur "+test.ID+" ne repond pas");
								out.print("Supression de l'annuaire du diffuseur "+test.ID);
								//bottin.supp(test.ID);
								bottin.supp(test);
							}
							//System.out.println("rep -> "+rep);
						
						}
					}	
				}	}		
			} catch (Exception e) {
				e.printStackTrace();
				out.print("timeout");
			}
			
			}	
		
	}
}
