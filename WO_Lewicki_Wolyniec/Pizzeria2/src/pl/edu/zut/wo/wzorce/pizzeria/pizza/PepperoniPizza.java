package pl.edu.zut.wo.wzorce.pizzeria.pizza;

import pl.edu.zut.wo.wzorce.pizzeria.fabryka.FabrykaSkładnikówPizzy;

public class PepperoniPizza extends Pizza {
	FabrykaSkładnikówPizzy fabrykaSkładników;
	public PepperoniPizza(FabrykaSkładnikówPizzy fabrykaSkładników)  {
		this.fabrykaSkładników = fabrykaSkładników;
	}

	public void przygotowanie() {
		System.out.println("Przygotowywanie: " + nazwa);
		ciasto = fabrykaSkładników.utwórzCiasto();
		sos = fabrykaSkładników.utwórzSos();
		ser = fabrykaSkładników.utwórzSer();
		pepperoni = fabrykaSkładników.utwórzPepperoni();

	}

}
