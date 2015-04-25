import java.io.*;

public class Menu {

    String intro;
    String args[];

    public Menu(String intro, String[] args) {
        this.args = args;
        this.intro = intro;
    }

    public int run(){
        String command="../../Menu/main ";
        command+="\""+intro+"\" ";

        for(int i=0;i<args.length;i++){
            command+="\""+args[i]+"\" ";
        }
        System.out.println("JAVA : DEBUT RUN;ARGS :\n---\n"+command+"\n-----\n");
        String s = "";
        try{
            Process p = Runtime.getRuntime().exec(command);
            //p.waitFor();
            BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));

            while ((s = stdInput.readLine()) != null) {
                System.out.print(s);
            }

            int res = Integer.parseInt(""+s.charAt((s.length()-1)));// FAUX : s=null a la fin
            return res;
        }catch (Exception e) {
            e.printStackTrace();
            System.out.println("Erreur a l'execution de  : " + command);
        }
        return -1;
    }

    public static boolean initMenu(){
        try {
            String command = "make clean";
            String[] envp = {};
            File dir = new File("../../Menu");
            Process proc = Runtime.getRuntime().exec(command, envp, dir);
            proc.waitFor();
            command="make";
            Process proc2 = Runtime.getRuntime().exec(command, envp, dir);
            proc2.waitFor();
        }catch (Exception e){
            return false;
        }
        return true;
    }
}