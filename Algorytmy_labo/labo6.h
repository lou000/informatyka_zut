#pragma once
#include <functional>
#include <QDebug>
#include <stdexcept>
#include "DArray.h"

template <typename T = int, typename MHComp = std::less<T>>
class MaxHeap
{
public:
    MaxHeap(MHComp comp):compare(comp){}
    MaxHeap(MHComp comp, T* array, uint64_t size):compare(comp)
    {
        data.addArray(array, size);
        for (int i = data.size()/2-1; i >= 0; i--)
           heap_down(i);
    }
    ~MaxHeap()
    {
        data.clear();
    }
private:
    MHComp compare;
    DArray<T> data;

public:
    bool add_element(T item)
    {
        data.append(item);
        heap_up(data.size()-1);
        return true;
    }
    T pop()
    {
        if(data.size()<1)
            throw std::logic_error("Heap is empty");
        T temp = data[0];
        swap(data.size()-1, 0);
        data.remove(data.size()-1);
        heap_down(0);
        return temp;
    }

    T get(uint64_t index)
    {
        if(index>=0 && index<data.size())
        {
            return data[index];
        }
        else throw std::logic_error("Index out of range");
    }

    void clear()
    {
        data.clear();
    }
    void print()
    {
        for(uint64_t i = 0; i<data.size(); i++)
        {
            qDebug()<<"Element at index"<<i<<"="<<&data[i];
        }
    }
    void sortMax(T* array, uint64_t size)
    {
        if(size == data.size())
        {
            for(uint64_t i = 0; i<size; i++)
                array[i] = pop();
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
        uint64_t largest = index;
        uint64_t left = 2 * index + 1;
        uint64_t right = 2 * index + 2;

        if (left < data.size() && compare(data[left], data[largest]))
            largest = left;

        if (right < data.size() && compare(data[right], data[largest]))
            largest = right;

        if (largest != index)
        {
            swap(index, largest);
            heap_down(largest);
        }
    }

    void heap_up(uint64_t index)
    {
        uint64_t parent = (index - 1)/2;
        if(index && compare(data[parent],data[index]))
        {
            swap(index, parent);
            heap_up(parent);
        }
    }
};
bool labo6();
