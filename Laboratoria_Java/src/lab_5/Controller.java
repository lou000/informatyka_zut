package lab_5;
import java.util.Scanner;

public class Controller {
    public int[][] getMatrix(int row, int column)
    {
        Scanner in  = new Scanner(System.in);
        int[][] matrix = new int[row][column];
        for (int r= 0; r < row; r++)
            for (int c = 0; c < column; c++)
                matrix[r][c] = in.nextInt();
        return matrix;
    }
    public int get_UI_input()
    {
        Scanner in  = new Scanner(System.in);
        return in.nextInt();
    }

    public void lab_5()
    {
        View menu = new View();
        Model matrices = new Model();
        int input = 1;
        while(input!=0)
        {
            int input2 = 1;
            menu.clear_console();
            menu.print_main_menu();
            input = get_UI_input();
            switch (input)
            {
                case 1:
                {
                    menu.clear_console();

                    menu.println("Wprowadź wielkości macierzy A.");
                    int row = get_UI_input();
                    int column = get_UI_input();
                    menu.println("Wprowadź składniki macierzy A.");
                    matrices.matrix_A = getMatrix(row, column);

                    menu.println("Wprowadź wielkości macierzy B.");
                    row = get_UI_input();
                    column = get_UI_input();
                    menu.println("Wprowadź składniki macierzy B.");
                    matrices.matrix_B = getMatrix(row, column);

                    menu.clear_console();
                    menu.print_main_menu();
                    break;
                }
                case 2:
                {
                    menu.clear_console();
                    menu.print_submenu_1();
                    while (input2 != 0)
                    {
                        input2 = get_UI_input();
                        switch (input2)
                        {
                            case 1:
                            {
                                if (matrices.matrix_A == null || matrices.matrix_B == null)
                                    menu.println("Macierze nie zostaly wprowadzone.");
                                else
                                {
                                    matrices.matrix_A = matrices.transpose_matrix(matrices.matrix_A);
                                    matrices.matrix_B = matrices.transpose_matrix(matrices.matrix_B);
                                    menu.println("Macierze zostały ztransponowane.");
                                }
                                break;
                            }
                            case 2:
                            {
                                if (matrices.matrix_A == null || matrices.matrix_B == null)
                                    menu.println("Macierze nie zostaly wprowadzone.");
                                else
                                {
                                    matrices.matrix_C = matrices.multiply_matrices(matrices.matrix_A, matrices.matrix_B);
                                    if(matrices.matrix_C == null)
                                        menu.println("Macierze mają zły rozmiar.");
                                    else
                                        menu.println("Macierze zostały przemnożone.");
                                }
                                break;
                            }
                            case 3:
                            {
                                if(matrices.matrix_C == null)
                                    menu.println("Macierz nie zostala przeliczona.");
                                else
                                {
                                    matrices.matrix_C = matrices.transpose_matrix(matrices.matrix_C);
                                    menu.println("Macierz wynikowa zostala ztransponowana.");
                                }
                                break;
                            }
                            case 0:
                            {
                                break;
                            }
                        }
                    }
                }
                case 3:
                {
                    menu.clear_console();
                    menu.print_submenu_2();
                    while (input2 != 0)
                    {
                        input2 = get_UI_input();
                        switch (input2)
                        {
                            case 1:
                            {
                                if(matrices.matrix_A == null || matrices.matrix_B == null)
                                    menu.println("Macierze nie zostaly wprowadzone.");
                                else
                                {
                                    menu.print_matrix(matrices.matrix_A);
                                    menu.println("");
                                    menu.print_matrix(matrices.matrix_B);
                                }
                                break;
                            }
                            case 2:
                            {
                                if(matrices.matrix_C == null)
                                    menu.println("Macierz nie zostala przeliczona.");
                                else
                                    menu.print_matrix(matrices.matrix_C);
                                break;
                            }
                            case 0:
                                break;
                        }
                    }
                }
                case 0:
                    break;
            }
        }
    }
}
