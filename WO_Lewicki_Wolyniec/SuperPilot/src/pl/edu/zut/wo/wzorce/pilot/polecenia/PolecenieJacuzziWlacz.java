package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Jacuzzi;

public class PolecenieJacuzziWlacz implements Polecenie{

    Jacuzzi jacuzzi;

    public PolecenieJacuzziWlacz(Jacuzzi jacuzzi)
    {
        super();
        this.jacuzzi = jacuzzi;
    }

    @Override
    public void wykonaj() {
        jacuzzi.włącz();
    }

    @Override
    public void wycofaj() {
        jacuzzi.wyłącz();
    }
}
