#include "sqlworker.h"
#include "issue.h"
#include "QSqlError"

SqlWorker::SqlWorker(int timerInterval)
{
    this->timerInterval = timerInterval;
    this->updateTimer = new QTimer(this);
    QObject::connect(updateTimer, &QTimer::timeout, [=]() {
        checkDbAndUpdate();
    });
}


void SqlWorker::checkDbAndUpdate()
{
    if(!Queries::isDbOpen())
        Queries::initDb();
    if(Queries::isDbOpen())
    {
        updateData();
    }
}

void SqlWorker::updateData()
{
    auto q = Queries::setqGetIssues("BugTracker");
    if(!q.exec())
        qDebug()<<q.lastError();
    QVector<IssueTicket*> temp;

    while(q.next())
    {
        auto type = static_cast<IssueType>(q.value(1).toInt());
        class IssueTicket* issue;
        switch (type)
        {
        case Bug:
            issue = new BugTicket(q.value(0).toInt(), q.value(7).toString(), q.value(2).toString(), q.value(3).toString(),
                                  QVector<User*>(), QVector<User*>(), static_cast<Status>(q.value(4).toInt()),
                                  q.value(5).toDateTime(), q.value(6).toDateTime());
            break;
        case Task:
            issue = new TaskTicket(q.value(0).toInt(), q.value(7).toString(), q.value(2).toString(), q.value(3).toString(),
                                   QVector<User*>(), QVector<User*>(), static_cast<Status>(q.value(4).toInt()),
                                   q.value(5).toDateTime(), q.value(6).toDateTime());
        default:
            break;
        }
        temp.append(issue);
    }
    qDebug()<<"Issues Updated!!";
    emit resultIssues(temp);

}

void SqlWorker::handleAddIssue(IssueType type, QString s_desc, QString desc, Status status, int proj_id)
{
 auto q = Queries::addIssue(type, s_desc, desc, status, proj_id);
 q.exec();
 updateData();

}
