package pl.edu.zut.wo.wzorce.symulator;

public class MiniSymulatorKaczki {

	public static void main(String[] args) {
		Kaczka dzika = new DzikaKaczka();
		dzika.wyswietl();
		dzika.wykonajKwacz();
		dzika.wykonajLec();
		Kaczka gumowa = new GumowaKaczka();
		gumowa.wyswietl();
		gumowa.wykonajKwacz();
		gumowa.wykonajLec();
		Kaczka plaskonos = new PlaskonosKaczka();
		plaskonos.wyswietl();
		plaskonos.wykonajKwacz();
		plaskonos.wykonajLec();
		Kaczka wabik = new WabikKaczka();
		wabik.wyswietl();
		wabik.wykonajKwacz();
		wabik.wykonajLec();
		ModelKaczki model = new ModelKaczki();
		model.wykonajLec();
		model.zmienNaped(new LotZNapedemRakietowym());
		model.wykonajLec();
	}
}
