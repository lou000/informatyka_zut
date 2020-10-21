#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setStyleSheet("background-color: #353c40;");
    this->flags.setFlag(ImageProcessor::Mode::Full, true);
    resize(START_WIDTH, START_HEIGHT);
    splitter = new QSplitter(this);
    camera   = new QCamera(this);
    auto imageProcessing = camera->imageProcessing();

    left  = new QWidget(this);
    left->setContentsMargins(0,0,0,0);
    QGridLayout* leftLayout = new QGridLayout;
    leftLayout->setMargin(0);
    leftLayout->setSpacing(0);
    left->setLayout(leftLayout);

    right = new QWidget(this);
    right->setContentsMargins(0,0,0,0);
    QGridLayout* rightLayout = new QGridLayout;
    rightLayout->setMargin(0);
    rightLayout->setSpacing(0);
    right->setLayout(rightLayout);


    splitter->addWidget(left);
    splitter->addWidget(right);
    splitter->setSizes(QList<int>()<<this->width()/2<<this->width()/2);



//    QGridLayout* leftLayout = new QGridLayout;
//    leftLayout->addWidget(saturation, 0, 0);
//    leftLayout->addWidget(saturation, 0, 1);
//    leftLayout->addWidget(saturation, 0, 2);
//    leftLayout->addWidget(saturation, 0, 3);
//    leftLayout->addWidget(saturation, 0, 4);
//    leftLayout->addWidget(saturation, 0, 5);

    originalImage  = new QLabel(left);
    processedImage = new QLabel(right);
    originalImage->setMinimumSize(QSize(100, 100));
    processedImage->setMinimumSize(QSize(100, 100));

    float initialRatio = (static_cast<float>(this->width())/2)/this->height();
    surface = new MyVideoSurface(originalImage, initialRatio, initialRatio, this);
    connect(splitter, &QSplitter::splitterMoved, this, [&]{
        surface->setImageRatios(static_cast<float>(processedImage->width())/processedImage->height(),
                                static_cast<float>((float)originalImage->width())/processedImage->height());
    });
    camera->setViewfinder(surface);
    connect(surface, SIGNAL(doProcessImage(const QImage)), this, SLOT(handleAddProcessingToPool(const QImage)));

    leftLayout->addWidget(originalImage, 0, 0);
    rightLayout->addWidget(processedImage, 0, 0);


    /////////////CONTROLS/////////////////////
    leftControls = new QWidget(this);
    leftControls->setStyleSheet("background-color: transparent;");
    QGridLayout* leftControlsLayout = new QGridLayout;
    leftControls->setLayout(leftControlsLayout);

    auto shadow1 = new QGraphicsDropShadowEffect(this);
    shadow1->setOffset(0,0);
    shadow1->setBlurRadius(10);
    shadow1->setColor(QColor(0, 0, 0, 255));
    auto shadow2 = new QGraphicsDropShadowEffect(this);
    shadow2->setOffset(0,0);
    shadow2->setBlurRadius(10);
    shadow2->setColor(QColor(0, 0, 0, 255));
    auto shadow3 = new QGraphicsDropShadowEffect(this);
    shadow3->setOffset(0,0);
    shadow3->setBlurRadius(10);
    shadow3->setColor(QColor(0, 0, 0, 255));
    auto shadow4 = new QGraphicsDropShadowEffect(this);
    shadow4->setOffset(0,0);
    shadow4->setBlurRadius(10);
    shadow4->setColor(QColor(0, 0, 0, 255));
    auto shadow5 = new QGraphicsDropShadowEffect(this);
    shadow5->setOffset(0,0);
    shadow5->setBlurRadius(10);
    shadow5->setColor(QColor(0, 0, 0, 255));
    auto shadow6 = new QGraphicsDropShadowEffect(this);
    shadow6->setOffset(0,0);
    shadow6->setBlurRadius(10);
    shadow6->setColor(QColor(0, 0, 0, 255));

    /////////SATURATION
    saturation   = new QSlider(Qt::Orientation::Horizontal, leftControls);
    saturation->setMinimum(-100);
    saturation->setMaximum(100);
    saturation->setValue(0);
    connect(saturation, &QSlider::valueChanged, this, [=](int val)
            {
                imageProcessing->setSaturation(static_cast<qreal>(val)/100);
            });
    leftControlsLayout->addWidget(saturation, 1, 0);
    auto lab1 = new QLabel("Saturation:");
    lab1->setGraphicsEffect(shadow1);
    lab1->setStyleSheet("color: white");
    leftControlsLayout->addWidget(lab1, 0, 0);

    /////////BRIGHTNESS
    brightness   = new QSlider(Qt::Orientation::Horizontal, leftControls);
    brightness->setMinimum(-100);
    brightness->setMaximum(100);
    brightness->setValue(0);
    connect(brightness, &QSlider::valueChanged, this, [=](int val)
            {
                imageProcessing->setBrightness(static_cast<qreal>(val)/100);
            });
    leftControlsLayout->addWidget(brightness, 1, 1);
    auto lab2 = new QLabel("Brightness:");
    lab2->setGraphicsEffect(shadow2);
    lab2->setStyleSheet("color: white");
    leftControlsLayout->addWidget(lab2, 0, 1);

    //////////CONTRAST
    contrast     = new QSlider(Qt::Orientation::Horizontal, leftControls);
    contrast->setMinimum(-100);
    contrast->setMaximum(100);
    contrast->setValue(0);
    connect(contrast, &QSlider::valueChanged, this, [=](int val)
            {
                imageProcessing->setContrast(static_cast<qreal>(val)/100);
            });
    leftControlsLayout->addWidget(contrast, 1, 2);
    auto lab3 = new QLabel("Contrast:");
    lab3->setGraphicsEffect(shadow3);
    lab3->setStyleSheet("color: white");
    leftControlsLayout->addWidget(lab3, 0, 2);

    //////////DENOISING
    denoising    = new QSlider(Qt::Orientation::Horizontal, leftControls);
    denoising->setMinimum(-100);
    denoising->setMaximum(100);
    denoising->setValue(0);
    connect(denoising, &QSlider::valueChanged, this, [=](int val)
            {
                imageProcessing->setDenoisingLevel(static_cast<qreal>(val)/100);
            });
    leftControlsLayout->addWidget(denoising, 3, 0);
    auto lab4 = new QLabel("Denoising:");
    lab4->setGraphicsEffect(shadow4);
    lab4->setStyleSheet("color: white");
    leftControlsLayout->addWidget(lab4, 2, 0);

    //////////SHARPENING
    sharpening   = new QSlider(Qt::Orientation::Horizontal, leftControls);
    sharpening->setMinimum(-100);
    sharpening->setMaximum(100);
    sharpening->setValue(0);
    connect(sharpening, &QSlider::valueChanged, this, [=](int val)
            {
                imageProcessing->setSharpeningLevel(static_cast<qreal>(val)/100);
            });
    leftControlsLayout->addWidget(sharpening, 3, 1);
    auto lab5 = new QLabel("Sharpening:");
    lab5->setGraphicsEffect(shadow5);
    lab5->setStyleSheet("color: white");
    leftControlsLayout->addWidget(lab5, 2, 1);

    //////////WHITEBALANCE
    whiteBalance = new QSlider(Qt::Orientation::Horizontal, leftControls);
    whiteBalance->setMinimum(-100);
    whiteBalance->setMaximum(100);
    whiteBalance->setValue(0);
    connect(whiteBalance, &QSlider::valueChanged, this, [=](int val)
            {
                imageProcessing->setManualWhiteBalance(static_cast<qreal>(val)/100);
            });
    leftControlsLayout->addWidget(whiteBalance, 3, 2);
    auto lab6 = new QLabel("White balance:");
    lab6->setGraphicsEffect(shadow6);
    lab6->setStyleSheet("color: white");
    leftControlsLayout->addWidget(lab6, 2, 2);

    leftControlsLayout->addItem(new QSpacerItem(100, 100), 4, 0);
    leftControlsLayout->setRowStretch(0, 1);
    leftControlsLayout->setRowStretch(1, 2);
    leftControlsLayout->setRowStretch(2, 1);
    leftControlsLayout->setRowStretch(3, 2);
    leftControlsLayout->setRowStretch(4, 20);



    rightControls = new QWidget(this);
    rightControls->setStyleSheet("background-color: transparent;");
    QGridLayout* rightControlsLayout = new QGridLayout;
    rightControls->setLayout(rightControlsLayout);

    rgbMask   = new QPushButton("RGB", rightControls);
    rgbMask->setCheckable(true);
    rgbMask->setStyleSheet("QPushButton {background-color: #353c40; color: white} QPushButton:checked { background-color: #007AD9; }");
    rightControlsLayout->addWidget(rgbMask, 0, 0);
    connect(rgbMask, &QPushButton::toggled, this, [=](bool checked)
            {
                flags.setFlag(ImageProcessor::Mode::RGB, checked);
                if(checked)
                    fullMask->setChecked(false);
            });

    hsvMask   = new QPushButton("HSV", rightControls);
    hsvMask->setCheckable(true);
    hsvMask->setStyleSheet("QPushButton {background-color: #353c40; color: white} QPushButton:checked { background-color: #007AD9; }");
    rightControlsLayout->addWidget(hsvMask, 0, 1);
    connect(hsvMask, &QPushButton::toggled, this, [=](bool checked)
            {
                flags.setFlag(ImageProcessor::Mode::HSV, checked);
                if(checked)
                    fullMask->setChecked(false);
            });

    YCbCrMask = new QPushButton("YCbCr", rightControls);
    YCbCrMask->setCheckable(true);
    YCbCrMask->setStyleSheet("QPushButton {background-color: #353c40; color: white} QPushButton:checked { background-color: #007AD9; }");
    rightControlsLayout->addWidget(YCbCrMask, 0, 2);
    connect(YCbCrMask, &QPushButton::toggled, this, [=](bool checked)
            {
                flags.setFlag(ImageProcessor::Mode::YCbCr, checked);
                if(checked)
                    fullMask->setChecked(false);
            });

    fullMask  = new QPushButton("FULL", rightControls);
    fullMask->setCheckable(true);
    fullMask->setChecked(true);
    fullMask->setStyleSheet("QPushButton {background-color: #353c40; color: white} QPushButton:checked { background-color: #007AD9; }");
    rightControlsLayout->addWidget(fullMask, 0, 3);
    connect(fullMask, &QPushButton::toggled, this, [=](bool checked)
            {
                flags.setFlag(ImageProcessor::Mode::Full, checked);
                if(checked)
                {
                    hsvMask->setChecked(false);
                    rgbMask->setChecked(false);
                    YCbCrMask->setChecked(false);
                }
            });

    leftLayout->addWidget(leftControls, 0, 0);
    rightLayout->addWidget(rightControls, 0, 0);

    rightControlsLayout->addItem(new QSpacerItem(100, 100), 1, 0);
    rightControlsLayout->setRowStretch(0, 1);
    rightControlsLayout->setRowStretch(1, 9);




    setCentralWidget(splitter);
    camera->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::handleAddProcessingToPool(const QImage &img)
{
    auto runnable = new ImageProcessor(img, flags);
    connect(runnable, SIGNAL(imageProcessed(const QPixmap)), this, SLOT(handleProcessedImage(const QPixmap)));
    QThreadPool::globalInstance()->start(runnable);
}

void MainWindow::handleProcessedImage(const QPixmap &img)
{
    processedImage->setPixmap(img.scaled(originalImage->size(), Qt::AspectRatioMode::KeepAspectRatioByExpanding));
}

