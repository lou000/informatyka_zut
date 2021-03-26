package pl.edu.zut.wo.wzorce.fabryka_czekolady.singleton.synchro;

public class CzekoladowyKociol5 {
    private static CzekoladowyKociol5 instance;
    private boolean pusty;
    private boolean ugotowany;

    public static synchronized CzekoladowyKociol5 getInstance()
    {
        if (instance == null) {
            instance = new CzekoladowyKociol5();
        }
        return instance;
    }

    private CzekoladowyKociol5() {
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
