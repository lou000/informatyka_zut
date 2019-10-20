#include <QCoreApplication>
#include <QDebug>
#include "stdlib.h"
#include "time.h"
#include <QTime>

struct arrayWithLen
{
    int** tab;
    int length;
    void initArray(int size, int numberShift)
    {
        tab = static_cast<int**>(malloc(static_cast<unsigned long long>(size)*sizeof (int*)));
        length = size;
        for(int i=0; i<size; i++)
        {
            tab[i] = new int(i + numberShift);
        }
    }
    void removeAt(int index)
    {
        *tab[index] = *tab[length-1];
        free(tab[length-1]);
        length--;
    }
};

struct Struktura
{
    int randomKey;
    char randomChar;
    float totallyNotInt;
};

Struktura** allocAndInit(int N)
{
    struct Struktura** tab = static_cast<struct Struktura**>(malloc(static_cast<unsigned long long>(N)*sizeof(struct s*)));
    struct arrayWithLen array;
    array.initArray(10001, -1000);
    for(int i=0; i<N; i++)
    {
        tab[i] = static_cast<struct Struktura*>(malloc(sizeof(struct Struktura)));
        int index = (rand() % (array.length+1));
        tab[i]->randomKey = *array.tab[index];
        array.removeAt(index);
        tab[i]->randomChar = static_cast<char>((rand() % 18) + 66);
        tab[i]->totallyNotInt = 1001+i;
    }
    for(int i=0; i<array.length-1; i++)
    {
        free(array.tab[i]);
    }
    free(array.tab);
    return tab;
}

void freeStruktury(Struktura** tab ,int size)
{
    for(int i=0; i<size-1; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

void bubbleSort(Struktura** tab, int size)
{
    bool swap = false;
    for(int j=0;j<size-1;j++)
    {
        for(int i=0;i<size-1-j;i++)
        {
            auto swap1 = [](Struktura* pointer1, Struktura* pointer2){Struktura temp = *pointer1; *pointer1 = *pointer2; *pointer2 = temp; return;};

            if(tab[i]->randomKey<tab[i+1]->randomKey)
            {
                swap1(tab[i], tab[i+1]);
                swap = true;
            }
        }
        if(!swap)
            return;
    }
}
int findNumeberOfObjectsWithChar(Struktura** tab, char X, int size)
{
    int count=0;
    for(int i=0;i<size-1;i++)
    {
        if(tab[i]->randomChar == X)
            count++;
    }
    return count;
}
void printStructure(Struktura* structure, int counter)
{
    qDebug()<<"--------------------------------------------------------";
    qDebug()<<"Obiekt nr "<<counter<<" randomKey:"<<structure->randomKey<<
              " randomChar:"<<structure->randomChar<<" float(1000+id)"<<structure->totallyNotInt;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime t;
    t.start();

    int N = 0;
    char X = 0;
    FILE* fp = fopen("inlab01.txt", "r");
    if (!fp)
        return -1;
    fscanf (fp, "%d %c", &N, &X);
    fclose(fp);

    srand(uint(t.secsTo(QTime(23,59))));

    Struktura** tab = allocAndInit(N);
    qDebug()<<"Created "<<N<<" randomized structures.";

    bubbleSort(tab,N);
    qDebug()<<"Sorted strucures. Displaying top 20:";

    for(int i=0; i<20; i++)
    {
        printStructure(tab[i], i+1);
    }
//    X= static_cast<char>(65);
    int count = findNumeberOfObjectsWithChar(tab, X, N);
    qDebug()<<"Number of objects with char "<<X<<" is "<< count;

    freeStruktury(tab, N);
    qDebug()<<"Structures freed.";

    qDebug()<<"Time elapsed: "<<t.elapsed()<<"ms";



    return a.exec();
}
