import java.util.LinkedHashMap;
public class MatchingElements {
	
	private LinkedHashMap<Integer, Integer> arrayData;
	
	public MatchingElements(int [] numbers) {
		arrayData = new LinkedHashMap<Integer, Integer> ();
		for(int i = 0; i < numbers.length; i++) {
			if(arrayData.containsKey(numbers[i]))
				arrayData.put(numbers[i], arrayData.get(numbers[i]) + 1);
			else
				arrayData.put(numbers[i], 1);
		}
	}
	
	public void printMatching() {
		boolean matchingExists = false;
		for(Integer key : arrayData.keySet()) {
			if(arrayData.get(key) > 1) {
				System.out.println(key);
				matchingExists = true;
			}
		}
		if(!matchingExists)
			System.out.println("The array has no matching elements... ");
	}

}
