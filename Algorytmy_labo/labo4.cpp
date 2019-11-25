#include "labo4.h"

void BalancedBST::rotate_right(binTreeNode* grandfather, binTreeNode* parent, binTreeNode* child)
{
    if(grandfather!=nullptr)
    {
        if(grandfather->rightChild == parent)
            grandfather->rightChild = child;
        else
            grandfather->leftChild = child;
    }
    else
        head = child;
    auto temp = child->rightChild;
    child->rightChild = parent;
    parent->leftChild = temp;
    return;
}

void BalancedBST::rotate_left(binTreeNode* grandfather, binTreeNode* parent, binTreeNode* child)
{
    if(grandfather!=nullptr)
    {
        if(grandfather->rightChild == parent)
            grandfather->rightChild = child;
        else
            grandfather->leftChild = child;
    }
    else
        head = child;
    auto temp = child->leftChild;
    child->leftChild = parent;
    parent->rightChild = temp;
    return;
}

void BalancedBST::balance_tree(int numberOfNodes)
{
    binTreeNode* grandfather = nullptr;
    auto temp = head;
    while(temp!=nullptr)
    {
        if(temp->leftChild!=nullptr)
        {
            auto temp2 = temp->leftChild;
            rotate_right(grandfather, temp, temp->leftChild);
            temp = temp2;
        }
        else
        {
            grandfather = temp;
            temp = temp->rightChild;
        }
    }

    grandfather = nullptr;
    temp = head;
    int m = 1;
    while(m<=numberOfNodes)
        m=2*m+1;
    m = m/2;
    for(int i=0; i<numberOfNodes-m; i++)
    {
        auto temp2 = temp->rightChild;
        if(temp2 != nullptr)
        {
            rotate_left(grandfather, temp, temp->rightChild);
            grandfather = temp2;
            temp = temp2->rightChild;
        }
    }
    while(m>1)
    {
        m = m/2;
        grandfather = nullptr;
        temp = head;
        for(int i=0; i<m; i++)
        {
            auto temp2 = temp->rightChild;
            rotate_left(grandfather, temp, temp->rightChild);
            grandfather = temp2;
            temp = temp2->rightChild;
        }
    }
}

int BalancedBST::treeHeight(binTreeNode* node)
{
    if (node == nullptr)
        return 0;
    else
    {
        int leftBranch = treeHeight(node->leftChild);
        int rightBranch = treeHeight(node->rightChild);

        if (leftBranch > rightBranch)
            return(leftBranch + 1);
        else return(rightBranch + 1);
    }
}

void BalancedBST::clearTree(binTreeNode *node1)
{
    std::function<void(binTreeNode*)> recursive = [&](binTreeNode* node)->void
    {
        if(node==nullptr)
            return;
        recursive(node->leftChild);
        recursive(node->rightChild);
        delete node;
    };
    recursive(node1);
    head = nullptr;
}

int BalancedBST::countNodes(binTreeNode* node1)
{
    int counter = 0;
    std::function<void(binTreeNode*)> recursive = [&](binTreeNode* node)->void
    {
        if(node==nullptr)
            return;
        counter++;
        recursive(node->leftChild);
        recursive(node->rightChild);
    };
    recursive(node1);
    return counter;
}

bool labo4()
{
    QTime t;
    int X1, X2;
    FILE* fp = fopen("inlab04.txt", "r");
    if (!fp)
        return false;
    fscanf (fp, "%d %d", &X1, &X2);
    fclose(fp);

    t.start();
    BalancedBST* tree = new BalancedBST();
    tree->addRandom(X1);
    int numberOfNodes = tree->countNodes(tree->head);
    printf("Wysokosc drzewa : %d\n", tree->treeHeight(tree->head));
    tree->balance_tree(numberOfNodes);
    printf("Wysokosc po balansowaniu : %d\n", tree->treeHeight(tree->head));
    tree->clearTree(tree->head);
    tree->addRandom(X2);
    numberOfNodes = tree->countNodes(tree->head);
    printf("Wysokosc drzewa : %d\n", tree->treeHeight(tree->head));
    tree->balance_tree(numberOfNodes);
    printf("Wysokosc po balansowaniu : %d\n", tree->treeHeight(tree->head));
    qDebug()<<"Time elapsed: "<<t.elapsed()<<"ms";
    return true;
}
