#pragma once

#include <QObject>
#include <QDockWidget>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <QSpacerItem>
#include <QAction>
#include <QTableWidget>
#include "threadcontroller.h"

class ActionWindows : public QWidget
{
public:
    ActionWindows(QWidget* parent, ThreadController* controller);

private:
    ThreadController* controller;

    QDockWidget* issueWindow;
    QComboBox* issueType;
    QTextEdit* issueShortDesc;
    QTextEdit* issueDesc;
    QComboBox* issueStatus;
    QComboBox* issueProjName;
    QPushButton* issueAdd;
    QPushButton* issueAccept;
    QPushButton* issueDiscard;

    QDockWidget* userWindow;
    QLineEdit* userLogin;
    QLineEdit* userName;
    QLineEdit* userSurname;
    QComboBox* userPosition;
    QVector<QCheckBox*> userPermissions;
    QPushButton* userAdd;
    QPushButton* userAccept;
    QPushButton* userDiscard;

    QDockWidget* projectWindow;
    QLineEdit* projectName;
    QTextEdit* projectDesc;
    QPushButton* projectAdd;
    QPushButton* projectAccept;
    QPushButton* projectDiscard;

    QDockWidget* addUserToIssue;
    QTableWidget* menagersList;
    QTableWidget* programmersList;
    QTableWidget* testersList;
    QMap<User*, QCheckBox*> menagersChecks;
    QMap<User*, QCheckBox*> programmersChecks;
    QMap<User*, QCheckBox*> testersChecks;
    QPushButton* addUserToIssueAccept;
    QPushButton* addUserToIssueDiscard;


    void initIssueWindow();
    void initUserWindow();
    void initProjectWindow();
    void initAddUserToIssue();

public slots:
    void showIssueWindow(IssueTicket* issue = nullptr);
    void showUserWindow(User* user = nullptr);
    void showProjectWindow(Project* project = nullptr);
    void showAddUserToIssue(IssueTicket* issue = nullptr);
};
