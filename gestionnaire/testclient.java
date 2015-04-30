//package pr6_projet;
import java.net.*;
import java.io.*;

public class testclient {

	public static void main(String[] args){
		
		try {
			Socket socket = new Socket("localhost", 5566);
			BufferedReader bf = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			
			//pw.print("REGI test1 192.168.1.54 5566 192.168.1.54 5566\r\n");
			//pw.flush();
			pw.print("REGI "+args[0]+" "+args[1]+" "+args[2]+" "+args[3]+" "+args[4]+"\r\n");
			pw.flush();
			String read="";
			while(true){
				read = bf.readLine();
				System.out.println(read);
				if(read.equals("RUOK")){
					pw.print("IMOK\r\n");
					pw.flush();
					System.out.println("IMOK envoye");
				}
			}
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}
