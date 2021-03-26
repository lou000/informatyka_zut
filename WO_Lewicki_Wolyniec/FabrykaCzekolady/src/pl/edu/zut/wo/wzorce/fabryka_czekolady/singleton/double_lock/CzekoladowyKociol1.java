package pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.double_lock;

public class CzekoladowyKociol1 {
    private static CzekoladowyKociol1 instance;
    private boolean pusty;
    private boolean ugotowany;

    public static CzekoladowyKociol1 getInstance()
    {
        if (instance == null) {
            synchronized (Singleton.class) {
                if (instance == null) {
                    instance = new CzekoladowyKociol1();
                }
            }
        }
        return instance;
    }

    private CzekoladowyKociol1() {
        pusty = true;
        ugotowany = false;
        System.out.println("Utworzenie instancji Czekoladowego Kotła: " + this);
    }

    public void napełniaj() {
        if (jestPusty()) {
            pusty = false;
            ugotowany = false;
            // napełniaj bojler mieszanką mleka i czekolady
            System.out.println("Napełnianie bojlera mieszanką czekolady i mleka");
        }
    }

    public void opróżniaj() {
        if (!jestPusty() && jestUgotowany()) {
            // opróżniaj bojler z ugotowanej mieszanki mleka i czekolady
            System.out.println("Opróżnianie bojlera z ugotowanej mieszanki czekolady i mleka");
            pusty = true;
        }
    }

    public void gotuj() {
        if (!jestPusty() && !jestUgotowany()) {
            // gotuj zawartość kotła
            System.out.println("Gotowanie mieszanki czekolady i mleka");
            ugotowany = true;
        }
    }

    public boolean jestPusty() {
        return pusty;
    }

    public boolean jestUgotowany() {
        return ugotowany;
    }
}
