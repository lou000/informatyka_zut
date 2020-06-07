#pragma once
#include <QThread>
#include <QObject>
#include "bugview.h"
#include "user.h"
#include "issue.h"
#include "project.h"
#include "sqlworker.h"

class ThreadController : public QObject
{
    Q_OBJECT
public:
    ThreadController(BugView* view, int sqlUpdateInterval);

private:
    BugView* view;
    QThread* sqlThread;
    SqlWorker* worker;
    int sqlUpdateInterval;

    QVector<User*> users;
    QVector<IssueTicket*> issues;
    QVector<Project*> projects;

public slots:
    void receiveIssues(const QVector<IssueTicket*> &issues);

};

