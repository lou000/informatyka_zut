#include "mainwindow.h"
#include "threadcontroller.h"


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
    this->mainView = tView;
    auto leftBar = new QDockWidget();
    leftBar->setFeatures(QDockWidget::DockWidgetMovable);
    auto leftBarWidget = new QWidget();
    leftBar->setWidget(leftBarWidget);
    auto leftBarLayout = new QGridLayout();
    leftBarWidget->setLayout(leftBarLayout);

    ThreadController* controller = new ThreadController(tView, 60000);

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

