#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pch.h"
#include <iostream>


////////////////////////////////////////////FUNKCJE//////////////////////////////////////////////////
bool IsSorted(int *tab, int s)
{
	int i;
	for (i = 0; i < s-1; i++)
	{
		if (tab[i] > tab[i + 1])
		{
			return 0;
		}
	}
	return 1;
}
void printBackwards(int *tab, int s)
{
	int i;
	for (i = s-1; i >= 0; i--)
	{
		printf("%d\n", tab[i]);
	}
}
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


int main(void) {

	setlocale(LC_ALL, ""); //Polskie znaki bez tego nie działają


	// Chciałem pozwolic uzytkownikowi na uruchamianie wszystkich zadañ w obrebie jednego pliku wiec zrobiłem to uzywajac switch i case
	int zadanie = 1;
	

	while (zadanie != 0)
	{	
		start:
		printf("\n\nProszę wybrać zadanie:\n1. Zadania od 1.1 do 2.3\n2. Zadania od 3.1 do 3.3\n");
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
					printf("\n\nProszę wybrać zadanie:\n1. (1.1)Największa liczba z tablicy.\n2. (1.2)Wyświetlić tablice od początku i od końca.\n3. (1.3)Sprawdzić czy tablica jest posortowana w kolejności niemalejącej(???)\n"
					"4. (2.1) Utworzyć osobną metodę bool IsSorted.\n5. (2.2) Utworzyć metodę void printBackwards\n6. (2.3) Utworzyć metodę printDots\n0. Zeby wrócić do wyboru zadań.\n");
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
						for (i=0, x= 0;i < (sizeof(tablica) / sizeof(tablica[0]))-1; i++)
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
					{
						printBackwards(tablica, sizeof(tablica) / sizeof(tablica[0]));
						break;
					}

					case 6:
					{
						printDots(tablica, sizeof(tablica) / sizeof(tablica[0]));
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




