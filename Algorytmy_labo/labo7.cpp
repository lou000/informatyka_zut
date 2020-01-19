#include "labo6.h"
#include "math.h"
#include <random>
#include <QTime>
#include <vector>

void countSort(int* array, int size)
{
    int MAX = array[0];
    int MIN = array[0];

    for(int i=1; i<size; i++)
    {
        if(array[i]<MIN)
            MIN = array[i];
        if(array[i]>MAX)
            MAX = array[i];
    }
    int countSize = MAX-MIN+1;
    int* count = new int[countSize];
    for(int i=0; i< countSize; i++)
        count[i] = 0;

    for(int i = 0; i<size; i++)
        count[array[i]-MIN]++;

    int l=0;
    for(int i=0; i<countSize; i++)
    {
        int j =0;
        for(j=l; j<count[i]+l; j++)
        {
            array[j]=i+MIN;
        }
        l=j;
    }
    delete[] count;
}

template <class T>
void bucketSort(T* array, int size)
{
    int bucketSize = 0;
    int MIN = static_cast<int>(ceil(array[0]));
    int MAX = static_cast<int>(ceil(array[0]));
    for(int i=0; i<size; i++)
    {
        if(array[i]<MIN)
            MIN = static_cast<int>(ceil(array[i]));
        if(array[i]>MAX)
            MAX = static_cast<int>(ceil(array[i]));
    }

    if((floor(array[0])-array[0])!=0)
        bucketSize = MAX*size;
    else
        bucketSize = MAX-MIN+1;

    std::vector<T> *bucket = new std::vector<T>[bucketSize];
    auto lambda = [](const T& x, const T& y){return x>y;};

    if((floor(array[0])-array[0])!=0)
        for(int i = 0; i<size; i++)
        {
           uint64_t index = static_cast<uint64_t>(size*array[i]);
           bucket[index].push_back(array[i]);
        }
    else
    {
        for(int i = 0; i<size; i++)
        {
           bucket[int(array[i]-MIN)].push_back(array[i]);
        }
    }
    for(int i = 0; i<size; i++) {
       sort(bucket[i].begin(), bucket[i].end(), lambda);
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

    qDebug()<<"\nCZESC PIERWSZA - LICZBY CALKOWITE";
    qDebug()<<"---------------------------------\n";
    for ( int o = 1; o <= MAX_ORDER-2 ; o ++)
    {
        uint64_t n = static_cast<uint64_t>(pow (10 , o ));
        int* array1 = new int[n];
        for(int i=0; static_cast<uint64_t>(i)<n; i++)
            array1[i] = distribution(generator);
        qDebug()<<"Pierwsze 10 wylosowanych liczb to:";
        for(uint64_t i=0; i<n && i<10; i++)
            printf("%d ", array1[i]);
        printf("\n\n");

        int* array2 = new int[n];
        int* array3 = new int[n];
        memcpy(array2, array1, n * sizeof(int));
        memcpy(array3, array1, n * sizeof(int));


        t.start();
        countSort(array1, static_cast<int>(n));
        qDebug()<<"Sortowanie przez zliczanie ukonczono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<10; i++)
            printf("%d ", array1[i]);
        printf("\n\n");


        auto lambda = [](const int& x, const int& y){return x>y;};
        MaxHeap<int, decltype(lambda)> heap(lambda, array2, n);
        t.restart();
        heap.sortMax(array2, n);
        qDebug()<<"Sortowanie przez kopcowanie ukonczono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<10; i++)
            printf("%d ", array2[i]);
        printf("\n\n");

        t.restart();
        bucketSort<int>(array3, static_cast<int>(n));
        qDebug()<<"Sortowanie kubelkowe ukonczono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<10; i++)
            printf("%d ", array3[i]);
        printf("\n\n");
    }


    qDebug()<<"CZESC DRUGA - LICZBY DOUBLE";
    qDebug()<<"---------------------------------\n";
    const double help_me = static_cast<double>(pow(2, 20));
    for ( int o = 1; o <= MAX_ORDER-2 ; o ++)
    {
        uint64_t n = static_cast<uint64_t>(pow (10 , o ));
        double* array1 = new double[n];
        for(int i=0; static_cast<uint64_t>(i)<n; i++)
            array1[i] = distribution(generator)/help_me;
        qDebug()<<"Pierwsze 10 wylosowanych liczb to:";
        for(uint64_t i=0; i<n && i<10; i++)
            printf("%f ", array1[i]);
        printf("\n\n");

        double* array2 = new double[n];
        memcpy(array2, array1, n * sizeof(double));


        auto lambda = [](const double& x, const double& y){return x<y;};
        MaxHeap<double, decltype(lambda)> heap(lambda, array1, n);
        t.restart();
        heap.sortMax(array1, n);
        qDebug()<<"Sortowanie przez kopcowanie ukonczono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<10; i++)
            printf("%f ", array1[i]);
        printf("\n\n");

        t.restart();
        bucketSort<double>(array2, static_cast<int>(n));
        qDebug()<<"Sortowanie kubelkowe ukonczono w"<<t.elapsed()<<"ms";
        for(uint64_t i=0; i<n && i<10; i++)
            printf("%f ", array2[i]);
        printf("\n\n");
    }
    return true;

}
