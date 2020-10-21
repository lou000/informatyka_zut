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

        //crop image to fit frame
        float imgRatio = static_cast<float>(mirrored.width())/mirrored.height();
        float croppedOrig = imgRatio - ratioOriginal;
        float croppedProc = imgRatio - ratioProcessed;

        auto croppedOriginal = mirrored.copy(mirrored.height()*croppedOrig/2, 0,
                                             mirrored.height()*ratioOriginal, mirrored.height());
        auto croppedProcessed = mirrored.copy(mirrored.height()*croppedProc/2, 0,
                                             mirrored.height()*ratioProcessed, mirrored.height());

        QPixmap pix1 = QPixmap::fromImage(croppedOriginal).scaled(originalImage->size(), Qt::AspectRatioMode::KeepAspectRatioByExpanding);
        originalImage->setPixmap(pix1);
        emit doProcessImage(croppedProcessed);
        return true;
    }
    return false;
}

void MyVideoSurface::setImageRatios(float ratioProcessed, float ratioOriginal)
{
    this->ratioOriginal = ratioOriginal;
    this->ratioProcessed = ratioProcessed;
}

ImageProcessor::ImageProcessor(const QImage &img, ModeFlags flags)
{
    this->img = img;
    this->flags = flags;
}

void ImageProcessor::run()
{
    for(int w=0; w<img.width(); w++)
        for(int h=0; h<img.height(); h++)
        {
            QColor pixel = img.pixel(w, h);
            auto hue = pixel.hue();
            auto sat = pixel.saturationF();
            auto r = pixel.red();
            auto g = pixel.green();
            auto b = pixel.blue();

            auto Y = 0.299*r + 0.587*g + 0.114*b;
            auto Cb = - 0.1687*r - 0.3313*g + 0.5*b + 128;
            auto Cr = 0.5*r - 0.4187*g - 0.0813*b + 128;

            // Algorithm below is based on paper: https://arxiv.org/ftp/arxiv/papers/1708/1708.02694.pdf

            // Human Skin Detection Using RGB, HSV and YCbCr Color Models
            // by: S. Kolkur D. Kalbande P. Shimpi C. Bapat and J. Jatakia
            // Department of Computer Engineering, Thadomal Shahani Engineering College, Bandra,Mumbai, India
            // Department of Computer Engineering, Sardar Patel Institute of Technology, Andheri,Mumbai, India
            // kolkur.seema@gmail.com; drkalbande@spit.ac.in; prajwalshimpi@gmail.com; chai.bapat@gmail.com;
            // jatakiajanvi12@gmail.com


            int pixVal = 255;
            bool hsvMask = 0;
            bool rgbMask = 0;
            bool YCbCrMask = 0;

            //0.0 <= H <= 50.0 and 0.23 <= S <= 0.68
            if(flags.testFlag(Mode::HSV) || flags.testFlag(Mode::Full))
                hsvMask = hue >= 0 && hue <= 50 && sat >= 0.23 && sat<= 0.68;

            //R > 95 and G > 40 and B > 20 and R > G and R > B and | R - G | > 15 and A > 15
            if(flags.testFlag(Mode::RGB) || flags.testFlag(Mode::Full))
                rgbMask = r>95 && g > 40 && b > 20 && r>g && r>b && abs(r-g) > 15;

            // Cr > 135 and Cb > 85 and Y > 80 and Cr <= (1.5862*Cb)+20 and
            // Cr>=(0.3448*Cb)+76.2069 and Cr >= (-4.5652*Cb)+234.5652 and
            // Cr <= (-1.15*Cb)+301.75 and Cr <= (-2.2857*Cb)+432.85
            if(flags.testFlag(Mode::YCbCr) || flags.testFlag(Mode::Full))
                YCbCrMask = Cr > 135 && Cb > 85 && Y > 80 && Cr <= (1.5862*Cb)+20
                            && Cr>=(0.3448*Cb)+76.2069 && Cr >= (-4.5652*Cb)+234.5652
                            && Cr <= (-1.15*Cb)+301.75 && Cr <= (-2.2857*Cb)+432.85;

            if(flags.testFlag(Mode::Full))
                pixVal *= ((rgbMask && YCbCrMask) || (rgbMask && hsvMask));
            else
                pixVal *= rgbMask || YCbCrMask || hsvMask;

            QRgb val = qRgb(pixVal, pixVal, pixVal);
            img.setPixel(w, h, val);
        }
    emit imageProcessed(QPixmap::fromImage(img));
}

