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
