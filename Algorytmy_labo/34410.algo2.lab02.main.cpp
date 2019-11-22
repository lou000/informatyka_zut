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
    std::default_random_engine generator;
};

bool labo2();

skipList::skipList(int maxH, float p)
{
    this->maxHeight = maxH;
    this->P = p;
    this->currentHeight = 0;
    this->head = new skipNode();
    head->key = -1;
    head->nextNode = new skipNode* [maxHeight];
    for(int i=0; i<maxHeight; i++)
    {
        head->nextNode[i] = nullptr;
    }

}

bool skipList::addNode(int key)
{
    if(key<=0)
        return false;
    std::uniform_real_distribution<double> distribution(-100,100);
    skipNode** listToUpdate = new skipNode* [maxHeight];
    for(int i=0; i<maxHeight; i++)
    {
        listToUpdate[i] = nullptr;
    }

    skipNode* currentNode = head;

    for(int i=currentHeight; i>=0; i--)
    {
        while(currentNode->nextNode[i] != nullptr && currentNode->nextNode[i]->key < key)
        {
            currentNode = currentNode->nextNode[i];
        }
        listToUpdate[i] = currentNode;
    }

    currentNode = currentNode->nextNode[0];

    if(currentNode==nullptr || currentNode->key != key)
    {
        float random = static_cast<float>(rand())/RAND_MAX;
        int height = 0;
        while (random < P && height < maxHeight-1)
        {
            height++;
            random = static_cast<float>(rand())/RAND_MAX;
        }
        if(height>currentHeight)
        {
            for(int i = currentHeight+1; i<height+1;i++)
            {
                listToUpdate[i] = head;
            }
            currentHeight = height;
        }
        skipNode* node = new skipNode();
        node->key = key;
        node->someChar = 'T';
        node->someValue = distribution(generator);
        node->nextNode = new skipNode* [maxHeight];
        for(int i=0; i<maxHeight; i++)
        {
            node->nextNode[i] = nullptr;
        }
        for(int i=0; i<=height; i++)
        {
            node->nextNode[i] = listToUpdate[i]->nextNode[i];
            listToUpdate[i]->nextNode[i] = node;
        }
//        qDebug()<<"Node with key "<<node->key<<" inserted.";
        return true;
    }
    else if(currentNode!=nullptr && currentNode->key == key)
    {
        currentNode->someChar = 'D';
//        qDebug()<<"Node with that key already exists. Setting someChar to \"D\"";
        return false;
    }
    else
    {
        qDebug()<<"How did we get here?";
        return false;
    }
}
void skipList::addRandomNodes(int numberOfNodes)
{
    if(numberOfNodes>99900)
        numberOfNodes = 99900;
    std::uniform_int_distribution<int> distribution(99,99999);
    for(int i=0; i<numberOfNodes; i++)
    {
        if(!addNode(distribution(generator)))
            i--;
    }
}

skipNode* skipList::findNode(int key)
{
    if(key<=0)
        return nullptr;
    skipNode* currentNode = head;
    int height = currentHeight;

    while(currentNode->key!=key && !(currentNode->nextNode[height]==nullptr && height<=0))
    {
        if(currentNode->nextNode[height]==nullptr || currentNode->nextNode[height]->key>key)
            height--;
        else
            currentNode = currentNode->nextNode[height];
    }
    if(currentNode->key == key)
        return currentNode;
    else return nullptr;
}

bool skipList::removeNode(int key)
{
    if(key<=0)
        return false;
    int height = currentHeight;
    skipNode* currentNode = head;
    skipNode* foundNode = nullptr;
    skipNode** nodesAfter = new skipNode* [maxHeight];
    for(int i=0; i<maxHeight; i++)
    {
        nodesAfter[i] = nullptr;
    }

    while(!(currentNode->nextNode[height]==nullptr && height==0) && foundNode==nullptr)
    {
        if(currentNode->nextNode[height]!=nullptr && currentNode->nextNode[height]->key == key)
            foundNode = currentNode->nextNode[height];
        else if(currentNode->nextNode[height]==nullptr || currentNode->nextNode[height]->key>key)
            height--;
        else if(currentNode->nextNode[height]->key!=key)
            currentNode = currentNode->nextNode[height];
    }

    if(foundNode)
    {
        nodesAfter = currentNode->nextNode[height]->nextNode;
        for(int i=height; i>=0; i--)
        {
            while(currentNode->nextNode[i]!=foundNode)
                currentNode = currentNode->nextNode[i];
            currentNode->nextNode[i] = nodesAfter[i];
        }
        qDebug()<<foundNode->key<<"removed";
        delete foundNode;
        return true;
    }
    else
    {
        return false;
    }
}

void skipList::printNodes(int numberOfNodes, int minHeight)
{
    int emptyCount = -1;
    for(int i=minHeight; i>=0; i--)
    {
        if(head->nextNode[i]!=nullptr)
        {
            skipNode* currentNode = head->nextNode[i];
            qDebug()<<"LEVEL"<<i<<"\n--------------------------------------------------------------------------------";
            for(int j=0; j<numberOfNodes && currentNode!=nullptr; j++)
            {
                if(currentNode->nextNode[i]!=nullptr && j<numberOfNodes-1)
                    printf("%d-->", currentNode->key);
                else
                    printf("%d", currentNode->key);
                currentNode = currentNode->nextNode[i];
            }
            qDebug()<<"\n--------------------------------------------------------------------------------\n";
        }
        else
        {
            emptyCount++;
        }
    }
    if(emptyCount==minHeight)
        qDebug()<<"List is empty.";
}

int skipList::countNodes(int height)
{
    skipNode* currentNode = head->nextNode[height];
    int count = 0;
    while(currentNode!=nullptr)
    {
        count++;
        currentNode = currentNode->nextNode[height];
    }
    return count;
}

void skipList::clearList()
{
    skipNode* currentNode = head->nextNode[0];
    while(currentNode!=nullptr)
    {
        skipNode* previousNode = currentNode;
        currentNode = currentNode->nextNode[0];
        delete previousNode;
    }
    for(int i=0; i<maxHeight; i++)
    {
        head->nextNode[i] = nullptr;
    }
}

bool labo2()
{
    QTime t;
    int X, LMAX, k1, k2, k3, k4, k5;
    FILE* fp = fopen("inlab02.txt", "r");
    if (!fp)
        return false;
    fscanf (fp, "%d %d %d %d %d %d %d", &X, &LMAX, &k1, &k2, &k3, &k4, &k5);
    fclose(fp);

    t.start();
    skipList* lista = new skipList(LMAX, 0.5);

    qDebug()<<lista->findNode(k1);
    lista->addRandomNodes(X);
    for(int i=0; i<=LMAX-1;i++)
        qDebug()<<"Poziom"<<i<<":"<<lista->countNodes(i);
    lista->printNodes(20,LMAX-1);
    lista->addNode(k2);
    lista->printNodes(20, 0);
    lista->addNode(k3);
    lista->printNodes(20, 0);
    lista->addNode(k4);
    lista->printNodes(20, 0);
    lista->addNode(k5);
    lista->printNodes(20, 0);
    for(int i=0; i<=LMAX-1;i++)
        qDebug()<<"Poziom"<<i<<":"<<lista->countNodes(i);
    lista->removeNode(k3);
    lista->removeNode(k2);
    lista->removeNode(k5);
    for(int i=0; i<=LMAX-1;i++)
        qDebug()<<"Poziom"<<i<<":"<<lista->countNodes(i);
    lista->printNodes(20,LMAX-1);
    qDebug()<<"Time elapsed: "<<t.elapsed()<<"ms";
    return true;
}



int main()
{
    if(labo2())
        qDebug()<<"Success";
}

