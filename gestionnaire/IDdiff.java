package pr6_projet;
import java.net.*;

public class IDdiff {
	String ID, ip1, ip2;
	int port1, port2;
	Socket socket;
	
	public IDdiff(String ID, String ip1, int port1, String ip2, int port2, Socket socket){
		this.ID = ID;
		this.ip1 = ip1;
		this.port1 = port1;
		this.ip2 = ip2;
		this.port2 = port2;
		this.socket = socket;
	}
	
	public IDdiff(String [] tab, Socket socket){
		this.ID = tab[1];//on commence a 1 car tab[0] = "REGI"
		this.ip1 = tab[2];
		this.port1 = Integer.parseInt(tab[3]);
		this.ip2 = tab[4];
		this.port2 = Integer.parseInt(tab[5]);
		this.socket = socket;
	}
	
	public String toString(){
		return (ID+" "+ip1+" "+port1+" "+ip2+" "+port2);
	}
}
