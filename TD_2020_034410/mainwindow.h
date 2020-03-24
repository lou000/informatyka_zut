#pragma once
#include <QMainWindow>
#include <QChartView>
#include <QChart>
#include <QTabBar>

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTabWidget* centralWidget;
};

