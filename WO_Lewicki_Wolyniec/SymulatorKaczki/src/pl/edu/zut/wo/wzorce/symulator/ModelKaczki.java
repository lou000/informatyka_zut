package pl.edu.zut.wo.wzorce.symulator;

public class ModelKaczki{
    public void wyświetl(){
        System.out.println("Wygląda jak model kaczki");
    }
    LatanieInterfejs latanieInterfejs = new NieLatam();
    KwakanieInterfejs kwakanieInterfejs =  new NieKwacz();

    void wykonajKwacz() {kwakanieInterfejs.kwacz();}
    void wykonajLec() {latanieInterfejs.lec();}

    public void zmienNaped(LatanieInterfejs interfejs)
    {
        latanieInterfejs = interfejs;
    }
    void plywaj() {
        System.out.println("Pływam jak kaczka.");
    }
    void wyswietl() {
        System.out.println("Wyglądam jak kaczka.");
    }
}
