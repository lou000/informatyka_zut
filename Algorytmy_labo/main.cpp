#include "DArray.h"
#include "labo1.cpp"
#include "labo2.h"
#include "labo3.h"
#include "labo4.h"
#include "labo5.h"
#include "labo6.h"

int main()
{
    DArray<int>* data = new DArray<int>();
    data->append(10);
    int lol1 = data->at(0);
    data->operator[](2);
    int lol = data[0];
    auto asdasdas = 'a';
//    if(labo6())
//        qDebug()<<"Success";
    return 0;
}
