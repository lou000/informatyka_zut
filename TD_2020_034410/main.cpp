#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "external/framelesswindow/framelesswindow.h"
#include "external/DarkStyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(new DarkStyle);
    FramelessWindow framelessWindow;
    MainWindow* w = new MainWindow();
    framelessWindow.setContent(w);
    framelessWindow.setWindowTitle(w->windowTitle());
    framelessWindow.show();
    return a.exec();
}
