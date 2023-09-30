
public abstract class Mammal {
	
	private int lungSize;
	private int teethSize;
	
	public Mammal(int lungs, int teeth) {
		lungSize = lungs;
		teethSize = teeth;
	}
	
	protected void setLungs(int lungs) {
		lungSize = lungs;
	}
	
	protected void setTeeth(int teeth) {
		teethSize = teeth;
	}
	
	protected int getLungs() {
		return lungSize;
	}
	
	protected int getTeeth() {
		return teethSize;
	}
	
	public abstract int getSpeed();

}
