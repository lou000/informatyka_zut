package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Jacuzzi;

public class PolecenieJacuzziWylaczDysze implements Polecenie{
    Jacuzzi jacuzzi;

    public PolecenieJacuzziWylaczDysze(Jacuzzi jacuzzi)
    {
        super();
        this.jacuzzi = jacuzzi;
    }

    @Override
    public void wykonaj() {
        jacuzzi.wyłączDysze();
    }

    @Override
    public void wycofaj() {
        jacuzzi.włączDysze();
    }
}
