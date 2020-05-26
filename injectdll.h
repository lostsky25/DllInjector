#ifndef INJECTDLL_H
#define INJECTDLL_H

#include <Windows.h>
#include <psapi.h>
#include <QString>

class InjectDLL
{
public:
    virtual int Initialize(QString, QString) = 0;
    virtual int injectDLL(QString, DWORD) = 0;
protected:
    HANDLE hTargetProc;
    HMODULE hKernel32;
    DWORD allocatedMemory;
    DWORD dwLoadLibAddr;
    PROCESS_MEMORY_COUNTERS pmc;
};

#endif // INJECTDLL_H
