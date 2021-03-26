package pl.edu.zut.wo.wzorce.cafe;

import pl.edu.zut.wo.wzorce.cafe.napoje.Espresso;
import pl.edu.zut.wo.wzorce.cafe.napoje.MocnoPalona;
import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;
import pl.edu.zut.wo.wzorce.cafe.składniki.Czekolada;
import pl.edu.zut.wo.wzorce.cafe.składniki.Mleko;

public class StarCafe {
	public static void main(String... params) {
		Napój napój = new Mleko(new Czekolada(new Espresso()));
		System.out.println(napój.pobierzOpis() + "\n" + napój.koszt() + "zł");
	}
}
