#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdarg.h>

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
		x = x + tab[i];												
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
	int i = 0;
	char x;
	char str2[100];
	strcpy(str2, str);
	while (i < getLenght(str2) / 2)
	{
		x = str2[i];
		str2[i] = str2[getLenght(str2) - i - 1];
		str2[getLenght(str2) - i - 1] = x;
		i++;
	}
	printf("String od końca: %s", str2);
}

//3.3. Napisać metodę bool containsDigits
bool containsDigits(char *str)
{
	int i;
	for (i = 0; i < getLenght(str); i++)
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

//funkcja do przechodzenia przez menu// gdzieś czytałem, że funkcję nie powinny być takie długie ale nie bardzo wiem jak ja skrocic
void menu(int *menuitem, bool *confirm, int numberofitems) //zakładam, że startowy menuitem=1
{
	bool y = 0;
	while (y != 1)
	{
		int x = 0;
		if (_kbhit())
		{
			x = _getch();
			if (x == 0 || x == 224)				// wykrywam czy pierwszy getch() złapał znaki poprzedzajace strzalki albo numpad
			{
				x = _getch();
			}
		}
		switch (x)								// na potrzeby mojego programu nie wykrywam nic wiecej niz strzalki i liczby<10
		{
		case 72:
		{
			if (*menuitem == 1)					//upewniam sie ze licznik mi sie obróci // potrzebna bedzie funkcja highlight(int linetohl, *str1, *str2....)
			{
				*menuitem = numberofitems;
			}
			else
			{
				*menuitem = *menuitem - 1;
			}
			y = 1;
			break;
		}
		case 80:
		{
			if (*menuitem == numberofitems)
			{
				*menuitem = 1;
			}
			else
			{
				*menuitem = *menuitem + 1;
			}
			y = 1;
			break;
		}
		case 13:
		{
			*confirm = true;
			y = 1;
			break;
		}
		case 27:
		{
			*menuitem = 0;
			*confirm = true;
			y = 1;
			break;
		}
		default:
		{
			if (x < 58 && x>47)
			{
				*menuitem = x - 48;
				*confirm = true;
				y = 1;
				break;
			}
		}
		}
	}
}

//funkcja highlight(int linetohl, str1, str2 ...)
void highlight(int numberoflines, int linetohl, const char* str...)
{
	va_list ap;
	int i;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		// windows api do zmiany koloru tekstu
	va_start(ap, linetohl);
	for (i = 1; i <= numberoflines; i++)
	{
		if (i == linetohl)
		{
			SetConsoleTextAttribute(hConsole, 14);
			printf("%s\n", va_arg(ap, const char*));
			SetConsoleTextAttribute(hConsole, 6);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 6);
			printf("%s\n", va_arg(ap, const char*));
		}
	}
	va_end(ap);


}

//funkcja do wyrównania tekstu// jeżeli chcemy przekazać zmienną do string trzeba bedzie uzyc sprintf//malloc strasznie upierdliwy
const char *printNicely(const char* str, int positionX, int positionY)
{
	int len, i, j;
	len = strlen(str);
	
	positionX = positionX - len / 2;
	char* output = (char*)malloc(sizeof(char)*(len + positionX + positionY+1));
	for (i = 0; i < positionY; i++)
	{
		output[i] = '\n';
	}
	for (i = positionY; i < positionX+positionY; i++)
	{
		output[i] = ' ';
	}
	for (i = positionX + positionY, j = 0; i < positionX + positionY + len; i++, j++)
	{
		output[i] = str[j];
	}
	output[i] = '\0';
	char test[300];
	sprintf(test, output); //próbowałem tak ale niestety funkcja przekazuje śmieci bez malloc, a nie mogę zwolnić pamieci w main bez przypisania wartości do zmiennej
	return output;
}

//okazuje się że najprościej będzie chyba połączyć funkcje highlight i printNicely//
void printMenu(unsigned int positionX, unsigned int positionY, unsigned int numberoflines, unsigned int hlAtt, unsigned int nAtt, unsigned int linetohl, const char* str...)
{
	va_list ap;
	unsigned int i, len, j, k, posX;
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		// windows api do zmiany koloru tekstu
	va_start(ap, linetohl);
	for (k = 1; k <= numberoflines; k++)
	{
		if (positionY < 0)
		{

		}
		const char* string = va_arg(ap, const char*);
		len = strlen(string);
		posX = positionX - len / 2;
		if (k!=1)
		{
			positionY = 0;
		}

		char* output = (char*)malloc(sizeof(char)*(len + posX + positionY + 1));
		for (i = 0; i < positionY; i++)
		{
			output[i] = '\n';
		}
		for (i = positionY; i < posX + positionY; i++)
		{
			output[i] = ' ';
		}
		for (i = posX + positionY, j = 0; i < posX + positionY + len; i++, j++)
		{
			output[i] = string[j];
		}
		output[i] = '\0';

		if (k == linetohl)
		{
			SetConsoleTextAttribute(hConsole, hlAtt);
			printf("%s\n", output);
			SetConsoleTextAttribute(hConsole, nAtt);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, nAtt);
			printf("%s\n", output);
		}
		free(output);						// tutaj mogę już użyć free
	}
	va_end(ap);
}

//prosta funkcja na offset następnej linii
void offsetNextLine(int positionX, int positionY)
{
	char* output = (char*)malloc(sizeof(char)*(positionX + positionY + 1));
	int i;
	for (i = 0; i < positionY; i++)
	{
		output[i] = '\n';
	}
	for (i = positionY; i < positionX + positionY; i++)
	{
		output[i] = ' ';
	}
	output[i] = '\0';
	printf(output);
	free(output);
}



////////////////////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////

int main(void) {

	setlocale(LC_ALL, "");
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 20;
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hConsole, 0, &info);

	int zadanie = 1;
	unsigned int hl = 14, nhl = 6;		//domyślne kolory tekstu
	while (zadanie != 0)
	{
		bool loopinterrupt = false;
		bool enter = false;
		while (zadanie != 0 && enter != true)
		{
			SetConsoleTextAttribute(hConsole, 6);   // próbowałem tutaj zmieniać pozycję tekstu poprzez SetConsoleCursorPosition ale nie chiało się centrować.
			printMenu(60, 10, 1, 15, nhl, 1, "Zadania programowanie C, grudzień:");
			printMenu(60, 1, 4, hl, nhl, zadanie, "1. Zadania od 1.1 do 2.5 (Tablice).", "2. Zadania od 3.1 do 3.4 (Stringi).", "3. Zadania od 4.1 do 4.3(Tablice n - elementów).", "4. Zadanie 4.4 Napisać metodę char * reverseString.");
			menu(&zadanie, &enter, 4);
			printf("%d", zadanie);
			system("cls");
		}
		switch (zadanie)
		{

			//1.1. Utworzyć 5-cio elementową tablicę typu int. Pobrać od użytkownika 5 elementów i dodać je do tablicy.
		case 1:
			printMenu(60, 10, 1, 15, nhl, 1, "Zadanie 1 oraz 2, 5- elementowa tablica.");
			{
				int tablica[5];
				int i, x, offset = 0, podpunkt = 1;
				printMenu(60, 1, 1, hl, nhl, 1, "Proszę wprowadzić 5 liczb oddzielonych spacją:");
				offsetNextLine(55, 2);
				scanf("%d %d %d %d %d", &tablica[0], &tablica[1], &tablica[2], &tablica[3], &tablica[4]);
				system("cls");

				while (podpunkt != 0)
				{
					if (loopinterrupt)
					{
						break;
					}
					bool enter = false;
					while (podpunkt != 0 && enter != true)
					{
						printMenu(60, 10-offset, 1, hl, nhl, 1, "Proszę wybrać zadanie:");
						printMenu(60, 1, 8, hl, nhl, podpunkt, "1. (1.1)Największa liczba z tablicy.", "2. (1.2)Wyświetlić tablice od początku i od końca.", "3. (1.3)Sprawdzić czy tablica jest posortowana w kolejności niemalejącej",
						"4. (2.1) Utworzyć osobną metodę bool IsSorted.", "5. (2.2) Utworzyć metodę void printBackwards.", "6. (2.3) Utworzyć metodę printDots.", "7. (2.4) Utworzyć metodę int Sum.", "8. (2.5) Sortowanie bąbelkowe.");
						menu(&podpunkt, &enter, 8);
						system("cls");
						offset = 0;
					}
					//podpunkty od 1.1 do 2.5
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
						printf("Nawiększa liczba to %d", x);
						break;
					}

					//1.2.Wyświetlić w pętli tablice z zadania 1.1 od początku i od końca(dwie pętle)
					case 2:
					{
						printf("Tablica od początku: ");
						for (i = 0; i < sizeof(tablica) / sizeof(tablica[0]); i++)
						{
							printf("%d ", tablica[i]);
						}
						printf("\nTablica od końca:    ");
						for (i = (sizeof(tablica) / sizeof(tablica[0]) - 1); i >= 0; i--)
						{
							printf("%d ", tablica[i]);
						}
						offset = 1;
						break;
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
							printf("Tablica nie jest niemalejąca.");
						}
						else
						{
							printf("Tablica jest niemalejąca.");
						}
						break;
					}

					case 4:
						//2.1. Utworzyć osobną metodę bool IsSorted(int *, int) realizującą zadanie 1.3 (UWAGA - w języku C niedostępny jest typ bool z wartościami true i false, zamiast niego należy użyć int i wartości 1 i 0)
					{
						if (IsSorted(tablica, sizeof(tablica) / sizeof(tablica[0])))
						{
							printf("Tablica jest niemalejąca.");
						}
						else
						{
							printf("Tablica nie jest niemalejąca.");
						}
						break;
					}

					case 5:
						//2.2. Utworzyć metodę void printBackwards(int *a, int s) służącą do wypisania tablicy OD KOŃCA
					{
						printBackwards(tablica, sizeof(tablica) / sizeof(tablica[0]));
						offset = sizeof(tablica) / sizeof(tablica[0]);
						break;
					}

					case 6:
						//2.3 Utworzyć metodę printDots(int *a, int s) wyświetlającą w nowych liniach tyle kropek, ile znajduje się w danym
						//elemencie tablicy.
					{
						printDots(tablica, sizeof(tablica) / sizeof(tablica[0]));
						offset = sizeof(tablica) / sizeof(tablica[0]);
						break;
					}

					case 7:
						//2.4. Utworzyć metodę int Sum(int *a, int s) liczącą sumę elementów tablicy. 
					{
						printf("Suma wszystkich elementów tablicy to: %d", sum(tablica, sizeof(tablica) / sizeof(tablica[0])));
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
							for (i = 0, j = 0; i < (sizeof(tab2) / sizeof(tab2[0]) - 1); i++)
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
						offset = 1;
						break;
					}

					case 0:
					{
						loopinterrupt = true;
						system("cls");
						break;
					}
					default:
					{
						printf("Nie ma takiego zadania.");
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
			int podpunkt = 1, offset = 0;
			printMenu(60, 10, 1, 15, nhl, 1, "Zadanie 3, String o określonym wymiarze.");
			printMenu(60, 1, 1, hl, nhl, 1, "Wpisz nie więcej niż 100 znaków.");
			offsetNextLine(55, 2);
			scanf("%s", str);
			system("cls");
			while (podpunkt != 0)
			{
				if (loopinterrupt)
				{
					break;
				}
				bool enter = false;
				while (podpunkt != 0 && enter != true)
				{
					printMenu(60, 10 - offset, 1, hl, nhl, 1, "Proszę wybrać zadanie:");
					printMenu(60, 1, 4, hl, nhl, podpunkt, "1. (3.1) Metoda int getLength.", "2. (3.2) Metoda void Reverse.", "3. (3.3) Metoda bool containsDigits.", "4. (3.4) Pobrać od użytkownika łańcuch znaków.");
					menu(&podpunkt, &enter, 4);
					offset = 0;
					system("cls");
				}
				system("cls");
				//podpunkty od 3.1 do 3.4
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
					loopinterrupt = true;
					system("cls");
					break;
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

		case 3:
		{
			int i, n, offset = 0;
			char buffer[100];
			int podpunkt = 1;
			printMenu(60, 10, 1, 15, nhl, 1, "Zadanie 4, Tablica o dowolnej wielkości.");
			printMenu(60, 1, 1, hl, nhl, 1, "Proszę wprowadzić wielkość tablicy.");
			offsetNextLine(60, 2);
			scanf("%d", &n);
			system("cls");
			int *tablica;
			tablica = (int*)malloc(sizeof(int *) * n);
			sprintf(buffer, "Proszę wprowadzić %d liczb oddzielonych spacją", n);
			printMenu(60, 10, 1, hl, nhl, 1, buffer);
			offsetNextLine(55, 2);
			i = 0;
			while (i < n)
			{
				scanf("%d", &tablica[i]);
				i++;
			}
			system("cls");

			while (podpunkt != 0)
			{
				if (loopinterrupt)
				{
					break;
				}
				bool enter = false;
				while (podpunkt != 0 && enter != true)
				{
					printMenu(60, 10 - offset, 1, hl, nhl, 1, "Proszę wybrać zadanie:");
					printMenu(60, 1, 3, podpunkt, hl, nhl, "1. (4.1.) Tablica n elementów + printBackwards z 2.2.", "2. (4.2) Tablica liczb ujemnych.", "3. (4.3) Metoda bool AreArraysldentical.");
					menu(&podpunkt, &enter, 3);
					system("cls");
				}
				system("cls");
				switch (podpunkt)
				{
				case 1:
					//4.1. Pobrać od użytkownika liczbę n. Zaalokować pamięć na n elementów int i pobrać je od użytkownika. Wykonać na
					//niej metodę printBackwards z 2.2.
				{
					printBackwards(tablica, n); //spędziłem tutaj godzinę debugując, tylko po to żeby dowiedzieć się, że sizeof(array) nie działa z malloc...
					offset = n;
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

					for (i = 0, j = 0; i < n; i++)
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
					printMenu(60, 10, 1, hl, nhl, 1, "Proszę wprowadzić wielkość tablicy do porównania.");
					offsetNextLine(60, 2);
					scanf("%d", &size2);
					int *array2;
					array2 = (int*)malloc(sizeof(int *) * size2);
					system("cls");
					sprintf(buffer, "Proszę wprowadzić %d liczb oddzielonych spacją", size2);
					printMenu(60, 10, 1, hl, nhl, 1, buffer);
					offsetNextLine(55, 2);
					i = 0;
					while (i < size2)
					{
						scanf("%d", &array2[i]);
						i++;
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
					loopinterrupt = true;
					system("cls");
					break;
				}
				default:
				{
					printf("Nie ma takiego zadania.\n");
					break;
				}
				}
			}
			break;
		}
		case 4:
			//4.4. Napisać metodę char * reverseString(char*s), która ZWRÓCI (a nie wypisze!) string, który jest odwróconym
			//stringiem przekazanym jako pierwszy parametr.Funkcja zaalokuje pamięć na nowy łańcuch i go zwróci. (cały
			//algorytm należy zaimplementować samodzielnie).Należy go następnie „przechwycić" w funkcji main, aby pamięć na
			//koniec wyczyścić
		{
			char str[100];
			char* rstring;
			printMenu(60, 10, 1, hl, nhl, 1, "Wpisz nie więcej niż 100 znaków.");
			offsetNextLine(55, 2);
			scanf("%s", str);
			rstring = reverseString(str);
			system("cls");
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
