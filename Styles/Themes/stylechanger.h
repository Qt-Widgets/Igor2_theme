#ifndef STYLES_THEMES_STYLECHANGER_H
#define STYLES_THEMES_STYLECHANGER_H

#include <QFile>
#include <QApplication>
#include <QPalette>
#include <QPair>

#include "Styles/Themes/themecolors.h"
#include "Styles/Themes/theme.h"

class StyleChanger: public QObject
{
   Q_OBJECT
public:
   StyleChanger(QApplication *app);
   ~StyleChanger();

public slots:

   void hangeTheme(bool state);

private:
   bool currentThemeIsWhite;

   Theme *m_darkTheme;
   Theme *m_whiteTheme;

   QString m_styleSheet;
   QApplication *m_myApp;
};

#endif // STYLES_THEMES_STYLECHANGER_H
