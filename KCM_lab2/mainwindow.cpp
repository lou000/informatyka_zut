#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setStyleSheet("background-color: #353c40;");
    splitter = new QSplitter(this);
    camera = new QCamera(this);
    processedImage = new QLabel(this);
    originalImage = new QLabel(this);
    surface = new MyVideoSurface(originalImage, this);

    connect(surface, SIGNAL(doProcessImage(const QImage)), this, SLOT(handleAddProcessingToPool(const QImage)));

    camera->setViewfinder(surface);
    camera->imageProcessing()->setDenoisingLevel(1);
    resize(START_WIDTH, START_HEIGHT);

    originalImage->setMinimumSize(QSize(100, 100));
    processedImage->setMinimumSize(QSize(100, 100));
    splitter->addWidget(originalImage);
    splitter->addWidget(processedImage);
    splitter->setSizes(QList<int>()<<this->width()/2<<this->width()/2);

    setCentralWidget(splitter);
    camera->start();
}

MainWindow::~MainWindow()
{

}

void MainWindow::handleAddProcessingToPool(const QImage &img)
{
    auto runnable = new ImageProcessor(img);
    connect(runnable, SIGNAL(imageProcessed(const QPixmap)), this, SLOT(handleProcessedImage(const QPixmap)));
    QThreadPool::globalInstance()->start(runnable);
}

void MainWindow::handleProcessedImage(const QPixmap &img)
{
    processedImage->setPixmap(img.scaled(originalImage->size(), Qt::AspectRatioMode::KeepAspectRatioByExpanding));
}

