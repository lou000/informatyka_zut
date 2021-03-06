#include <stdio.h>
#include <stdlib.h>
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdarg.h>

typedef struct Node Node;
////////////////////////////////////////////FUNKCJE CMD//////////////////////////////////////////////////



//funkcja do przechodzenia przez menu
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

//funkcja do drukowania menu
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
		if (k != 1)
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

////////////////////////////////////////////FUNKCJE DO ZADAŃ//////////////////////////////////////////////////

//Zadania 1.1 i 1.2
struct Student
{
	int Age;
	int Height;
	int Semester;
};

Student* StudentCreate(int age, int height, int semester)
{
	Student * student = (Student*)malloc(sizeof(Student));
	student->Age = age;
	student->Height = height;
	student->Semester = semester;
	return student;
}

void PrintStudent(Student *s)
{
	printf("Age = %d \nHeight = %d\nSemester = %d", s->Age, s->Height, s->Semester);
}

bool AreEqual(Student *s1, Student *s2)
{
	if (s1->Age == s2->Age && s1->Height == s2->Height && s1->Semester == s2->Semester)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

struct Node
{
	int Value;
	Node * Next;
};

Node * Create(int value)
{
	Node *ptr = (Node*)malloc(sizeof(Node));
	if (ptr)
	{
		ptr->Value = value;
		ptr->Next = ptr;
	}
	else
		return NULL;		//tutaj wyskakuje warning, ale chciałbym zwrócić NULL jak malloc sie nie powiedzie
}

Node* GetTail(Node* root)
{
	Node *ptr = root;
	while (ptr->Next != root)
	{
		ptr = ptr->Next;
	}
	return ptr;
}

void PrintList(Node* root)
{
	Node * ptr = root;
	Node * tail = GetTail(root);		
	while (ptr!=tail)			//nie wiem po co mi tutaj tail, gdyby nie polecenie to zrobiłbym while(ptr->next!=root) i tak musze przejsc przez wszystkie nody
	{
		printf("%d->", ptr->Value);
		ptr = ptr->Next;
	}
	printf("%d\n", ptr->Value);
}

void Add(Node* root, int value)
{
	Node * tail = GetTail(root);
	tail->Next = (Node*)malloc(sizeof(Node));
	Node * newnode = tail->Next;
	newnode->Next = root;
	newnode->Value = value;
}

void RemoveNode(Node * root, int value)
{
	Node * ptr = root;
	if (ptr->Value == value)				// jeżeli użytkownik usunie root to będzie musiał sam go najpierw zastąpić root->Next 
	{										// (Wydaje mi sie, że jeżeli chciałbym zmienić root wewnątrz tej funkcji to chyba musiałbym przekazać **root, a to nie zgadza sie z trescia zadania)
		Node * tail = GetTail(root);
		tail->Next = ptr->Next;
		Node * temp = ptr;
		ptr = ptr->Next;
		root = ptr;
		free(temp);
	}
	while (ptr->Next != root)
	{
		if (ptr->Next->Value == value)
		{
			Node * temp = ptr->Next;
			ptr->Next = temp->Next;
			free(temp);
		}
		ptr = ptr->Next;
	}
}

void FreeList(Node * root)
{
	Node * ptr = root->Next;
	while (ptr!=root)
	{
		Node * temp = ptr;
		ptr = ptr->Next;
		free(temp);
	}
	free(root);
}

int Count(Node *root)
{
	Node * ptr = root;
	int count = 1;
	while (ptr->Next != root)
	{
		ptr = ptr->Next;
		count++;
	}
	return count;
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

	int offset = 0, zadanie = 1;
	unsigned int hl = 14, nhl = 6;		//domyślne kolory tekstu
	while (zadanie != 0)
	{
		bool loopinterrupt = false;
		bool enter = false;
		while (zadanie != 0 && enter != true)
		{
			SetConsoleTextAttribute(hConsole, 6);
			printMenu(60, 10-offset, 1, 15, nhl, 1, "Zadania programowanie C, styczeń:");
			printMenu(60, 1, 3, hl, nhl, zadanie, "1. Zadania od 1.1 do 1.2 (Struktury).", "2. Zadanie 2 (Listy).", "3. Zadania od 3.1 do 3.3 (Import/export).");
			menu(&zadanie, &enter, 3);
			system("cls");
			offset = 0;
		}
		switch (zadanie)
		{
		
		/*Zad 1.1
		Utworzyć strukturę Student taką jak powyżej.Napisać metody :
		Student * Create(int age, int height, int semester) // alokuje pamięć i tworzy studenta o podanych parametrach.
		WAŻNE - pamięć należy potem zwolnić w main() !
		void PrintStudent(Student *s) // wypisuje wszystkich składowych struktury
		bool AreEqueal(Student* sl, Student* s2) // zwraca informację, czy składowe są takie same (Uwaga - w C int zamiast
		bool)*/
		case 1:
			{
				int podpunkt = 1;
				while (podpunkt != 0)
				{
					if (loopinterrupt)
					{
						break;
					}
					bool enter = false;
					while (podpunkt != 0 && enter != true)
					{
						printMenu(60, 10 - offset, 1, 15, nhl, 1, "Zadania 1.1 i 1.2, Struktury danych.");
						printMenu(60, 1, 3, hl, nhl, podpunkt, "1. (1.1) Metody Student * Create, void PrintStudent", "2. (1.1) Metoda bool AreEqual", "3. (1.2) Tablica struktur");
						menu(&podpunkt, &enter, 3);
						system("cls");
						offset = 0;
					}
					//podpunkty od 1.1 do 1.2
					switch (podpunkt)
					{

					//1. (1.1) Metody Student * Create, void PrintStudent
					case 1:
					{
						Student *s = StudentCreate(25, 180, 5);
						PrintStudent(s);
						free(s);
						offset = 2;
						break;
					}

					//2. (1.1) Metoda bool AreEqual
					case 2:
					{
						int a, h, s;
						printMenu(60, 10, 1, 15, nhl, 1, "Zadanie 1.1 Metoda bool AreEqual.");
						printMenu(60, 1, 1, hl, nhl, 1, "Proszę wprowadzić dane pierwszego studenta (wiek wzrost semestr):");
						offsetNextLine(55, 2);
						scanf("%d %d %d", &a, &h, &s);
						Student *s1 = StudentCreate(a, h, s);
						system("cls");
						printMenu(60, 10, 1, 15, nhl, 1, "Zadanie 1.1 Metoda bool AreEqual.");
						printMenu(60, 1, 1, hl, nhl, 1, "Proszę wprowadzić dane drugiego studenta (wiek wzrost semestr):");
						offsetNextLine(55, 2);
						scanf("%d %d %d", &a, &h, &s);
						Student *s2 = StudentCreate(a, h, s);
						system("cls");
						if (AreEqual(s1, s2))
							printf("Studenci mają takie same dane.");
						else
							printf("Studenci mają różne dane.");
						free(s1);
						free(s2);
						break;
					}
					//Zad 1 2
					//Utworzyć tablicę 3 studentów.Zapełnić ją wartościami, wyświetlić, zwolnić pamięć.Tablica powinna być utworzona za
					//pomocą metody malloc(proszę pilnować odpowiedniej ilości gwiazdek!)
					case 3:
					{
						int arr_size = 3;
						int i;
						char buffer[100];
						Student* s_arr = (Student*)malloc(arr_size * sizeof(Student));
						for (i = 0; i < arr_size; i++)
						{
							sprintf(buffer, "Proszę wprowadzić dane studenta nr %d:", i+1);
							printMenu(60, 1, 1, hl, nhl, 1, buffer);
							offsetNextLine(55, 2);
							scanf("%d %d %d", &s_arr[i].Age, &s_arr[i].Height, &s_arr[i].Semester);
							system("cls");
						}
						for (i = 0; i < arr_size; i++)
						{
							printf("Student %d: Age = %d, Height = %d, Semester = %d\n", i + 1, s_arr[i].Age, s_arr[i].Height, s_arr[i].Semester);
						}
						offset = 3;
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
			//Listy
		{
			Node * root = Create(2);
			PrintList(root); // 2
			Add(root, 4);
			Add(root, 8);
			Add(root, 16);
			PrintList(root); // 2 -> 4 -> 8 -> 16
			Add(root, 20);
			PrintList(root); // 2 4 8 16 20
			printf("Ostatni wezel ma wartosc %d\n", GetTail(root)->Value); // 20
			Add(root, 16);
			PrintList(root); // 2 -> 4 -> 8 -> 16 -> 20 -> 16
			printf("%d\n", Count(root)); // 6
			RemoveNode(root, 8);
			PrintList(root); // 2 -> 4 -> 16 -> 20 -> 16
			RemoveNode(root, 10); // element nieistniejący
			PrintList(root); // 2 -> 4 -> 16 -> 20 -> 16
			RemoveNode(root, 16); // usuń wszystkie węzły o wartości 16
			PrintList(root); // 2 -> 4 -> 20
			printf("%d\n", Count(root)); // 3
			FreeList(root); // zwolnienie pamięci na wszystkie węzły.
			//PrintList(root); // (nic, lista niezaalokowana)			//tutaj mi wyskakuje exception, nie bardzo widze jak to zabezpieczyć w tym miejscu, pamieć jest niezaalokowana
			offset = 10;												// zostawiam wykomentowane
			break;														
		}

		//Zad. 3
		//Zapis i odczyt z pliku, sortowanie linked list.
		case 3:
		{
			Node * root = NULL;
			int podpunkt = 1;
			while (podpunkt != 0)
			{
				if (loopinterrupt)
				{
					break;
				}
				bool enter = false;
				while (podpunkt != 0 && enter != true)
				{
					printMenu(60, 10 - offset, 1, 15, nhl, 1, "Zadania 3.1 do 3.3, Zapis/odczyt pliu oraz sortowanie list.");
					printMenu(60, 1, 3, hl, nhl, podpunkt, "1. (3.1.) Wczytywanie podanych liczb do pliku.", "2. (3.2) Tworzenie listy kierunkowej z podanych liczb.", "3. (3.3) Sortowanie listy.");
					menu(&podpunkt, &enter, 3);
					system("cls");
					offset = 0;
				}
				system("cls");

				switch (podpunkt)
				{
				/*Zad. 3.1
				Wczytywać od użytkownika liczby, aż nie poda on 0. Wszystkie wczytane liczby zapisać do pliku numbers.txt*/
				case 1:
				{
					FILE * test;								//na wypadek gdyby plik juz istnial
					if (test = fopen("numbers.txt", "r"))
					{
						fclose(test);
						remove("numbers.txt");
					}

					FILE * plik = fopen("numbers.txt", "w");
					int input = 1;

					while (input != 0)
					{
						printMenu(60, 10, 1, 15, nhl, 1, "Zadanie 3.1 wczytywanie podanych liczb do pliku.");
						printMenu(60, 1, 1, hl, nhl, 1, "Proszę wprowadzić liczby (podanie 0 zakonczy wczytywanie):");
						offsetNextLine(55, 2);
						scanf("%d", &input);
						system("cls");
						if (input!=0)						//nie jestem pewien czy wg zadania zero ma być wczytane czy nie, jeżeli ma byc wczytane to tej linii nie powinno byc
							fprintf(plik, "%d ", input);
					}
					fclose(plik);
					break;
				}

				/*Zad. 3.2
				Wczytać z numbers.txt liczby.Utworzyć listę jednokierunkową(z zadania 2) zawierającą te liczby.Wypisać je na
				ekran.*/
				case 2:
				{
					FILE * plik = fopen("numbers.txt", "r");
					if (plik == NULL)
					{
						printf("Plik nie istnieje.");
						offset = 1;
						break;
					}
					int output = 0;
					fscanf(plik, "%d ", &output);
					root = Create(output);
					while (fscanf(plik, "%d ", &output) != EOF)
					{
						Add(root, output);
					}
					PrintList(root);
					offset = 1;
					break;
				}

				//Zad. 3.3
				//Posortować(w dowolny sposób) listę z zadania 2.3 (już po wczytaniu z pliku).Zapisać posortowaną liczbę do pliku
				//sorted.txt.Algorytm sortowania proszę zaimplementować samodzielnie.
				case 3:
				{
					if (root == NULL)	//próba implementacji sortowania kubełkowego uzywajac tylko jednej listy (zły pomysł bardzo skomplikowane i niewydajne, to że lista jest cykliczna pogarsza sprawę)
					{					//zrobiło się z tego spaghetti ale działa
						printf("Lista nie została zainicjalizowana.");
						break;
					}
					if (root->Next == root)
					{
						printf("Lista ma tylko jeden element.");
						break;
					}
					Node * current = root;
					Node * previous = GetTail(root);
					int value;
					bool change = false;
					bool sorted = false;
					while (!sorted)
					{
						while(change == false)
						{
							if (current == root)
							{
								if (current->Value > current->Next->Value)
								{
									previous = GetTail(root);
									root = root->Next;
									previous->Next = root;
									value = current->Value;
									free(current);
									current = root;
									change = true;
								}
								else
								{
									previous = current;
									current = current->Next;
								}
							}
							else
							{
								if (current->Value > current->Next->Value)
								{
									previous->Next = current->Next;
									value = current->Value;
									free(current);
									current = previous->Next;
									change = true;
								}
								else
								{
									previous = current;
									current = current->Next;
								}
							}
						}

						Node * count = root;
						bool found = false;
						while (found == false && change == true)
						{
							if (value < root->Value)
							{
								Node * tail = GetTail(root);
								Node * newnode = (Node*)malloc(sizeof(Node));
								newnode->Next = root;
								newnode->Value = value;
								tail->Next = newnode;
							}
							if (value < count->Next->Value || (count->Next == root && found == false))
							{
								Node * newnode = (Node*)malloc(sizeof(Node));
								newnode->Next = count->Next;
								newnode->Value = value;
								count->Next = newnode;
								found = true;
							}
							else
							{
								count = count->Next;
							}
						}
						change = false;
						Node * temp = root;
						sorted = true;
						while (temp->Next != root)	//wszystko działa ale nie wiem jak określić kiedy nastąpił koniec sortowania bez dodatkowego przechodzenia przez całą listę
						{
							if (temp->Value > temp->Next->Value)
								sorted = false;
							temp = temp->Next;
						}
					}

					FILE * test;								//na wypadek gdyby plik juz istnial
					if (test = fopen("sorted.txt", "r"))
					{
						fclose(test);
						remove("sorted.txt");
					}

					Node * temp = root;
					FILE * plik = fopen("sorted.txt", "w");
					while (temp->Next!=root)
					{
						fprintf(plik, "%d ", temp->Value);
						temp = temp->Next;
					}
					fprintf(plik, "%d ", temp->Value);
					fclose(plik);
					PrintList(root);
					offset = 1;
					break;
				}

				case 0:
				{
					loopinterrupt = true;
					if (root != NULL)
						FreeList(root);
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
