import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Class that controls the running and solves the problem
 * @author Abel Pascual
 *
 */
public class catvsdog {

	public static void main(String[] args) {
		System.out.println(solver(System.in));
	}
	
	public static String solver(InputStream is)
	{
		String answer = "";

		// Setting scanner
		Scanner scanner = new Scanner(is);
		// Reading the number of scenarios
		int total = scanner.nextInt();

		for(int i=0;i<total;i++)
		{
			// Reading number of cats, dogs and voters
			int c = scanner.nextInt();
			int d = scanner.nextInt();
			int v = scanner.nextInt();

			// Arrays to store the votes depending on the preference
			List<Vote> catsLovers = new ArrayList<Vote>();
			List<Vote> dogsLovers = new ArrayList<Vote>();

			// Arrays to store the votes depending on the preference
			for(int j=0;j<v;j++)
			{
				String toKeep = scanner.next();
				String toThrow = scanner.next();

				if(toKeep.startsWith("C"))
				{
					catsLovers.add(new Vote(toKeep, toThrow));
				}
				else if(toKeep.startsWith("D"))
				{
					dogsLovers.add(new Vote(toKeep, toThrow));
				}
			}

			// Storing for every Vote other incompatible Votes
			for(int j=0;j<catsLovers.size();j++)
			{
				for(int k=0;k<dogsLovers.size();k++)
				{
					if(catsLovers.get(j).getToKeep().compareTo(dogsLovers.get(k).getToThrow())==0
							|| catsLovers.get(j).getToThrow().compareTo(dogsLovers.get(k).getToKeep())==0)
					{
						// Store the incompatibilities only in the cats lover votes
						catsLovers.get(j).addNotCompatibleRule(dogsLovers.get(k));
					}
				}
			}

			// Retrieve maximum number of incompatibilities
			int incompatibilities = solve(catsLovers, dogsLovers);

			// Maximum number of voters satisfied would be total_number_voters - max_incompatibilities
			answer = answer + (v-incompatibilities) + "\n";
		}
		
		return answer;
	}


	/**
	 * Method that receives two sets of votes and calculates the maximum number
	 * of incompatibilities.
	 * @param catLovers
	 * @param dogLovers
	 * @return
	 */
	public static int solve(List<Vote> catLovers, List<Vote> dogLovers)
	{
		int sum = 0;
		// Iterate through the cat votes
		for(int i=0;i<catLovers.size();i++)
		{
			Vote catNode = catLovers.get(i);

			// Set all the alreadyExplored variables to false
			for(int j=0;j<dogLovers.size();j++)
				dogLovers.get(j).setAlreadyExplored(false);

			// If this vote can be assigned to another incompatible vote, increment sum
			if(assign(catNode)) sum++;
		}
		return sum;
	}

	/**
	 * Method that checks if a vote can be assined to other incompatible vote.
	 * @param catNode
	 * @return
	 */
	private static boolean assign(Vote catNode) {
		// Iterate through the incompatible votes of catNode
		for(int j=0;j<catNode.getNotCompatible().size();j++)
		{
			Vote dogNode = catNode.getNotCompatible().get(j);

			// If the catNode and dogNode are incompatible and dogNode has not been explored yet...
			if(!dogNode.isAlreadyExplored())
			{
				// First mark as explored dogNode
				dogNode.setAlreadyExplored(true);

				// If dogNode has no vote assigned yet or if it was assigned but can be changed
				if (dogNode.getLink()==null || assign(dogNode.getLink())){
					catNode.setLink(dogNode);
					dogNode.setLink(catNode);
					return true;
				}
			}
		}
		return false;
	}
}

/**
 * Class that handles the votes of the users and have some attributes 
 * used in the resolution process
 * @author Abel Pascual
 *
 */
class Vote {

	// Animal that is wanted to be kept
	private String toKeep;
	// Animal that is wanted to be thrown
	private String toThrow;

	// List of incompatible votes
	private List<Vote> notCompatible;
	// Boolean indicating if this vote has been explored
	private boolean alreadyExplored;
	// Vote linked
	private Vote link;

	// Constructor
	public Vote(String toKeep, String toThrow) {
		super();
		this.toKeep = toKeep;
		this.toThrow = toThrow;
		this.alreadyExplored = false;
		this.notCompatible = new ArrayList<Vote>();
		this.link = null;
	}

	// Typical set of methods to access to the attibutes

	public Vote getLink() {
		return link;
	}
	public void setLink(Vote link) {
		this.link = link;
	}
	public String getToKeep() {
		return toKeep;
	}
	public void setToKeep(String toKeep) {
		this.toKeep = toKeep;
	}
	public String getToThrow() {
		return toThrow;
	}
	public void setToThrow(String toThrow) {
		this.toThrow = toThrow;
	}
	public List<Vote> getNotCompatible() {
		return notCompatible;
	}
	public void setNotCompatible(List<Vote> notCompatible) {
		this.notCompatible = notCompatible;
	}
	public boolean isAlreadyExplored() {
		return alreadyExplored;
	}
	public void setAlreadyExplored(boolean alreadyExplored) {
		this.alreadyExplored = alreadyExplored;
	}
	public void addNotCompatibleRule(Vote aux)
	{
		if(!this.notCompatible.contains(aux))
			this.notCompatible.add(aux);
	}
	public String toString()
	{
		return this.toKeep + " - " + this.toThrow;
	}
}


