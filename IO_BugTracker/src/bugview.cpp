#include "bugview.h"
#include <QLabel>
#include <QDebug>
#include <QHeaderView>
#include "issue.h"


BugView::BugView(ThreadController* cont, QWidget *parent)
    :QTableWidget(parent), controller(cont)
{


}

void BugView::fillRows(ViewMode mode)
{
    switch (mode) {
    case Issue:
        this->setRowCount(100);
        this->setColumnCount(11);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->setHorizontalHeaderLabels(QStringList()<<" "<<"ID"<<"Project"<<"Short Desc."<<"Description"<<"Menagers"
                                         <<"Programmers Assigned"<<"Testers Assigned"<<"Status"<<"Date Added"<<"Date Status");
        this->horizontalHeader()->setCascadingSectionResizes(true);
        this->clearContents();
        for(int i=0; i<controller->issues.length(); i++)
        {
            auto issue = controller->issues.at(i);
            QString programmers = QString();
            QString menagers = QString();
            QString testers = QString();
            for(auto test : issue->testers())
                testers.append(test->login() + ", ");
            testers.chop(2);
            for(auto men : issue->menagers())
                menagers.append(men->login() + ", ");
            menagers.chop(2);
            for(auto prog : issue->programmers())
                programmers.append(prog->login() + ", ");
            programmers.chop(2);

            QLabel * label = new QLabel();
            label->setPixmap(IssueTicket::getIconFromIssueType(issue->type()).pixmap(QSize(30,30)));
            this->setCellWidget(i, 0, label);
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(issue->id()));
            this->setItem(i, 1, id);
            QTableWidgetItem* project = new QTableWidgetItem(issue->project());
            this->setItem(i, 2, project);
            QTableWidgetItem* s_desc = new QTableWidgetItem(issue->shortDescription());
            this->setItem(i, 3, s_desc);
            QTableWidgetItem* desc = new QTableWidgetItem(issue->description());
            this->setItem(i, 4, desc);
            QTableWidgetItem* u1 = new QTableWidgetItem(menagers);
            this->setItem(i, 5, u1);
            QTableWidgetItem* u2 = new QTableWidgetItem(programmers);
            this->setItem(i, 6, u2);
            QTableWidgetItem* u3 = new QTableWidgetItem(testers);
            this->setItem(i, 7, u3);
            QTableWidgetItem* s = new QTableWidgetItem(enumToString<IssueTicket::Status>(issue->status()));
            this->setItem(i, 8, s);
            QTableWidgetItem* dateAdded = new QTableWidgetItem(issue->dateAdded().toString());
            this->setItem(i, 9, dateAdded);
            QTableWidgetItem* dateStatus = new QTableWidgetItem(issue->dateStatusChanged().toString());
            this->setItem(i, 10, dateStatus);
        }
        this->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        this->horizontalHeader()->resizeSection(4, 400);
        break;

    case User:
        this->setRowCount(100);
        this->setColumnCount(5);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Login"<<"Name"<<"Surname"<<"Position");
        this->horizontalHeader()->setCascadingSectionResizes(true);
        this->clearContents();
        for(int i=0; i<controller->users.length(); i++)
        {
            auto user = controller->users.at(i);

            QTableWidgetItem* id = new QTableWidgetItem(QString::number(user->id()));
            this->setItem(i, 0, id);
            QTableWidgetItem* login = new QTableWidgetItem(user->login());
            this->setItem(i, 1, login);
            QTableWidgetItem* name = new QTableWidgetItem(user->name());
            this->setItem(i, 2, name);
            QTableWidgetItem* surname = new QTableWidgetItem(user->surname());
            this->setItem(i, 3, surname);
            QTableWidgetItem* pos = new QTableWidgetItem(enumToString<User::UserPosition>(user->position()));
            this->setItem(i, 4, pos);
        }
        this->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        break;

    case Project:
        this->setRowCount(100);
        this->setColumnCount(3);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Name"<<"Description");
        this->horizontalHeader()->setCascadingSectionResizes(true);
        this->clearContents();
        for(int i=0; i<controller->projects.length(); i++)
        {
            auto project = controller->projects.at(i);

            QTableWidgetItem* id = new QTableWidgetItem(QString::number(project->id()));
            this->setItem(i, 0, id);
            QTableWidgetItem* name = new QTableWidgetItem(project->name());
            this->setItem(i, 1, name);
            QTableWidgetItem* desc = new QTableWidgetItem(project->desc());
            this->setItem(i, 2, desc);
        }
        this->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
        break;

    default:
        break;
    }
}

void BugView::switchMode(BugView::ViewMode m)
{
    mode = m;
    fillRows(m);
    for(auto action : this->actions())
        if(action->text() == "Add/Remove recources")
        {
            if(m == Issue)
                action->setVisible(true);
            else
                action->setVisible(false);
        }
    modeChanged(m);
}

void BugView::fillIssues()
{
    if(mode == Issue)
        fillRows(mode);
}

void BugView::fillUsers()
{
    if(mode == User)
        fillRows(mode);
}

void BugView::fillProjects()
{
    if(mode == Project)
        fillRows(mode);
}


