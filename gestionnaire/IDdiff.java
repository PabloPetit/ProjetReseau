
import java.io.*;
import java.net.*;

public class IDdiff {
	String ID, ip1, ip2;
	int port1, port2;
	Socket socket;
	private boolean testing = false;
	private PrintWriter pw;
	//private BufferedReader bf;
	
	public IDdiff(String ID, String ip1, int port1, String ip2, int port2, Socket socket, PrintWriter pw){
		
		if(ID.length() == 8){this.ID = ID;}
		else{ while(ID.length()<8) ID+='#';}
		this.ip1 = ip1;
		this.port1 = port1;
		this.ip2 = ip2;
		this.port2 = port2;
		this.socket = socket;
		this.pw = pw;
		
	}
	
	public IDdiff(String [] tab, Socket socket, PrintWriter pw){
		this.ID = tab[1];//on commence a 1 car tab[0] = "REGI"
		if(this.ID.length() == 8){this.ID = ID;}
		else{ while(ID.length()<8) ID+='#';}
		this.ip1 = tab[2];
		this.port1 = Integer.parseInt(tab[3]);
		this.ip2 = tab[4];
		this.port2 = Integer.parseInt(tab[5]);
		this.socket = socket;
		this.pw = pw;
	}
	
	public String toString(){
		return (ID+" "+ip1+" "+port1+" "+ip2+" "+port2);
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
	
/*	public String read(){
		String s = null;
		try {
			s = bf.readLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return s; 
	}*/
}
