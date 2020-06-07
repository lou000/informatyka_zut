#pragma once
#include <QIcon>
#include <QDateTime>
#include <QImage>
#include <QFile>
#include "user.h"
enum IssueType
{
    Bug,
    Task
};

enum Status
{
    Created,
    InProgress,
    CheckIn,
    Approved,
    NotApproved,
    Closed
};

class IssueTicket
{
public:
    IssueType type() const              {return m_type;}
    int id() const                      {return m_id;}
    QString shortDescription() const    {return m_shortDescription;}
    QString description() const         {return m_description;}
    QString project() const             {return m_project;}
    User* manager() const               {return m_manager;}
    QVector<User*> programmers() const  {return m_programmers;}
    QVector<User*> testers() const      {return m_testers;}
    Status status() const               {return m_status;}
    const QDateTime dateAdded() const   {return m_dateAdded;}
    QDateTime dateStatusChanged() const {return m_dateStatusChanged;}


    void setShortDescription(const QString &shortDescription) {m_shortDescription = shortDescription;}
    void setDescription(const QString &description)           {m_description = description;}
    void setProject(const QString &project)                   {m_project = project;}
    void setManager(User *manager)                            {m_manager = manager;}
    void addProgrammer(User * programmer)                     {m_programmers.append(programmer);}
    void removeProgrammer(User * programmer)                  {m_programmers.removeOne(programmer);}
    void addTesters(User* tester)                             {m_testers.append(tester);}
    void removeTesters(User* tester)                          {m_testers.removeOne(tester);}
    void setStatus(Status status)                             {m_status = status;}

    static QIcon getIconFromIssueType(IssueType type);
    static QString getIssueTypeText(IssueType type);
    static IssueType getIssueTypeFromText(QString type);
    static QString getStatusText(Status s);
    static Status getStatusFromText(QString s);
//    virtual void saveChanges() = 0;

protected:
    IssueTicket(const IssueType type, int id, const QString &project, const QString &s_desc, const QString &desc,
          QVector<User *> programmers, QVector<User *> testers, Status status, QDateTime dateAdded,
          QDateTime dateStatusChanged);
    const IssueType m_type;
    const int m_id;
    QString m_project;
    QString m_shortDescription;
    QString m_description;
    User* m_manager;
    QVector<User*> m_programmers;
    QVector<User*> m_testers;
    Status m_status;
    const QDateTime m_dateAdded;
    QDateTime m_dateStatusChanged;
};

class BugTicket : public IssueTicket
{
public:
    BugTicket(int id, const QString &project, const QString &s_desc, const QString &desc, QVector<User*> programmers,
              QVector<User*> testers, Status status, QDateTime dateAdded, QDateTime dateStatusChanged);
//    void saveChanges() override;

    QString stackTrace() const           {return m_stackTrace;}
    QVector<QImage*> screenshots() const {return m_screenshots;}
    QVector<QFile*> logs() const         {return m_logs;}

    void setStackTrace(const QString &stackTrace) {m_stackTrace = stackTrace;}
    void addScreenshot(QImage* screenshot)        {m_screenshots.append(screenshot);}
    void removeScreenshot(QImage* screenshot)     {m_screenshots.removeOne(screenshot);}
    void addLog(QFile *log)                       {m_logs.append(log);}
    void removeLog(QFile *log)                    {m_logs.removeOne(log);}

private:
    QString m_stackTrace;
    QVector<QImage*> m_screenshots;
    QVector<QFile*> m_logs;
};

class TaskTicket : public IssueTicket
{
public:
    TaskTicket(int id, const QString &project, const QString &s_desc, const QString &desc, QVector<User*> programmers,
               QVector<User*> testers, Status status, QDateTime dateAdded, QDateTime dateStatusChanged);
//    void saveChanges() override;

    QVector<QFile*> additionalFiles() const {return m_additionalFiles;}

    void addAdditonalFile(QFile* file) {m_additionalFiles.append(file);}
    void removeAdditionalFile(QFile* file) {m_additionalFiles.removeOne(file);}

private:
    QVector<QFile*> m_additionalFiles;
};


