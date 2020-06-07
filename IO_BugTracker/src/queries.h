#pragma once
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QDateTime>

namespace Queries{

void initDb();
bool isDbOpen();

QSqlQuery setqGetIssues(QString connection);

};
