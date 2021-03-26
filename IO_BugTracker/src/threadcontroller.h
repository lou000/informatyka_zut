#pragma once
#include <QMessageBox>
#include <QThread>
#include <QFile>
#include <QObject>
#include "user.h"
#include "issue.h"
#include "project.h"
#include "sqlworker.h"


class ThreadController : public QObject
{
    Q_OBJECT
public:
    ThreadController(int sqlUpdateInterval);
    SqlWorker* worker;
    QVector<User*> users;
    QVector<IssueTicket*> issues;
    QVector<Project*> projects;

private:
    QThread* sqlThread;
    int sqlUpdateInterval;


signals:
    void timerStart();
    void updateIssues();
    void updateUsers();
    void updateProjects();
    void addIssue(IssueTicket::IssueType type, QString s_desc, QString desc, IssueTicket::Status status, int proj_id);
    void addUser(const QString &login, const QString &name, const QString &surname,
                 User::UserPosition position, User::UserPermissionsFlags permissions);
    void addProject(const QString name, const QString desc);

    void editIssue(int id, IssueTicket::IssueType type, QString s_desc, QString desc, IssueTicket::Status status,
                   int proj_id, QDateTime statusDate);
    void editUser(int id, const QString &name, const QString &surname, User::UserPosition position,
                  User::UserPermissionsFlags permissions);
    void editProject(int id, const QString name, const QString desc);

    void deleteIssue(int id);
    void deleteUser(int id);
    void deleteProject(int id);

    void addUserToIssue(int id_user, int id_issue);
    void removeUserFromIssue(int id_user, int id_issue);


public slots:
    void receiveIssues(const QVector<IssueTicket*> &issues);
    void receiveUsers(const QVector<User *> &users);
    void receiveProjects(const QVector<Project *> &projects);
};

