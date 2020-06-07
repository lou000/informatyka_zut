#include "issue.h"
#include <QMap>

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


QString IssueTicket::getStatusText(Status s)
{
    QString status;
    switch(s)
    {
    case Status::Closed:
        status = "Closed";
        break;
    case Status::CheckIn:
        status = "CheckIn";
        break;
    case Status::Created:
        status = "Created";
        break;
    case Status::Approved:
        status = "Approved";
        break;
    case Status::InProgress:
        status = "InProgress";
        break;
    case Status::NotApproved:
        status = "NotApproved";
        break;
    default:
        break;
    }
    return status;
}

Status IssueTicket::getStatusFromText(QString s)
{
    if(s == "Closed")
        return Closed;
    else if (s == "CheckIn")
        return CheckIn;
    else if (s == "Created")
        return Created;
    else if (s == "Approved")
        return Approved;
    else if (s == "InProgress")
        return InProgress;
    else if (s == "NotApproved")
        return NotApproved;
    else return Created;
}

QString IssueTicket::getIssueTypeText(IssueType type)
{
    QString s;
    switch(type)
    {
    case IssueType::Bug:
        s = "Bug";
        break;
    case IssueType::Task:
        s = "Task";
        break;
    default:
        break;
    }
    return s;
}

IssueType IssueTicket::getIssueTypeFromText(QString type)
{
    if(type == "Bug")
        return Bug;
    else return Task;
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


