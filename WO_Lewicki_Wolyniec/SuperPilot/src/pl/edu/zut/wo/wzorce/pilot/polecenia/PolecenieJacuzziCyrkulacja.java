package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Jacuzzi;

public class PolecenieJacuzziCyrkulacja implements Polecenie{

    Jacuzzi jacuzzi;

    public PolecenieJacuzziCyrkulacja(Jacuzzi jacuzzi)
    {
        super();
        this.jacuzzi = jacuzzi;
    }

    @Override
    public void wykonaj() {
        jacuzzi.cyrkulacja();
    }

    @Override
    public void wycofaj() {
        //nie istnieje
    }
}
