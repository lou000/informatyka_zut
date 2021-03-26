#include "issue.h"
#include <QMap>

IssueTicket::IssueTicket(const IssueType type, int id, const QString &project, const QString &s_desc, const QString &desc,
                         Status status, QDateTime dateAdded, QDateTime dateStatusChanged)
      : m_type(type), m_id(id), m_project(project), m_shortDescription(s_desc), m_description(desc),
        m_status(status), m_dateAdded(dateAdded), m_dateStatusChanged(dateStatusChanged)
{

}

BugTicket::BugTicket(int id, const QString &project, const QString &s_desc, const QString &desc, Status status, QDateTime dateAdded, QDateTime dateStatusChanged)
    : IssueTicket(IssueType::Bug, id, project, s_desc, desc, status, dateAdded, dateStatusChanged)
{

}

TaskTicket::TaskTicket(int id, const QString &project, const QString &s_desc, const QString &desc,
                       Status status, QDateTime dateAdded, QDateTime dateStatusChanged)
    : IssueTicket(IssueType::Task, id, project, s_desc, desc, status, dateAdded, dateStatusChanged)
{

}

QIcon IssueTicket::getIconFromIssueType(IssueType type)
{
    QIcon i;
    switch(type)
    {
    case IssueType::Bug:
        i = QIcon(":/icons/bug_icon.png");
        break;
    case IssueType::Task:
        i = QIcon(":/icons/task_icon.png");
        break;
    default:
        break;
    }
    return i;
}


