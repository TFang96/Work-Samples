import java.util.Scanner;
public class PalindromeDriver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Scanner keyboard = new Scanner(System.in);
		System.out.println("Please enter a word you wish to test: ");
		String word = keyboard.nextLine();
		keyboard.close();
		Palindrome test = new Palindrome(word);
		if(test.isPalindrome())
			System.out.println("The word, " + word + " is a palindrome.");
		else
			System.out.println("The word, " + word + " is not a palindrome.");

	}

}
