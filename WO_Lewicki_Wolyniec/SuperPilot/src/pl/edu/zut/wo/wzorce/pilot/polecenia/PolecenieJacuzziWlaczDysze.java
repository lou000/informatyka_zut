package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Jacuzzi;

public class PolecenieJacuzziWlaczDysze implements Polecenie{

    Jacuzzi jacuzzi;

    public PolecenieJacuzziWlaczDysze(Jacuzzi jacuzzi)
    {
        super();
        this.jacuzzi = jacuzzi;
    }

    @Override
    public void wykonaj() {
        jacuzzi.włączDysze();
    }

    @Override
    public void wycofaj() {
        jacuzzi.wyłączDysze();
    }

}
