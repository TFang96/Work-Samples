
public class Bat extends Mammal {
	
	private int wingLength;
	private int flightSpeed;
	
	public Bat(int lungs, int teeth, int wings, int speed) {
		super(lungs, teeth);
		wingLength = wings;
		flightSpeed = speed;
	}
	
	public int getWings() {
		return wingLength;
	}
	
	public int getSpeed() {
		return flightSpeed;
	}
	
	public void setWings(int w) {
		wingLength = w;
	}
	
	public void setSpeed(int s) {
		flightSpeed = s;
	}

}
