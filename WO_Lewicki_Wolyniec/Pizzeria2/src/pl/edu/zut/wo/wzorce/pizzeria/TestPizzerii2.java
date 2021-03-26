package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii2 {

	public static void main(String[] args) {
		WłoskaPizzeria pizzeriaWloska = new WłoskaPizzeria();
		AmerykanskaPizzeria pizzeriaAmericanoooo = new AmerykanskaPizzeria();

		Pizza pizza = pizzeriaWloska.zamówPizza("owoce morza");
		System.out.println(pizza);
		Pizza aPizza = pizzeriaAmericanoooo.zamówPizza("pepperoni");
		System.out.println(aPizza);
	}
}
