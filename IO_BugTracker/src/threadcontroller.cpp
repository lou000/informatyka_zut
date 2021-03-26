#include "threadcontroller.h"
#include <QMetaType>
ThreadController::ThreadController(int timer)
{

    this->issues = QVector<IssueTicket*>();
    this->sqlUpdateInterval = timer;
    this->sqlThread = new QThread();
    worker = new SqlWorker(timer);
    qRegisterMetaType<QVector<IssueTicket*>>("QVector<IssueTicket*>");
    qRegisterMetaType<QVector<User*>>("QVector<User*>");
    qRegisterMetaType<QVector<Project*>>("QVector<Project*>");
    qRegisterMetaType<User::UserPosition>("User::UserPosition");
    qRegisterMetaType<User::UserPermission>("User::UserPermission");
    qRegisterMetaType<User::UserPermissionsFlags>("User::UserPermissionsFlags");
    qRegisterMetaType<IssueTicket::IssueType>("IssueTicket::IssueType");
    qRegisterMetaType<IssueTicket::Status>("IssueTicket::Status");

    QObject::connect(this, SIGNAL(timerStart()), worker, SLOT(timerStart()));

    QObject::connect(worker, SIGNAL(resultIssues(const QVector<IssueTicket*>)),
                     this, SLOT(receiveIssues(const QVector<IssueTicket*>)));
    QObject::connect(worker, SIGNAL(resultUsers(const QVector<User*>)),
                     this, SLOT(receiveUsers(const QVector<User*>)));
    QObject::connect(worker, SIGNAL(resultProjects(const QVector<Project*>)),
                     this, SLOT(receiveProjects(const QVector<Project*>)));


    QObject::connect(this, SIGNAL(addIssue(IssueTicket::IssueType, QString, QString, IssueTicket::Status, int)),
                     worker, SLOT(handleAddIssue(IssueTicket::IssueType, QString, QString, IssueTicket::Status, int)));
    QObject::connect(this, SIGNAL(addUser(const QString, const QString, const QString,
                                                User::UserPosition, User::UserPermissionsFlags)),
                     worker, SLOT(handleAddUser(const QString, const QString, const QString,
                                                User::UserPosition, User::UserPermissionsFlags)));
    QObject::connect(this, SIGNAL(addProject(const QString, const QString)),
                     worker, SLOT(handleAddProject(const QString, const QString)));


    QObject::connect(this, SIGNAL(editIssue(int, IssueTicket::IssueType, QString, QString, IssueTicket::Status, int, QDateTime)),
                     worker, SLOT(handleEditIssue(int, IssueTicket::IssueType, QString, QString, IssueTicket::Status, int, QDateTime)));
    QObject::connect(this, SIGNAL(editUser(int, const QString, const QString, User::UserPosition,
                                           User::UserPermissionsFlags)),
                     worker, SLOT(handleEditUser(int, const QString, const QString, User::UserPosition,
                                                 User::UserPermissionsFlags)));
    QObject::connect(this, SIGNAL(editProject(int, const QString, const QString)),
                     worker, SLOT(handleEditProject(int, const QString, const QString)));


    QObject::connect(this, SIGNAL(deleteIssue(int)), worker, SLOT(handleDeleteIssue(int)));
    QObject::connect(this, SIGNAL(deleteUser(int)),worker, SLOT(handleDeleteUser(int)));
    QObject::connect(this, SIGNAL(deleteProject(int)),worker, SLOT(handleDeleteProject(int)));

    QObject::connect(this, SIGNAL(addUserToIssue(int, int)),worker, SLOT(handleAddUserToIssue(int, int)));
    QObject::connect(this, SIGNAL(removeUserFromIssue(int, int)),worker, SLOT(handleRemoveUserFromIssue(int, int)));


    worker->moveToThread(sqlThread);
    sqlThread->start();
    emit timerStart();
}


void ThreadController::receiveIssues(const QVector<IssueTicket*> &issues)
{
    this->issues = issues;
    emit updateIssues();
}

void ThreadController::receiveUsers(const QVector<User*> &users)
{
    this->users = users;
    emit updateUsers();
}

void ThreadController::receiveProjects(const QVector<Project*> &projects)
{
    this->projects = projects;
    emit updateProjects();
}










