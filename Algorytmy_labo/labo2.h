#pragma once
#include <random>
#include <QDebug>
#include <QTime>

class skipNode
{
    friend class skipList;

public:
    int key;
    double someValue;
    char someChar;
private:
    skipNode** nextNode;
};

class skipList
{
public:
    skipList(int maxHeight, float P);
    bool addNode(int key);
    void addRandomNodes(int numberOfNodes);
    skipNode* findNode(int key);
    bool removeNode(int key);
    void printNodes(int numberOfNodes, int minHeight);
    int countNodes(int height);
    void clearList();
private:
    int maxHeight;
    float P;
    int currentHeight;
    skipNode* head;
    skipNode* tail;
    std::default_random_engine generator;
};

bool labo2();
