package pl.edu.zut.wo.wzorce.symulator;

public class WabikKaczka extends Kaczka {
    public void wyświetl(){
        System.out.println("Nie wyglada jak kaczka");
    }
    public WabikKaczka() {
        latanieInterfejs = new NieLatam();
        kwakanieInterfejs = new Kwacz();
    }
}
