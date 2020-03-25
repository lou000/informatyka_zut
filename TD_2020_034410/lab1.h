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
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPlainTextEdit>

//TODO add zooming, change default theme

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

    //there is a lot of repetition here but i couldnt be bothered to refactor
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

    QSpinBox* userIndex;
    QDoubleSpinBox* rangeFrom;
    QDoubleSpinBox* rangeTo;
    QSpinBox* steps;

    QDoubleSpinBox* rangeFrom1;
    QDoubleSpinBox* rangeTo1;
    QDoubleSpinBox* rangeFrom2;
    QDoubleSpinBox* rangeTo2;
    QDoubleSpinBox* rangeFrom3;
    QDoubleSpinBox* rangeTo3;

    QLineEdit* numberSet;

    QPlainTextEdit* additionalOutput;
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
