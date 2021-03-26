package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.*;

public class WłoskaFabrykaPizzy extends ProstaFabrykaPizzy {
    public Pizza utwórzPizza(String type) {
        Pizza pizza = null;
        if (type.equals("Wloska Serowa")) {
            pizza = new SerowaPizza();
        } else if (type.equals("Wloska Wege")) {
            pizza = new GreckaPizza();
        } else if (type.equals("Wloska Peperoni")) {
            pizza = new PepperoniPizza();
        } else if (type.equals("Wloska Owoce Morza")) {
            pizza = new OwoceMorzaPizza();
        }
        pizza.przygotowanie();
        pizza.pieczenie();
        pizza.krojenie();
        pizza.pakowanie();

        return pizza;
    }
}
