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

    enum Series{
        seriesX,
        seriesY,
        seriesZ,
        seriesU,
        seriesV,
        seriesP
    };

    QVector<int> parsedIndex();
    QVector<int> parsedNumberSet();
    double xFunction(double x, QVector<int> indexData);
    double yFunction(double x, QVector<int> indexData);
    double zFunction(double x, QVector<int> indexData);
    double uFunction(double x, QVector<int> indexData);

    QVector<QLineSeries*> seriesVec;

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

private slots:
    void handleSeriesSelectionChanged(int selection, Series type);
    void calculateSeries(Series type);
};
