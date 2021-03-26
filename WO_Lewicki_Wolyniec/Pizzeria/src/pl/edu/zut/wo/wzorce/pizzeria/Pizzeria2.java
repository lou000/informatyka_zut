package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.GreckaPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.PepperoniPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.SerowaPizza;

public class Pizzeria2 {
	Pizza zamówPizza(String type) {
		Pizza pizza = null;
		if (type.equals("serowa")) {
			pizza = new SerowaPizza();
		} else if (type.equals("grecka")) {
			pizza = new GreckaPizza();
		} else if (type.equals("pepperoni")) {
			pizza = new PepperoniPizza();
		}
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
	}
}
