package pl.edu.zut.wo.wzorce.fabryka_czekolady;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.double_lock.CzekoladowyKociol1;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.eager.CzekoladowyKociol2;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.jbloch.CzekoladowyKociol3;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.klasyczny.CzekoladowyKociol4;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.synchro.CzekoladowyKociol5;

public class FabrykaCzekolady {

	public static void main(String... params) {
		CzekoladowyKocioł kocioł = new CzekoladowyKocioł();
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();

		CzekoladowyKociol1 kocioł1 = CzekoladowyKociol1.getInstance();
		kocioł1.napełniaj();
		kocioł1.gotuj();
		kocioł1.opróżniaj();

		CzekoladowyKociol2 kocioł2 = CzekoladowyKociol2.getInstance();
		kocioł2.napełniaj();
		kocioł2.gotuj();
		kocioł2.opróżniaj();

		CzekoladowyKociol3 kocioł3 = CzekoladowyKociol3.INSTANCE;
		kocioł3.napełniaj();
		kocioł3.gotuj();
		kocioł3.opróżniaj();

		CzekoladowyKociol4 kocioł4 = CzekoladowyKociol4.getInstance();
		kocioł4.napełniaj();
		kocioł4.gotuj();
		kocioł4.opróżniaj();

		CzekoladowyKociol5 kocioł5 = CzekoladowyKociol5.getInstance();
		kocioł5.napełniaj();
		kocioł5.gotuj();
		kocioł5.opróżniaj();

	}
}
