
import java.util.*;

public class annuaire {

	private int max_diff = 100; // .size()
	private ArrayList<IDdiff> list;
	
	public annuaire(){
		list = new ArrayList<IDdiff>();
	}
	
	public annuaire(int max){
		max_diff = max;
		list = new ArrayList<IDdiff>();
	}
	
	private boolean containsDiff(IDdiff diff){
		for(IDdiff diffreg : list){
			if(diff.toString().equals(diffreg.toString()))
				return true;
		}
		return false;
	}
	
	public synchronized boolean add(IDdiff diff){
		if(list.size()<max_diff){
			if (containsDiff(diff)) return false;
			list.add(diff);
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
			if(ID.equals(tmp.getId())){
				list.remove(tmp);
				return true;
			}
		}
		return false;
	}
	
	public synchronized boolean supp(IDdiff diff){
		return list.remove(diff);
	}
	
	public synchronized int length(){
		try{
			//wait();
		}catch(Exception e){e.printStackTrace();}
		return list.size();
	}
	
	public synchronized String[] lister(){
		try{
			//wait();
		}catch(Exception e){e.printStackTrace();}
		String listDiff[] = new String[list.size()];
		int i=0;
		Iterator<IDdiff> it = list.iterator();
		while(it.hasNext()){
			listDiff[i] = it.next().toString();
			i++;
		}
		return listDiff;
	}
	
	public ArrayList<IDdiff> getList(){
		ArrayList<IDdiff> clone = new ArrayList<IDdiff>();
		for( IDdiff diff : list) 
			clone.add(diff);		
		return clone;
	}
	
	public synchronized IDdiff getRandom(){
		if(list.size()>1){
			IDdiff tmp = null;
			Iterator<IDdiff> it = list.iterator();
			Random rand = new Random();
			int r = rand.nextInt(list.size() +1);
			for(int i=0; i<r; i++){
				tmp = it.next();
			}
			
			return tmp;
		}else if (list.size() > 0){
			return list.get(0);
		}
		return null;
	}
}
