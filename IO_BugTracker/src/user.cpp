#include "user.h"

User::User(int id, const QString &login, const QString &name, const QString &surname, const UserPosition &position,
           UserPermissionsFlags permisions)
     : m_id(id), m_login(login), m_name(name), m_surname(surname), m_position(position), m_permisions(permisions)
{

}
