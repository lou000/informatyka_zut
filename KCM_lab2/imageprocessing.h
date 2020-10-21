#pragma once

#include <QObject>
#include <QAbstractVideoSurface>
#include <QLabel>
#include <QDebug>
#include <QThread>
#include <QRunnable>

/////////////////////////////////////////////////////////////////////////////////////
/// \brief The MyVideoSurface class
///
class MyVideoSurface: public QAbstractVideoSurface{
    Q_OBJECT
public:
    MyVideoSurface(QLabel* oImage, float rProcessed, float rOriginal, QObject* parent = nullptr) : QAbstractVideoSurface(parent)
    {
        originalImage = oImage;
        ratioOriginal = rOriginal;
        ratioProcessed = rProcessed;
    }

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const;
    bool present(const QVideoFrame& frame);

private:
    QLabel* originalImage;
    float ratioProcessed;
    float ratioOriginal;

signals:
    void doProcessImage(const QImage &img);

public slots:
    void setImageRatios(float ratioProcessed, float ratioOriginal);
};


/////////////////////////////////////////////////////////////////////////////////////
/// \brief The ImageProcessor class
///
class ImageProcessor : public QObject, public QRunnable
{
    Q_OBJECT
public:
    enum Mode{
        RGB = 1,
        HSV = 2,
        YCbCr = 4,
        Full = 8
    };
    Q_ENUM(Mode)
    Q_DECLARE_FLAGS(ModeFlags, Mode)

    ImageProcessor(const QImage &img, ModeFlags flags);
    virtual void run() override;

private:
    QImage img;
    ModeFlags flags;

signals:
    void imageProcessed(const QPixmap &img);

};
Q_DECLARE_OPERATORS_FOR_FLAGS(ImageProcessor::ModeFlags)
