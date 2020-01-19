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
    MaxHeap<Example, decltype(lambda)> heap(lambda);
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
        int it=0;
        int index = 0;
        while(index<n)
        {
            for(int i = 0;i < pow(2, it) && index<n; i++)
            {
                printf("%d ", heap.get(index).integer);
                index++;
            }
            printf("\n");
            it++;
        }
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
