#include "startupwizard.h"

StartupWizard::StartupWizard(const QString &rlsTiFolder, LoadingState &loadedDbAdnRolesState, LinuxUserService *linuxUserService, ISqlDatabaseService *iSqlDataBaseService, QWidget *parent)
    : QWizard(parent)
{
    CreateServices(rlsTiFolder, loadedDbAdnRolesState, linuxUserService, iSqlDataBaseService);
    CreateUI(loadedDbAdnRolesState);
    InitSizes();
    InitStyles();
    InitBehaviour();
    ConnectObjects();
}

StartupWizard::~StartupWizard()
{
    delete m_wizardService;
    delete m_introPage;
    delete m_userWizardPage;

    for (int i = 0; i < Roles.size(); ++i) {
        delete m_rolesPages.at(i);
    }

    delete m_conclusionPage;
    delete m_themePushButton;
}


void StartupWizard::CreateServices(const QString &rlsTiFolder, LoadingState &loadedDbAdnRolesState, LinuxUserService *linuxUserService, ISqlDatabaseService *iSqlDataBaseService)
{
    m_wizardService = new WizardService(rlsTiFolder, loadedDbAdnRolesState, linuxUserService, iSqlDataBaseService, this);
}

void StartupWizard::CreateUI(LoadingState &loadedDbAdnRolesState)
{
    m_themePushButton = new QPushButton();
    m_themePushButton->setCheckable(true);
    m_themePushButton->setChecked(1);
    m_themePushButton->setFlat(true);
    m_themePushButton->setDefault(false);
    m_themePushButton->setAutoDefault(false);
    m_themePushButton->setFocusPolicy(Qt::NoFocus);
    m_themePushButton->setIcon(QIcon(":/images/sun"));
    m_themePushButton->setIconSize(QSize(30, 30));

    m_introPage = new IntroPage(loadedDbAdnRolesState, m_wizardService, m_themePushButton, this);

    m_userWizardPage = new UserWizardPage(m_wizardService, m_themePushButton, this);
    m_rolesPages.resize(Roles.size());

    for (int i = 0; i < Roles.size(); i++) {
        m_rolesPages[i] = new RoleAppsWizardPage(Roles.at(i), i, m_wizardService, this);
    }

    m_conclusionPage = new ConclusionWizardPage(m_wizardService, this);

}

void StartupWizard::InitSizes()
{
    setMinimumSize(900, 700);
}

void StartupWizard::InitStyles()
{
    setWizardStyle(QWizard::ModernStyle);
    this->setAutoFillBackground(true);
}

void StartupWizard::InitBehaviour()
{

    setPage(Page_Intro, m_introPage);
    setPage(Page_UserData, m_userWizardPage);

    for (int i = 0; i < m_rolesPages.size(); i++) {
        setPage(i + 2, m_rolesPages.at(i));
    }

    setPage(Page_Conclusion, m_conclusionPage);

    setStartId(Page_Intro);
    setOption(QWizard::HaveHelpButton);
}

void StartupWizard::ConnectObjects()
{
    connect(this, &QWizard::helpRequested, this, &StartupWizard::OnHelpButtonClick);
    connect(m_themePushButton, &QPushButton::clicked, this, &StartupWizard::OnThemeButtonClick);
}

void StartupWizard::OnHelpButtonClick()
{
    QString message;
    bool hasBackUp = m_wizardService->HasUserBackup() || m_wizardService->HasProgramBackUp();
    bool hasOldData = m_wizardService->HasUserOldData() || m_wizardService->HastProgramOldData();

    switch (currentId()) {
    case Page_Intro:
        message = "При запуске приложения, если необходимые данные не были обнаружены, инициируется процесс автоматического восстановления.\n"
                  "Несмотря на то, что приведенные ниже шаги могут показаться сложными на первом этапе, просто выполните их по порядку, и мы попробуем помочь вам.\n"
                  "Если у вас есть готовый файл восстановления, выберите его, нажав на кнопку папки справа. Если файл корректный он отобразится в поле файла, иначе изменений не произойдет. \n"
                  "Если файла нет прочитайте краткое руководство и нажмите Далее...";
        break;

    case Page_UserData:
        if (hasBackUp) {
            if (hasOldData) {
                message = "Поле ввода данных администратора.\n"
                          "Ваша программа обнаружила уже имеющиеся данные, так же вы предоставили файл восстановления, "
                          "все эти файлы были загружены.\n"
                          "Необходимо выбрать только один источник, выбрать необходимый вы можете в самом"
                          "нижнем поле программы.\n"
                          "Вы можете изменить ФИО, или воиское звание, в соответсвующих полях\n"
                          "Поля пользователей разрешается отредактировать в интерфейсе программы позже.\n"
                          "Затем, нажмите кнопку Далее...";
            } else {
                message = "Поле ввода данных администратора.\n "
                          "Вы предоставили программе предоставили файл восстановления, данный файл был успешно заружен.\n"
                          "Вы можете не использовать базу из файла восстановления, выбрав нужный вариант в самом нижнем поле, и создать новую, записав в нее только данные администратора.\n"
                          "При необходимости измените ФИО, или воиское звание.\n"
                          "Поля пользователей разрешается отредактировать в интерфейсе программы позже.\n"
                          "Затем, нажмите кнопку Далее...";
            }
        } else {
            if (hasOldData) {
                message = "Поле ввода данных администратора.\n "
                          "Ваша программа обнаружила уже имеющиеся данные, они были загружены, файл восстановления не выбран, "
                          "при необходимости вы можете изменить ФИО, или воиское звание.\n"
                          "Так же вы можете не использовать имеющуюся базу, выбрав нужный вариант в самом нижнем поле, и создать новую, записав в нее только данные администратора.\n"
                          "Поля пользователей разрешается отредактировать в интерфейсе программы позже.\n"
                          "Затем, нажмите кнопку Далее...";
            } else {
                message = "Поле ввода данных администратора.\n "
                          "К сожалению, у вас нет ни данных, ни файла восстановления, поэтому "
                          "введите пожалуйста ФИО, и выберите воиское звание снизу.\n"
                          "Поля пользователей разрешается отредактировать в интерфейсе программы позже.\n"
                          "Затем, нажмите кнопку Далее...";
            }
        }

        break;

    case Page_FirstRole:
    case Page_SecondRole:
    case Page_ThirdRole:
    case Page_FourthRole:
        if (hasBackUp) {
            if (hasOldData) {
                message = "Данные для программ-ярлыков в режиме киоска, а так же программ которые будут перезапущены для роли: " + Roles.at(currentId() - 2) +
                        "\nВаша программа обнаружила уже имеющиеся данные, так же вы предоставили файл восстановления, "
                        "все эти файлы были загружены.\n"
                        "Необходимо выбрать только один источник, выбрать необходимый вы можете в самом"
                        "нижнем поле программы.\n"
                        "Доступные программы разрешается отредактировать в интерфейсе программы позже.\n"
                        "Затем, нажмите кнопку Далее...";
            } else {
                message = "Данные для программ-ярлыков в режиме киоска, а так же программ которые будут перезапущены для роли: " + Roles.at(currentId() - 2) +
                        "\nВы предоставили программе предоставили файл восстановления, данный файл был успешно заружен.\n"
                        "Вы можете не использовать базу из файла восстановления, выбрав нужный вариант в самом нижнем поле, и создать новую, записав в нее только данные администратора.\n"
                        "Доступные программы разрешается отредактировать в интерфейсе программы позже.\n"
                        "Затем, нажмите кнопку Далее...";
            }
        } else {
            if (hasOldData) {
                message = "Данные для программ-ярлыков в режиме киоска, а так же программ которые будут перезапущены для роли: " + Roles.at(currentId() - 2) +
                        "\nВаша программа обнаружила уже имеющиеся данные, они были загружены, файл восстановления не выбран, "
                        "Так же вы можете не использовать имеющуюся базу, выбрав нужный вариант в самом нижнем поле, и создать новую, записав в нее только данные администратора.\n"
                        "Доступные программы разрешается отредактировать в интерфейсе программы позже.\n"
                        "Затем, нажмите кнопку Далее...";
            } else {
                message = "Данные для программ-ярлыков в режиме киоска, а так же программ которые будут перезапущены для роли: " + Roles.at(currentId() + 2) +
                        "\nК сожалению, у вас нет ни данных, ни файла восстановления, поэтому "
                        "Доступные программы разрешается отредактировать в интерфейсе программы позже.\n"
                        "Затем, нажмите кнопку Далее...";
            }
        }

        break;

    case Page_Conclusion:
        message = "Заключительный этап настройки.\n"
                  "Проверьте правильность настроек, и импорт данных из источников.\n"
                  "Если все правильно, нажмите кнопку Завершить..\n."
                  "Иначе нажмите кнопку Назад, и измените необходимые параметры...\n";

        break;
    }

    QMessageBox::information(this, "Окно справки", message);
}

void StartupWizard::OnThemeButtonClick(bool checked)
{
    if (checked) {
        m_themePushButton->setIcon(QIcon(":/images/sun"));
    } else {
        m_themePushButton->setIcon(QIcon(":/images/moon"));
    }

    m_themePushButton->setIconSize(QSize(30, 30));
    Q_EMIT ToChangeTheme(checked);
}

void StartupWizard::accept()
{
    m_wizardService->ApplyWizardActions();
    QWizard::accept();
}

void StartupWizard::reject()
{
    QWizard::reject();
}
