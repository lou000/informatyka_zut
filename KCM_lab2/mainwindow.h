#pragma once

#include <QMainWindow>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QSplitter>
#include <QLabel>
#include <QDesktopWidget>
#include <QThreadPool>
#include "imageprocessing.h"
#define START_HEIGHT 600
#define START_WIDTH 1000
//TODO: add fps display, add mask selection

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QCamera* camera;
    MyVideoSurface* surface;
    QSplitter* splitter;
    QLabel* originalImage;
    QLabel* processedImage;


public slots:
    void handleAddProcessingToPool(const QImage &img);
    void handleProcessedImage(const QPixmap &img);
};

