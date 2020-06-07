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
    SqlWorker* worker;

private:
    BugView* view;
    QThread* sqlThread;
    int sqlUpdateInterval;

    QVector<User*> users;
    QVector<IssueTicket*> issues;
    QVector<Project*> projects;

signals:
    void timerStart();
    void addIssue(IssueType type, QString s_desc, QString desc, Status status, int proj_id);

public slots:
    void receiveIssues(const QVector<IssueTicket*> &issues);

};

