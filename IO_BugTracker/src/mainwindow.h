#pragma once
#include <QMainWindow>
#include <QDockWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QSqlError>
#include <QSqlRecord>
#include <QScreen>
#include "external/hashing/hashlibpp.h"
#include "external/framelesswindow/framelesswindow.h"
#include "bugview.h"
#include "threadcontroller.h"
#include "src/actionwindows.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum LoginStatus{
        Success,
        Fail,
        ChangePassword
    };
    MainWindow(QWidget *parent = nullptr);
    FramelessWindow* window;

    void login();
    void changePassword(const QString &login);
    void init();

    void addNewHashAndSalt(const QString &login, const QString &password);
    LoginStatus checkLogin(const QString &login, const QString &password);

signals:
    void move(int x, int y);
    void show();

private:
    BugView* mainView;
    ActionWindows* aWindows;
    ThreadController* controller;

    QSqlQuery getUserPassword(const QString &login);
    QSqlQuery setUserPassword(const QString &login, const QString &hash, const QString &salt);

};

