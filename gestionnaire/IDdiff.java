
import java.io.*;
import java.net.*;

public class IDdiff {
	private String ID, ip1, ip2;
	private int port1, port2;
	Socket socket;
	private boolean testing = false;
	private PrintWriter pw;
	
	public IDdiff(String ID, String ip1, int port1, String ip2, int port2, Socket socket, PrintWriter pw){
		
		if(ID.length() == 8){this.ID = ID;}
		else{ while(ID.length()<8) ID+='#';}//correction de l'ID
		this.ip1 = ip1;
		this.port1 = port1;
		this.ip2 = ip2;
		this.port2 = port2;
		this.socket = socket;
		this.pw = pw;
		
	}
	
public IDdiff(String ID, String ip1, int port1, String ip2, int port2){
		
		if(ID.length() == 8){this.ID = ID;}
		else{ while(ID.length()<8) ID+='#';}//correction de l'ID
		this.ip1 = ip1;
		this.port1 = port1;
		this.ip2 = ip2;
		this.port2 = port2;
		
		
	}
	
	public IDdiff(String [] tab, Socket socket, PrintWriter pw){
		this.ID = tab[1];//on commence a 1 car tab[0] = "REGI"
		while(ID.length()<8) ID+='#';//correction ID
		this.ip1 = tab[2];
		this.port1 = Integer.parseInt(tab[3]);
		this.ip2 = tab[4];
		this.port2 = Integer.parseInt(tab[5]);
		this.socket = socket;
		this.pw = pw;
	}
	
	public String toString(){
		String PORT1 = ""+port1, PORT2 = ""+port2;
		while(PORT1.length()<4){
			PORT1 = "0"+PORT1;
		}
		while(PORT2.length()<4){
			PORT2 = "0"+PORT2;
		}
		return (ID+" "+ip1+" "+PORT1+" "+ip2+" "+PORT2);
	}
	
	public synchronized void setTestOK(){
		testing = true;
		notifyAll();
	}
	
	public synchronized void resetTest(){
		 testing = false;
		 notifyAll();
	 }
	
	public synchronized boolean getTest(){
		return testing;
	}
	
	public void send(String s){
		pw.print(s);
		pw.flush();
	}
	
	public String getId(){
		return ID;
	}
	
	public void close(){
		pw.close();
		try {
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
