#include "imageprocessing.h"


QList<QVideoFrame::PixelFormat> MyVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    Q_UNUSED(type)
    return QList<QVideoFrame::PixelFormat>()
           << QVideoFrame::Format_RGB32
        ;
}

bool MyVideoSurface::present(const QVideoFrame &frame)
{
    if (frame.isValid()) {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        const QImage img(cloneFrame.bits(),
                         cloneFrame.width(),
                         cloneFrame.height(),
                         QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));


        auto mirrored = img.mirrored(true, true);

        QPixmap pix1 = QPixmap::fromImage(mirrored).scaled(originalImage->size(), Qt::AspectRatioMode::KeepAspectRatioByExpanding);
        originalImage->setPixmap(pix1);
        emit doProcessImage(mirrored);
        return true;
    }
    return false;
}

ImageProcessor::ImageProcessor(const QImage &img)
{
    this->img = img;
}

void ImageProcessor::run()
{
    auto temp = img.copy();
    for(int w=0; w<temp.width(); w++)
        for(int h=0; h<temp.height(); h++)
        {
            QColor pixel = temp.pixel(w, h);
            auto hue = pixel.hue();
            auto sat = pixel.saturationF();
            auto r = pixel.red();
            auto g = pixel.green();
            auto b = pixel.blue();

            auto Y = 0.299*r + 0.587*g + 0.114*b;
            auto Cb = - 0.1687*r - 0.3313*g + 0.5*b + 128;
            auto Cr = 0.5*r - 0.4187*g - 0.0813*b + 128;

            int pixVal = 0;
            //0.0 <= H <= 50.0 and 0.23 <= S <= 0.68
            bool hsvMask = hue >= 0 && hue <= 50 && sat >= 0.23 && sat<= 0.68;

            //R > 95 and G > 40 and B > 20 and R > G and R > B and | R - G | > 15 and A > 15
            bool rgbMask = r>95 && g > 40 && b > 20 && r>g && r>b && abs(r-g) > 15;

            // Cr > 135 and Cb > 85 and Y > 80 and Cr <= (1.5862*Cb)+20 and
            // Cr>=(0.3448*Cb)+76.2069 and Cr >= (-4.5652*Cb)+234.5652 and
            // Cr <= (-1.15*Cb)+301.75 and Cr <= (-2.2857*Cb)+432.85
            bool YCbCrMask = Cr > 135 && Cb > 85 && Y > 80 && Cr <= (1.5862*Cb)+20
                             && Cr>=(0.3448*Cb)+76.2069 && Cr >= (-4.5652*Cb)+234.5652
                             && Cr <= (-1.15*Cb)+301.75 && Cr <= (-2.2857*Cb)+432.85;

            pixVal = ((rgbMask && YCbCrMask) || (rgbMask && hsvMask))*255;
            QRgb val = qRgb(pixVal, pixVal, pixVal);
            temp.setPixel(w, h, val);
        }
    emit imageProcessed(QPixmap::fromImage(temp));
}

