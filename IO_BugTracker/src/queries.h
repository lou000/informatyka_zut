#pragma once
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QDateTime>
#include "issue.h"

namespace Queries{

void initDb();
bool isDbOpen();

QSqlQuery setqGetIssues(QString connection);
QSqlQuery addIssue(IssueType type, QString s_desc, QString desc, Status status, int proj_id);


};
