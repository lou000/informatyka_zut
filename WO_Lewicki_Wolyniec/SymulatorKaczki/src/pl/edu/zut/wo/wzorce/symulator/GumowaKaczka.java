package pl.edu.zut.wo.wzorce.symulator;


public class GumowaKaczka extends Kaczka {

	public void wyświetl(){
		System.out.println("Wygląda jak gumowa kaczka");
	}
	public GumowaKaczka() {
		latanieInterfejs = new NieLatam();
		kwakanieInterfejs = new Piszcz();
	}
}