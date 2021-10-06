#ifndef ADMIN_GUI_VIEWS_TOPBAR_H
#define ADMIN_GUI_VIEWS_TOPBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QPushButton>
#include <QResizeEvent>

class TopBar : public QWidget
{
    Q_OBJECT

public:

    explicit TopBar(QWidget *parent);

    ~TopBar();

    void setData(QString &rank, QString &FCS, QString &role);

signals:

    void hideAdditionalSettings(bool state);
    void setTheme(bool state);

private:

    void initUI();

    void applyStyle();

    void insertWidgetsIntoLayouts();

    void createConnections();

private:

    QDateTime *m_dateTime;

    QTimer *m_timer;

    QHBoxLayout *m_userInfoLayout;

    QLabel *m_currentUserNameLabel;

    QLabel *m_currentTimeLabel;

    QLabel *m_currentUseRoleLabel;

    QPushButton *m_settingsPushButtton;

    QPushButton *m_themePushButtton;

private slots:

    void onSettingsButtonClick(bool state);
    void onThemeButtonClick(bool state);
    void refreshDateTime();

private:

    QFont *m_titleFont;
    const int m_smallFontSize=10;
    const int m_bigFontSize=17;

private:

    void calculateFontSize(int width);
protected:

    void resizeEvent(QResizeEvent *event);
};

#endif // ADMIN_GUI_VIEWS_TOPBAR_H
