package pl.edu.zut.wo.wzorce.pilot;

import pl.edu.zut.wo.wzorce.pilot.polecenia.Polecenie;

public class MiniPilot {
	Polecenie slot;
	
	public void ustawPolecenie(Polecenie polecenie) {
		slot = polecenie;
	}
	
	public void przyciskZostałNaciśnięty() {
		slot.wykonaj();
	}

}
