package lab_7;

public class Handlowiec extends Pracownik
{
    public double provision = 0;
    public double provision_limit = 0;

    @Override
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
            System.out.printf("Stanowisko                   :      %s\n", job);
        if(pay != 0)
            System.out.printf("Wynagrodzenie (zł)           :      %f\n", pay);
        if(phone_nr != 0)
            System.out.printf("Telefon służbowy numer       :      %d\n", phone_nr);
        if(provision != 0)
            System.out.printf("Prowizja (%%)                :      %f\n", provision);
        if(provision_limit != 0)
            System.out.printf("Limit prowizji/miesiąc (zł)  :      %f\n", provision_limit);
    }
}
