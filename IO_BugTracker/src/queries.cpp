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
