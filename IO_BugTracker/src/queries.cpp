#include "queries.h"

void Queries::initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "BugTracker");
    QString connectString = "Driver={SQL Server};"; // Driver is now {SQL Server}
    connectString.append("Server=192.168.1.128,1433;"); // IP,Port
    connectString.append("Database=IO_Bugtracker;");  // Schema
    connectString.append("Uid = Lewy;");           // User
    connectString.append("Pwd = lol;");           // Pass
    db.setDatabaseName(connectString);
    if (!db.open())
    {
        qDebug() << "IO_Bugtracker Database: ERROR connection with database fail";
    }
    else
    {
        qDebug() << "IO_Bugtracker Database: connection ok";
    }
}

bool Queries::isDbOpen()
{
    return QSqlDatabase::database("BugTracker").isOpen();
}

QSqlQuery Queries::setqGetIssues(QString connection)
{
    QSqlDatabase db = QSqlDatabase::database(connection);
    if(!db.isValid() || !db.isOpen())
        return QSqlQuery();
    QSqlQuery q(db);
    q.setForwardOnly(true);
    q.prepare("EXEC IO_BugTracker.dbo.getIssues;");
    return q;
}

QSqlQuery Queries::addIssue(IssueType type, QString s_desc, QString desc, Status status, int proj_id)
{
    QSqlDatabase db = QSqlDatabase::database("BugTracker");
    if(!db.isValid() || !db.isOpen())
        return QSqlQuery();
    QSqlQuery q(db);
    q.setForwardOnly(true);
    q.prepare("EXEC IO_BugTracker.dbo.addIssue :type, :s_desc, :desc, :status, :dateAdded, :dateStatus, :projID; " );
    q.bindValue(":type", type);
    q.bindValue(":s_desc", s_desc);
    q.bindValue(":desc", desc);
    q.bindValue(":status", status);
    q.bindValue(":dateAdded", QDateTime::currentDateTime());
    q.bindValue(":dateStatus", QDateTime::currentDateTime());
    q.bindValue(":projID", proj_id);
    return q;
}
