#include "labo6.h"
#include "math.h"
#include <random>
#include <QTime>
#include <vector>

void countSort(int* array, int size)
{
    int MAX = 0;
    for(int i=0; i<size; i++)
        if(array[i]>MAX)
            MAX = array[i];
    int* temp = new int[size+1];
    int* count = new int[MAX+1];
    for(int i=0; i<=MAX; i++)
        count[i] = 0;
    for(int i = 0; i<size; i++)
        count[array[i]]+=1;
    for(int i=1; i<=MAX; i++)
        count[i]+=count[i-1];
    for(int i=size-1; i>=0; i--)
    {
        temp[count[array[i]]] = array[i];
        count[array[i]] -= 1;
    }
    for(int i=0; i<size; i++)
    {
        array[i] = temp[i];
    }
    delete[] temp;
    delete[] count;
}
template <class T>
void bucketSort(T* array, int size)
{
    int maxValue = array[0]; //start with first element
    int minValue = array[0];


    std::vector<T> bucket[size];
    for(int i = 0; i<size; i++)
    {
       bucket[int(size % array[i])].push_back(array[i]);
    }
    for(int i = 0; i<size; i++) {
       sort(bucket[i].begin(), bucket[i].end());
    }
    int index = 0;
    for(int i = 0; i<size; i++) {
       while(!bucket[i].empty()) {
          array[index++] = *(bucket[i].begin());
          bucket[i].erase(bucket[i].begin());
       }
    }
}

bool labo7()
{
    QTime t;
    const int MAX_ORDER = 7; // maksymalny rzad wielkosci sortowanych danych
    const int m = static_cast<int>(pow (10 , 7)); // sortowane liczby ze zbioru {0 , ... , m - 1}
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,m-1);

    for ( int o = 1; o <= MAX_ORDER ; o ++)
    {
        qDebug()<<"CZESC PIERWSZA - LICZBY CALKOWITE";
        uint64_t n = static_cast<uint64_t>(pow (10 , o ));
        int* array1 = new int[n];
        for(int i=0; static_cast<uint64_t>(i)<n; i++)
            array1[i] = distribution(generator);
        qDebug()<<"Pierwsze 10 wylosowanych liczb to:";
        for(uint64_t i=0; i<n && i<20; i++)
            printf("%d ", array1[i]);
        printf("\n");

        int* array2 = new int[n];
        int* array3 = new int[n];
        memcpy(array2, array1, n * sizeof(int));
        memcpy(array3, array1, n * sizeof(int));


        t.start();
        countSort(array1, static_cast<int>(n));
        qDebug()<<"Sortowanie przez zliczanie ukończono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<20; i++)
            printf("%d ", array1[i]);
        printf("\n");


        auto lambda = [](const int& x, const int& y){return x>y;};
        MaxHeap<int, decltype(lambda)> heap(lambda, array2, n);
        t.restart();
        heap.sortMax(array2, n);
        qDebug()<<"Sortowanie przez kopcowanie ukończono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<20; i++)
            printf("%d ", array2[i]);
        printf("\n");

        t.restart();
        bucketSort<int>(array3, static_cast<int>(n));
        qDebug()<<"Sortowanie kubełkowe ukonczono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<20; i++)
            printf("%d ", array3[i]);
        printf("\n");



    }
    return true;

}
