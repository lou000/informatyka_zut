package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.TV;

public class PolecenieUstawDvd implements Polecenie{
    TV tv;
    int prev = 0;

    public PolecenieUstawDvd(TV tv)
    {
        super();
        this.tv = tv;
    }

    @Override
    public void wykonaj() {
//        prev = tv.getChannel();
        tv.ustawDVD();
    }

    @Override
    public void wycofaj() {
//        tv.setChannel(prev);
    }
}
