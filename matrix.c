#include <stdlib.h>
#include <stdio.h>
int main()
{
	FILE*temp;
	int m, n;
    int i, l;

    printf("Podaj wymiary tablicy\n");
    scanf("%d %d", &m, &n);
    int random[m][n];
    srand(time(NULL));
    for(l = 0; l<m; l++)
        for(i = 0; i<n; i++)
            random[l][i] = rand() % 10;
    
    temp=fopen("temp.txt","w");
    fprintf(temp, "%d %d\n", m, n);
    int j, k;
    for(k=0; k<m; k++){
        for(j=0; j<n; j++){
            printf("%d ", random[k][j]);
            fprintf(temp,"%d", random[k][j]);
        }
        printf("\n");
        fprintf(temp,"\n");
    }
    fclose(temp);

    return 0;
}
