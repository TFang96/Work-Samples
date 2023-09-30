
public class Palindrome {
	
	private String checkString;
	
	public Palindrome(String s) {
		checkString = s;
	}
	
	public boolean isPalindrome() {
		if(checkString.length() == 0 || checkString.length() == 1)
			return true;
		else {
			if(checkString.charAt(0) != checkString.charAt(checkString.length() - 1))
				return false;
			else {
				checkString = checkString.substring(1, checkString.length() - 1);
				return isPalindrome();
			}
		}
	}

}
