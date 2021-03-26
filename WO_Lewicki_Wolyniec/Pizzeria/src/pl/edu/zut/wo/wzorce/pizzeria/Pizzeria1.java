package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public class Pizzeria1 {

	Pizza zamówPizza() {
		Pizza pizza = new Pizza();
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
		}
}
