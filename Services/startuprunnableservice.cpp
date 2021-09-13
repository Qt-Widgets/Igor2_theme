#include "startuprunnableservice.h"
#include <QDebug>

StartupRunnableService::StartupRunnableService(Terminal *terminal, QObject *parent)
    : QObject(parent)
    , m_terminal(terminal)
    , m_runnableProcess(new QVector<QProcess*>)
    , m_processParams(new QStringList())
{

}

StartupRunnableService::~StartupRunnableService()
{
    if (!(m_runnableProcess->isEmpty()))
    {
        for (QVector<QProcess*>::reverse_iterator iter=m_runnableProcess->rbegin(); iter!=m_runnableProcess->rend(); iter++)
        {
            delete *iter;
        }
    }
    delete m_runnableProcess;
    delete m_processParams;
}

bool StartupRunnableService::run(const QString &userName)
{
    QStringList execs=readUserExecFile(userName);
    if(isAllExecsValid(execs))
    {
        initProcessStruct(execs);
        return true;
    }
    else
    {
        return false;
    }
}

QStringList StartupRunnableService::readUserExecFile(const QString &userName)
{
    QString m_startupFile="/home/"+userName+"/RLS_TI/Startup";
    QString ecexs=m_terminal->getFileTextNoSU(m_startupFile, "StartupManagerService::getAllEcexFromStartupFile");
    QStringList execsList=ecexs.split('\n');
    execsList.removeAll("");
    return execsList;
}

bool StartupRunnableService::isAllExecsValid(QStringList &execsList)
{
    for (QStringList::const_iterator it=execsList.cbegin(); it!=execsList.cend(); ++it)
    {
        if (!QFile::exists(*it))
        {
            emit noExecApplication(*it);
            return false;
        }
    }
    return true;
}

void StartupRunnableService::initProcessStruct(QStringList execsList)
{
    m_runnableProcess->resize(execsList.size());
    if (m_runnableProcess->isEmpty())
    {
        return;
    }
    else
    {
        QVector<QProcess*>::iterator processIter=m_runnableProcess->begin();
        for (QList<QString>::ConstIterator programPath=execsList.cbegin(); programPath!=execsList.cend(); ++programPath)
        {
            (*processIter)=new QProcess();
            (*processIter)->setObjectName(*programPath);
            connect(*processIter , QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &StartupRunnableService::restartProcess);
            if(!((*processIter)->state() == QProcess::Running))
                (*processIter)->start(*programPath, QStringList());
        }
    }
}

void StartupRunnableService::restartProcess()
{
    QProcess* process=static_cast<QProcess*>(sender());
    process->start();
    emit programFall();
}
