import java.util.Stack;
public class ReverseStringApp {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String word = "top";
		System.out.println("Word is " + word + " reverse is: " + reverseString(word) + ".");

	}
	
	public static String reverseString(String word) {
		Stack<Character> reverseStack = new Stack<>();
		String reverseWord = "";
		for(int i = 0; i < word.length(); i++) 
			reverseStack.push(word.charAt(i));
		for(int i = 0; i < word.length(); i++) 
			reverseWord+=reverseStack.pop();
		return reverseWord;
	}

}
