package pl.edu.zut.wo.wzorce.pilot.sterowniki;

public class Jacuzzi {
	boolean włączone;
	int temperatura;

	public Jacuzzi() {
	}

	public void włącz() {
		włączone = true;
	}

	public void wyłącz() {
		włączone = false;
	}

	public void cyrkulacja() {
		if (włączone) {
			System.out.println("Jacuzzi bąbluje!");
		}
	}

	public void włączDysze() {
		if (włączone) {
			System.out.println("Jacuzzi dysze są włączone");
		}
	}

	public void wyłączDysze() {
		if (włączone) {
			System.out.println("Jacuzzi dysze są wyłączone");
		}
	}

	public void ustawTemperaturę(int temperatura) {
		if (temperatura > this.temperatura) {
			System.out.println("Jacuzzi nagrzewa się do parowania w temp. " + temperatura + " stopni");
		}
		else {
			System.out.println("Jacuzzi oziębia się do temp. " + temperatura + " stopni");
		}
		this.temperatura = temperatura;
	}
}
