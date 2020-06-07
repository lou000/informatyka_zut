#include "issue.h"

IssueTicket::IssueTicket(const IssueType type, int id, const QString &project, const QString &s_desc, const QString &desc,
             QVector<User *> programmers,QVector<User *> testers, Status status, QDateTime dateAdded,
             QDateTime dateStatusChanged)
      : m_type(type), m_id(id), m_project(project), m_shortDescription(s_desc), m_description(desc), m_programmers(programmers),
        m_testers(testers), m_status(status), m_dateAdded(dateAdded), m_dateStatusChanged(dateStatusChanged)
{

}

BugTicket::BugTicket(int id, const QString &project, const QString &s_desc, const QString &desc, QVector<User *> programmers,
         QVector<User *> testers, Status status, QDateTime dateAdded, QDateTime dateStatusChanged)
    : IssueTicket(IssueType::Bug, id, project, s_desc, desc, programmers, testers, status, dateAdded, dateStatusChanged)
{

}

TaskTicket::TaskTicket(int id, const QString &project, const QString &s_desc, const QString &desc, QVector<User *> programmers,
           QVector<User *> testers, Status status, QDateTime dateAdded, QDateTime dateStatusChanged)
    : IssueTicket(IssueType::Task, id, project, s_desc, desc, programmers, testers, status, dateAdded, dateStatusChanged)
{

}


