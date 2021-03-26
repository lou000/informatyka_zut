package pl.edu.zut.wo.wzorce.pogodynka;

import java.io.BufferedWriter;
import java.util.ArrayList;

import pl.edu.zut.wo.wzorce.pogodynka.wyświetl.*;

public class DanePogodowe implements Podmiot {
	private float temperatura;
	private float wilgotność;
	private float ciśnienie;
	private ArrayList<Obserwator> obserwators = new ArrayList<>();

	@Override
	public void zarejestrujObserwatora(Obserwator o) {obserwators.add(o);}

	@Override
	public void usunObserwatora(Obserwator o) {obserwators.remove(o);}

	@Override
	public void powiadomObserwatorow() {
		for(Obserwator obs : obserwators)
			obs.aktualizacja(temperatura, wilgotność, ciśnienie);
	}

	public void odczytyZmiana(){
		float temp = pobierzTemperaturę();
		float wilgotność = pobierzWilgotność();
		float ciśnienie = pobierzCiśnienie();
		powiadomObserwatorow();
	}

	private float pobierzTemperaturę(){
		return temperatura;
	}

	private float pobierzWilgotność(){
		return wilgotność;
	}

	private float pobierzCiśnienie(){
		return ciśnienie;
	}
	
	public void ustawOdczyty(float temperatura, float wilgotność, float ciśnienie) {
		this.temperatura = temperatura;
		this.wilgotność = wilgotność;
		this.ciśnienie = ciśnienie;
		odczytyZmiana();
	}
}
