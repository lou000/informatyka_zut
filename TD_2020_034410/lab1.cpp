#include "lab1.h"

Lab1::Lab1(QWidget *parent) : QWidget(parent)
{
    //Initialize all series and append them to vector
    //from now on we will be refering to them using the Series enum

    auto seriesX = new QLineSeries(this);
    seriesX->setName("X(t)");
    seriesX->setColor(QColor("cornflowerblue"));
    seriesVec.append(seriesX);

    auto seriesY = new QLineSeries(this);
    seriesY->setColor(QColor("palegreen"));
    seriesY->setName("Y(t)");
    seriesVec.append(seriesY);

    auto seriesZ = new QLineSeries(this);
    seriesZ->setColor(QColor("peachpuff"));
    seriesZ->setName("Z(t)");
    seriesVec.append(seriesZ);

    auto seriesU = new QLineSeries(this);
    seriesU->setColor(QColor("orchid"));
    seriesU->setName("Y(t)");
    seriesVec.append(seriesU);

    auto seriesV = new QLineSeries(this);
    seriesV->setColor(QColor("navajowhite"));
    seriesV->setName("V(t)");
    seriesVec.append(seriesV);

    auto seriesP1 = new QLineSeries(this);
    seriesP1->setColor(QColor("tomato"));
    seriesP1->setName("P1(t)");
    seriesVec.append(seriesP1);

    auto seriesP2 = new QLineSeries(this);
    seriesP2->setColor(QColor("crimson"));
    seriesP2->setName("P2(t)");
    seriesVec.append(seriesP2);

    auto seriesP3 = new QLineSeries(this);
    seriesP3->setColor(QColor("pink"));
    seriesP3->setName("P3(t)");
    seriesVec.append(seriesP3);

    auto mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    auto leftBarLayout = new QGridLayout();
    mainLayout->addLayout(leftBarLayout);
    leftBarLayout->setAlignment(Qt::AlignTop);

    leftBarLayout->setVerticalSpacing(5);

    ///////////////////USER INDEX///////////////////
    this->userIndex = new QSpinBox(this);
    this->userIndex->setAlignment(Qt::AlignRight);
    this->userIndex->setMaximum(999999);
    this->userIndex->setValue(34410);
    this->userIndex->setMaximumWidth(80);
    leftBarLayout->addWidget(new QLabel("Index:", this), 0, 0, 1, 2, Qt::AlignRight);
    leftBarLayout->addWidget(userIndex, 0, 2, 1, 2, Qt::AlignLeft);

    /////////////COMBO BOX FOR SELECTING CHARTS////////////////////
    auto charts = new QGroupBox("Charts", this);
    auto chartsLayout = new QGridLayout();
    charts->setMinimumWidth(200);
    charts->setMaximumHeight(150);
    this->chartX = new QCheckBox("X(t)", this);
    this->chartY = new QCheckBox("Y(t)", this);
    this->chartZ = new QCheckBox("Z(t)", this);
    this->chartU = new QCheckBox("U(t)", this);
    this->chartV = new QCheckBox("V(t)", this);
    this->chartP = new QCheckBox("P(t)", this);
    chartsLayout->addWidget(chartX, 0, 0, Qt::AlignHCenter);
    chartsLayout->addWidget(chartY, 0, 1, Qt::AlignHCenter);
    chartsLayout->addWidget(chartZ, 0, 2, Qt::AlignHCenter);
    chartsLayout->addWidget(chartU, 1, 0, Qt::AlignHCenter);
    chartsLayout->addWidget(chartV, 1, 1, Qt::AlignHCenter);
    chartsLayout->addWidget(chartP, 1, 2, Qt::AlignHCenter);
    charts->setLayout(chartsLayout);
    leftBarLayout->addWidget(charts, 1, 0, 1, 4, Qt::AlignHCenter);


    /////////////RANGE SELECTION GROUP/////////////
    auto range = new QGroupBox("Range", this);
    auto rangeLayout = new QGridLayout();
    range->setMinimumWidth(200);
    range->setMaximumHeight(150);

    this->rangeFrom = new QDoubleSpinBox(this);
    this->rangeFrom->setAlignment(Qt::AlignRight);
    this->rangeFrom->setMaximumWidth(50);
    this->rangeFrom->setMaximum(999);
    this->rangeFrom->setMinimum(-999);
    this->rangeFrom->setValue(0.0);
    rangeLayout->addWidget(new QLabel("From:", this), 0, 0, Qt::AlignRight);
    rangeLayout->addWidget(rangeFrom, 0, 1, Qt::AlignLeft);

    this->rangeTo = new QDoubleSpinBox(this);
    this->rangeTo->setAlignment(Qt::AlignRight);
    this->rangeTo->setMaximumWidth(50);
    this->rangeTo->setMaximum(999);
    this->rangeTo->setMinimum(-999);
    this->rangeTo->setValue(1.0);
    rangeLayout->addWidget(new QLabel("To:", this), 0, 2, Qt::AlignRight);
    rangeLayout->addWidget(rangeTo, 0, 3, Qt::AlignLeft);

    this->steps = new QSpinBox(this);
    this->steps->setAlignment(Qt::AlignRight);
    this->steps->setMaximumWidth(80);
    this->steps->setMaximum(999999);
    this->steps->setMinimum(1);
    this->steps->setValue(2000);
    rangeLayout->addWidget(new QLabel("Steps:", this), 1, 0, Qt::AlignLeft);
    rangeLayout->addWidget(steps, 1, 1, 1, 2, Qt::AlignLeft);

    range->setLayout(rangeLayout);
    leftBarLayout->addWidget(range, 2, 0 , 1, 4, Qt::AlignHCenter);

    //////////RANGE SELECTION GROUP FOR V(T)///////////////
    auto rangeV = new QGroupBox("Range for V(t) chart", this);
    auto rangeVLayout = new QGridLayout();
    rangeV->setMinimumWidth(200);
    rangeV->setMaximumHeight(200);
    rangeVLayout->setSpacing(9);

    this->rangeFrom1 = new QDoubleSpinBox(this);
    this->rangeFrom1->setMaximumWidth(50);
    this->rangeFrom1->setValue(0.22);
    rangeVLayout->addWidget(rangeFrom1, 0, 0, Qt::AlignRight);
    rangeVLayout->addWidget(new QLabel(">", this), 0, 1, Qt::AlignHCenter);
    rangeVLayout->addWidget(new QLabel("t", this), 0, 2, Qt::AlignHCenter);
    rangeVLayout->addWidget(new QLabel(">=", this), 0, 3, Qt::AlignHCenter);
    this->rangeTo1 = new QDoubleSpinBox(this);
    this->rangeTo1->setMaximumWidth(50);
    this->rangeTo1->setValue(0);
    rangeVLayout->addWidget(rangeTo1, 0, 4, Qt::AlignRight);


    this->rangeFrom2 = new QDoubleSpinBox(this);
    this->rangeFrom2->setMaximumWidth(50);
    this->rangeFrom2->setValue(0.22);
    rangeVLayout->addWidget(rangeFrom2, 1, 0, Qt::AlignRight);
    rangeVLayout->addWidget(new QLabel("<=", this), 1, 1, Qt::AlignHCenter);
    rangeVLayout->addWidget(new QLabel("t", this), 1, 2, Qt::AlignHCenter);
    rangeVLayout->addWidget(new QLabel("<", this), 1, 3, Qt::AlignHCenter);
    this->rangeTo2 = new QDoubleSpinBox(this);
    this->rangeTo2->setMaximumWidth(50);
    this->rangeTo2->setValue(0.7);
    rangeVLayout->addWidget(rangeTo2, 1, 4, Qt::AlignRight);

    this->rangeFrom3 = new QDoubleSpinBox(this);
    this->rangeFrom3->setMaximumWidth(50);
    this->rangeFrom3->setValue(1.0);
    rangeVLayout->addWidget(rangeFrom3, 2, 0, Qt::AlignRight);
    rangeVLayout->addWidget(new QLabel(">=", this), 2, 1, Qt::AlignHCenter);
    rangeVLayout->addWidget(new QLabel("t", this), 2, 2, Qt::AlignHCenter);
    rangeVLayout->addWidget(new QLabel(">=", this), 2, 3, Qt::AlignHCenter);
    this->rangeTo3 = new QDoubleSpinBox(this);
    this->rangeTo3->setMaximumWidth(50);
    this->rangeTo3->setValue(0.7);
    rangeVLayout->addWidget(rangeTo3, 2, 4, Qt::AlignRight);

    rangeV->setLayout(rangeVLayout);
    leftBarLayout->addWidget(rangeV, 3, 0 , 1, 4, Qt::AlignHCenter);

    //////////////NUMBER SET FOR P(t)///////////////////////////
    this->numberSet = new QLineEdit("2, 4, 99", this);
    this->numberSet->setAlignment(Qt::AlignRight);
    this->numberSet->setValidator(new QRegExpValidator(QRegExp("[0-9, ]*"), this));
    this->numberSet->setMaximumWidth(80);
    leftBarLayout->addWidget(new QLabel("Set of numbers for P(t):", this), 4, 1, Qt::AlignLeft);
    leftBarLayout->addWidget(numberSet, 4, 2, Qt::AlignLeft);

    /////////////////ADITIONAL OUTPUT/////////////////////////////////
    auto addOutput = new QGroupBox("Additional output", this);
    auto addOutputLayout = new QGridLayout();
    addOutput->setMaximumSize(200,200);
    this->additionalOutput = new QPlainTextEdit("", this);
    this->additionalOutput->setReadOnly(true);
    addOutputLayout->addWidget(additionalOutput, 0, 0, Qt::AlignLeft);
    addOutput->setLayout(addOutputLayout);
    leftBarLayout->addWidget(addOutput, 5, 0, 1, 4, Qt::AlignHCenter);


    auto chart = new QChart();
    auto axisX = new QValueAxis();
    auto axisY = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
    this->setLayout(mainLayout);

    chartView->chart()->setTheme(QChart::ChartThemeDark);

    QObject::connect(chartX, &QCheckBox::stateChanged, this, [=](int sel){handleSeriesSelectionChanged(sel, Series::seriesX);});
    QObject::connect(chartY, &QCheckBox::stateChanged, this, [=](int sel){handleSeriesSelectionChanged(sel, Series::seriesY);});
    QObject::connect(chartZ, &QCheckBox::stateChanged, this, [=](int sel){handleSeriesSelectionChanged(sel, Series::seriesZ);});
    QObject::connect(chartU, &QCheckBox::stateChanged, this, [=](int sel){handleSeriesSelectionChanged(sel, Series::seriesU);});
    QObject::connect(chartV, &QCheckBox::stateChanged, this, [=](int sel){handleSeriesSelectionChanged(sel, Series::seriesV);});
    QObject::connect(chartP, &QCheckBox::stateChanged, this, [=](int sel){handleSeriesSelectionChanged(sel, Series::seriesP);});

    QObject::connect(userIndex, &QSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesX);
                                                                      calculateSeries(Series::seriesY);
                                                                      calculateSeries(Series::seriesZ);
                                                                      calculateSeries(Series::seriesU);});

    QObject::connect(rangeFrom, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesY);
                                                                            calculateSeries(Series::seriesZ);
                                                                            calculateSeries(Series::seriesU);
                                                                            calculateSeries(Series::seriesP);});

    QObject::connect(rangeTo, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesY);
                                                                            calculateSeries(Series::seriesZ);
                                                                            calculateSeries(Series::seriesU);
                                                                            calculateSeries(Series::seriesP);});

    QObject::connect(steps, &QSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesX);
                                                                  calculateSeries(Series::seriesY);
                                                                  calculateSeries(Series::seriesZ);
                                                                  calculateSeries(Series::seriesU);
                                                                  calculateSeries(Series::seriesV);
                                                                  calculateSeries(Series::seriesP);});

    QObject::connect(rangeFrom1, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesV);});
    QObject::connect(rangeTo1, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesV);});
    QObject::connect(rangeFrom2, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesV);});
    QObject::connect(rangeTo2, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesV);});
    QObject::connect(rangeFrom3, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesV);});
    QObject::connect(rangeTo3, &QDoubleSpinBox::editingFinished, this, [=]{calculateSeries(Series::seriesV);});

    QObject::connect(numberSet, &QLineEdit::editingFinished, this, [=]{calculateSeries(Series::seriesP);});

    calculateSeries(Series::seriesX);
    calculateSeries(Series::seriesY);
    calculateSeries(Series::seriesZ);
    calculateSeries(Series::seriesU);
    calculateSeries(Series::seriesV);
    calculateSeries(Series::seriesP);
}


QVector<int> Lab1::parsedIndex()
{
    int index = userIndex->text().toInt();
    QVector<int> temp;
    while(index>0)
    {
        if(index%10 == 0)
            temp.append(1);
        else
            temp.append(index%10);
        index/=10;
    }
    while(temp.length()<6)
        temp.append(1);
    return temp;
}

QVector<int> Lab1::parsedNumberSet()
{
    QVector<int> temp;
    QStringList list = numberSet->text().split(",");
    for(auto string : list)
    {
        temp.append(string.toInt());
    }
    return temp;
}

double Lab1::xFunction(double x, QVector<int> indexData)
{
    Q_ASSERT(indexData.length()>=6);
    return indexData[0]*x*x+indexData[1]*x+indexData[2];
}

double Lab1::yFunction(double x, QVector<int> indexData)
{
    Q_ASSERT(indexData.length()>=6);
    return 2*(xFunction(x, indexData))*(xFunction(x, indexData))+12*qCos(x);
}

double Lab1::zFunction(double x, QVector<int> indexData)
{
    Q_ASSERT(indexData.length()>=6);
    return qSin(2*M_PI*7*x)*xFunction(x, indexData) - 0.2*log10(abs(yFunction(x, indexData))+M_PI);
}

double Lab1::uFunction(double x, QVector<int> indexData)
{
    Q_ASSERT(indexData.length()>=6);
    return sqrt(abs(yFunction(x, indexData)*yFunction(x, indexData)*zFunction(x, indexData)))
                - 1.8*sin(0.4*x*zFunction(x, indexData)*xFunction(x, indexData));
}

void Lab1::handleSeriesSelectionChanged(int selected, Series type)
{
    Q_ASSERT(seriesVec.length()>=8);
    auto series = seriesVec.at(type);
    if(type == Series::seriesP)
    {
        if(selected == 2)
        {
            chartView->chart()->addSeries(series);
            chartView->chart()->addSeries(seriesVec.at(type+1));
            chartView->chart()->addSeries(seriesVec.at(type+2));
            chartView->chart()->createDefaultAxes();
        }
        else
        {
            chartView->chart()->removeSeries(series);
            chartView->chart()->removeSeries(seriesVec.at(type+1));
            chartView->chart()->removeSeries(seriesVec.at(type+2));
            auto series = chartView->chart()->series();
            for(auto item : series)
                chartView->chart()->removeSeries(item);
            for(auto item : series)
                chartView->chart()->addSeries(item);
            chartView->chart()->createDefaultAxes();
        }
    }
    else
    {
        if(selected == 2)
        {
            chartView->chart()->addSeries(series);
            chartView->chart()->createDefaultAxes();
        }
        else
        {
            chartView->chart()->removeSeries(series);
            auto series = chartView->chart()->series();
            for(auto item : series)
                chartView->chart()->removeSeries(item);
            for(auto item : series)
                chartView->chart()->addSeries(item);
            chartView->chart()->createDefaultAxes();
        }
    }
}

void Lab1::calculateSeries(Series type)
{
    auto series = seriesVec.at(type);
    QVector<int> indexData = parsedIndex();
    double rangeF = rangeFrom->value();
    double rangeT = rangeTo->value();
    if(rangeF>rangeT)
        return;
    int steps = this->steps->text().toInt();
    if(steps<=0)
        return;
    double step = (rangeT - rangeF)/steps;

    bool contains;
    if(type == Series::seriesP)
    {
        contains = chartView->chart()->series().contains(series) ||
                   chartView->chart()->series().contains(seriesVec.at(type+1)) ||
                   chartView->chart()->series().contains(seriesVec.at(type+2));
        if(contains)
        {
            chartView->chart()->removeSeries(series);
            chartView->chart()->removeSeries(seriesVec.at(type+1));
            chartView->chart()->removeSeries(seriesVec.at(type+2));
        }
        series->clear();
        seriesVec.at(type+1)->clear();
        seriesVec.at(type+2)->clear();
    }
    else
    {
        contains = chartView->chart()->series().contains(series);
        if(contains)
           chartView->chart()->removeSeries(series);
        series->clear();
    }

    switch (type) {
    case Series::seriesX:
    {
        rangeF = -10;
        rangeT = 10;
        for(double x = rangeF; x<=rangeT; x+=step)
            series->append(x, xFunction(x, indexData));
        double det = indexData[1]*indexData[1]-4*indexData[0]*indexData[2];
        if(det>0)
        {
            additionalOutput->setPlainText("Miejsca zerowe X(t)\n"+
                                           QString::number((-indexData[1]+sqrt(det))/(2*indexData[0]))
                                           +"\n"+ QString::number((-indexData[1]-sqrt(det))/(2*indexData[0])));
        }
        else if(det==0)
        {
            additionalOutput->setPlainText("Miejsce zerowe X(t)\n"+
                                           QString::number(((-indexData[1])/(2*indexData[0]))));
        }
        else if(det<0)
        {
            additionalOutput->setPlainText("Miejsca zerowe X(t)\n"+
                                           QString::number(((-indexData[1])/(2*indexData[0])))+"+"+
                                           QString::number(sqrt(-det)/(2*indexData[0]))+"i"+"\n"+
                                           QString::number(((-indexData[1])/(2*indexData[0])))+"-"+
                                           QString::number(sqrt(-det)/(2*indexData[0]))+"i");
        }
        break;
    }
    case Series::seriesY:
    {
        for(double x = rangeF; x<=rangeT; x+=step)
            series->append(x, yFunction(x, parsedIndex()));
        break;
    }
    case Series::seriesZ:
    {
        for(double x = rangeF; x<=rangeT; x+=step)
            series->append(x, zFunction(x, parsedIndex()));
        break;
    }
    case Series::seriesU:
    {
        for(double x = rangeF; x<=rangeT; x+=step)
            series->append(x, uFunction(x, parsedIndex()));
        break;
    }
    case Series::seriesV:
    {
        double range1From = rangeFrom1->value();
        double range2From = rangeFrom2->value();
        double range3From = rangeFrom3->value();
        double range1To = rangeTo1->value();
        double range2To = rangeTo2->value();
        double range3To = rangeTo3->value();

        int steps = this->steps->value();
        if(steps<=0)
            return;
        if(range1From<range1To || range2From>range2To || range3From<range3To)
            return;
        if(range1To>range3From)
            return;
        double step = (range3From - range1To)/steps;

        for(double x = range1To; x<range1From; x+=step)
            series->append(x, (1-7*x)*qSin((2*M_PI*x*10)/(x+0.04)));
        for(double x = range2From; x<range2To; x+=step)
            series->append(x, 0.63*x*qSin(125*x));
        for(double x = range3To; x<=range3From; x+=step)
            series->append(x, qPow(x, -0.662)+0.77*qSin(8*x));
        break;
    }
    case Series::seriesP:
    {
        QVector<int> set = parsedNumberSet();
        if(set.length()>0)
        {
            for(double x = rangeF; x<=rangeT; x+=step)
            {
                double y=0;
                for(int number=1; number<=set[0]; number++)
                {
                    y += (qCos(12*x*number*number) + qCos(16*x*number))/(number*number);
                }
                series->append(x, y);
            }
        }
        if(set.length()>1)
        {
            for(double x = rangeF; x<=rangeT; x+=step)
            {
                double y=0;
                for(int number=1; number<=set[1]; number++)
                {
                    y += (qCos(12*x*number*number) + qCos(16*x*number))/(number*number);
                }
                seriesVec.at(type+1)->append(x, y);
            }
        }
        if(set.length()>2)
        {
            for(double x = rangeF; x<=rangeT; x+=step)
            {
                double y=0;
                for(int number=1; number<=set[2]; number++)
                {
                    y += (qCos(12*x*number*number) + qCos(16*x*number))/(number*number);
                }
                seriesVec.at(type+2)->append(x, y);
            }
        }
        break;
    }
    default:
        return;

    }

    if(contains)
        handleSeriesSelectionChanged(2, type);
}
