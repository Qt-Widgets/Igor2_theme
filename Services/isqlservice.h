#ifndef ISQLSERVICE_H
#define ISQLSERVICE_H

#include "Structs/userstruct.h"
#include "Structs/programstruct.h"

class ISqlDatabaseService
{
public:

    //check Tables
    virtual bool CheckUserTable() = 0;

    virtual bool CheckExecTables() = 0;

    virtual bool ChekcDesktopTables() = 0;

    //clear tables

    virtual void ClearUserTable() = 0;

    virtual void ClearExecsTable(quint8 roleId) = 0;

    virtual void ClearDesktopTable(quint8 roleId) = 0;

    //create Tables    
    virtual void CreateUsersTableIfNotExists() = 0;

    virtual void CreateExecsTableInNotExists(quint8 roleId) = 0;

    virtual void CreateDesktopRolesIfNotExists(quint8 roleId) = 0;

    //users
    virtual void AppendUserIntoTable(User &user) = 0;

    virtual void RemoveUserIntoTable(quint8 roleId, User &user) = 0;

    virtual QList<User> GetAllUsers() = 0;

    //execs
    virtual void AppendExecIntoRole(quint8 roleId, const QString &startupPath) = 0;

    virtual void RemoveExecIntoRole(quint8 roleId, const QString &startupPath) = 0;

    virtual QStringList GetAllRoleExecs(quint8 roleId) = 0;

    //desktops
    virtual void AppendDesktopIntoRole(quint8 roleId, DesktopEntity &entity) = 0;

    virtual void RemoveDesktopIntoRole(quint8 roleId, DesktopEntity &entity) = 0;

    virtual QList<DesktopEntity> GetAllRoleDesktops(quint8 roleId) = 0;

    //admin

    virtual QStringList GetAdminsRoleUserName() = 0;

    virtual QString GetUserFCS(QString &userName) = 0;

    virtual QString GetUserRank(QString &userName) = 0;

    virtual QString GetUserRole(const QString &userName) = 0;

};

#endif // ISQLSERVICE_H
