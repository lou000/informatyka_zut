#include "labo6.h"
#include <random>
#include <math.h>
#include <stdio.h>
#include <QTime>

class Example
{
public:
    int integer;
};

bool labo6()
{
    QTime t;
    const int MAX_ORDER = 7;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(20000,40000);

    auto lambda = [](const Example& x, const Example& y){return x.integer<y.integer;};
    MaxHeap<Example, decltype(lambda)> heap(static_cast<uint64_t>(pow(10, MAX_ORDER)), lambda);
    t.start();
    for(int i=0; i<= MAX_ORDER; i++)
    {
        const int n = static_cast<int>(pow(10, i));
        t.restart();
        for(int j=0; j<n; j++)
        {
            Example ex;
            ex.integer = distribution(generator);
            heap.add_element(ex);
        }
        qDebug()<<"Dodano"<<n<<"elementow"<<"w czasie"<<t.elapsed()<<"ms";
//      WYPISYWANIE DO KONSOLI TEJ LICZBY ELEMENTOW JEST ZBYT WOLNE
//        uint64_t index = 0;
//        for(int i=1; i<log2(n+1); i++)
//        {
//            for(int j=0; j<pow(2, (i-1))-1;j++)
//            {
//                printf("%d ", heap.get(index).integer);
//                index++;
//            }
//            printf("\n");
//        }
        t.restart();
        for(int j=0; j<n; j++)
        {
            heap.pop();
        }
        qDebug()<<"Usunieto"<<n<<"elementow"<<"w czasie"<<t.elapsed()<<"ms";
        heap.clear();
    }
    return true;
}
