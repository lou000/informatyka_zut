package pl.edu.zut.wo.wzorce.symulator;

public class PlaskonosKaczka extends Kaczka {
	public void wyświetl(){
		System.out.println("Wygląda jak płaskonos");
	}
	public PlaskonosKaczka() {
		latanieInterfejs = new LatamBoMamSkrzydla();
		kwakanieInterfejs = new Kwacz();
	}
}