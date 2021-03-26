#pragma once
#include <QTimer>
#include <QObject>
#include <QVector>
#include "issue.h"
#include "project.h"
#include "queries.h"

class SqlWorker : public QObject
{
    Q_OBJECT
public:
    bool timerStop = false;
    SqlWorker(int timerInterval);
    QTimer* updateTimer;

    int timerInterval;
    void checkDbAndUpdate();
    void updateData();

signals:
    void resultIssues(const QVector<IssueTicket*> &issues);
    void resultUsers(const QVector<User*> &users);
    void resultProjects(const QVector<Project*> &issues);

public slots:
    void timerStart() {updateTimer->start(timerInterval); checkDbAndUpdate();}
    void handleAddIssue(IssueTicket::IssueType type, const QString &s_desc, const QString &desc,IssueTicket::Status status, int proj_id);
    void handleAddUser(const QString &login, const QString &name, const QString &surname,
                       User::UserPosition position, User::UserPermissionsFlags permissions);
    void handleAddProject(const QString name, const QString desc);

    void handleEditIssue(int id, IssueTicket::IssueType type, const QString &s_desc, const QString &desc, IssueTicket::Status status, int proj_id, QDateTime statusDate);
    void handleEditUser(int id, const QString &name, const QString &surname,
                       User::UserPosition position, User::UserPermissionsFlags permissions);
    void handleEditProject(int id, const QString name, const QString desc);

    void handleDeleteIssue(int id);
    void handleDeleteUser(int id);
    void handleDeleteProject(int id);

    void handleAddUserToIssue(int id_user, int id_issue);
    void handleRemoveUserFromIssue(int id_user, int id_issue);
};


