#ifndef RUNNINGPROCESSES_H
#define RUNNINGPROCESSES_H

#include <Windows.h>
#include <tlhelp32.h>

#include <QWidget>
#include <QObject>
#include <QVector>
#include <QThread>
#include <QPair>

//Uses for catch a mistake
#include "logging.h"

class RunningProcesses : public QObject
{
    Q_OBJECT
private:
    PROCESSENTRY32 pe;
//    TCHAR szBuff[1024];
    DWORD dwTemp;
    HANDLE hSnapshot;
    int count;

    QVector<QPair<QString, QString>> allProcesses;

    Logging *logging;

signals:
    void resultReady(QVector<QPair<QString, QString>> allProcesses);

public:
    RunningProcesses();
    ~RunningProcesses();

    void Initialize(DWORD);
    void getAllProcesses(void);


};

#endif // RUNNINGPROCESSES_H
