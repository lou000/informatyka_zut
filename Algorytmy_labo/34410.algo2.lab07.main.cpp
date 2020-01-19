// ALGO2 IN1 20B LAB07
// LEWICKI MACIEJ
// LM34410@ZUT.EDU.PL
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
    item& operator [] (unsigned int index);
    item const& operator [] (unsigned int index) const;

    item& at(unsigned int index)
    {
        if(index>currentSize-1)
            throw std::out_of_range("Index out of range, DArray::at()");
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
    void addArray(item *array, unsigned int size)
    {
        while (maxSize-currentSize<size)
        {
            maxSize = maxSize*sizeMultiplier;
            data = static_cast<item*>(realloc(data, byteSize()));
            if(data == nullptr)
                throw std::bad_alloc();
        }
        memcpy(&data[currentSize], array, size*sizeof (item));
        currentSize = currentSize + size;
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
            throw std::out_of_range("Index out of range, DArray::remove()");
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
        maxSize = s;
    }
    unsigned int byteSize(){return maxSize*sizeof(item);}

};

template <class item>
item& DArray<item>::operator [](unsigned int index)
{
    if(index>currentSize-1)
        throw std::out_of_range("Index out of range, DArray::operator[]");
    return data[index];
}

template <class item>
item const& DArray<item>::operator [](unsigned int index) const
{
    if(index>currentSize-1)
        throw std::out_of_range("Index out of range, DArray::operator[] const");
    return data[index];
}




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
