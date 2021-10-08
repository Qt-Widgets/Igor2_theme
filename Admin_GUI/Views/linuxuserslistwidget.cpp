#include "linuxuserslistwidget.h"

#include <QDebug>

LinuxUsersListWidget::LinuxUsersListWidget(UserModel *userModel, QWidget *parent)
    : QWidget(parent)
    , m_oldFontSize(0)
{
    createProxyModel(userModel);
    initUI();
    insertWidgetsIntoLayout();
    setModelToView();
    createConnections();
}

LinuxUsersListWidget::~LinuxUsersListWidget()
{
    delete m_font;

    delete m_searchLayout;
    delete m_mainLayout;

    delete m_sortModel;
    delete m_userDelegate;

    delete m_linuxUsersLabel;
    delete m_searchLineEdit;
    delete m_searchTypeComboBox;
    delete m_allUsersListView;
}

void LinuxUsersListWidget::createProxyModel(UserModel *userModel)
{
    m_model=userModel->getModel();
    m_sortModel=new SortModel();
    m_sortModel->setSourceModel(m_model);
    m_sortModel->setDynamicSortFilter(true);
}

void LinuxUsersListWidget::setModelToView()
{
    m_allUsersListView->setModel(m_sortModel);
}

void LinuxUsersListWidget::initUI()
{
    m_mainLayout=new QVBoxLayout();

    m_linuxUsersLabel=new QLabel("Пользователи операционной системы Astra Linux: ");

    m_font=new QFont(m_linuxUsersLabel->font());

    m_userDelegate=new UserDelegate(m_font, this);

    m_searchLayout=new QHBoxLayout();
    m_searchTypeComboBox=new QComboBox();
    m_searchTypeComboBox->addItems(comboBoxSearchAttributes);
    m_searchLineEdit=new QLineEdit();
    m_searchLineEdit->setMaximumWidth(195);

    m_allUsersListView=new QListView();
    m_allUsersListView->setItemDelegate(m_userDelegate);
}

void LinuxUsersListWidget::insertWidgetsIntoLayout()
{
    m_searchLayout->addWidget(m_searchLineEdit);
    m_searchLayout->addWidget(m_searchTypeComboBox);

    m_mainLayout->addWidget(m_linuxUsersLabel);
    m_mainLayout->addLayout(m_searchLayout);
    m_mainLayout->addWidget(m_allUsersListView);

    setLayout(m_mainLayout);
}

void LinuxUsersListWidget::createConnections()
{
    connect(m_allUsersListView, &QListView::clicked, this, &LinuxUsersListWidget::getUserData);
    connect(m_searchLineEdit, &QLineEdit::textChanged, this, &LinuxUsersListWidget::onLineEditChange);
    connect(m_searchTypeComboBox, &QComboBox::currentTextChanged, this, &LinuxUsersListWidget::onComboBoxChange);
    connect(this, &LinuxUsersListWidget::search, m_sortModel, &SortModel::UpdateSeachWordAndSeachAttribute);
}

void LinuxUsersListWidget::updateFontSize()
{
    m_font->setPointSize(m_oldFontSize);
    m_linuxUsersLabel->setFont(*m_font);
    m_searchLineEdit->setFont(*m_font);
    m_searchTypeComboBox->setFont(*m_font);
    m_allUsersListView->setFont(*m_font);
}

void LinuxUsersListWidget::onLineEditChange(const QString &text)
{
    const QString attribute=m_searchTypeComboBox->currentText();
    m_sortModel->UpdateSeachWordAndSeachAttribute(text, attribute);
}

void LinuxUsersListWidget::onComboBoxChange(const QString &attribute)
{
    const QString text=m_searchLineEdit->text();
    m_sortModel->UpdateSeachWordAndSeachAttribute(text, attribute);
}

void LinuxUsersListWidget::getUserData(const QModelIndex &index)
{
    QVariant indexData=index.data(Qt::UserRole+1);
    User user=indexData.value<User>();
    emit onUserClick(user);
}

void LinuxUsersListWidget::resizeEvent(QResizeEvent *event)
{
    int width=event->size().width();
    qDebug()<< width;
    if (width>930)
    {
        if (m_oldFontSize!=20)
        {
            m_oldFontSize=20;
            updateFontSize();
            m_searchTypeComboBox->setFixedHeight(44);
            m_searchLineEdit->setFixedHeight(44);
        }
    }
    else
    {
        if (width>861)
        {
            if (m_oldFontSize!=19)
            {
                m_oldFontSize=19;
                updateFontSize();
                m_searchTypeComboBox->setFixedHeight(42);
                m_searchLineEdit->setFixedHeight(42);
            }
        }
        else
        {
            if(width>845)
            {
                if (m_oldFontSize!=18)
                {
                    m_oldFontSize=18;
                    updateFontSize();
                    m_searchTypeComboBox->setFixedHeight(40);
                    m_searchLineEdit->setFixedHeight(40);
                }
            }
            else
            {
                if(width>810)
                {
                    if (m_oldFontSize!=17)
                    {
                        m_oldFontSize=17;
                        updateFontSize();
                        m_searchTypeComboBox->setFixedHeight(38);
                        m_searchLineEdit->setFixedHeight(38);
                    }
                }
                else
                {
                    if(width>726)
                    {
                        if (m_oldFontSize!=16)
                        {
                            m_oldFontSize=16;
                            updateFontSize();
                            m_searchTypeComboBox->setFixedHeight(36);
                            m_searchLineEdit->setFixedHeight(36);
                        }
                    }
                    else
                    {
                        if(width>700)
                        {
                            if (m_oldFontSize!=15)
                            {
                                m_oldFontSize=15;
                                updateFontSize();
                                m_searchTypeComboBox->setFixedHeight(34);
                                m_searchLineEdit->setFixedHeight(34);
                            }
                        }
                        else
                        {
                            if(width>666)
                            {
                                if (m_oldFontSize!=14)
                                {
                                    m_oldFontSize=14;
                                    updateFontSize();
                                    m_searchTypeComboBox->setFixedHeight(33);
                                    m_searchLineEdit->setFixedHeight(33);
                                }
                            }
                            else
                            {
                                if(width>600)
                                {
                                    if (m_oldFontSize!=13)
                                    {
                                        m_oldFontSize=13;
                                        updateFontSize();
                                        m_searchTypeComboBox->setFixedHeight(32);
                                        m_searchLineEdit->setFixedHeight(32);
                                    }
                                }
                                else
                                {
                                    if(width>565)
                                    {
                                        if (m_oldFontSize!=12)
                                        {
                                            m_oldFontSize=12;
                                            updateFontSize();
                                            m_searchTypeComboBox->setFixedHeight(31);
                                            m_searchLineEdit->setFixedHeight(31);
                                        }
                                    }
                                    else
                                    {
                                        if(width>550)
                                        {
                                            if (m_oldFontSize!=11)
                                            {
                                                m_oldFontSize=11;
                                                updateFontSize();
                                                m_searchTypeComboBox->setFixedHeight(30);
                                                m_searchLineEdit->setFixedHeight(30);
                                            }
                                        }
                                        else
                                        {
                                            if (m_oldFontSize!=10)
                                            {
                                                m_oldFontSize=10;
                                                updateFontSize();
                                                m_searchTypeComboBox->setFixedHeight(29);
                                                m_searchLineEdit->setFixedHeight(29);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}