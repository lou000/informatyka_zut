#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pch.h"
#include <iostream>


////////////////////////////////////////////FUNKCJE//////////////////////////////////////////////////

//2.1. Utworzyć osobną metodę bool IsSorted
bool IsSorted(int *tab, int s)
{
	int i;
	for (i = 0; i < s - 1; i++)
	{
		if (tab[i] > tab[i + 1])
		{
			return 0;
		}
	}
	return 1;
}

//2.2. Utworzyć metodę void printBackwards
void printBackwards(int *tab, int s)
{
	int i;
	for (i = s - 1; i >= 0; i--)
	{
		printf("%d\n", tab[i]);
	}
}

//2.3 Utworzyć metodę printDots
void printDots(int *tab, int s)
{
	int i, x;
	for (i = 0; i < s; i++)
	{
		for (x = 0; x < tab[i]; x++)
		{
			printf(".");
		}
		printf("\n");
	}
}

//2.4. Utworzyć metodę int Sum
int sum(int *tab, int s)
{
	int x, i;
	for (x = 0, i = 0; i < s; i++)
	{
		x=x+tab[i];
	}
	return x;
}

//3.1. Napisać metodę int getLength
int getLenght(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

//3.2. Napisać metodę void Reverse
void Reverse(char *str)
{
	int i=0;
	char x;
	char str2[100];
	strcpy(str2, str);
	while (i < getLenght(str2) / 2)
	{
		x = str2[i];
		str2[i] = str2[getLenght(str2) -i-1];
		str2[getLenght(str2) -i-1] = x;
		i++;
	}
	printf("String od końca: %s", str2);
}

//3.3. Napisać metodę bool containsDigits
bool containsDigits(char *str)
{
	int i;
	for ( i = 0; i < getLenght(str); i++)
	{
		if (isdigit(str[i]))
		{
			return 1;
		}
	}
	return 0;
}

//4.3. Napisać metodę bool AreArraysldentical
bool AreArreysIdentical(int *a1, int *a2, int s1, int s2)
{
	int i;
	if (s1 != s2)
	{
		return 0;
	}
	for (i = 0; i < s1; i++)
	{
		if (a1[i] != a2[i])
		{
			return 0;
		}
	}
	return 1;
}

//4.4. Napisać metodę char * reverseString(char*s)   zakładam, że początkowy string ma z góry określoną maks wielkość, zakładam też, że mogę używać strcpy()
char * reverseString(char *str)
{
	int i = 0, l;
	char x;
	char *str2;

	l = getLenght(str);
	str2 = (char*)malloc((l + 1) * sizeof(char));
	strcpy(str2, str);
	while (i < l / 2)
	{
		x = str2[i];
		str2[i] = str2[l - i - 1];
		str2[l - i - 1] = x;
		i++;
	}
	return str2;
}



////////////////////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////

int main(void) {

	setlocale(LC_ALL, ""); //Polskie znaki bez tego nie działają


	// Chciałem pozwolic uzytkownikowi na uruchamianie wszystkich zadañ w obrebie jednego pliku wiec zrobiłem to uzywajac switch i case
	int zadanie = 1;


	while (zadanie != 0)
	{
	start:
		printf("\n\nProszę wybrać zadanie:\n1. Zadania od 1.1 do 2.5 (Tablice).\n2. Zadania od 3.1 do 3.4 (Stringi)\n3. Zadania od 4.1 do 4.3(Tablice n-elementów)\n4. Zadanie 4.4 Napisać metodę char * reverseString.\n0. Wyjście.\n");
		scanf("%d", &zadanie);
		system("cls");
		switch (zadanie)
		{

			//1 Wszystkie zadania z tablica jako submenu. 
			//1.1. Utworzyć 5-cio elementową tablicę typu int. Pobrać od użytkownika 5 elementów i dodać je do tablicy.
		case 1:
			printf("Zadanie 1, 5- elementowa tablica\n");
			{
				int tablica[5];
				int i, x;
				int podpunkt = 1;
				printf("Proszę wprowadzić 5 liczb oddzielonych spacją\n");
				scanf("%d %d %d %d %d", &tablica[0], &tablica[1], &tablica[2], &tablica[3], &tablica[4]);
				system("cls");

				while (podpunkt != 0)
				{
					printf("\n\nProszę wybrać zadanie:\n1. (1.1)Największa liczba z tablicy.\n2. (1.2)Wyświetlić tablice od początku i od końca.\n3. (1.3)Sprawdzić czy tablica jest posortowana w kolejności niemalejącej\n"
						"4. (2.1) Utworzyć osobną metodę bool IsSorted.\n5. (2.2) Utworzyć metodę void printBackwards\n6. (2.3) Utworzyć metodę printDots\n7. (2.4) Utworzyć metodę int Sum\n8. (2.5) Sortowanie bąbelkowe.\n0. Zeby wrócić do wyboru zadań.\n");
					scanf("%d", &podpunkt);
					system("cls");
					switch (podpunkt)
					{

						//1.1 Następnie wyświetlić największą liczbę z tablicy (algorytm do samodzielnej implementacji).
					case 1:
					{
						for (i = 1, x = tablica[0]; i < sizeof(tablica) / sizeof(tablica[0]); i++)
						{
							if (x < tablica[i])
							{
								x = tablica[i];
							}
						}
						printf("Nawiększa liczba to %d\n", x);
						break;
						system("cls");
					}

					//1.2.Wyświetlić w pętli tablice z zadania 1.1 od początku i od końca(dwie pętle)
					case 2:
					{
						printf("Tablica od początku:\n");
						for (i = 0; i < sizeof(tablica) / sizeof(tablica[0]); i++)
						{
							printf("%d\n", tablica[i]);
						}
						printf("Tablica od końca:\n");
						for (i = (sizeof(tablica) / sizeof(tablica[0]) - 1); i >= 0; i--)
						{
							printf("%d\n", tablica[i]);
						}
						break;
						system("cls");
					}
					//1.3 Napisać algorytm sprawdzający, czy tablica jest posortowana w kolejności niemalejącej
					case 3:
					{
						for (i = 0, x = 0; i < (sizeof(tablica) / sizeof(tablica[0])) - 1; i++)
						{
							if (tablica[i] > tablica[i + 1])
							{
								x = 1;
							}
						}
						if (x == 1)
						{
							printf("Tablica nie jest niemalejąca.\n");
						}
						else
						{
							printf("Tablica jest niemalejąca.\n");
						}
						break;
					}

					case 4:
						//2.1. Utworzyć osobną metodę bool IsSorted(int *, int) realizującą zadanie 1.3 (UWAGA - w języku C niedostępny jest typ bool z wartościami true i false, zamiast niego należy użyć int i wartości 1 i 0)
					{
						if (IsSorted(tablica, sizeof(tablica) / sizeof(tablica[0])))
						{
							printf("Tablica jest niemalejąca.\n");
						}
						else
						{
							printf("Tablica nie jest niemalejąca.\n");
						}
						break;
					}

					case 5:
						//2.2. Utworzyć metodę void printBackwards(int *a, int s) służącą do wypisania tablicy OD KOŃCA
					{
						printBackwards(tablica, sizeof(tablica) / sizeof(tablica[0]));
						break;
					}

					case 6:
						//2.3 Utworzyć metodę printDots(int *a, int s) wyświetlającą w nowych liniach tyle kropek, ile znajduje się w danym
						//elemencie tablicy.
					{
						printDots(tablica, sizeof(tablica) / sizeof(tablica[0]));
						break;
					}

					case 7:
						//2.4. Utworzyć metodę int Sum(int *a, int s) liczącą sumę elementów tablicy. 
					{
						printf("%d", (sum(tablica, sizeof(tablica) / sizeof(tablica[0]))));
						break;
					}

					case 8:
						//2.5. Zaimplementować algorytm sortowania bąbelkowego (w funkcji main(), nie ma potrzeby tworzenia dodatkowej
						//funkcji).Algorytm powinien posortować dowolnie dużą tablicę w kolejności niemalejącej.
					{
						//inicjalizacja zmiennych i tab2=tablica
						int j = 1, i, x;
						int tab2[sizeof(tablica) / sizeof(tablica[0])];
						for (i = 0; i < sizeof(tablica) / sizeof(tablica[0]); i++)
						{
							tab2[i] = tablica[i];
						}

						//sortowanie
						while (j > 0)
						{
							for (i = 0, j = 0; i < (sizeof(tab2) / sizeof(tab2[0])-1); i++)
							{
								if (tab2[i] > tab2[i + 1])
								{
									x = tab2[i];
									tab2[i] = tab2[i + 1];
									tab2[i + 1] = x;
									j++;
								}
							}
						}

						//przedstawienie danych
						printf("Początkowa tablica: ");
						for (i = 0; i < sizeof(tablica) / sizeof(tablica[0]); i++)
						{
							printf("%d ", tablica[i]);
						}
						printf("\n             Wynik: ");
						for (i = 0; i < sizeof(tab2) / sizeof(tab2[0]); i++)
						{
							printf("%d ", tab2[i]);
						}
						break;
					}

					case 0:
					{
						system("cls");
						goto start;
					}
					default:
					{
						printf("Nie ma takiego zadania\n");
						break;
					}
					}
				}
				break;
			}
		case 2:
		//Łańcuchy znaków 
		{
			char str[100];
			int podpunkt = 1;
			printf("Wpisz nie więcej niż 100 znaków.\n");
			scanf("%s", str);
			system("cls");
			while (podpunkt != 0)
			{
				printf("\n\nProszę wybrać zadanie:\n1. (3.1) Metoda int getLength.\n2. (3.2) Metoda void Reverse\n3. (3.3) Metoda bool containsDigits.\n4. (3.4) Pobrać od użytkownika łańcuch znaków.\n0. Zeby wrócić do wyboru zadań.\n");
				scanf("%d", &podpunkt);
				system("cls");
				switch (podpunkt)
				{
				
				case 1:
					//Napisać metodę int getLength(char *str) , w której WŁASNORECZNIE (nie wolno korzystać z metody strlen() )
					//przeliczony zostanie rozmiar łańcucha(bez null - terminatora).Dla przykładu dla „Hello!" wynik powinien wynosić 6. 

				{
					printf("String ma długość: %d", getLenght(str));
					break;
				}

				case 2:
					//3.2. Napisać metodę void Reverse (char *str) , która wypisze łańcuch znaków od końca (zakaz używania strlen,
					//można uzyć metodę z zadania 3.1.)
				{
					Reverse(str);
					break;
				}

				case 3:
					//3.3.Napisać metodę bool containsDigits(char * str), która zwróci informację, czy w danym stringu znajduje się
					//jakakolwiek cyfra.Dla przykładu : „asdfgzxcv" -> false, „asdf5asdf" -> true
				{
					if (containsDigits(str))
					{
						printf("String zawiera liczby.");
					}
					else
					{
						printf("String nie zawiera liczb.");
					}
					break;
				}

				case 4:
					//3.4. Pobrać od użytkownika łańcuch znaków (dowolna metoda). Przekazać go do każdej z metod z 3. części zadań. 
				{
					printf("Zrobiłem to tak od początku w celu prostego debugowania");
					break;
				}

				case 0:
				{
					system("cls");
					goto start;
				}

				default:
				{
					printf("Nie ma takiego zadania\n");
					break;
				}
					
				}

			}



		}

		case 3:
		{
			int i, n;
			int podpunkt = 1;
			printf("Proszę wprowadzić wielkość tablicy\n");
			scanf("%d", &n);
			int *tablica;
			tablica = (int*) malloc(sizeof(int *) * n); // sizeof(int) crashował przy free()
			printf("Proszę wprowadzić %d elementów.\n", n);
			for (i = 0; i < n; i++)
			{
				printf("Wpisz element %d.\n", i);
				scanf("%d", &tablica[i]);
			}
			system("cls");

			while (podpunkt != 0)
			{
				printf("\n\nProszę wybrać zadanie:\n1. (4.1.) Tablica n elementów + printBackwards z 2.2.\n2. (4.2) Tablica liczb ujemnych.\n3. (4.3) Metoda bool AreArraysldentical.\n0. Zeby wrócić do wyboru zadań.\n");
				scanf("%d", &podpunkt);
				system("cls");
				switch (podpunkt)
				{
				case 1:
					//4.1. Pobrać od użytkownika liczbę n. Zaalokować pamięć na n elementów int i pobrać je od użytkownika. Wykonać na
					//niej metodę printBackwards z 2.2.
				{	
					printBackwards(tablica, n); //spędziłem tutaj godzinę debugując, tylko po to żeby dowiedzieć się, że sizeof(array) nie działa z malloc...
					break;
				}
				case 2:
					//4.2.Pobrać od użytkownika liczbę n.Zaalokować pamięć na n elementów int i pobrać je od użytkownika.Następnie
						//zaalokować pamięć i utworzyć tablicę, w której będą tylko UJEMNE wartości z pierwszej tablicy.Na koniec zwolnić
						//pamięć na obie tablice.
				{
					int m = 0, i = 0, j;
					while (i < n)
					{
						if (tablica[i] < 0)
						{
							m++;
						}
						i++;
					}

					int *ujemne;
					ujemne = (int*)malloc(sizeof(int *) * m); 

					for (i = 0, j=0; i < n; i++)
					{
						if (tablica[i] < 0)
						{
							ujemne[j] = tablica[i];
							j++;
						}
					}
					printf("Tablica liczb ujemnych: ");
					for (i = 0; i < m; i++)
					{
						printf("%d ", ujemne[i]);
					}
					free(ujemne);
					break;
				}
				case 3:
					//4.3. Napisać metodę bool AreArraysldentical(int * al, int sl, int * a2, int s2) zwracającą informację, czy dwie tablice
					//podane jako parametr są identyczne, tj.czy mają taką samą długość i czy na każdym indeksie występuje taki sam
					//element.
				{
					int size2;
					printf("Proszę wprowadzić wielkość tablicy do porównania\n");
					scanf("%d", &size2);
					int *array2;
					array2 = (int*)malloc(sizeof(int *) * size2);
					printf("Proszę wprowadzić %d elementów.\n", size2);
					for (i = 0; i < size2; i++)
					{
						printf("Wpisz element %d.\n", i);
						scanf("%d", &array2[i]);
					}
					system("cls");
					if (AreArreysIdentical(tablica, array2, n, size2))
						printf("Tablice są identyczne.\n");
					else
						printf("Tablice różnią się.\n");
					free(array2);
					break;
				}

				case 0:
				{	
					free(tablica);
					system("cls");
					goto start;
				}
				default:
				{
					printf("Nie ma takiego zadania.\n");
					break;
				}
				}
			}
		}
		case 4:
			//4.4. Napisać metodę char * reverseString(char*s), która ZWRÓCI (a nie wypisze!) string, który jest odwróconym
			//stringiem przekazanym jako pierwszy parametr.Funkcja zaalokuje pamięć na nowy łańcuch i go zwróci. (cały
			//algorytm należy zaimplementować samodzielnie).Należy go następnie „przechwycić" w funkcji main, aby pamięć na
			//koniec wyczyścić
		{
			char str[100];
			char* rstring;
			printf("Wpisz nie więcej niż 100 znaków.\n");
			scanf("%s", str);

			rstring = reverseString(str);
			printf("String od końca:%s", rstring);
			free(rstring);
			break;
		}
		case 0:
		{
			system("cls");
			printf("Koniec\n");
			break;
		}
		default:
		{
			printf("Nie ma takiego zadania.\n");
			break;
		}
		}
	}
	return 0;
}



