#pragma once
#include <QMainWindow>
#include <QDockWidget>
#include <QGridLayout>
#include "bugview.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QTableWidget* mainView;
};

