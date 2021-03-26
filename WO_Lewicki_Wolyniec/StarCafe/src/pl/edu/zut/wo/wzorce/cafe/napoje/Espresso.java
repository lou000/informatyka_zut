package pl.edu.zut.wo.wzorce.cafe.napoje;

public class Espresso extends Napój {

    public Espresso(){
        opis = "Kawa Espresso";
    }

    @Override
    public double koszt() {
        return 5;
    }
}
