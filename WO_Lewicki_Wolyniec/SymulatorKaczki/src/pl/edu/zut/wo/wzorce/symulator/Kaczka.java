package pl.edu.zut.wo.wzorce.symulator;

public class Kaczka{

    static LatanieInterfejs latanieInterfejs;
    static KwakanieInterfejs kwakanieInterfejs;

    void wykonajKwacz() {kwakanieInterfejs.kwacz();}
    void wykonajLec() {latanieInterfejs.lec();}


    void plywaj() {
    	System.out.println("Pływam jak kaczka.");
    }
    void wyswietl() {
    	System.out.println("Wyglądam jak kaczka.");
    }

}
