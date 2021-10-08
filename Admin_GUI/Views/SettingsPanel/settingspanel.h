#ifndef ADMIN_GUI_VIEWS_EDITPANEL_H
#define ADMIN_GUI_VIEWS_EDITPANEL_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFrame>
#include <QComboBox>
#include <QMessageBox>
#include <QResizeEvent>

#include "Admin_GUI/Model/usermodel.h"
#include "Admin_GUI/Views/SettingsPanel/userinfopanel.h"
#include "Admin_GUI/Views/SettingsPanel/usereditpanel.h"

#include "Admin_GUI/Views/qtoast.h"

#include "Admin_GUI/Widgets/qtmaterialtoggle.h"

class SettingsPanel : public QWidget
{
    Q_OBJECT

public:

    explicit SettingsPanel(const QString &userName, UserModel *model, Terminal *terminal, QWidget *parent);
    ~SettingsPanel();

    void setUser(User &user);

signals:

    void setDefaultRoleApps(const QString &role);
    void roleToViewChanged(const QString &role);

protected:

    void resizeEvent(QResizeEvent *event) override;

private:

    void initUI(const QString &userName, UserModel *model, Terminal *terminal);
    void applyStyle();
    void insertWidgetsIntoLayout();
    void createConnections();

private:
    QVBoxLayout *m_mainLayout;
    UserInfoPanel *m_userInfoPanel;
    UserEditPanel *m_userEditPanel;

    int m_oldFontSize;

};

#endif // ADMIN_GUI_VIEWS_EDITPANEL_H