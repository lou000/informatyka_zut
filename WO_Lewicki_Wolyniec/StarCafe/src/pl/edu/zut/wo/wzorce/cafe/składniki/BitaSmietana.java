package pl.edu.zut.wo.wzorce.cafe.składniki;
import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;
import pl.edu.zut.wo.wzorce.cafe.składniki.SkladnikDekorator;

public class BitaSmietana extends SkladnikDekorator {

    public BitaSmietana(Napój n){napoj = n; opis = "BitaSmietana";}
    @Override
    public String pobierzOpis() {
        return napoj.pobierzOpis() + "\n" + opis;
    }
    @Override
    public double koszt() {
        return napoj.koszt()+0.5;
    }
}
