package pl.edu.zut.wo.wzorce.pilot;

import pl.edu.zut.wo.wzorce.pilot.polecenia.*;
import pl.edu.zut.wo.wzorce.pilot.sterowniki.*;

public class SuperPilotTestMakro {
    public static void main(String[] args) {
        SuperPilot superPilot = new SuperPilot();

        Światło salonŚwiatło = new Światło("Salon");
        Światło kuchniaŚwiatło = new Światło("Kuchnia");
        WentylatorSufitowy wentylatorSufitowy = new WentylatorSufitowy("Salon");
        WieżaStereo stereo = new WieżaStereo("Salon");
        DrzwiGarażu drzwi = new DrzwiGarażu("Garaż");
        TV tv = new TV("Salon");
        Jacuzzi jacuzzi = new Jacuzzi();

        Polecenie salonŚwiatłoWłącz = new PolecenieWłączŚwiatło(salonŚwiatło);
        Polecenie salonŚwiatłoWyłącz = new PolecenieWylaczSwiatlo(salonŚwiatło);
        Polecenie kuchniaŚwiatłoWłącz = new PolecenieWłączŚwiatło(kuchniaŚwiatło);
        Polecenie kuchniaSwiatloWylacz = new PolecenieWylaczSwiatlo(kuchniaŚwiatło);
        Polecenie stereoWlacz = new PolecenieWlaczStereo(stereo);
        Polecenie stereoWylacz = new PolecenieWylaczStereo(stereo);
        Polecenie tvWlacz = new PolecenieWlaczTV(tv);
        Polecenie tvUstawDvd = new PolecenieUstawDvd(tv);
        Polecenie tvWylacz = new PolecenieWylaczTV(tv);
        Polecenie jacuzziCyrk = new PolecenieJacuzziCyrkulacja(jacuzzi);
        Polecenie jacuzziWlaczDysze = new PolecenieJacuzziWlaczDysze(jacuzzi);
        Polecenie jacuzziWylaczDysze = new PolecenieJacuzziWylaczDysze(jacuzzi);
        Polecenie jacuzziUstawTemp = new PolecenieJacuzziUstawTemperature(jacuzzi, 30, 0);
        Polecenie jacuzziWlacz = new PolecenieJacuzziWlacz(jacuzzi);
        Polecenie jacuzziWylacz = new PolecenieJacuzziWylacz(jacuzzi);

        Polecenie[] polWlaczSwiatla = {salonŚwiatłoWłącz, kuchniaŚwiatłoWłącz};
        Polecenie[] polWylaczSwiatla = {salonŚwiatłoWyłącz, kuchniaSwiatloWylacz};

        MakroPolecenie wlaczSwiatla = new MakroPolecenie(polWlaczSwiatla);
        MakroPolecenie wylaczSwiatla = new MakroPolecenie(polWylaczSwiatla);

        Polecenie[] polImprezkaOn = {salonŚwiatłoWyłącz, kuchniaSwiatloWylacz, stereoWlacz, tvWlacz, tvUstawDvd,
                                     jacuzziWlacz, jacuzziUstawTemp, jacuzziWlaczDysze, jacuzziCyrk};

        Polecenie[] polImprezkaOff = {salonŚwiatłoWłącz, kuchniaŚwiatłoWłącz, stereoWylacz,
                                      tvWylacz, jacuzziWylaczDysze, jacuzziWylacz};

        MakroPolecenie imprezkaOn = new MakroPolecenie(polImprezkaOn);
        MakroPolecenie imprezkaOff = new MakroPolecenie(polImprezkaOff);


        superPilot.ustawPolecenie(5, wlaczSwiatla, wylaczSwiatla);
        superPilot.ustawPolecenie(6, imprezkaOn, imprezkaOff);

        System.out.println(superPilot);



        superPilot.wciśniętoPrzyciskWłącz(5);
        superPilot.wciśniętoPrzyciskWyłącz(5);
        superPilot.wciśniętoPrzyciskWłącz(6);
        superPilot.wciśniętoPrzyciskWyłącz(6);
    }
}
