package pl.edu.zut.wo.wzorce.pilot;

import pl.edu.zut.wo.wzorce.pilot.polecenia.PolecenieWłączŚwiatło;
import pl.edu.zut.wo.wzorce.pilot.sterowniki.Światło;

public class MiniPilotTest {
	public static void main(String[] args) {
		MiniPilot pilot = new MiniPilot();
		Światło światło = new Światło("lokalizacja: ");
		pilot.ustawPolecenie(new PolecenieWłączŚwiatło(światło));
		pilot.przyciskZostałNaciśnięty();
	}
}
