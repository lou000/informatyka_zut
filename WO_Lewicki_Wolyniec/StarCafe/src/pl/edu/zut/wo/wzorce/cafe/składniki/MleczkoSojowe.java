package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public class MleczkoSojowe extends SkladnikDekorator{
    public MleczkoSojowe(Napój n){napoj = n; opis = "Mleczko sojowe";}
    @Override
    public String pobierzOpis() {
        return napoj.pobierzOpis() + "\n" + opis;
    }
    @Override
    public double koszt() {
        return napoj.koszt()+0.2;
    }
}
