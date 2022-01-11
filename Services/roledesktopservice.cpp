#include <QStandardItemModel>
#include <QList>

#include "Services/Terminals/terminal.h"
#include "Services/Sql/isqlservice.h"

#include "roledesktopservice.h"

RoleDesktopService::RoleDesktopService(Terminal *terminal, ISqlDatabaseService *sqlDatabaseService)
    : DesktopService(terminal, sqlDatabaseService)
{

}

RoleDesktopService::~RoleDesktopService()
{

}

void RoleDesktopService::CheckRoleDesktopTable(const quint8 &roleId)
{
    m_sqlDatabaseService->CreateDesktopRolesIfNotExists(roleId);
}

void RoleDesktopService::GetAllRoleDesktops(const quint8 &roleId)
{
    const QList<DesktopEntity> listOfDesktops= m_sqlDatabaseService->GetAllRoleDesktops(roleId);
    UpdateModel(listOfDesktops);
}

void RoleDesktopService::AddIconToRole(const quint8 &roleId, const DesktopEntity &entity)
{
    const QStringList userWithThisRoleId=m_sqlDatabaseService->GetAllUsersWithRoleId(roleId);
    for (const QString &userName: userWithThisRoleId)
    {
        const QString userDesktopPath = GetUserDesktopPath(userName);
        CreateIconWithData(userDesktopPath, entity);
    }
    m_sqlDatabaseService->AppendDesktopIntoRole(roleId, entity);
    GetAllRoleDesktops(roleId);
}

void RoleDesktopService::DeleteIconToRole(const quint8 &roleId, const QString iconName)
{
    const QStringList userWithThisRoleId=m_sqlDatabaseService->GetAllUsersWithRoleId(roleId);
    for (const QString &userName: userWithThisRoleId)
    {
        const QString userDesktopPath = GetUserDesktopPath(userName);
        CheckPath(userDesktopPath);
        DeleteIcon(userDesktopPath+iconName);
    }
    m_sqlDatabaseService->RemoveDesktopIntoRole(roleId, iconName);
    GetAllRoleDesktops(roleId);
}

void RoleDesktopService::SetDefaultIconsToUserOnUserRoleUpdate(const quint8 &oldRoleId, const quint8 &newRoleId, const QString &currentUserName)
{
    const QString userDesktopPath = GetUserDesktopPath(currentUserName);
    CheckPath(userDesktopPath);
    if(oldRoleId>=0 && oldRoleId<Roles.count())
    {
        DeleteOldIconsFromUser(oldRoleId, userDesktopPath);
    }
    SetIconsToUser(newRoleId, userDesktopPath);
}

void RoleDesktopService::DeleteOldIconsFromUser(const quint8 &roleId, const QString &userDesktopPath)
{
    const QList<DesktopEntity> listOfDesktopsToDelete= m_sqlDatabaseService->GetAllRoleDesktops(roleId);

    for (const DesktopEntity &entityToDelete: listOfDesktopsToDelete)
    {
        DeleteIcon(userDesktopPath+entityToDelete.name);
    }
}

void RoleDesktopService::SetIconsToUser(const quint8 &roleId, const QString &userDesktopPath)
{
    const QList<DesktopEntity> listOfDesktops= m_sqlDatabaseService->GetAllRoleDesktops(roleId);
    for (const DesktopEntity &entity: listOfDesktops)
    {
        if (m_terminal->IsFileNotExists(userDesktopPath+entity.name, Q_FUNC_INFO, true))
        {
            CreateIconWithData(userDesktopPath, entity);
        }
    }
}

