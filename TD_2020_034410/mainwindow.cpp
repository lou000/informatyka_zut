#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lab1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Transmisja danych - Laboratoria - by Lewicki Maciej");
    this->setFixedSize(QSize(1000, 600));
    centralWidget = new QTabWidget(this);
    centralWidget->insertTab(0, new Lab1(centralWidget), "Lab1");
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}


