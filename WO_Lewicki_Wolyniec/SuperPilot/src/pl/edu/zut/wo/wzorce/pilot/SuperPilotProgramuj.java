package pl.edu.zut.wo.wzorce.pilot;

import pl.edu.zut.wo.wzorce.pilot.polecenia.*;
import pl.edu.zut.wo.wzorce.pilot.sterowniki.DrzwiGarażu;
import pl.edu.zut.wo.wzorce.pilot.sterowniki.WentylatorSufitowy;
import pl.edu.zut.wo.wzorce.pilot.sterowniki.WieżaStereo;
import pl.edu.zut.wo.wzorce.pilot.sterowniki.Światło;

public class SuperPilotProgramuj {
 
	public static void main(String[] args) {
		SuperPilot superPilot = new SuperPilot();
 
		Światło salonŚwiatło = new Światło("Salon");
		Światło kuchniaŚwiatło = new Światło("Kuchnia");
		WentylatorSufitowy wentylatorSufitowy = new WentylatorSufitowy("Salon");
		WieżaStereo stereo = new WieżaStereo("Salon");
		DrzwiGarażu drzwi = new DrzwiGarażu("Garaż");
		
		Polecenie salonŚwiatłoWłącz = new PolecenieWłączŚwiatło(salonŚwiatło);
		Polecenie salonŚwiatłoWyłącz = new PolecenieWylaczSwiatlo(salonŚwiatło);
		Polecenie kuchniaŚwiatłoWłącz = new PolecenieWłączŚwiatło(kuchniaŚwiatło);
		Polecenie kuchniaSwiatloWylacz = new PolecenieWylaczSwiatlo(kuchniaŚwiatło);
		Polecenie stereoWlacz = new PolecenieWlaczStereo(stereo);
		Polecenie stereoWylacz = new PolecenieWylaczStereo(stereo);
		Polecenie drzwiOtworz = new PolecenieOtworzDrzwi(drzwi);
		Polecenie drzwiZamknij = new PolecenieZamknijDrzwi(drzwi);
		Polecenie wentWylacz = new PolecenieWylaczWentylator(wentylatorSufitowy);
		Polecenie wentSzybko = new PolecenieWentylatorWysokieObroty(wentylatorSufitowy);

		
		superPilot.ustawPolecenie(0, salonŚwiatłoWłącz, salonŚwiatłoWyłącz);
		superPilot.ustawPolecenie(1, kuchniaŚwiatłoWłącz, kuchniaSwiatloWylacz);
		superPilot.ustawPolecenie(2, wentSzybko, wentWylacz);
		superPilot.ustawPolecenie(3, drzwiOtworz, drzwiZamknij);
		superPilot.ustawPolecenie(4, stereoWlacz, stereoWylacz);
  
		System.out.println(superPilot);
 
		superPilot.wciśniętoPrzyciskWłącz(0);
		superPilot.wciśniętoPrzyciskWycofaj();
		superPilot.wciśniętoPrzyciskWyłącz(0);
		superPilot.wciśniętoPrzyciskWłącz(1);
		superPilot.wciśniętoPrzyciskWyłącz(1);
		superPilot.wciśniętoPrzyciskWłącz(2);
		superPilot.wciśniętoPrzyciskWyłącz(2);
		superPilot.wciśniętoPrzyciskWłącz(3);
		superPilot.wciśniętoPrzyciskWyłącz(3);
		superPilot.wciśniętoPrzyciskWłącz(4);
		superPilot.wciśniętoPrzyciskWyłącz(4);
	}
}
