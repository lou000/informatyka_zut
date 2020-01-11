#include "labo6.h"
#include <random>
#include <math.h>
#include <stdio.h>
class Example
{
public:
    int integer;
};

bool labo6()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(20000,40000);

    auto lambda = [](const Example& x, const Example& y){return x.integer<y.integer;};
    MaxHeap<Example, decltype(lambda)> heap(60, lambda);
    Example ex;
    ex.integer = 5;
    heap.add_element(ex);
    heap.print();
    heap.clear();
    for(int i=0; i<50; i++)
    {
        Example temp;
        temp.integer = distribution(generator);
        heap.add_element(temp);
    }

    uint64_t index = 0;
    for(int i=1; i<log2(50+1); i++)
    {
        for(int j=0; j<pow(2, (i-1));j++)
        {
            printf("%d ", heap.get(index).integer);
            index++;
        }
        printf("\n");
    }
    return true;
}
