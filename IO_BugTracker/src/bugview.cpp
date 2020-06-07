#include "bugview.h"
#include <QLabel>
#include <QDebug>
#include <QHeaderView>


BugView::BugView(QWidget *parent)
{
    this->setParent(parent);

}

void BugView::fillRows(const QVector<IssueTicket *> &issues)
{
    for(int i=0; i<issues.length(); i++)
    {
        auto issue = issues.at(i);
        QString type;
        QIcon icon;
        QString status;
        switch(issues.at(i)->type())
        {
        case IssueType::Bug:
            type = "Bug";
            icon = QIcon(":/icons/bug_icon.png");
            break;
        case IssueType::Task:
            type = "Task";
            icon = QIcon(":/icons/task_icon.png");
            break;
        default:
            break;
        }

        switch(issues.at(i)->status())
        {
        case Status::Closed:
            status = "Closed";
            break;
        case Status::CheckIn:
            status = "CheckIn";
            break;
        case Status::Created:
            status = "Created";
            break;
        case Status::Approved:
            status = "Approved";
            break;
        case Status::InProgress:
            status = "InProgress";
            break;
        case Status::NotApproved:
            status = "NotApproved";
            break;
        default:
            break;
        }

        QLabel * label = new QLabel();
        label->setPixmap(icon.pixmap(QSize(30,30)));
        this->setCellWidget(i, 0, label);
        QTableWidgetItem* id = new QTableWidgetItem(QString::number(issue->id()));
        this->setItem(i, 1, id);
        QTableWidgetItem* project = new QTableWidgetItem(issue->project());
        this->setItem(i, 2, project);
        QTableWidgetItem* s_desc = new QTableWidgetItem(issue->shortDescription());
        this->setItem(i, 3, s_desc);
        QTableWidgetItem* desc = new QTableWidgetItem(issue->description());
        this->setItem(i, 4, desc);
        QTableWidgetItem* s = new QTableWidgetItem(status);
        this->setItem(i, 7, s);
        QTableWidgetItem* dateAdded = new QTableWidgetItem(issue->dateAdded().toString());
        this->setItem(i, 8, dateAdded);
        QTableWidgetItem* dateStatus = new QTableWidgetItem(issue->dateStatusChanged().toString());
        this->setItem(i, 9, dateStatus);
    }
    this->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
}
