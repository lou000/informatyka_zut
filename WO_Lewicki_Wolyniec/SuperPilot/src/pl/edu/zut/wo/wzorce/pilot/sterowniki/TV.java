package pl.edu.zut.wo.wzorce.pilot.sterowniki;

public class TV {
	String lokalizacja;
	int kanał;

	public TV(String lokalizacja) {
		this.lokalizacja = lokalizacja;
	}

	public void włącz() {
		System.out.println(lokalizacja + " TV jest włączony");
	}

	public void wyłącz() {
		System.out.println(lokalizacja + " TV jest wyłączony");
	}

	public void ustawDVD() {
		this.kanał = 3;
		System.out.println(lokalizacja + " TV kanał jest ustawiony na DVD");
	}
}
