package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public abstract class Pizzeria {
	public Pizza zamówPizza(String type) {
		Pizza pizza;
		pizza = utwórzPizza(type);
		System.out.println("---------------------------------------------");
		pizza.przygotowanie();
		pizza.pieczenie();
		pizza.krojenie();
		pizza.pakowanie();
		return pizza;
	}

	abstract Pizza utwórzPizza(String type);
}