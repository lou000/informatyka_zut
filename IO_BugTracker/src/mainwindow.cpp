#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon());
    this->setWindowTitle("BugTracker   -   Project IO   -   by Lewicki Maciej and Jakub Kościołowski");
    this->setFixedSize(QSize(1800, 1000));
    this->setContentsMargins(10, 10, 10, 10);
}

MainWindow::~MainWindow()
{
}

