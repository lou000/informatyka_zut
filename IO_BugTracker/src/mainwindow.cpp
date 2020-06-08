#include "mainwindow.h"
#include "threadcontroller.h"
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QSpinBox>
#include "queries.h"
#include <QPushButton>
#include <QAbstractButton>
#include "issue.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    auto tView = new BugView(this);
    tView->setRowCount(100);
    tView->setColumnCount(10);
    tView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tView->setHorizontalHeaderLabels(QStringList()<<" "<<"ID"<<"Project"<<"Short Desc."<<"Description"
                                     <<"Programmers Assigned"<<"Testers Assigned"<<"Status"<<"Date Added"<<"Date Status");
    ThreadController* controller = new ThreadController(tView, 5000);

    this->mainView = tView;
    auto leftBar = new QDockWidget();
    leftBar->setWindowTitle("Add issue:");
    leftBar->setMinimumWidth(350);
    leftBar->setFeatures(QDockWidget::DockWidgetMovable);
    auto leftBarWidget = new QWidget();
    leftBar->setWidget(leftBarWidget);
    auto leftBarLayout = new QGridLayout();
    leftBarWidget->setLayout(leftBarLayout);

    auto issueType = new QComboBox(this);
    issueType->addItem("Bug");
    issueType->addItem("Task");
    leftBarLayout->addWidget(issueType, 0, 1);
    leftBarLayout->addWidget(new QLabel("Issue type:"),0 ,0, Qt::AlignRight);

    auto s_desc = new QTextEdit();
    s_desc->setPlaceholderText("Short Description");
    leftBarLayout->addWidget(s_desc, 2, 0, 2, 4);

    auto desc = new QTextEdit();
    desc->setPlaceholderText("Full Description");
    leftBarLayout->addWidget(desc, 4, 0, 4, 4);

    auto status = new QComboBox(this);
    status->addItem("Created");
    status->addItem("InProgress");
    status->addItem("CheckIn");
    status->addItem("Approved");
    status->addItem("NotApproved");
    status->addItem("Closed");
    leftBarLayout->addWidget(status, 0, 3);
    leftBarLayout->addWidget(new QLabel("Status:"),0 ,2, Qt::AlignRight);

    auto proj_id = new QSpinBox(this);
    proj_id->setMinimum(1);
    proj_id->setValue(1);
    leftBarLayout->addWidget(proj_id, 1, 1);
    leftBarLayout->addWidget(new QLabel("Project ID:"),1 ,0, Qt::AlignRight);

    auto accept_button = new QPushButton("Add");
    leftBarLayout->addWidget(accept_button, 8, 0, 2, 4);

    QObject::connect(accept_button, &QPushButton::clicked, this, [=]
        {
         emit controller->addIssue(IssueTicket::getIssueTypeFromText(issueType->currentText()),
                                   s_desc->toPlainText(), desc->toPlainText(),
                                   IssueTicket::getStatusFromText(status->currentText()),
                                   proj_id->value());
        });





    setCentralWidget(tView);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, leftBar);
    setWindowIcon(QIcon());
    this->setWindowTitle("BugTracker   -   Project IO   -   by Lewicki Maciej and Jakub Kościołowski");
    this->setFixedSize(QSize(1800, 1000));
    this->setContentsMargins(10, 10, 10, 10);
}

MainWindow::~MainWindow()
{
}

