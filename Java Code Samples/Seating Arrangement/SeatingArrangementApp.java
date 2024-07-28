import java.util.Scanner;

public class SeatingArrangementApp {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner keyboard = new Scanner(System.in);
		System.out.println("Please enter the possibility number. ");
		int n = keyboard.nextInt();
		keyboard.close();
		System.out.println("The " + n + "th possibility is: " + Possibility(n));

	}
	
	public static String Possibility(int n) {
		int counter = 1;
		int currentPos = 0;
		while(currentPos < n) {
			if(!Integer.toBinaryString(counter).contains("11"))
				currentPos++;
			counter++;
		}
		return Integer.toBinaryString(counter-1); // the -1 would offset the counter++. it would increment before we check the condition.
	}

}
