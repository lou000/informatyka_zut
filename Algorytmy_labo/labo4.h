#pragma once
#include "labo3.h"

class BalancedBST : public binTree
{
public:
    void rotate_right(binTreeNode* grandfather, binTreeNode* parent, binTreeNode* child);
    void rotate_left(binTreeNode* grandfather, binTreeNode* parent, binTreeNode* child);
    void balance_tree(int numberOfNodes);
    void clearTree(binTreeNode* node);
    int treeHeight(binTreeNode* node);
    int countNodes(binTreeNode* node);
};

bool labo4();
