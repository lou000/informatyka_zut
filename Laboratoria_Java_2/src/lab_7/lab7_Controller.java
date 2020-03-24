package lab_7;

import java.util.Iterator;
import java.util.Scanner;

public class lab7_Controller
{
    private int get_int_input()
    {
        Scanner in  = new Scanner(System.in);
        return in.nextInt();
    }
    private String get_string_input()
    {
        Scanner in  = new Scanner(System.in);
        return in.nextLine();
    }
    private long get_long_input()
    {
        Scanner in  = new Scanner(System.in);
        return in.nextLong();
    }

    public void lab_7()
    {
        lab7_Model model = new lab7_Model();
        lab7_View menu = new lab7_View();
        int input1 = 1;
        while(input1!=0)
        {
            menu.clear_console();
            menu.print_main_menu();
            input1 = get_int_input();
            switch (input1)
            {
                case 1:
                {
                    int position = 1;
                    Iterator valueIterator=model.data.values().iterator();
                    if(model.data.size()>0)
                    {
                        while (position != 0)
                        {
                            menu.clear_console();
                            menu.print_worker_list((Pracownik) valueIterator.next(), position, model.data.size());
                            int input = get_int_input();
                            if (input == 1)
                                position++;
                            else position = 0;
                            if(position>model.data.size())
                                position = 0;
                        }
                    }
                    break;
                }
                case 2:
                {
                    Pracownik temp = new Pracownik();

                    menu.clear_console();
                    temp.print();
                    menu.println("Podaj rodzaj pracownika.");
                    String input_s = get_string_input();
                    while(!input_s.equals("D") && !input_s.equals("H"))
                    {
                        menu.println("Niepoprawny rodzaj pracownika.");
                        input_s = get_string_input();
                    }
                    if(input_s.equals("D"))
                        temp.job = Pracownik.Job.Dyrektor;
                    else
                        temp.job = Pracownik.Job.Handlowiec;

                    menu.clear_console();
                    temp.print();
                    menu.println("Podaj poprawny PESEL.");
                    long input = get_long_input();
                    while(!model.validateKey(input))
                    {
                        menu.println("Niepoprawny pesel.");
                        input = get_long_input();
                    }
                    temp.pesel=input;

                    menu.clear_console();
                    temp.print();
                    menu.println("Podaj imię.");
                    temp.name = get_string_input();

                    menu.clear_console();
                    temp.print();
                    menu.println("Podaj nazwisko.");
                    temp.surname = get_string_input();

                    menu.clear_console();
                    temp.print();
                    menu.println("Podaj wysokość wynagrodzenia.");
                    temp.pay = get_int_input();

                    menu.clear_console();
                    temp.print();
                    menu.println("Podaj numer telefonu.");
                    temp.phone_nr = get_long_input();

                    if(temp.job == Pracownik.Job.Handlowiec)
                    {
                        Handlowiec temp2 = new Handlowiec();
                        temp2.pay = temp.pay;
                        temp2.name = temp.name;
                        temp2.job = temp.job;
                        temp2.pesel = temp.pesel;
                        temp2.surname = temp.surname;
                        temp2.phone_nr = temp.phone_nr;

                        menu.clear_console();
                        temp2.print();
                        menu.println("Podaj wysokość prowizji.");
                        temp2.provision = get_int_input();

                        menu.clear_console();
                        temp2.print();
                        menu.println("Podaj limit prowizji.");
                        temp2.provision_limit = get_int_input();

                        menu.clear_console();
                        temp2.print();
                        menu.println("1. Zatwierdź");
                        menu.println("0. Odrzuć");
                        if(get_int_input()==1)
                        {
                            model.addWorker(temp2.pesel, temp2);
                        }

                    }
                    else
                    {
                        Dyrektor temp2 = new Dyrektor();
                        temp2.pay = temp.pay;
                        temp2.name = temp.name;
                        temp2.job = temp.job;
                        temp2.pesel = temp.pesel;
                        temp2.surname = temp.surname;
                        temp2.phone_nr = temp.phone_nr;

                        menu.clear_console();
                        temp2.print();
                        menu.println("Podaj wysokość dodatku służbowego.");
                        temp2.bonus = get_int_input();

                        menu.clear_console();
                        temp2.print();
                        menu.println("Numer karty służbowej.");
                        temp2.card = get_string_input();

                        menu.clear_console();
                        temp2.print();
                        menu.println("Podaj limit kosztów/miesiąc.");
                        temp2.cost_limit = get_int_input();

                        menu.clear_console();
                        temp2.print();
                        menu.println("1. Zatwierdź");
                        menu.println("0. Odrzuć");
                        if(get_int_input()==1)
                        {
                            model.addWorker(temp2.pesel, temp2);
                        }
                    }
                    break;
                }
                case 3:
                {
                    menu.clear_console();
                    menu.println("Podaj identyfikator pracownika");
                    long temp_long = get_long_input();
                    while (model.getWorker(temp_long)==null)
                    {
                        menu.println("Nie ma takiego pracownika");
                        temp_long = get_long_input();
                    }
                    ((Pracownik) model.getWorker(temp_long)).print();
                    menu.println("------------------------------------------------------------------");
                    menu.println("1. Potwierdź");
                    menu.println("0. – Porzuć");
                    if(get_int_input()==1)
                        model.removeWorker(temp_long);
                    break;
                }
                case 4:
                {
                    menu.clear_console();
                    String file = null;
                    lab7_Model.BackupJob backupJob = lab7_Model.BackupJob.UNDEFINED;
                    lab7_Model.CompressionMode compressionMode = lab7_Model.CompressionMode.UNDEFINED;
                    menu.print_backup_menu(file, compressionMode,backupJob);
                    menu.println("1. Zachowaj");
                    menu.println("2. Odtwórz");
                    int temp_int = get_int_input();
                    while(temp_int!=1 && temp_int!=2)
                    {
                        menu.println("Nieprawidlowy wybor");
                        temp_int = get_int_input();
                    }
                    if(temp_int == 1)
                        backupJob = lab7_Model.BackupJob.EXPORT;
                    else
                        backupJob = lab7_Model.BackupJob.IMPORT;
                    if(backupJob == lab7_Model.BackupJob.EXPORT)
                    {
                        menu.clear_console();
                        menu.print_backup_menu(file, compressionMode, backupJob);
                        menu.println("1. GZIP");
                        menu.println("2. ZIP");
                        temp_int = get_int_input();
                        while (temp_int != 1 && temp_int != 2)
                        {
                            menu.println("Nieprawidlowy wybor");
                            temp_int = get_int_input();
                        }
                        if (temp_int == 1)
                            compressionMode = lab7_Model.CompressionMode.GZIP;
                        else
                            compressionMode = lab7_Model.CompressionMode.ZIP;
                    }
                    menu.clear_console();
                    menu.print_backup_menu(file, compressionMode, backupJob);
                    menu.println("Podaj nazwę pliku z rozszerzeniem.");
                    file = get_string_input();

                    menu.clear_console();
                    menu.print_backup_menu(file, compressionMode, backupJob);
                    menu.println("1. Potwierdź");
                    menu.println("0. Porzuć");
                    temp_int = get_int_input();
                    while(temp_int!=1 && temp_int!=0)
                    {
                        menu.println("Nieprawidlowy wybor");
                        temp_int = get_int_input();
                    }
                    if(temp_int == 1)
                    {
                        if (backupJob == lab7_Model.BackupJob.EXPORT)
                            model.exportBackup(file, compressionMode);
                        else
                            model.importBackup(file);
                    }
                    break;
                }
            }
        }
    }
}
