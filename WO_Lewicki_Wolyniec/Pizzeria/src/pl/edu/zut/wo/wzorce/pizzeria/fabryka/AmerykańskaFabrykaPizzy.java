package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.*;

public class AmerykańskaFabrykaPizzy extends ProstaFabrykaPizzy {
    public Pizza utwórzPizza(String type) {
        Pizza pizza = null;
        if (type.equals("Amerykanska Serowa")) {
            pizza = new SerowaPizza();
        } else if (type.equals("Amerykanska Wege")) {
            pizza = new GreckaPizza();
        } else if (type.equals("Amerykanska Peperoni")) {
            pizza = new PepperoniPizza();
        } else if (type.equals("Amerykanska Owoce Morza")) {
            pizza = new OwoceMorzaPizza();
        }
        pizza.przygotowanie();
        pizza.pieczenie();
        pizza.krojenie();
        pizza.pakowanie();

        return pizza;
    }
}
