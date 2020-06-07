#include "bugview.h"
#include <QLabel>
#include <QDebug>
#include <QHeaderView>
#include "issue.h"


BugView::BugView(QWidget *parent)
{
    this->setParent(parent);

}

void BugView::fillRows(const QVector<IssueTicket *> &issues)
{
    this->horizontalHeader()->setCascadingSectionResizes(true);
    for(int i=0; i<issues.length(); i++)
    {
        auto issue = issues.at(i);

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
        QTableWidgetItem* s = new QTableWidgetItem(IssueTicket::getStatusText(issue->status()));
        this->setItem(i, 7, s);
        QTableWidgetItem* dateAdded = new QTableWidgetItem(issue->dateAdded().toString());
        this->setItem(i, 8, dateAdded);
        QTableWidgetItem* dateStatus = new QTableWidgetItem(issue->dateStatusChanged().toString());
        this->setItem(i, 9, dateStatus);
    }
    this->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    this->horizontalHeader()->resizeSection(4, 400);
//    this->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
//    this->horizontalHeader()->setMaximumSectionSize(50);
}
