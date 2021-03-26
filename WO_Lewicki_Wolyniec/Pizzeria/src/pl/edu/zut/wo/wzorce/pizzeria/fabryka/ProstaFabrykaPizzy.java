package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.*;

public class ProstaFabrykaPizzy {
	public Pizza utwórzPizza(String type) {
		Pizza pizza = null;
		if (type.equals("serowa")) {
			pizza = new SerowaPizza();
		} else if (type.equals("grecka")) {
			pizza = new GreckaPizza();
		} else if (type.equals("pepperoni")) {
			pizza = new PepperoniPizza();
		} else if (type.equals("owocemorza")) {
			pizza = new OwoceMorzaPizza();
		} else if (type.equals("wegetariańska")) {
			pizza = new WegetariańskaPizza();
		}
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();

		return pizza;
	}
}