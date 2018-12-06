#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pch.h"
#include <iostream>


////////////////////////////////////////////FUNKCJE//////////////////////////////////////////////////

void newLine()
{
	printf("\n");
}

void newLines(int x)
{
	int i;
	for (i = 0; i < x; i++)
	{
		printf("\n");
	}
}

int WriteBiggerNumber(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	else if(y > x)
	{
		return y;
	}
	else
	{
		return NULL; // jeżeli użytkownik wpisze 2 takie same liczby funckja zwraca NULL
	}
}

int Multiply(int x, int y)
{
	return x * y;
}



int main(void) {

	setlocale(LC_ALL, ""); //Polskie znaki bez tego nie działają


	// Chciałem pozwolic uzytkownikowi na uruchamianie wszystkich zadañ w obrebie jednego pliku wiec zrobiłem to uzywajac switch i case
	int zadanie = 1;
	
	while (zadanie != 0)
	{
		printf("Wprowadź numer zadania do uruchomienia (od 1 do 19), wprowadz 0 zeby wyjsc.\n");
		scanf("%d", &zadanie);
		switch (zadanie) {

			//1.1. Zadeklarowaæ zmienne typu int, float, char. Przypisaæ do nich wartoœæ, wyœwietliæ je na ekran.
		case 1:
			printf("Zadanie 1_1\n");
			{
				int a = 14;
				float b = 1.3;
				char c = 'c';
				printf("int=%d,float=%f,char=%c\n", a, b, c);
				break;
			}


			//1.2. Wyœwietliæ zmienn¹ typu int na ekran. Nale¿y u¿yæ metody printf i konstrukcji %d
		case 2:
			printf("Zadanie 1_2\n");
			{
				int a = 10;
				printf("int=%d\n", a);
				break;
			}

			//1.3. Pobrać od użytkownika liczbę x. Wyświetlić kwadrat liczby x.
		case 3:
			printf("Zadanie 1_3\n");
			{
				int x = 0;
				printf("Wprowadź liczbę do skwadracenia.\n");
				scanf("%d", &x);
				printf("x=%d\n", x*x);
				break;
			}

			//1.4. Zapoznać się z instrukcjami warunkowymi (if, else if, else oraz switch). Pobrać od używkownika liczbę i wyświetlić informację, czy jest
		   //ona: mniejsza, większa, czy równa 0.

		case 4:
			printf("Zadanie 1_4\n");
			{
				int x = 0;
				printf("Podaj liczbę.\n");
				scanf("%d", &x);
				if (x < 0)
				{
					printf("Liczba mniejsza od 0\n");
				}
				else if (x = 0)
				{
					printf("Liczba równa 0\n");
				}
				else
				{
					printf("Liczba większa od 0\n");
				}
				break;
			}

			//1.5. Pobrać ud użytkownika 3 liczby (x1, x2, x3). Wyświetlić informację, która z tych liczb jest największa.

		case 5:
			printf("Zadanie 1_5\n");
			{
				int x, y;
				printf("Podaj pierwsza liczbe\n");
				scanf("%d", &x);
				for (int i = 0; i < 2; i++)             //nie chciałem tego robić if else
				{
					printf("Podaj następną liczbe\n");
					scanf("%d", &y);
					if (y > x)
					{
						x = y;
					}
				}
				printf("Największa liczba to %d\n", x);

				break;
			}

			//1.6. Napisać prosty kalkulator. Należy pobrać od użytkownika 2 liczby oraz operator (jeden z czterech: mnożenie, dzielenie, dodawanie,
			//odejmowanie). Wymagane jest utworzenie prostego menu użytkownika. Uwaga - należy pamiętać o ułamkach (1/3 powinno dać 0.33, a nie
			//0)
		case 6:
			printf("Zadanie 1_6\n");
			{
				int x = 0, y = 0;				//liczby na ktorych przeprowadzam operacje
				float odp;					//odpowiedz
				char dzialanie = NULL;		//operacja
				while (dzialanie != 'k')	//pętla, kalkulator będzie działał aż wpiszemy k																									
				{
					printf("\nKalkulator, wprowadź rodzaj działania(+,-,/,*), wpisz k żeby wyjść.\n");		//nowa linia na początku pętli, dziwne rzeczy działy się jak \n było w printf odpowiedzi									
					scanf(" %c", &dzialanie);
					switch (dzialanie)	// switch i case do operacji																										
					{
					case '+':
					{
						printf("Wpisz liczby oddzielone spacją\n"); // ten print jest w każdym casie żeby nie powtarzał się jak wpiszemy k lub niepoprawne dzialanie
						scanf("%d %d", &x, &y);
						printf("%d+%d=%f", x, y, odp = (float)x + (float)y);
						break;
					}
					case '-':
					{
						printf("Wpisz liczby oddzielone spacją\n");
						scanf("%d %d", &x, &y);
						printf("%d-%d=%f", x, y, odp = (float)x - (float)y);
						break;
					}
					case '/':
					{
						printf("Wpisz liczby oddzielone spacją\n");
						scanf("%d %d", &x, &y);
						printf("%d/%d=%f", x, y, odp = (float)x / (float)y);
						break;
					}
					case '*':
					{
						printf("Wpisz liczby oddzielone spacją\n");
						scanf("%d %d", &x, &y);
						printf("%d*%d=%f", x, y, odp = (float)x * (float)y);
						break;
					}
					case 'k':
					{
						printf("Koniec\n");
						break;
					}
					default: printf("Niepoprawne działanie");
						break;
					}

				}
				break;

			}

			/*2. Pętle
			2.1.Zapoznać się z pętlą while.Pętla ta służy do wielokrotnego wykonania fragmentu kodu przez NIEZNANĄ Z GÓRY ilość razy.Pętla
			wykonuje się zawsze, jeśli warunek jest prawdziwy(ewaluowany do true).Napisać pętlę, w któej użytkownik podaje liczbę x.Należy
			wyświetlić tę liczbę.Jeżeli użytkownik poda 0, należy zakończyć program.*/
		case 7:
			printf("Zadanie 2_1\n");
			{
				int x = 1;
				while (x != 0)
				{
					printf("Podaj liczbę\n");
					scanf("%d", &x);
					printf("Twoja liczba to %d\n", x);
				}
				break;
			}

			/*2.2.Przerobić kalkulator z zadania 1.6.Teraz po każdym działaniu program powinien spytać użytkownika, czy ten chce powtórzyć
			wszystko od początku.Jeśli tak - restartujemy kalkulator i zaczynamy od nowa.Jeśli nie - kończymy program.*/
		case 8:
			printf("Zadanie 2_2\n Zrobiłem kalkulator w ten sposob za pierwszym razem.");
			break;


			//2.3.Pobrać od użytkownika liczbę x.Należy wyświetlić wszystkie kolejne potęgi liczby x.Zakończyć program, kiedy liczba przekroczy 100 000.
		case 9:
			printf("Zadanie 2_3\n");
			{
				long int x, y, i = 2;
				printf("Podaj liczbę do spotęgowania.\n");
				scanf("%d", &x);
				y = x;
				while (x < 100000)
				{
					x = x * y;
					printf("%d^%d=%d\n", y, i, x);
					i++;
				}
				break;
			}

			/*2.4.Pobrać od użytkownika liczbę x.Jeśli liczba jest niedodatnia - należy zakończyć program.Następnie należy wyświetlać kolejno(w
			nowej linii) wszystkie liczby mniejsze od x, aż osiągnięte zostanie 0.*/
		case 10:
			printf("Zadanie 2_4\n");
			{
				int x;
				printf("Podaj liczbę x\n");
				scanf("%d", &x);
				while (x > 0)
				{
					x = x - 1;
					printf("%d\n", x);
				}
				break;
			}

			/*2.5.Zapoznać się z instrukcjami continue; i break; .Pierwsza służy do zakończenia iteracji i przejścia do następnej, a druga natychmiast
			kończy pętlę.Przerobić program z zadania 1.4 , aby wyświetlał tylko parzyste liczby(użyć if oraz continue).Jeśli liczba wynosi 40, należy
			wyjść z pętli i zakończyć program.*/
		case 11:
			printf("Zadanie 2_5\n"); //(ZAKŁADAM, ŻE CHODZIŁO O 2.4 A NIE 1.4 BO W 1.4 NIE MA NAWET PĘTLI)
			{
				int x;
				printf("Podaj liczbę x\n");
				scanf("%d", &x);
				while (x > 0)
				{
					x = x - 1;
					if (x == 40)
					{
						break;
					}
					else if (x % 2 == 0)   //nie jestem do konca pewien czy o to chodziło
					{
						printf("%d\n", x);
					}
					else continue;
				}
				break;
			}

			/*2.6.Zapoznać się z pętlą for.Pętla służy do wykonania danego fragmentu kodu ZNANĄ Z GÓRY określoną ilość razy.Uwaga - każdą pętlę
			for można zastąpić pętlą while i wzajemnie.Zwyczajowo obowiazuje zasada, że jeśli ilość iteracji jest znana - używamy for, a jeśli nie jest
			znana(zależy od użytkownika lub jakiegoś stanu zewnętrznego) - używamy pętli while.Pętla for składa się z : ZMIENNEJ ITERACYJNEJ,
			czyli stanu początkowego pętli, np. int i = 0. Następnie WARUNKU ZAKOŃCZENIA PĘTLI, np.i < 10. Następnie OPERACJI WYKONYWANEJ
			PO KAŻDEJ ITERACJI - zazwyczaj jest to zwiększenie iteratora o 1, czyli i = i + 1, bądź w skrócie i++.Napisać pętlę for, która wyświetli cyfry
			od 0 do 9.*/
		case 12:
			printf("Zadanie 2_6\n");
			{
				int i;
				for (i = 0; i <= 9; i++)
				{
					printf("%d\n", i);
				}
				break;
			}

			/*2.7.Pobrać od użytkownika liczby x i y.Zakładamy, że y > x(zawsze, nie musimy tego sprawdzać).Za pomocą pętli for wypisać liczby
			między x a y(do przemyślenia - co jest stanem początkowym, a co warunkiem zakończenia pętli ? )*/
		case 13:
			printf("Zadanie 2_7\n");
			{
				int x, y, i;
				printf("Wpisz liczby oddzielone spacją\n");
				scanf("%d %d", &x, &y);
				for (i = 1; x + i != y; i++)
				{
					printf("%d\n", x + i);
				}
				break;
			}

			/*2.8.Pobrać od użytkownika liczbę x.Za pomocą pętli for wypisać wszystkie liczby mniejsze od x, ale większe niż 0.*/
		case 14:
			printf("Zadanie 2_8\n");
			{
				int x, i;
				printf("Wpisz liczbę\n");
				scanf("%d", &x);
				for (i = 1; i < x; i++)
				{
					printf("%d\n", i);
				}
				break;
			}

			/*2.9.Pobrać od użytkownika liczbę x.Za pomocą pętli for wypisywać CO TRZECIĄ liczbę większą od x.Pętla powinna się zakończyć, jeśli
			liczba przekroczy 100. Uwaga - proszę nie używać operacji continue i break, a sterować tylko parametrami pętli.*/
		case 15:
			printf("Zadanie 2_9\n");
			{
				int x, i;
				printf("Wpisz liczbę\n");
				scanf("%d", &x);
				for (i = x + 3; i < 100; i = i + 3)
				{
					printf("%d\n", i);
				}
				break;

			}

			/*3.1.Napisać metodę void NewLine().Powinna ona wypisać na ekran pojedynczą pustą linię.Użyć tej metodę w main().*/
		case 16:
			printf("Zadanie 3_1");//nie ma tu nowej linii
		{
			newLine();				//wprowadzam ją funckją
			break;			
		}

			/*3.2.Napisać metodę void NewLines(int count).Powinna ona wypisać tyle nowych linii, ile zostało podanych W PARAMETRZE count(należy
			użyć pętli for).Użyć metodę w main()*/
		case 17:
			printf("Zadanie 3_2\n");
		{
				newLines(5);
				break;
		}

			/*3.3.Napisać metodę void WriteBiggerNumber(int x, int y).Metoda powinna pobrać 2 parametry i zwrócić większy z nich.Wykorzystać
			funckję w metodzie main().UWAGA - pobieranie liczb od użytkownika powinno odbyć się w funkcji main(), a NIE w WriteBiggerNumber!Do
			funkcji należy jedynie przesłać pobrane wcześniej parametry.*/
		case 18:
			printf("Zadanie 3_3\n");
		{
				int x, y;
				printf("Wpisz liczby oddzielone spacją\n");
				scanf("%d %d", &x, &y);
				printf("%d jest większa\n", WriteBiggerNumber(x, y));
				break;
		}

			//3.4.Napisać metodę Multiply(int x, int y).Metoda powinna ZWRÓCIĆ(słowo kluczowe return) iloczyn dwóch parametrów.Uwaga!Metoda
			//NIE POWINNA wypisywać wyniku - powinien on być wyświetlony w funkcji main!
		case 19:
			printf("Zadanie 3_4\n");
		{
				int x, y;
				printf("Wpisz liczby oddzielone spacją\n");
				scanf("%d %d", &x, &y);
				printf("%d * %d = %d\n", x, y, Multiply(x, y));
				break;

		}

		case 0: 
		{
			printf("Koniec\n");
			break;
		}
		default: printf("Nie ma takiego zadania.");
			break;
		}
	}
	return 0;
}





