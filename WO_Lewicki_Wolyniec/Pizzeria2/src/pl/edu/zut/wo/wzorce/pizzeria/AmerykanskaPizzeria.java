package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.fabryka.AmerykanskaFabrykaSkladnikowPizzy;
import pl.edu.zut.wo.wzorce.pizzeria.fabryka.FabrykaSkładnikówPizzy;
import pl.edu.zut.wo.wzorce.pizzeria.fabryka.WłoskaFabrykaSkładnikówPizzy;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.*;

public class AmerykanskaPizzeria extends Pizzeria {
    protected Pizza utwórzPizza(String item) {
        Pizza pizza = null;
        FabrykaSkładnikówPizzy fabrykaSkładników = new AmerykanskaFabrykaSkladnikowPizzy();
        if (item.equals("serowa")) {
            pizza = new SerowaPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykanska Pizza Serowa");
        } else if (item.equals("wegetariańska")) {
            pizza = new WegetariańskaPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykanska Pizza Wegetariańska");
        } else if (item.equals("owoce morza")) {
            pizza = new OwoceMorzaPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykanska Pizza Owoce Morza");
        } else if (item.equals("pepperoni")) {
            pizza = new PepperoniPizza(fabrykaSkładników);
            pizza.ustawNazwa("Amerykanska Pizza Pepperoni");
        }
        return pizza;
    }
}
