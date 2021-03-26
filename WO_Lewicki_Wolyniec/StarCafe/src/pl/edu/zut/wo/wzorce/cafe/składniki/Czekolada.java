package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public class Czekolada extends SkladnikDekorator {
    public Czekolada(Napój n){napoj = n; opis = "Czekolada";}
    @Override
    public String pobierzOpis() {
        return napoj.pobierzOpis() + "\n" + opis;
    }
    @Override
    public double koszt() {
        return napoj.koszt()+10;
    }
}
