package pl.edu.zut.wo.wzorce.pogodynka.wyświetl;

public class IndeksWyswietlanie implements Obserwator, WyswietlElement{
    private float temperatura;
    private float wilgotność;
    private float ciśnienie;
    @Override
    public void aktualizacja(float temp, float wilg, float cis) {
        this.temperatura = temperatura;
        this.wilgotność = wilgotność;
        this.ciśnienie = ciśnienie;
        wyświetl();
    }

    @Override
    public void wyświetl() {
        System.out.println("Indeks bieżący " + computeHeatIndex(temperatura, wilgotność));
    }

    private float computeHeatIndex(float t, float rh) {
        return (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh)
                + (0.00941695 * (t * t)) + (0.00728898 * (rh * rh))
                + (0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
                (0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *
                (rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
                (0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +
                0.000000000843296 * (t * t * rh * rh * rh)) -
                (0.0000000000481975 * (t * t * t * rh * rh * rh)));
    }
}
