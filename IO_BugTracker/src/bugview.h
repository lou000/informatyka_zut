#pragma once
#include <QTableWidget>
#include <QAction>
#include "issue.h"
#include "threadcontroller.h"


class BugView : public QTableWidget
{
public:
    enum ViewMode{
        Issue,
        User,
        Project,
    };
    Q_OBJECT
public:
    BugView(ThreadController* controller, QWidget* parent);
    void fillRows(ViewMode mode);
    void switchMode(ViewMode m);
    ViewMode getMode(){return mode;}
private:
    ViewMode mode = ViewMode::Issue;
    ThreadController* controller;
signals:
    void modeChanged(ViewMode mode);

public slots:
    void fillIssues();
    void fillUsers();
    void fillProjects();

};

