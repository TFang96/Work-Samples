import java.util.LinkedHashMap;
public class Anagram {
	
	LinkedHashMap<Character, Integer> wordData1;
	LinkedHashMap<Character, Integer> wordData2;
	
	public Anagram(String w1, String w2) {
		wordData1 = new LinkedHashMap<Character, Integer> ();
		wordData2 = new LinkedHashMap<Character, Integer> ();
		
		for(int i = 0; i < w1.length(); i++) {
			if(!wordData1.containsKey(w1.charAt(i)))
				wordData1.put(w1.charAt(i), 1);
			else
				wordData1.put(w1.charAt(i), wordData1.get(w1.charAt(i)) + 1);
		}
		for(int i = 0; i < w2.length(); i++) {
			if(!wordData2.containsKey(w2.charAt(i)))
				wordData2.put(w2.charAt(i), 1);
			else
				wordData2.put(w2.charAt(i), wordData2.get(w2.charAt(i)) +1);
		}
	}
	
	public boolean isAnagram() {
		for(Character k : wordData1.keySet()) {
			if(!wordData2.containsKey(k))
				return false;
			else {
				if(wordData2.get(k) != wordData1.get(k))
					return false;
			}
		}
		return true;
	}

}
