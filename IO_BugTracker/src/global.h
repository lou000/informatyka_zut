#pragma once
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QAbstractEventDispatcher>
#include <QCoreApplication>

inline std::string const &_sqlConnectionString = std::string();


inline void infoBox(const QString &str)
{
    QMetaObject::invokeMethod(QAbstractEventDispatcher::instance(QCoreApplication::instance()->thread()),[=]{
        QMessageBox msgbox;
        msgbox.setText(str);
        msgbox.setWindowFlag(Qt::WindowStaysOnTopHint);
        msgbox.exec();
        msgbox.raise();
    });
}

inline bool importSqlConnectionString(QFile &file)
{
    if(!file.open(QIODevice::ReadOnly)) {
        infoBox("Couldn't open the file:\n " + file.fileName() +
                "\n\nThis file is required in order to connect with the database."
                "Please check if the file is present and its access settings are correct.");
        return false;
    }
    else
    {
        QString temp;
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            auto sLine = line.split(";");
            if(sLine.length()>0)
                temp.append(sLine.at(0)).append(";");
        }
        const_cast<std::string&>(_sqlConnectionString) = QString(temp).toStdString();
        return true;
    }
}
