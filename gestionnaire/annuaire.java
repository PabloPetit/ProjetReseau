package pr6_projet;
import java.util.*;

public class annuaire {

	private int max_diff = 100, taille = 0;
	private ArrayList<IDdiff> list;
	
	public annuaire(){
		list = new ArrayList<IDdiff>();
	}
	
	public annuaire(int max){
		max_diff = max;
		taille = 0;
		list = new ArrayList<IDdiff>();
	}
	
	public synchronized boolean add(IDdiff diff){
		if(taille<max_diff){
			list.add(diff);
			taille++;
			notifyAll();
			return true;
		}
		else return false;
	}
	
	public synchronized boolean supp(String ID){
		try{
			//wait();
		}catch(Exception e){
			e.printStackTrace();
		}
		Iterator<IDdiff> it = list.iterator();
		IDdiff tmp;
		while(it.hasNext()){
			tmp = it.next();
			if(ID.equals(tmp.ID)){
				list.remove(tmp);
				taille--;
				return true;
			}
		}
		return false;
	}
	
	public synchronized int length(){
		try{
			//wait();
		}catch(Exception e){e.printStackTrace();}
		return taille;
	}
	
	public synchronized String[] lister(){
		try{
			//wait();
		}catch(Exception e){e.printStackTrace();}
		String listDiff[] = new String[taille];
		int i=0;
		Iterator<IDdiff> it = list.iterator();
		while(it.hasNext()){
			listDiff[i] = it.next().toString();
			i++;
		}
		return listDiff;
	}
	
	public synchronized IDdiff getRandom(){
		if(taille>0){
			IDdiff tmp = null;
			Iterator<IDdiff> it = list.iterator();
			Random rand = new Random();
			int r = rand.nextInt(taille +1);
			for(int i=0; i<r; i++){
				tmp = it.next();
			}
			
			return tmp;
		}
		return null;
	}
	
	public static void main(String[] args){
		
	/*	annuaire bottin = new annuaire(10);
		System.out.println("annuaire créé");
		IDdiff diffu = new IDdiff("hello","localhost",45,"localhost",5677);
		bottin.add(diffu);
		IDdiff diffu2 = new IDdiff("heo","192.168.0.1",45,"localhost",5677);
		bottin.add(diffu2);
		String[] temp = bottin.lister();
		for(int i=0; i<temp.length;i++){
			System.out.println(temp[i]);
		}*/
	}
}
