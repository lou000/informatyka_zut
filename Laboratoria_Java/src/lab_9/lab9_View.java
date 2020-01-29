package lab_7;

public class lab7_View
{
    void println(Object line) {
        System.out.println(line);
    }
    public void clear_console()
    {
        for(int i=0; i<20; i++)
            println("\n");
    }
    public void print_main_menu()
    {
        println("JAVA LAB 9\n");
        println("1. Lista pracowników.");
        println("2. Dodaj pracownika.");
        println("3. Usuń pracownika.");
        println("4. Kopia zapasowa.");
        println("0. Wyjdź.\n\n");
    }
    public void print_worker_list(Pracownik worker, int position, int max)
    {
        println("Lista pracowników.");
        worker.print();
        System.out.printf("                                       [Pozycja: %d/%d]\n", position, max);
        println("1. Następny");
        println("0. Powrót");
    }
    public void print_backup_menu(String filename, lab7_Model.CompressionMode mode, lab7_Model.BackupJob job)
    {
        println("4. Kopia zapasowa\n");
        String temp = null;
        if(job == lab7_Model.BackupJob.EXPORT)
            temp = "Zachowaj";
        else if (job == lab7_Model.BackupJob.IMPORT)
            temp = "Odtwórz";
        System.out.printf("Zachowaj/Odtwórz           : %s\n", temp);
        println("------------------------------------------------------------------");
        if(job == lab7_Model.BackupJob.EXPORT || job== lab7_Model.BackupJob.UNDEFINED)
        {
            temp = null;
            if (mode == lab7_Model.CompressionMode.GZIP)
                temp = "GZIP";
            else if (mode == lab7_Model.CompressionMode.ZIP)
                temp = "ZIP";
            System.out.printf("Kompresja [G]zip/[Z]ip     : %s\n", temp);
        }
        System.out.printf("Nazwa pliku                : %s\n", filename);
        println("------------------------------------------------------------------");

    }

}
