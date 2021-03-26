#pragma once
#include <QtGlobal>
#include <QFlags>
#include <QString>
#include <QObject>
#include <QMetaEnum>

template<typename QEnum>
QString enumToString(const QEnum value)
{
  return QMetaEnum::fromType<QEnum>().valueToKey(value);
}

template<typename QEnum>
QEnum stringToEnum(const QString &value)
{
    return static_cast<QEnum>(QMetaEnum::fromType<QEnum>().keyToValue(value.toStdString().c_str()));
}

class User : public QObject
{
    Q_OBJECT
public:
enum UserPermission{
    CreateIssue       = 1,
    ModifyIssue       = 2,
    ModifyIssueStatus = 4,
    CreateProject     = 8,
    ModifyProject     = 16,
    CreateUser        = 32,
    ModifyUser        = 64
};
Q_ENUM(UserPermission)
Q_DECLARE_FLAGS(UserPermissionsFlags, UserPermission)

enum UserPosition{
    Administrator,
    Manager,
    Programmer,
    Tester
};
Q_ENUM(UserPosition)

public:
    User(int id, const QString &login, const QString &name, const QString &surname, const UserPosition &position,
         UserPermissionsFlags permisions);

    int id() const {return m_id;}
    QString login() const {return m_login;}
    QString name() const {return m_name;}
    QString surname() const {return m_surname;}
    UserPosition position() const {return m_position;}
    UserPermissionsFlags permisions() const {return m_permisions;}

    void setName(const QString &name) {m_name = name;}
    void setSurname(const QString &surname) {m_surname = surname;}
    void setPosition(const UserPosition &position) {m_position = position;}
    void addPermision(UserPermission permision) {m_permisions.setFlag(permision);}
    void revokePermision(UserPermission permision) {m_permisions.setFlag(permision, 0);}


private:
    const int m_id;
    const QString m_login;
    QString m_name;
    QString m_surname;
    UserPosition m_position;
    UserPermissionsFlags m_permisions;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(User::UserPermissionsFlags)
