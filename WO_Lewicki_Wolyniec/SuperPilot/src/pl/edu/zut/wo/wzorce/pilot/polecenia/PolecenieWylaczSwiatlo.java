package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Światło;

public class PolecenieWylaczSwiatlo implements Polecenie{

    Światło światło;

    public PolecenieWylaczSwiatlo(Światło światło) {
        super();
        this.światło = światło;
    }

    public void wykonaj() {
        światło.wyłącz();
    }

    @Override
    public void wycofaj() {
        światło.włącz();
    }
}
