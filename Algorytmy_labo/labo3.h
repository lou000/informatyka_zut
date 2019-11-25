#pragma once
#include <stdio.h>
#include <random>
#include <QDebug>
#include <QTime>

class binTreeNode{
    friend class binTree;
    friend class BalancedBST;
public:
    int key;
    char tab[10];
private:
    binTreeNode(int key);
    binTreeNode* leftChild;
    binTreeNode* rightChild;
};

class binTree{
public:
    binTree();
    binTreeNode* head;
//    bool addNodeRecursive(int index, binTreeNode* head);
    bool addNode(int index);
    void addRandom(int amount);
//    binTreeNode* findNodeRecursive(int index, binTreeNode* head);
    binTreeNode* findNode(int index);
    bool removeNode(int index);
    int displayPreorder(binTreeNode* head);
    int displayPostorder(binTreeNode* head);
    int displayInorder(binTreeNode* head);
private:
    std::default_random_engine generator;
};

bool labo3();
