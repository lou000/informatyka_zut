package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public abstract class SkladnikDekorator extends Napój{
    protected Napój napoj;
    public abstract String pobierzOpis();
}
