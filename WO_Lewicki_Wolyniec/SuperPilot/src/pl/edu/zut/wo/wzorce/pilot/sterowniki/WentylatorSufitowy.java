package pl.edu.zut.wo.wzorce.pilot.sterowniki;


public class WentylatorSufitowy {
	public static final int SZYBKO = 3;
	public static final int ŚREDNIO = 2;
	public static final int WOLNO = 1;
	public static final int WYŁĄCZONY = 0;
	String lokalizacja;
	int obroty;
 
	public WentylatorSufitowy(String location) {
		this.lokalizacja = location;
	}
  
	public void szybko() {
		// turns the ceiling fan on to high
		obroty = SZYBKO;
		System.out.println(lokalizacja + " wentylator sufitowy wysokie obroty.");
	} 

	public void średnio() {
		// turns the ceiling fan on to medium
		obroty = ŚREDNIO;
		System.out.println(lokalizacja + " wentylator sufitowy średnie obroty.");
	}

	public void wolno() {
		// turns the ceiling fan on to low
		obroty = WOLNO;
		System.out.println(lokalizacja + " wentylator sufitowy wolne obroty.");
	}
 
	public void off() {
		// turns the ceiling fan off
		obroty = WYŁĄCZONY;
		System.out.println(lokalizacja + " wentylator sufitowy jest wyłączony.");
	}
 
	public int pobierzSzybkość() {
		return obroty;
	}
}
