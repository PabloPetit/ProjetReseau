
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
							bottin.supp(test.getId());
						}else{
							out.print("Test du diffuseur "+test.getId());
							test.send("RUOK\r\n");
							
							try{
								TimeUnit.SECONDS.sleep(3);	
							if(test.getTest()){
								out.print("Diffuseur "+test.getId()+" est OK");
								test.resetTest();
							}else{
								out.print("Supression de l'annuaire du diffuseur "+test.getId());
								if (bottin.supp(test)) out.print(test.getId()+" supprimé");
								
							}
							}catch(Exception e){
								//e.printStackTrace();
								out.print("Le diffuseur "+test.getId()+" ne repond pas");
								out.print("Supression de l'annuaire du diffuseur "+test.getId());
								//bottin.supp(test.getId());
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
