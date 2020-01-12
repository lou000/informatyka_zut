// ALGO2 IN1 20B LAB06
// LEWICKI MACIEJ
// LM34410@ZUT.EDU.PL
#pragma once
#include <functional>
#include <QDebug>
#include <stdexcept>

template <typename T = int, typename MHComp = std::less<T>>
class MaxHeap
{
public:
    MaxHeap(uint64_t max_size, MHComp comp):compare(comp), max_heapsize(max_size)
    {
        data = new T[max_size];
    }
private:
    MHComp compare;
    T* data;
    uint64_t heapsize = 0;
    uint64_t max_heapsize;

public:
    bool add_element(T item)
    {
        if(heapsize>=max_heapsize)
            return false;
        data[heapsize] = item;
        heapsize++;
        heap_up(heapsize-1);
        return true;
    }
    T pop()
    {
        if(heapsize<1)
            throw std::logic_error("Heap is empty");
        T temp = data[0];
        swap(heapsize-1, 0);
        heapsize--;
        heap_down(0);
        return temp;
    }

    T get(uint64_t index)
    {
        if(index>=0 && index<heapsize)
        {
            return data[index];
        }
        else throw std::logic_error("Index out of range");
    }

    void clear()
    {
        heapsize = 0;
    }
    void print()
    {
        for(uint64_t i = 0; i<heapsize; i++)
        {
            qDebug()<<"Element at index"<<i<<"="<<&data[i];
        }
    }

private:
    void swap(uint64_t index1, uint64_t index2)
    {
        T temp = data[index1];
        data[index1] = data[index2];
        data[index2] = temp;
    }

    void heap_down(uint64_t index)
    {
        uint64_t left = 2 * index + 1;
        uint64_t right = 2 * index + 2;

        if (left < heapsize && compare(data[left], data[index]) && compare(data[left], data[right]))
        {
            swap(index, left);
            heap_down(left);
        }

        else if (right < heapsize && compare(data[right], data[index]))
        {
            swap(index, right);
            heap_down(right);
        }
    }

    void heap_up(uint64_t index)
    {
        int parent = (index - 1)/2;
        if(index && compare(data[parent],data[index]))
        {
            swap(index, parent);
            heap_up(parent);
        }
    }
};
bool labo6();

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
