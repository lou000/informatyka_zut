#pragma once
#include <QTimer>
#include <QObject>
#include <QVector>
#include "issue.h"
#include "queries.h"

class SqlWorker : public QObject
{
    Q_OBJECT
public:
    bool timerStop = false;
    SqlWorker(int timerInterval);
    QTimer* updateTimer;

    int timerInterval;
    void checkDbAndUpdate();
    void updateData();

signals:
    void resultIssues(const QVector<IssueTicket*> &issues);

public slots:
    void timerStart() {updateTimer->start(timerInterval); checkDbAndUpdate();}
    void handleAddIssue(IssueType type, QString s_desc, QString desc, Status status, int proj_id);
};


