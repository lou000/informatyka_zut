#include "mainwindow.h"
#include "external/framelesswindow/framelesswindow.h"
#include "external/DarkStyle.h"
#include <QScreen>
#include <QApplication>
#include "threadcontroller.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(QCoreApplication::applicationDirPath() + "/SqlConnectionSettings.txt");
    importSqlConnectionString(file);
    a.setStyle(new DarkStyle);
    FramelessWindow* framelessWindow = new FramelessWindow();
    MainWindow* window = new MainWindow(framelessWindow);
    framelessWindow->setContent(window);
    framelessWindow->setWindowTitle("BugTracker   -   Project IO   -   by Lewicki Maciej and Jakub Kościołowski");
    QFont font = QFont("Calibri", 12);
    a.setFont(font);
    QObject::connect(window, &MainWindow::move, framelessWindow, [=](int x, int y)
    {
        framelessWindow->move(x, y);
    });
    QObject::connect(window, &MainWindow::show, framelessWindow, [=]
    {
        framelessWindow->show();
    });
    return a.exec();
}
