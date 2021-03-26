package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Światło;

public class PolecenieWłączŚwiatło implements Polecenie {

	Światło światło;

	public PolecenieWłączŚwiatło(Światło światło) {
		super();
		this.światło = światło;
	}

	public void wykonaj() {
		światło.włącz();
	}

	@Override
	public void wycofaj() {
		światło.wyłącz();
	}
}
