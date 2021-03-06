// matrixgen.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main()
{
	FILE*temp;
	int m, n;
	int i, l;

	printf("Podaj wymiary tablicy\n");
	scanf("%d %d", &m, &n);

	int** random = new int*[m];
	for (int i = 0; i < m; i++)
		random[i] = new int[n];

	srand(time(NULL));
	for (l = 0; l < m; l++)
		for (i = 0; i < n; i++)
			random[l][i] = rand() % 10;

	temp = fopen("temp.txt", "w");
	fprintf(temp, "%d %d\n", m, n);
	int j, k;
	for (k = 0; k < m; k++) {
		for (j = 0; j < n; j++) {
			printf("%d ", random[k][j]);
			fprintf(temp, "%d ", random[k][j]);
		}
		printf("\n");
		fprintf(temp, "\n");
	}
	fclose(temp);

	for (int i = 0; i < m; i++)
		delete[] random[i];
	delete[] random;

	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
