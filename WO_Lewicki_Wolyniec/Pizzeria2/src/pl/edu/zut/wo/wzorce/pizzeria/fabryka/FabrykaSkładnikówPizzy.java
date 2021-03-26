package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.składniki.Ciasto;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Małże;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Pepperoni;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Ser;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sos;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Warzywa;

public interface FabrykaSkładnikówPizzy {

	public Ciasto utwórzCiasto();
	public Sos utwórzSos();
	public Ser utwórzSer();
	public Warzywa[] utwórzWarzywa();
	public Pepperoni utwórzPepperoni();
	public Małże utwórzMałże();

}