import java.io.IOException;

public class MenuFleche extends Menu{

    public MenuFleche(String intro,String args[]){
        super(intro,args);
    }

    public static int captureSelect(){
        try {
            int c = System.in.read();
            if(c==27){
                System.in.read();
                c=System.in.read();
                if(c==65)return -1;//HAUT
                else if(c==66)return 1;//BAS
                else return 0;
            }else if(c==10)return -2;
        } catch (IOException e) {
            System.out.println("Capture de l'entre console impossible");
            return -3;
        }
        return 0;
    }

    public int runSimple(){
        char c;
        int selected=0;
        boolean ok=false;
        while(!ok){
            System.out.println(intro + "\n");
            for(int i=0;i<args.length;i++){
                if(i==selected){//  \e[1;34m-> %s\e[0m\n
                    System.out.println("-> "+args[i]);
                }else{
                    System.out.println("   "+args[i]);
                }
            }
            int capt=captureSelect();
            if(capt==-3)return 0;
            else if(capt==-2)ok=false;
            else selected=Math.min(Math.max(selected + capt, 0), args.length - 1);
            clear();
        }
        return selected;
    }

    public static void clear(){
        try{
            Runtime.getRuntime().exec("clear");
        }catch (Exception e){
            System.out.println("CLEAR a echoue");
        }
    }

    public static void initMenu(){
        /*
        try{
            Process p =Runtime.getRuntime().exec(new String[] {"sh","-c","stty -icanon min 1 < /dev/tty"});
            Process p2 = Runtime.getRuntime().exec(new String[] {"sh","-c","-echo"});
            p.waitFor();
            p2.waitFor();
        }catch (Exception e){
            System.out.println("Impossible de passer la console en mode non-canonique");
        }
        */
    }

}
