package lab_7;

import java.io.Serializable;

public class Pracownik implements Serializable
{
    public enum Job
    {
        Dyrektor,
        Handlowiec,
        Undefined
    }
    public long pesel = 0;
    public String name = null;
    public String surname = null;
    public Job job = Job.Undefined;
    public double pay = 0;
    public long phone_nr = 0;
    public void print()
    {
        if(job != Job.Undefined)
        {
            switch (job)
            {
                case Dyrektor:
                {
                    System.out.print("Stanowisko                   :      Dyrektor\n");
                    break;
                }
                case Handlowiec:
                {
                    System.out.print("Stanowisko                   :      Handlowiec\n");
                    break;
                }
            }
        }
        if(pesel != 0)
            System.out.printf("Identyfikator PESEL          :      %d\n", pesel);
        if(name != null)
            System.out.printf("Imię                         :      %s\n", name);
        if(surname != null)
            System.out.printf("Nazwisko                     :      %s\n", surname);
        if(pay != 0)
            System.out.printf("Wynagrodzenie (zł)           :      %f\n", pay);
        if(phone_nr != 0)
            System.out.printf("Telefon służbowy numer       :      %d\n", phone_nr);
    }
}

