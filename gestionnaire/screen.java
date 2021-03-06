import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;


public class screen {

	private ArrayList<String> events;
	private int ligneMax;
	private int charMax;
	private annuaire bottin;
	private String hostname;
	private String colonne1 = "Events";
	private String colonne2 = "Diffuseur(s)";
	private String ip;
	private int port;
	
	public screen(int ligneMax, int charMax, annuaire bottin, String hostname, String ip, int port){
		this.events = new ArrayList<String>();
		this.ligneMax = ligneMax;
		this.charMax = charMax;
		this.bottin = bottin;
		this.hostname = hostname;
		this.ip = ip;
		this.port = port;
	}
	
	public String[] cutR(String s){
		
		int len;
		int cursor=0;
		if(s.length() % charMax != 0) len = (s.length() / charMax) +1;
		else len = s.length() / charMax;
		
		String [] ret = new String[len];
		
		for(int i=0; i<len;i++){
			if((cursor + charMax) < s.length() ){ 
				ret[i] = s.substring(cursor, cursor+charMax);
				cursor+=charMax;
			}else
				ret[i] = s.substring(cursor, s.length());
		}
		
		for(int i=0; i<len; i++)
		System.out.println("Ret -> "+ret[i]);
		
		return ret;
	}
	
	public void print(String s){
		Date date = new Date();
		 SimpleDateFormat dateFormat;
		 
		dateFormat = new SimpleDateFormat("hh:mm:ss");
		s = dateFormat.format(date)+"->"+s;
		String [] S = cutR(s);
		
		//for(String str : S){
		for(int i=0; i<S.length; i++){
			if( events.size() == ligneMax)
				events.remove(0);
			events.add(S[i]);
			//System.out.println("print S-> "+S[i]);
			//affiche();
		}
		
		affiche();
	}
	
	public static void clear(){
		final String ESC = "\033[";
		System.out.print (ESC + "2J");
		System.out.print (ESC + "0;0H");
		System.out.flush();
	}
	
	private void cadre(int type){
		
		
		switch(type){
		
		case 0 :
			System.out.print("┌");
			for (int i=0; i<charMax; i++) System.out.print("─");
			System.out.print("┬");
			for (int j=0; j<52; j++) System.out.print("─");
			System.out.println("┐");
			break;
		
		case 1 :
			for(int i=0; i< charMax - colonne1.length()+2; i++){
				if(i == 0) System.out.print("│");
				else if(i == 1) System.out.print(colonne1);
				else System.out.print(" ");
			}
			for(int j=0; j< 52  - colonne2.length()+2; j++){
				if(j == 0) System.out.print("│");
				else if(j == 1) System.out.print(colonne2);
				else System.out.print(" ");
			}
			System.out.println("│");
			break;
			
		case 3 : 
			System.out.print("├");
			for (int i=0; i<charMax; i++) System.out.print("─");
			System.out.print("┼");
			for (int j=0; j<52; j++) System.out.print("─");
			System.out.println("┤");
			break;
		
		case 4:
			System.out.print("└");
			for (int i=0; i<charMax; i++) System.out.print("─");
			System.out.print("┴");
			for (int j=0; j<52; j++) System.out.print("─");
			System.out.println("┘");
			break;
	
		}
	}	
	
	public void affiche(){
		//├  ─  ┤ │ ┼ ┐ └ ┴ ┬ ┘ ┌
		clear();
		
		System.out.println("Gestionnaire -> nom : "+hostname+" ip : "+ip+"  port : "+port);
		
		cadre(0);
		cadre(1);
		cadre(3);
		String [] liste = bottin.lister();
		String tmp;
		
		for(int i=0; i<ligneMax; i++){
			System.out.print("│");
			if( i< events.size()){
				tmp = events.get(i);
				System.out.print(events.get(i));
				for(int j=0; j<charMax - events.get(i).length(); j++) System.out.print(" ");
			}else{ for(int j=0; j<charMax; j++) System.out.print(" ");}
			System.out.print("│");
			if(i< liste.length){
				System.out.print(liste[i]);
				for(int j=0; j<52 -liste[i].length(); j++)
					System.out.print(" ");
			}else{for(int j=0; j<52; j++) System.out.print(" ");}
			System.out.println("│");
		}

		cadre(4);
	
	}
	
/*	
	public static void main(String [] args){
	annuaire bottin = new annuaire();
		screen cons =  new screen(30, 100, bottin);
		Scanner scan = new Scanner(System.in);
		do{
			cons.print(scan.nextLine());
		}while(true);
		
		
		
	}*/
	
}
