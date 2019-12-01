#pragma once
#include <stdio.h>
#include <QDebug>
#include <random>
#include <QTime>

enum Mode{
    DOUBLE_HASH,
    LINEAR_HASH
};

class HashTable
{
public:
    HashTable(int size, Mode mode);
    bool insert(int key);
    bool remove(int key);
    void insertX(int amount);
    int find(int key);
    void displayElements(int start, int stop);

    int seed;

private:
    int hashFunction(int key);
    int secondHashFunction(int key);

    int **table;
    int currentSize;
    int maxSize;
    Mode mode;
    std::default_random_engine generator;
};

bool labo5();



HashTable::HashTable(int size, Mode mode)
{
    this->table = new int* [size];
    for(int i=0; i<size; i++)
    {
        this->table[i] = new int(0);
    }
    this->maxSize = size;
    this->currentSize = 0;
    this->mode = mode;
    this->seed = QTime::currentTime().msec();
    this->generator.seed(seed);
}

int HashTable::hashFunction(int key)
{
    return ((key % 1000)+(2^(key % 10))+1) % 997;
}

int HashTable::secondHashFunction(int key)
{
    return ((3*key) % 19)+1;
}

bool HashTable::insert(int key)
{
    if(currentSize>=maxSize-1)
        return false;
    int index = hashFunction(key);
    int tries = 0;
    int newIndex = 0;

    while(true)
    {
        if(mode == DOUBLE_HASH)
                newIndex = (index + tries * secondHashFunction(key))%maxSize;
        else if(mode == LINEAR_HASH)
                newIndex = (index + tries)%maxSize;
        else
        {
            qDebug()<<"There is no mode"<<mode;
            return false;
        }
        if(*table[newIndex] == key)
            return false;
        if(*table[newIndex]<=0)
        {
            *table[newIndex] = key;
            currentSize++;
            return true;
        }
        tries++;
    }
}

bool HashTable::remove(int key)
{
    int index = find(key);

    if(index<0)
        return false;
    else
    {
        *table[index] = -1;
        currentSize--;
        return true;
    }
}

void HashTable::insertX(int amount)
{
    std::uniform_int_distribution<int> distribution(20000,40000);
    for(int i=0; i<amount; i++)
    {
        int key = distribution(generator);
        if(!insert(key))
            i--;
        if(currentSize>=maxSize)
            break;
    }
    return;
}

int HashTable::find(int key)
{
    int index = hashFunction(key);
    int newIndex = index;
    int tries = 0;
    while(*table[newIndex]!=0)
    {
        if(mode == DOUBLE_HASH)
                newIndex = (index + tries * secondHashFunction(key))%maxSize;
        else if(mode == LINEAR_HASH)
                newIndex = (index + tries)%maxSize;
        else
        {
            qDebug()<<"There is no mode"<<mode;
            return -1;
        }
        if(*table[newIndex]==key)
        {
            return newIndex;
        }
        else if(*table[newIndex] == 0)
            return -1;
        tries++;
    }
    return -1;
}

void HashTable::displayElements(int start, int stop)
{
    if(stop<start)
    {
        qDebug()<<"End of the range is lower then the start.";
        return;
    }
    if(stop>maxSize)
    {
        qDebug()<<"End of the range is greater then size of table.";
        return;
    }

    int index = start;
    qDebug()<<"Displaying indexes from"<<start<<"to"<<stop;
    for(int i=0; i<=stop-start; i++, index++)
    {
        printf_s("%d ", *table[index]);
    }
    qDebug()<<"\n";
    return;
}

bool labo5()
{
    QTime t;
    int X, k1, k2, k3, k4;
    FILE* fp = fopen("inlab05.txt", "r");
    if (!fp)
        return false;
    fscanf (fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
    fclose(fp);

    t.start();
    HashTable* hTable = new HashTable(997, LINEAR_HASH);
    hTable->remove(k1); //25013
    hTable->insert(k1); //25013
    hTable->displayElements(0, 100);
    hTable->insertX(X); //500
    hTable->displayElements(0, 100);
    hTable->insert(k2); //29511
    hTable->insert(k3); //37013
    hTable->insert(k4); //32511
    hTable->displayElements(0, 100);
    hTable->displayElements(500, 600);
    hTable->remove(k3); //37013
    hTable->remove(k4); //32511
    hTable->displayElements(0, 100);
    hTable->displayElements(500, 600);
    qDebug()<<"Time elapsed: "<<t.elapsed()<<"ms";
    qDebug()<<"\n--------------------------------------------------------------------\n";

    t.restart();
    HashTable* hTable2 = new HashTable(5000, DOUBLE_HASH);
    hTable2->remove(k1); //25013
    hTable2->insert(k1); //25013
    hTable2->displayElements(0, 100);
    hTable2->insertX(X); //500
    hTable2->displayElements(0, 100);
    hTable2->insert(k2); //29511
    hTable2->insert(k3); //37013
    hTable2->insert(k4); //32511
    hTable2->displayElements(0, 100);
    hTable2->displayElements(500, 600);
    hTable2->remove(k3); //37013
    hTable2->remove(k4); //32511
    hTable2->displayElements(0, 100);
    hTable2->displayElements(500, 600);
    qDebug()<<"Time elapsed: "<<t.elapsed()<<"ms";
    return true;
}











