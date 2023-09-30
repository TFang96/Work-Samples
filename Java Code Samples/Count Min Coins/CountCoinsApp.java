/**
 * 
 */

/**
 * 
 */
import java.util.Scanner;
public class CountCoinsApp {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner keyboard = new Scanner(System.in);
		int amount;
		System.out.println("Please enter a value (in cents): ");
		amount = keyboard.nextInt();
		while (amount <= 0) { // this is to prevent any negative values
			System.out.println("Please enter a value greater than 0... ");
			amount = keyboard.nextInt();
		}
		keyboard.close();
		System.out.println("The amount of " + amount + " cents can be satisfied by a minimum of " + CountCoins(amount) 
			+ " coins.");

	}
	
	public static int CountCoins(int amount) {
		if(amount == 0)
			return 0;
		else if(amount == 1)
			return 1;
		else if(amount == 2)
			return 2;
		else if(amount == 3)
			return 3;
		else if(amount == 4)
			return 4;
		else {
			if(amount - 100 >= 0)
				return 1 + CountCoins(amount - 100);
			else if(amount - 50 >= 0)
				return 1 + CountCoins(amount - 50);
			else if(amount - 25 >= 0)
				return 1 + CountCoins(amount-25);
			else if(amount - 10 >= 0)
				return 1 + CountCoins(amount - 10);
			else if(amount - 5 >= 0)
				return 1 + CountCoins(amount - 5);
			else
				return 1 + CountCoins(amount - 1);
		}
	}

}
