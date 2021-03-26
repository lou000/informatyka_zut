package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Jacuzzi;
import pl.edu.zut.wo.wzorce.pilot.sterowniki.TV;

public class PolecenieWlaczTV implements Polecenie{
    TV tv;

    public PolecenieWlaczTV(TV tv)
    {
        super();
        this.tv = tv;
    }

    @Override
    public void wykonaj() {
        tv.włącz();
    }

    @Override
    public void wycofaj() {
        tv.wyłącz();
    }
}
