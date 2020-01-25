package lab_5;

public class lab5_View
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
        println("JAVA LAB 5\n");
        println("1. Wprowadź macierze wejściowe.");
        println("2. Operacje arytmetyczne.");
        println("3. Wyświetl macierze.");
        println("0. Wyjdź.\n\n");
    }
    public void print_submenu_1()
    {
        println("1. Transponuj macierze wejściowe.");
        println("2. Pomnóż macierze wejściowe.");
        println("3. Transponuj macierz wynikową.");
        println("0. Powrót.\n\n");
    }
    public void print_submenu_2()
    {
        println("1. Wyświetl macierze wejściowe.");
        println("2. Wyświetl macierz wynikową.");
        println("0. Powrót.\n\n");
    }
    public void print_matrix(int[][] A)
    {
        for(int row = 0; row<A.length; row++)
        {
            for (int column = 0; column < A[0].length; column++)
                System.out.printf("%d ", A[row][column]);
            System.out.print("\n");
        }
    }
}
