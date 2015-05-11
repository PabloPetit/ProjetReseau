
import java.util.*;

public class annuaire {

	private int max_diff = 100, taille = 0; // .size()
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
	
	public synchronized boolean supp(IDdiff diff){
		taille--;
		return list.remove(diff);
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
		if(taille>1){
			IDdiff tmp = null;
			Iterator<IDdiff> it = list.iterator();
			Random rand = new Random();
			int r = rand.nextInt(taille +1);
			for(int i=0; i<r; i++){
				tmp = it.next();
			}
			
			return tmp;
		}else if (taille > 0){
			return list.get(0);
		}
		return null;
	}
}
