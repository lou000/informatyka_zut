package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.WentylatorSufitowy;

public class PolecenieWentylatorWysokieObroty implements Polecenie{
    private int prevSpeed;
    private WentylatorSufitowy wentylator;

    public PolecenieWentylatorWysokieObroty(WentylatorSufitowy went)
    {
        super();
        this.prevSpeed = went.pobierzSzybkość();
        this.wentylator = went;
    }

    @Override
    public void wykonaj() {
        prevSpeed = wentylator.pobierzSzybkość();
        wentylator.szybko();
    }

    @Override
    public void wycofaj() {
        switch (prevSpeed) {
            case 0 -> wentylator.off();
            case 1 -> wentylator.wolno();
            case 2 -> wentylator.średnio();
            case 3 -> wentylator.szybko();
        }
    }
}
