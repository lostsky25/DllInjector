#include "runningprocesses.h"

RunningProcesses::RunningProcesses()
{
    logging = new Logging();

    //Just counter
    count = 0;
}

void RunningProcesses::Initialize(DWORD dwFlags){
    //This snapshot stores all processes of Windows.
    hSnapshot = CreateToolhelp32Snapshot(dwFlags, 0);

    if(INVALID_HANDLE_VALUE == hSnapshot){
        logging->messageHandler(QtCriticalMsg, QString("Can\'t open a snapshot"));
    }
}

void RunningProcesses::getAllProcesses(void){
    pe.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &pe);
    do {
//        qDebug() << QString("%1 %2\r\n").arg(pe.th32ProcessID).arg(pe.szExeFile).toLatin1();
        allProcesses.append({QString("%1").arg(pe.th32ProcessID, 5, 10, QChar('0')).toLatin1(), QString("%1").arg(pe.szExeFile).toLatin1()});
//        emit resultReady{QString("%1\r\n").arg(pe.th32ProcessID).toLatin1(), QString("%1\r\n").arg(pe.szExeFile).toLatin1()}));

        count++;
    } while (Process32Next(hSnapshot, &pe));
    emit resultReady(allProcesses);
}

RunningProcesses::~RunningProcesses(){
    delete logging;
    CloseHandle(hSnapshot);
}
