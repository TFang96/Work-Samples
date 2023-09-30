
public class Human extends Mammal {
	
	private int armLength;
	private int runSpeed;
	
	public Human(int lungs, int teeth, int arms, int speed) {
		super(lungs, teeth);
		armLength = arms;
		runSpeed = speed;
	}
	
	public int getArms() {
		return armLength;
	}
	
	public int getSpeed() {
		return runSpeed;
	}
	
	public void setArms(int a) {
		armLength = a;
	}
	
	public void setSpeed(int s) {
		runSpeed = s;
	}

}
