package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public class Mleko extends SkladnikDekorator {
    public Mleko(Napój n){napoj = n; opis = "Mleko";}
    @Override
    public String pobierzOpis() {
        return napoj.pobierzOpis() + "\n" + opis;
    }
    @Override
    public double koszt() {
        return napoj.koszt()+0.1;
    }
}
