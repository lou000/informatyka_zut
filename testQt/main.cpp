#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include <QSharedPointer>

class Test
{
public:
    ~Test()
    {
        qDebug()<<"I am destroyed";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    {
        QVector<Test*> asd;
        asd.append(new Test());
    }
    Test* test = new Test();
    QSharedPointer<Test> tst(test);
    {
        QVector<QSharedPointer<Test>> asd;
        Test* test2 = new Test();
        tst.reset(test2);
        asd.append(QSharedPointer<Test>(test));
        asd.clear();
        qDebug()<<"Finished";
    }

    return a.exec();
}
