
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.regex.Pattern;


class Item
{
	private double q_i;
	private String name;

	public Item(double q_i, String name) {
		super();
		this.q_i = q_i;
		this.name = name;
	}
	public double getQ_i() {
		return q_i;
	}
	public void setQ_i(double q_i) {
		this.q_i = q_i;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}

	public String toString()
	{
		return q_i + " " + name;
	}

}

class ItemComparator implements Comparator<Item>
{
	@Override
	public int compare(Item arg0, Item arg1) {
		Double a = new Double(arg0.getQ_i());
		Double b = new Double(arg1.getQ_i());
		return b.compareTo(a);
	}
}

public class zipfsong {

	private static final long MAX_VALUE = (long) java.lang.Math.pow(10,12);

	public static void main(String args[])
	{
		List<Item> list = new ArrayList<Item>();

		Kattio io = new Kattio(System.in, System.out);

		//BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
		/*File f = new File("prueba.txt");
			BufferedReader bufferRead = null;
			try {
				bufferRead = new BufferedReader(new FileReader(f));
			} catch (FileNotFoundException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		 */
		String s = "";
		int total = io.getInt();
		int selection = io.getInt();

		if(total>=1 && total<=50000 && selection>=1 && selection<=total)
		{
			for(int i=0;i<total;i++)
			{
				double f_i = io.getDouble();
				if(f_i<0 || f_i>MAX_VALUE)
					System.exit(0);

				double q_i = f_i * (i+1);
				String name = io.getWord();
				name = name.trim();
				if(name.length()>30)
					System.exit(0);

				Pattern p = Pattern.compile("[^a-z0-9_]");
				if (p.matcher(name).find())
					System.exit(0);

				list.add(new Item(q_i, name));
			}
		}

		Collections.sort(list, new ItemComparator());

		for(int i=0;i<selection;i++)
		{
			System.out.println(list.get(i).getName());
		}

		io.close();
	}
}