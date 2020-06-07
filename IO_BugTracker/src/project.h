#pragma once
#include <QString>
#include "user.h"
#include "issue.h"
class Project
{
public:
    Project(int id, const QString &name, const QVector<IssueTicket*> &issues, const QVector<User*> &users);

    int id() const {return m_id;}
    QString name() const {return m_name;}
    QVector<IssueTicket *> issues() const {return m_issues;}
    QVector<User *> users() const {return m_users;}

    void setName(const QString &name) {m_name = name;}
    void addIssue(IssueTicket* issue) {m_issues.append(issue);}
    void removeIssue(IssueTicket* issue) {m_issues.removeOne(issue);}
    void addUser(User* user) {m_users.append(user);}
    void removeUser(User* user) {m_users.removeOne(user);}

private:
    const int m_id;
    QString m_name;
    QVector<IssueTicket*> m_issues;
    QVector<User*> m_users; //???
};

