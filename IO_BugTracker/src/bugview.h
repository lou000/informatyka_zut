#pragma once
#include <QTableWidget>
#include "issue.h"


class BugView : public QTableWidget
{
    Q_OBJECT
public:
    BugView(QWidget* parent);
    void fillRows(const QVector<IssueTicket*> &issues);
};

