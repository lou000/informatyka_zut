package pl.edu.zut.wo.wzorce.pilot;

import java.util.*;

import pl.edu.zut.wo.wzorce.pilot.polecenia.BrakPolecenia;
import pl.edu.zut.wo.wzorce.pilot.polecenia.Polecenie;

//
// This is the invoker
//
public class SuperPilot {
	Polecenie[] poleceniaWłącz;
	Polecenie[] poleceniaWyłącz;
	Polecenie polecenieWycofaj;
 
	public SuperPilot() {
		poleceniaWłącz = new Polecenie[7];
		poleceniaWyłącz = new Polecenie[7];
 
		Polecenie brakPolecenia = new BrakPolecenia();
		for(int i=0; i<7; i++) {
			poleceniaWłącz[i] = brakPolecenia;
			poleceniaWyłącz[i] = brakPolecenia;
		}
		polecenieWycofaj = brakPolecenia;
	}
  
	public void ustawPolecenie(int slot, Polecenie polecenieWłącz, Polecenie polecenieWyłącz) {
		poleceniaWłącz[slot] = polecenieWłącz;
		poleceniaWyłącz[slot] = polecenieWyłącz;
	}
 
	public void wciśniętoPrzyciskWłącz(int slot) {
		poleceniaWłącz[slot].wykonaj();
		polecenieWycofaj = poleceniaWłącz[slot];
	}
 
	public void wciśniętoPrzyciskWyłącz(int slot) {
		poleceniaWyłącz[slot].wykonaj();
		polecenieWycofaj = poleceniaWyłącz[slot];
	}

	public void wciśniętoPrzyciskWycofaj() {
		polecenieWycofaj.wycofaj();
	}
 
	public String toString() {
		StringBuffer stringBuff = new StringBuffer();
		stringBuff.append("\n------ Super Pilot -------\n");
		for (int i = 0; i < poleceniaWłącz.length; i++) {
			stringBuff.append("[slot " + i + "] " + poleceniaWłącz[i].getClass().getName()
				+ "    " + poleceniaWyłącz[i].getClass().getName() + "\n");
		}
		stringBuff.append("[undo] " + polecenieWycofaj.getClass().getName() + "\n");
		return stringBuff.toString();
	}
}
