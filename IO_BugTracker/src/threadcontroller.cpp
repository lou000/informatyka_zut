#include "threadcontroller.h"

ThreadController::ThreadController(BugView *view, int timer)
    :view(view)
{

    this->issues = QVector<IssueTicket*>();
    this->sqlUpdateInterval = timer;
    this->sqlThread = new QThread();
    worker = new SqlWorker(timer);
    QObject::connect(worker, SIGNAL(resultIssues(const QVector<IssueTicket*>)),
                     this, SLOT(receiveIssues(const QVector<IssueTicket*>)));

    worker->initialize();
    worker->moveToThread(sqlThread);
    worker->checkDbAndUpdate();
}

void ThreadController::receiveIssues(const QVector<IssueTicket *> &issues)
{
    this->issues = issues;
    view->fillRows(issues);
}

