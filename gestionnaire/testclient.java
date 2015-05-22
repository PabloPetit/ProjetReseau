//package pr6_projet;
import java.net.*;
import java.io.*;

public class testclient {

	public static void main(String[] args){
		
		try {
			Socket socket = new Socket(args[0], Integer.parseInt(args[1]));
			BufferedReader bf = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			
			//pw.print("REGI test1 192.168.1.54 5566 192.168.1.54 5566\r\n");
			//pw.flush();
			pw.print("REGI "+args[2]+" "+args[3]+" "+args[4]+" "+args[5]+" "+args[6]+"\r\n");
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
