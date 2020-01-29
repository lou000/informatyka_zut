package lab_7;

public class Dyrektor extends Pracownik
{
    public double bonus = 0;
    public String card = null;
    public double cost_limit = 0;
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
        if(pay != 0)
            System.out.printf("Wynagrodzenie (zł)           :      %f\n", pay);
        if(phone_nr != 0)
            System.out.printf("Telefon służbowy numer       :      %d\n", phone_nr);
        if(bonus != 0)
            System.out.printf("Dodatek służbowy (zł)        :      %f\n", bonus);
        if(card != null)
            System.out.printf("Karta służbowa numer         :      %s\n", card);
        if(cost_limit != 0)
            System.out.printf("Limit kosztów/miesiąc (zł)   :      %f\n", cost_limit);
    }
}
