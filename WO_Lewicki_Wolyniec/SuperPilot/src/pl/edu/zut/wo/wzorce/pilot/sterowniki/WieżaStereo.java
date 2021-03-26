package pl.edu.zut.wo.wzorce.pilot.sterowniki;

public class WieżaStereo {
	String lokalizacja;

	public WieżaStereo(String location) {
		this.lokalizacja = location;
	}

	public void włącz() {
		System.out.println(lokalizacja + " wieża stereo jest włączona");
	}

	public void wyłącz() {
		System.out.println(lokalizacja + " wieża stereo jest wyłączona");
	}

	public void ustawCD() {
		System.out.println(lokalizacja + " wieża stereo CD jest włączone");
	}

	public void ustawDVD() {
		System.out.println(lokalizacja + " wieża stereo DVD jest włączone");
	}

	public void ustawRadio() {
		System.out.println(lokalizacja + " wieża stereo Radio jest włączone");
	}

	public void ustawGłośność(int głośność) {
		// code to set the volume
		// valid range: 1-11 (after all 11 is better than 10, right?)
		System.out.println(lokalizacja + " wieża stereo głośność ustawiona na " + głośność);
	}
}
