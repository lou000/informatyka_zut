package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.fabryka.ProstaFabrykaPizzy;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.*;

public class Pizzeria4 {
    public Pizzeria4() {fabryka = new ProstaFabrykaPizzy();}

    ProstaFabrykaPizzy fabryka;
    Pizza zamówPizza(String type) {
        return fabryka.utwórzPizza(type);
    }
}
