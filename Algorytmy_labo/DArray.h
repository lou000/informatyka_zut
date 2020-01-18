#pragma once
#include <cstdlib>
#include <cstring>
#include <array>
template<class item>
class DArray
{
public:
    DArray()
    {
        maxSize = startSize;
        currentSize = 0;
        data = static_cast<item*>(malloc(byteSize()));
        if(data == nullptr)
            throw std::bad_alloc();
        memset(data, 0, sizeof (byteSize()));
    }
    ~DArray()
    {
        free(data);
        data = nullptr;
    }
    DArray(const DArray &a)
    {
        data = static_cast<item*>(malloc(a.maxSize*sizeof (item)));
        if(data == nullptr)
            throw std::bad_alloc();
        maxSize = a.maxSize;
        currentSize = a.currentSize;
        memcpy(data, a.data, a.maxSize*sizeof (item));
    }
    item& operator[](unsigned int index);
    item const& operator[](unsigned int index) const noexcept
    {
        if(index>currentSize-1)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    item& at(unsigned int index)
    {
        if(index>currentSize-1)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    DArray& operator = (const DArray &a)
    {
        if(this == &a)
            return this;
        if(a.currentSize == 0)
            clear();
        setMaxSize(a.maxSize);
        memcpy(data, a.data, a.byteSize());
        return *this;
    }
    void append(const item &i)
    {
        if(currentSize+1>maxSize)
        {
            maxSize = maxSize*sizeMultiplier;
            data = static_cast<item*>(realloc(data, byteSize()));
            if(data == nullptr)
                throw std::bad_alloc();
        }
        data[currentSize] = i;
        currentSize++;
    }
    void clear()
    {
        currentSize = 0;
        setMaxSize(startSize);
        memset(data, 0, sizeof (byteSize()));
    }
    void remove(unsigned int index)
    {
        if(index>currentSize-1)
            throw std::out_of_range("Index out of range, max index is %d", currentSize-1);
        for(unsigned int i=index; i<currentSize-1; i++)
            data[i] = data[i+1];
        memset(&data[currentSize], 0, sizeof(item));
        currentSize--;
    }
    unsigned int size(){return currentSize;}

private:
    item* data;
    unsigned int maxSize;
    unsigned int currentSize;
    unsigned int startSize = 64;
    unsigned int sizeMultiplier = 2;
    void setMaxSize(unsigned int s)
    {
        if(s < startSize)
            s = startSize;
        if(s>maxSize || s<maxSize/2)
        {
            data = static_cast<item*>(realloc(data, s*sizeof (item)));
            if(data == nullptr)
                throw std::bad_alloc();
        }

    }
    unsigned int byteSize(){return maxSize*sizeof(item);}

};

template <class item>
item& DArray<item>::operator[](unsigned int index)
{
    if(index>currentSize-1)
        throw std::out_of_range("Index out of range");
    return data[index];
}
