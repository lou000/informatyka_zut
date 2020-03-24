#pragma once

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QGridLayout>
#include <QChart>
#include <QLabel>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QLineSeries>
#include <QChartView>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QValueAxis>
#include <QtMath>

using namespace QtCharts;

class Lab1 : public QWidget
{
    Q_OBJECT
public:
    explicit Lab1(QWidget *parent = nullptr);


private:
    QVector<int> parsedIndex();
    QVector<int> parsedNumberSet();
    double xFunction(double x, QVector<int> indexData);
    double yFunction(double x, QVector<int> indexData);
    double zFunction(double x, QVector<int> indexData);
    double uFunction(double x, QVector<int> indexData);

    //there is a lot of repetition here but i couldnt be bothered
    QLineSeries* seriesX;
    QLineSeries* seriesY;
    QLineSeries* seriesZ;
    QLineSeries* seriesU;
    QLineSeries* seriesV;
    QLineSeries* seriesP;

    QCheckBox* chartX;
    QCheckBox* chartY;
    QCheckBox* chartZ;
    QCheckBox* chartU;
    QCheckBox* chartV;
    QCheckBox* chartP;

    QLineEdit* userIndex;
    QLineEdit* rangeFrom;
    QLineEdit* rangeTo;
    QLineEdit* steps;

    QLineEdit* rangeFrom1;
    QLineEdit* rangeTo1;
    QLineEdit* rangeFrom2;
    QLineEdit* rangeTo2;
    QLineEdit* rangeFrom3;
    QLineEdit* rangeTo3;

    QLineEdit* numberSet;

    QChartView* chartView;
    QValueAxis* axisX;
    QValueAxis* axisY;

signals:
    void xChanged();
    void yChanged();
    void zChanged();
    void uChanged();
    void vChanged();
    void pChanged();

private slots:
    void handleXselected(int selected);
    void handleYselected(int selected);
    void handleZselected(int selected);
    void handleUselected(int selected);
    void handleVselected(int selected);
    void handlePselected(int selected);

    void calculateX();
    void calculateY();
    void calculateZ();
    void calculateU();
    void calculateV();
    void calculateP();
};
