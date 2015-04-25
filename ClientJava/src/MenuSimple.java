/**
 * Created by Pablo on 22/04/2015.
 */
public class MenuSimple extends Menu{

    public MenuSimple(String intro,String args[]){
        super(intro,args);
    }

    public int run() {
        System.out.println(intro+"\n");
        for (int i = 0; i < args.length; i++) {
            System.out.println(i + " : " + args[i]);
        }
        int c=-1;
        try {
            while (!(c>-1 && c<10)) {
                c=System.in.read()-48;
            }
        }catch (Exception e){
            System.err.println("Probleme Menu Simple");
        }
        return c;
    }
}
