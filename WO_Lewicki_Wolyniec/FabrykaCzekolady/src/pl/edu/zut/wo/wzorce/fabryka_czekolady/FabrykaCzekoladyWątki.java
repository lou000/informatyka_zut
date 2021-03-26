package pl.edu.zut.wo.wzorce.fabryka_czekolady;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.double_lock.CzekoladowyKociol1;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.eager.CzekoladowyKociol2;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.jbloch.CzekoladowyKociol3;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.klasyczny.CzekoladowyKociol4;
import pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.synchro.CzekoladowyKociol5;


public class FabrykaCzekoladyWątki {

	private static void test() {
		System.out.println("Uruchomione przez: " + Thread.currentThread().getName());
		CzekoladowyKocioł kocioł = new CzekoladowyKocioł();
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();
	}
	private static void test1() {
		System.out.println("Uruchomione przez: " + Thread.currentThread().getName());
		CzekoladowyKociol1 kocioł = CzekoladowyKociol1.getInstance();
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();
	}
	private static void test2() {
		System.out.println("Uruchomione przez: " + Thread.currentThread().getName());
		CzekoladowyKociol2 kocioł = CzekoladowyKociol2.getInstance();
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();
	}
	private static void test3() {
		System.out.println("Uruchomione przez: " + Thread.currentThread().getName());
		CzekoladowyKociol3 kocioł = CzekoladowyKociol3.INSTANCE;
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();
	}
	private static void test4() {
		System.out.println("Uruchomione przez: " + Thread.currentThread().getName());
		CzekoladowyKociol4 kocioł = CzekoladowyKociol4.getInstance();
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();
	}
	private static void test5() {
		System.out.println("Uruchomione przez: " + Thread.currentThread().getName());
		CzekoladowyKociol5 kocioł = CzekoladowyKociol5.getInstance();
		kocioł.napełniaj();
		kocioł.gotuj();
		kocioł.opróżniaj();
	}
	public static void main(String... params) {
		Thread wątek1 = new Thread("Wątek 1") {
			public void run() {
				test();
				test1();
				test2();
				test3();
				test4();
				test5();
			}
		};
		Thread wątek2 = new Thread("Wątek 2") {
			public void run() {
				test();
				test1();
				test2();
				test3();
				test4();
				test5();
			}
		};
		wątek1.start();
		wątek2.start();
	}
}
