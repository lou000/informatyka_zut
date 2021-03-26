package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.DrzwiGarażu;

public class PolecenieOtworzDrzwi implements Polecenie{

    DrzwiGarażu drzwi;

    public PolecenieOtworzDrzwi(DrzwiGarażu drzwi)
    {
        super();
        this.drzwi = drzwi;
    }

    @Override
    public void wykonaj()
    {
        drzwi.podnieś();
    }

    @Override
    public void wycofaj()
    {
        drzwi.opuść();
    }
}
