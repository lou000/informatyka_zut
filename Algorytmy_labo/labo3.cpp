#include "labo3.h"

binTreeNode::binTreeNode(int key)
{
    this->key = key;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    snprintf(tab, sizeof (tab), "%d", key);
}

binTree::binTree()
{
    this->head = nullptr;
    this->generator.seed(QTime::currentTime().msec());
}

//bool binTree::addNodeRecursive(int key, binTreeNode* node)
//{
//    if(this->head == nullptr)
//    {
//        this->head = new binTreeNode(key);
//        return true;
//    }
//    else if(node->key>key)
//    {
//        if(node->leftChild == nullptr)
//            addNodeRecursive(key, node->leftChild);
//        else
//        {
//            node->leftChild = new binTreeNode(key);
//            return true;
//        }
//    }
//    else if(node->key<key)
//    {
//        if(node->rightChild == nullptr)
//            addNodeRecursive(key, node->rightChild);
//        else
//        {
//            node->rightChild = new binTreeNode(key);
//            return true;
//        }
//    }
//    else if(node->key == key)
//        return false;
//    return false;
//}

bool binTree::addNode(int key)
{
    if(this->head == nullptr)
    {
        this->head = new binTreeNode(key);
        return true;
    }
    binTreeNode* temp = this->head;
    binTreeNode* prev = nullptr;
    while(temp!=nullptr)
    {
        prev = temp;
        if(temp->key == key)
            return false;
        else if(temp->key>key)
            temp = temp->leftChild;
        else if(temp->key<key)
            temp = temp->rightChild;
    }
    if(prev->key>key)
        prev->leftChild = new binTreeNode(key);
    else
        prev->rightChild = new binTreeNode(key);
//    qDebug()<<"Dodano klucz"<<key;
    return true;
}

void binTree::addRandom(int amount)
{
    std::uniform_int_distribution<int> distribution(-10000,10000);
    for(int i=0; i<amount; i++)
    {
        if(!addNode(distribution(generator)))
            i--;
    }
}

//binTreeNode* binTree::findNodeRecursive(int key, binTreeNode* node)
//{
//    if(node == nullptr)
//        return nullptr;
//    else if(node->key == key)
//        return node;
//    else if(node->key>key)
//        findNodeRecursive(key, node->leftChild);
//    else if(node->key<key)
//        findNodeRecursive(key, node->rightChild);
//    return nullptr;
//}

binTreeNode* binTree::findNode(int key)
{
    binTreeNode* temp = head;
    while(temp!=nullptr)
    {
        if(temp->key == key)
            return temp;
        else if(temp->key>key)
            temp = temp->leftChild;
        else if(temp->key<key)
            temp = temp->rightChild;
    }
    return nullptr;
}

bool binTree::removeNode(int key)
{
    binTreeNode* prevNode = nullptr;
    binTreeNode* temp = head;
    while(temp!=nullptr)
    {
        if(head == nullptr)
            return false;
        else if(temp->key == key)
        {
            if(temp->leftChild == nullptr && temp->rightChild == nullptr)
            {
                delete temp;
                return true;
            }
            else if(temp->leftChild == nullptr)
            {
                if(temp == head)
                {
                    head = head->rightChild;
                    delete temp;
                    return true;
                }
                if(prevNode->leftChild == temp)
                    prevNode->leftChild = temp->rightChild;
                else
                    prevNode->rightChild = temp->rightChild;
                delete temp;
                return true;
            }
            else if(temp->rightChild == nullptr)
            {
                if(temp == head)
                {
                    head = head->leftChild;
                    delete temp;
                    return true;
                }
                if(prevNode->leftChild == temp)
                    prevNode->leftChild = temp->leftChild;
                else
                    prevNode->rightChild = temp->leftChild;
                delete temp;
                return true;
            }
            else
            {

                binTreeNode* prev = temp;
                binTreeNode* temp1 = temp->leftChild;
                while (temp1->rightChild != nullptr)
                {
                    prev = temp1;
                    temp1 = temp1->rightChild;
                }
                binTreeNode* predecesor = nullptr;
                if(prev == temp)
                {
                    predecesor = prev->leftChild;
                    temp->key = predecesor->key;
                    strcpy(temp->tab, predecesor->tab);
                    prev->leftChild = predecesor->leftChild;
                    delete predecesor;
                    return true;
                }
                else
                {
                    predecesor = prev->rightChild;
                    if (predecesor->leftChild == nullptr)
                    {
                        temp->key = predecesor->key;
                        strcpy(temp->tab, predecesor->tab);
                        prev->rightChild = nullptr;
                        delete predecesor;
                        return true;
                    }
                    else
                    {
                        temp->key = predecesor->key;
                        strcpy(temp->tab, predecesor->tab);
                        prev->rightChild = predecesor->leftChild;
                        delete predecesor;
                        return true;
                    }
                }
            }
        }
        else if(temp->key > key)
        {
            prevNode = temp;
            temp = temp->leftChild;
        }
        else if(temp->key < key)
        {
            prevNode = temp;
            temp = temp->rightChild;
        }
    }
    return false;
}

void binTree::displayPreorder(binTreeNode* node1)
{
    qDebug()<<"Preorder";
    int counter = -1;
    std::function<void(binTreeNode*)> recursive = [&](binTreeNode* node)->void
    {
        if(!node)
            return;
        counter++;
        printf("%d ", node->key);
        recursive(node->leftChild);
        recursive(node->rightChild);
    };

    recursive(node1);
    qDebug()<<"\nLiczba odwiedzonych wezlow:"<<counter<<"\n";
}



void binTree::displayPostorder(binTreeNode* node1)
{
    int counter = -1;
    qDebug()<<"Postorder";
    std::function<void(binTreeNode*)> recursive = [&](binTreeNode* node)->void
    {
        if(!node)
            return;
        counter++;
        recursive(node->leftChild);
        recursive(node->rightChild);
        printf("%d ", node->key);
    };

    recursive(node1);
    qDebug()<<"\nLiczba odwiedzonych wezlow:"<<counter<<"\n";
}

void binTree::displayInorder(binTreeNode* node1)
{
    qDebug()<<"Inorder";
    int counter = -1;
    std::function<void(binTreeNode*)> recursive = [&](binTreeNode* node)->void
    {
        if(!node)
            return;
        counter++;
        recursive(node->leftChild);
        printf("%d ", node->key);
        recursive(node->rightChild);
    };

    recursive(node1);
    qDebug()<<"\nLiczba odwiedzonych wezlow:"<<counter<<"\n";
}

bool labo3()
{
    QTime t;
    int X, k1, k2, k3, k4;
    FILE* fp = fopen("inlab03.txt", "r");
    if (!fp)
        return false;
    fscanf (fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
    fclose(fp);

    t.start();
    binTree* tree = new binTree();
    tree->removeNode(k1);
    tree->addNode(k1);
    tree->addRandom(X);
    tree->displayInorder(tree->head);
    tree->displayPreorder(tree->head);
    tree->addNode(k2);
    tree->displayInorder(tree->head);
    tree->addNode(k3);
    tree->addNode(k4);
    tree->removeNode(k1);
    tree->displayPreorder(tree->head);
    tree->findNode(k1);
    tree->removeNode(k2);
    tree->displayInorder(tree->head);
    tree->removeNode(k3);
    tree->removeNode(k4);
    qDebug()<<"Time elapsed: "<<t.elapsed()<<"ms";

    return true;
}
