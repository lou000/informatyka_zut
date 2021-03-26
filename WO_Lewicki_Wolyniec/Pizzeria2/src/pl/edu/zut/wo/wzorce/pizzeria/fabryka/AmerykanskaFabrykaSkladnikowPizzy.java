package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.składniki.*;

public class AmerykanskaFabrykaSkladnikowPizzy implements FabrykaSkładnikówPizzy{
    public Ciasto utwórzCiasto() {
        return new Ciasto();
    }
    public Sos utwórzSos() {
        return new Sos();
    }
    public Ser utwórzSer() {
        return new Ser();
    }
    public Warzywa[] utwórzWarzywa() {
        Warzywa warzywa[] = {new Cebula(), new Pieczarki()};
        return warzywa;
    }
    public Pepperoni utwórzPepperoni() {
        return new Pepperoni();
    }
    public Małże utwórzMałże() {
        return new Małże();
    }
}
