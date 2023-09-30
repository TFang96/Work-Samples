
public class Whale extends Mammal {
	
	private int tailLength;
	private int swimSpeed;
	
	public Whale(int lungs, int teeth, int tail, int speed) {
		super(lungs, teeth);
		tailLength = tail;
		swimSpeed = speed;
	}
	
	public int getTail() {
		return tailLength;
	}
	
	public int getSpeed() {
		return swimSpeed;
	}
	
	public void setTail(int t) {
		tailLength = t;
	}
	
	public void setSpeed(int s) {
		swimSpeed = s;
	}

}
