/**
 * Created by Pablo on 22/04/2015.
 */
public class Menu {

    public String intro;
    public String args[];

    public Menu(){
        this.intro="";
        this.args=new String[0];
    }

    public Menu(String intro, String args[]){
        this.intro=intro;
        this.args=args;
    }

}
