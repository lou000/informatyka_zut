package pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.klasyczny;

public class Singleton {
	private static Singleton unikalnaInstancja;

	// tutaj umieść inne użyteczne zmienne obiektowe
	private Singleton() {
	}

	public static Singleton pobierzInstancję() {
		if (unikalnaInstancja == null) {
			unikalnaInstancja = new Singleton();
		}
		return unikalnaInstancja;
	}
	// tutaj umieść inne użyteczne metody
}