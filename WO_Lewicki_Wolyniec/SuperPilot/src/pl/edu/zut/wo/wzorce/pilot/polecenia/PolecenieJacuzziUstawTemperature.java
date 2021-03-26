package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.Jacuzzi;

public class PolecenieJacuzziUstawTemperature implements Polecenie{
    Jacuzzi jacuzzi;
    int tempOn;
    int tempOff;

    public PolecenieJacuzziUstawTemperature(Jacuzzi jacuzzi, int tempOn, int tempOff)
    {
        super();
        this.jacuzzi = jacuzzi;
        this.tempOn = tempOn;
        this.tempOff = tempOff;
    }

    @Override
    public void wykonaj() {
        jacuzzi.ustawTemperaturę(tempOn);
    }

    @Override
    public void wycofaj() {
        jacuzzi.ustawTemperaturę(tempOff);
    }
}
