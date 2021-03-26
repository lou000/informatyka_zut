package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Jacuzzi;

public class PolecenieJacuzziWylacz implements Polecenie{

    Jacuzzi jacuzzi;

    public PolecenieJacuzziWylacz(Jacuzzi jacuzzi)
    {
        super();
        this.jacuzzi = jacuzzi;
    }

    @Override
    public void wykonaj() {
        jacuzzi.wyłącz();
    }

    @Override
    public void wycofaj() {
        jacuzzi.włącz();
    }
}
