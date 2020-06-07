#include "project.h"

Project::Project(int id, const QString &name, const QVector<IssueTicket *> &issues, const QVector<User *> &users)
        : m_id(id), m_name(name), m_issues(issues), m_users(users)
{

}

