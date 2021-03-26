package pl.edu.zut.wo.wzorce.pilot.polecenia;


public class MakroPolecenie implements Polecenie {
	Polecenie[] polecenia;
 
	public MakroPolecenie(Polecenie[] commands) {
		this.polecenia = commands;
	}
 
	public void wykonaj() {
		for (int i = 0; i < polecenia.length; i++) {
			polecenia[i].wykonaj();
		}
	}
 
	public void wycofaj() {
		for (int i = 0; i < polecenia.length; i++) {
			polecenia[i].wycofaj();
		}
	}
}

