#include "lab1.h"

Lab1::Lab1(QWidget *parent) : QWidget(parent)
{
    //there is a lot of repetition here but i couldnt be bothered to refactor
    seriesX = new QLineSeries();
    seriesX->setName("X(t)");
    seriesX->setColor(QColor("blue"));

    seriesY = new QLineSeries();
    seriesY->setColor(QColor("green"));
    seriesY->setName("Y(t)");

    seriesZ = new QLineSeries();
    seriesZ->setColor(QColor("orange"));
    seriesZ->setName("Z(t)");

    seriesU = new QLineSeries();
    seriesU->setColor(QColor("purple"));
    seriesU->setName("Y(t)");

    seriesV = new QLineSeries();
    seriesV->setColor(QColor("pink"));
    seriesV->setName("V(t)");

    seriesP = new QLineSeries();
    seriesP->setColor(QColor("red"));
    seriesP->setName("P(t)");

    auto mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    auto leftBarLayout = new QGridLayout();
    mainLayout->addLayout(leftBarLayout);
    leftBarLayout->setAlignment(Qt::AlignTop);

    leftBarLayout->setVerticalSpacing(10);


    /////////////COMBO BOX FOR SELECTING CHARTS////////////////////
    auto charts = new QGroupBox("Charts", this);
    auto chartsLayout = new QGridLayout();
    charts->setMinimumWidth(200);
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
    leftBarLayout->addWidget(charts, 0, 0, 1, 4, Qt::AlignHCenter);

    ///////////////////USER INDEX///////////////////
    auto index = new QWidget(this);
    index->setMinimumWidth(200);
    auto indexLayout = new QGridLayout();
    this->userIndex = new QSpinBox(this);
    this->userIndex->setAlignment(Qt::AlignRight);
    this->userIndex->setMaximum(999999);
    this->userIndex->setValue(98099);
    this->userIndex->setMaximumWidth(80);
    indexLayout->addWidget(new QLabel("Index:", this), 0, 0, Qt::AlignRight);
    indexLayout->addWidget(userIndex, 0, 1, Qt::AlignLeft);
    index->setLayout(indexLayout);
    leftBarLayout->addWidget(index, 1, 0, 1, 4, Qt::AlignHCenter);

    /////////////RANGE SELECTION GROUP/////////////
    auto range = new QGroupBox("Range", this);
    auto rangeLayout = new QGridLayout();
    range->setMinimumWidth(200);

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
    this->steps->setValue(22050);
    rangeLayout->addWidget(new QLabel("Steps:", this), 1, 0, Qt::AlignLeft);
    rangeLayout->addWidget(steps, 1, 1, 1, 2, Qt::AlignLeft);

    range->setLayout(rangeLayout);
    leftBarLayout->addWidget(range, 2, 0 , 1, 4, Qt::AlignHCenter);

    //////////RANGE SELECTION GROUP FOR V(T)///////////////
    auto rangeV = new QGroupBox("Range for V(t) chart", this);
    auto rangeVLayout = new QGridLayout();
    rangeV->setMinimumWidth(200);
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
    addOutput->setMaximumSize(200,100);
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

    QObject::connect(this, SIGNAL(xChanged()), this, SLOT(calculateX()));
    QObject::connect(this, SIGNAL(yChanged()), this, SLOT(calculateY()));
    QObject::connect(this, SIGNAL(zChanged()), this, SLOT(calculateZ()));
    QObject::connect(this, SIGNAL(uChanged()), this, SLOT(calculateU()));
    QObject::connect(this, SIGNAL(vChanged()), this, SLOT(calculateV()));
    QObject::connect(this, SIGNAL(pChanged()), this, SLOT(calculateP()));

    QObject::connect(chartX, SIGNAL(stateChanged(int)), this, SLOT(handleXselected(int)));
    QObject::connect(chartY, SIGNAL(stateChanged(int)), this, SLOT(handleYselected(int)));
    QObject::connect(chartZ, SIGNAL(stateChanged(int)), this, SLOT(handleZselected(int)));
    QObject::connect(chartU, SIGNAL(stateChanged(int)), this, SLOT(handleUselected(int)));
    QObject::connect(chartV, SIGNAL(stateChanged(int)), this, SLOT(handleVselected(int)));
    QObject::connect(chartP, SIGNAL(stateChanged(int)), this, SLOT(handlePselected(int)));

    QObject::connect(userIndex, SIGNAL(editingFinished()), this, SLOT(calculateX()));
    QObject::connect(userIndex, SIGNAL(editingFinished()), this, SLOT(calculateY()));
    QObject::connect(userIndex, SIGNAL(editingFinished()), this, SLOT(calculateZ()));
    QObject::connect(userIndex, SIGNAL(editingFinished()), this, SLOT(calculateU()));

    QObject::connect(rangeFrom, SIGNAL(editingFinished()), this, SLOT(calculateY()));
    QObject::connect(rangeFrom, SIGNAL(editingFinished()), this, SLOT(calculateZ()));
    QObject::connect(rangeFrom, SIGNAL(editingFinished()), this, SLOT(calculateU()));
    QObject::connect(rangeFrom, SIGNAL(editingFinished()), this, SLOT(calculateP()));

    QObject::connect(rangeTo, SIGNAL(editingFinished()), this, SLOT(calculateY()));
    QObject::connect(rangeTo, SIGNAL(editingFinished()), this, SLOT(calculateZ()));
    QObject::connect(rangeTo, SIGNAL(editingFinished()), this, SLOT(calculateU()));
    QObject::connect(rangeTo, SIGNAL(editingFinished()), this, SLOT(calculateP()));

    QObject::connect(steps, SIGNAL(editingFinished()), this, SLOT(calculateX()));
    QObject::connect(steps, SIGNAL(editingFinished()), this, SLOT(calculateY()));
    QObject::connect(steps, SIGNAL(editingFinished()), this, SLOT(calculateZ()));
    QObject::connect(steps, SIGNAL(editingFinished()), this, SLOT(calculateU()));
    QObject::connect(steps, SIGNAL(editingFinished()), this, SLOT(calculateP()));

    QObject::connect(rangeFrom1, SIGNAL(editingFinished()), this, SLOT(calculateV()));
    QObject::connect(rangeTo1, SIGNAL(editingFinished()), this, SLOT(calculateV()));
    QObject::connect(rangeFrom2, SIGNAL(editingFinished()), this, SLOT(calculateV()));
    QObject::connect(rangeTo2, SIGNAL(editingFinished()), this, SLOT(calculateV()));
    QObject::connect(rangeFrom3, SIGNAL(editingFinished()), this, SLOT(calculateV()));
    QObject::connect(rangeTo3, SIGNAL(editingFinished()), this, SLOT(calculateV()));

    QObject::connect(numberSet, SIGNAL(editingFinished()), this, SLOT(calculateP()));

    calculateX();
    calculateY();
    calculateZ();
    calculateU();
    calculateP();
    calculateV();
}

void Lab1::handleXselected(int selected)
{
    Q_ASSERT(seriesX);
    if(selected == 2)
    {
        chartView->chart()->addSeries(seriesX);
        chartView->chart()->createDefaultAxes();
    }
    else
    {
        chartView->chart()->removeSeries(seriesX);
        auto series = chartView->chart()->series();
        for(auto item : series)
            chartView->chart()->removeSeries(item);
        for(auto item : series)
            chartView->chart()->addSeries(item);
        chartView->chart()->createDefaultAxes();
    }
}

void Lab1::handleYselected(int selected)
{
    Q_ASSERT(seriesY);
    if(selected == 2)
    {
        chartView->chart()->addSeries(seriesY);
        chartView->chart()->createDefaultAxes();
    }
    else
    {
        chartView->chart()->removeSeries(seriesY);
        auto series = chartView->chart()->series();
        for(auto item : series)
            chartView->chart()->removeSeries(item);
        for(auto item : series)
            chartView->chart()->addSeries(item);
        chartView->chart()->createDefaultAxes();
    }
}

void Lab1::handleZselected(int selected)
{
    Q_ASSERT(seriesZ);
    if(selected == 2)
    {
        chartView->chart()->addSeries(seriesZ);
        chartView->chart()->createDefaultAxes();
    }
    else
    {
        chartView->chart()->removeSeries(seriesZ);
        auto series = chartView->chart()->series();
        for(auto item : series)
            chartView->chart()->removeSeries(item);
        for(auto item : series)
            chartView->chart()->addSeries(item);
        chartView->chart()->createDefaultAxes();
    }
}

void Lab1::handleUselected(int selected)
{
    Q_ASSERT(seriesU);
    if(selected == 2)
    {
        chartView->chart()->addSeries(seriesU);
        chartView->chart()->createDefaultAxes();
    }
    else
    {
        chartView->chart()->removeSeries(seriesU);
        auto series = chartView->chart()->series();
        for(auto item : series)
            chartView->chart()->removeSeries(item);
        for(auto item : series)
            chartView->chart()->addSeries(item);
        chartView->chart()->createDefaultAxes();
    }
}

void Lab1::handleVselected(int selected)
{
    Q_ASSERT(seriesV);
    if(selected == 2)
    {
        chartView->chart()->addSeries(seriesV);
        chartView->chart()->createDefaultAxes();
    }
    else
    {
        chartView->chart()->removeSeries(seriesV);
        auto series = chartView->chart()->series();
        for(auto item : series)
            chartView->chart()->removeSeries(item);
        for(auto item : series)
            chartView->chart()->addSeries(item);
        chartView->chart()->createDefaultAxes();
    }
}

void Lab1::handlePselected(int selected)
{
    Q_ASSERT(seriesP);
    if(selected == 2)
    {
        chartView->chart()->addSeries(seriesP);
        chartView->chart()->createDefaultAxes();
    }
    else
    {
        chartView->chart()->removeSeries(seriesP);
        auto series = chartView->chart()->series();
        for(auto item : series)
            chartView->chart()->removeSeries(item);
        for(auto item : series)
            chartView->chart()->addSeries(item);
        chartView->chart()->createDefaultAxes();
    }
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


void Lab1::calculateX()
{
    QVector<int> indexData = parsedIndex();
    double rangeF = -10;
    double rangeT = 10;
    if(rangeF>rangeT)
        return;
    int steps = this->steps->text().toInt();
    if(steps<=0)
        return;
    double step = (rangeT - rangeF)/steps;

    bool contains = chartView->chart()->series().contains(seriesX);
    if(contains)
       chartView->chart()->removeSeries(seriesX);

    seriesX->clear();
    for(double x = rangeF; x<=rangeT; x+=step)
        seriesX->append(x, xFunction(x, indexData));
    if(contains)
        handleXselected(2);
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
}

void Lab1::calculateY()
{
    QVector<int> indexData = parsedIndex();
    double rangeF = this->rangeFrom->value();
    double rangeT = this->rangeTo->value();
    if(rangeF>rangeT)
        return;
    int steps = this->steps->text().toInt();
    if(steps<=0)
        return;
    double step = (rangeT - rangeF)/steps;
    Q_ASSERT(indexData.length()>=6);

    bool contains = chartView->chart()->series().contains(seriesY);
    if(contains)
       chartView->chart()->removeSeries(seriesY);
    seriesY->clear();

    for(double x = rangeF; x<=rangeT; x+=step)
        seriesY->append(x, yFunction(x, parsedIndex()));

    if(contains)
        handleYselected(2);
}

void Lab1::calculateZ()
{
    QVector<int> indexData = parsedIndex();
    double rangeF = this->rangeFrom->value();
    double rangeT = this->rangeTo->value();
    if(rangeF>rangeT)
        return;
    int steps = this->steps->text().toInt();
    if(steps<=0)
        return;
    double step = (rangeT - rangeF)/steps;
    Q_ASSERT(indexData.length()>=6);

    bool contains = chartView->chart()->series().contains(seriesZ);
    if(contains)
       chartView->chart()->removeSeries(seriesZ);

    seriesZ->clear();
    for(double x = rangeF; x<=rangeT; x+=step)
        seriesZ->append(x, zFunction(x, parsedIndex()));

    if(contains)
        handleZselected(2);

}

void Lab1::calculateU()
{
    QVector<int> indexData = parsedIndex();
    double rangeF = this->rangeFrom->value();
    double rangeT = this->rangeTo->value();
    if(rangeF>rangeT)
        return;
    int steps = this->steps->text().toInt();
    if(steps<=0)
        return;
    double step = (rangeT - rangeF)/steps;
    Q_ASSERT(indexData.length()>=6);

    bool contains = chartView->chart()->series().contains(seriesU);
    if(contains)
       chartView->chart()->removeSeries(seriesU);

    seriesU->clear();
    for(double x = rangeF; x<=rangeT; x+=step)
        seriesU->append(x, uFunction(x, parsedIndex()));

    if(contains)
        handleUselected(2);
}

void Lab1::calculateV()
{
    double range1From = rangeFrom1->value();
    double range2From = rangeFrom2->value();
    double range3From = rangeFrom3->value();
    double range1To = rangeTo1->value();
    double range2To = rangeTo2->value();
    double range3To = rangeTo3->value();

    int steps = this->steps->text().toInt();
    if(steps<=0)
        return;
    if(range1From<range1To || range2From>range2To || range3From<range3To)
        return;
    if(range1To>range3From)
        return;
    double step = (range3From - range1To)/steps;

    bool contains = chartView->chart()->series().contains(seriesV);
    if(contains)
       chartView->chart()->removeSeries(seriesV);

    seriesV->clear();
    for(double x = range1To; x<range1From; x+=step)
        seriesV->append(x, (1-7*x)*qSin((2*M_PI*x*10)/(x+0.04)));
    for(double x = range2From; x<range2To; x+=step)
        seriesV->append(x, 0.63*x*qSin(125*x));
    for(double x = range3To; x<=range3From; x+=step)
        seriesV->append(x, qPow(x, -0.662)+0.77*qSin(8*x));

    if(contains)
        handleVselected(2);

}

void Lab1::calculateP()
{
    QVector<int> set = parsedNumberSet();
    double rangeF = this->rangeFrom->value();
    double rangeT = this->rangeTo->value();
    if(rangeF>rangeT)
        return;
    int steps = this->steps->text().toInt();
    if(steps<=0)
        return;
    double step = (rangeT - rangeF)/steps;
    Q_ASSERT(set.length()>=3);

    bool contains = chartView->chart()->series().contains(seriesP);
    if(contains)
       chartView->chart()->removeSeries(seriesP);

    seriesP->clear();
    for(double x = rangeF; x<=rangeT; x+=step)
    {
        double y=0;
        for(int number=1; number<=set[2]; number++)
        {
            y += (qCos(12*x*number*number) + qCos(16*x*number))/(number*number);
        }
        seriesP->append(x, y);
    }

    if(contains)
        handlePselected(2);
}
