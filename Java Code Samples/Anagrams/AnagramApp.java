import java.util.Scanner;
public class AnagramApp {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner keyboard = new Scanner(System.in);
		System.out.println("Please enter a word: ");
		String w1 = keyboard.nextLine();
		System.out.println("Please enter another word: ");
		String w2 = keyboard.nextLine();
		keyboard.close();
		Anagram anagram = new Anagram(w1, w2);
		if(anagram.isAnagram())
			System.out.println(w1 + " and " + w2 + " are anagrams.");
		else
			System.out.println(w1 + " and " + w2 + " are not anagrams.");

	}

}
