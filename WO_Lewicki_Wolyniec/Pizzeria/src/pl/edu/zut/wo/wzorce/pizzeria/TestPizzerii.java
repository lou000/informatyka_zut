package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii {

	public static void main(String[] args) {
		Pizzeria4 pizzeria = new Pizzeria4();
		Pizza pizza = pizzeria.zamówPizza("serowa");
		System.out.println(pizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza.getClass().getSimpleName());
	}
}
