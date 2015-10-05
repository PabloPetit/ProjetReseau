import java.net.InetAddress;
import java.lang.Exception;
import java.lang.String;

class Ip{

	public static String format(String s){
		while(s.length()!=3){
			s="0"+s;
		}
		return s;
	}

	public static void main(String[] args){
		try{
			String str = InetAddress.getLocalHost().getHostAddress();
			String t[] = str.split("\\.");
			System.out.println(format(t[0])+"."+format(t[1])+"."+format(t[2])+"."+format(t[3]));
		}catch(Exception e){

		}
	}
}