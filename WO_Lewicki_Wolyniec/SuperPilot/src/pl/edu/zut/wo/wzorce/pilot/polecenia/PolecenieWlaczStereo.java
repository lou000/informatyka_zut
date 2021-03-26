package pl.edu.zut.wo.wzorce.pilot.polecenia;

import pl.edu.zut.wo.wzorce.pilot.sterowniki.WieżaStereo;

public class PolecenieWlaczStereo implements Polecenie{
    WieżaStereo stereo;

    public PolecenieWlaczStereo(WieżaStereo stereo)
    {
        super();
        this.stereo = stereo;
    }

    @Override
    public void wykonaj() {
        stereo.włącz();
    }
    @Override
    public void wycofaj() {
        stereo.wyłącz();
    }
}
