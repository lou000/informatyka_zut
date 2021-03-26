package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.WieżaStereo;

public class PolecenieWylaczStereo implements Polecenie{
    WieżaStereo stereo;

    public PolecenieWylaczStereo(WieżaStereo stereo)
    {
        super();
        this.stereo = stereo;
    }

    @Override
    public void wykonaj() {
        stereo.wyłącz();
    }
    @Override
    public void wycofaj() {
        stereo.włącz();
    }
}
