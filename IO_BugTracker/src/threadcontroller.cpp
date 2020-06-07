#include "threadcontroller.h"
#include <QMetaType>

ThreadController::ThreadController(BugView *view, int timer)
    :view(view)
{

    this->issues = QVector<IssueTicket*>();
    this->sqlUpdateInterval = timer;
    this->sqlThread = new QThread();
    worker = new SqlWorker(timer);
    qRegisterMetaType<QVector<IssueTicket*>>("QVector<IssueTicket*>");
    qRegisterMetaType<IssueType>("IssueType");
    qRegisterMetaType<Status>("Status");

    QObject::connect(worker, SIGNAL(resultIssues(const QVector<IssueTicket*>)),
                     this, SLOT(receiveIssues(const QVector<IssueTicket*>)));

    QObject::connect(this, SIGNAL(timerStart()), worker, SLOT(timerStart()));
    QObject::connect(this, SIGNAL(addIssue(IssueType, QString, QString, Status, int)),
                     worker, SLOT(handleAddIssue(IssueType, QString, QString, Status, int)));

    worker->moveToThread(sqlThread);
    sqlThread->start();
    emit timerStart();
}

void ThreadController::receiveIssues(const QVector<IssueTicket *> &issues)
{
    this->issues = issues;
    view->fillRows(issues);
}

