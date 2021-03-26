#pragma once
#include <QString>
#include "user.h"
#include "issue.h"
class Project
{
public:
    Project(int id, const QString &name, const QString &desc);

    int id() const {return m_id;}
    QString name() const {return m_name;}
    QString desc() const {return m_desc;}
    QVector<IssueTicket *> issues() const {return m_issues;}

    void setName(const QString &name) {m_name = name;}
    void setDesc(const QString &desc) {m_desc = desc;}
    void setIssues(const QVector<IssueTicket *> &issues) {m_issues = issues;}

private:
    const int m_id;
    QString m_name;
    QString m_desc;
    QVector<IssueTicket*> m_issues;
};

