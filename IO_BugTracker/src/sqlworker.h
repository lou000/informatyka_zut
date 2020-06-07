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
    void initialize();
    void checkDbAndUpdate();
    void updateData();

signals:
    void resultIssues(const QVector<IssueTicket*> &issues);
};


