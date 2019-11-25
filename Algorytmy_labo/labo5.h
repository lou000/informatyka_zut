#ifndef LABO5_H
#define LABO5_H
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

#endif // LABO5_H
