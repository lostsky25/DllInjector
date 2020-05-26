#include "loaddll.h"

LoadDLL::LoadDLL(QWidget *parent) : QWidget(parent)
{
    logging = new Logging();
    btnInjectDLL = new QPushButton("Inject", this);
    lbInjectStatus = new QLabel("Without injet");
    lbProcInfo = new QLabel("PageFaultCount: 0x%08X\n\
PeakWorkingSetSize: NaN\n\
PeakWorkingSetSize: NaN\n\
WorkingSetSize: NaN\n\
QuotaPeakPagedPoolUsage: NaN\n\
QuotaPagedPoolUsage: NaN\n\
QuotaPeakNonPagedPoolUsage: NaN\n\
QuotaNonPagedPoolUsage: NaN\n\
PagefileUsage: NaN\n\
PeakPagefileUsage: NaN\n");

    lbInjectStatus->setStyleSheet("QLabel { color : rgb(149, 165, 166); }");

    horizontalLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout();

    connect(btnInjectDLL, &QPushButton::clicked, this, &LoadDLL::load);

    horizontalLayout->addWidget(lbInjectStatus);
    horizontalLayout->addWidget(btnInjectDLL);

    verticalLayout->addWidget(lbProcInfo);
    verticalLayout->addLayout(horizontalLayout);

    setLayout(verticalLayout);
}

void LoadDLL::setDllPath(QString path){
    if(!path.isEmpty()){
        pathToDll = path;
    }else{
        //
    }
}

void LoadDLL::setProcID(DWORD procId)
{
    this->procId = procId;
}

void LoadDLL::updateProcInfo(DWORD processID)
{
    QString buffer;

    hTargetProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    qDebug() << processID;

    if(INVALID_HANDLE_VALUE != hTargetProc){
        if (GetProcessMemoryInfo(hTargetProc, &pmc, sizeof(pmc)))
        {
            buffer = buffer.sprintf("PageFaultCount: 0x%08X\n\
PeakWorkingSetSize: 0x%08X\n\
PeakWorkingSetSize: 0x%08X\n\
WorkingSetSize: 0x%08X\n\
QuotaPeakPagedPoolUsage: 0x%08X\n\
QuotaPagedPoolUsage: 0x%08X\n\
QuotaPeakNonPagedPoolUsage: 0x%08X\n\
QuotaNonPagedPoolUsage: 0x%08X\n\
PagefileUsage: 0x%08X\n\
PeakPagefileUsage: 0x%08X\n",
                                    pmc.PageFaultCount,
                                    pmc.PeakWorkingSetSize,
                                    pmc.WorkingSetSize,
                                    pmc.QuotaPeakPagedPoolUsage,
                                    pmc.QuotaPagedPoolUsage,
                                    pmc.QuotaPeakNonPagedPoolUsage,
                                    pmc.QuotaNonPagedPoolUsage,
                                    pmc.PagefileUsage,
                                    pmc.PeakPagefileUsage);
            lbProcInfo->setText(buffer);
            lbProcInfo->setAlignment(Qt::AlignLeft);
        }else{
            buffer = buffer.sprintf("PageFaultCount: 0x%08X\n\
PeakWorkingSetSize: NaN\n\
PeakWorkingSetSize: NaN\n\
WorkingSetSize: NaN\n\
QuotaPeakPagedPoolUsage: NaN\n\
QuotaPagedPoolUsage: NaN\n\
QuotaPeakNonPagedPoolUsage: NaN\n\
QuotaNonPagedPoolUsage: NaN\n\
PagefileUsage: NaN\n\
PeakPagefileUsage: NaN\n");
        }
    }

    lbProcInfo->setText(buffer);
    lbProcInfo->setAlignment(Qt::AlignLeft);
//    lbProcInfo->update();
//    lbProcInfo->repaint();
    CloseHandle(hTargetProc);
}

void LoadDLL::load(){
    Initialize("kernel32.dll", "LoadLibraryA");
//    if(!pathToDll.isEmpty()){
        injectDLL(pathToDll.replace("\\", "\\\\"), procId);
//    }

}

int LoadDLL::Initialize(QString module, QString fucntion){
    hKernel32 = GetModuleHandleA(module.toStdString().c_str());

    if(hKernel32 == NULL){
        logging->messageHandler(QtCriticalMsg, "Can\'t open a module");

        return EXIT_FAILURE;
    }else{
        dwLoadLibAddr = (DWORD)GetProcAddress(hKernel32, fucntion.toStdString().c_str());

        if(dwLoadLibAddr == NULL){
            logging->messageHandler(QtCriticalMsg, "Can\'t load a realizetion");
            return EXIT_FAILURE;
        }else {
            return EXIT_SUCCESS;
        }
    }
}

int LoadDLL::injectDLL(QString dllPath, DWORD processID){
    hTargetProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

    if(INVALID_HANDLE_VALUE == hTargetProc){
        return EXIT_FAILURE;
    }

    else{
        if((hKernel32 == NULL) && (dwLoadLibAddr == NULL)){
            logging->messageHandler(QtWarningMsg, "Some parameters did\'t initialize");
                lbInjectStatus->setStyleSheet("color: #F75C4C;");
                lbInjectStatus->setText("Unsuccessfully");
            return EXIT_FAILURE;
        }else{
            allocatedMemory = (DWORD)VirtualAllocEx(hTargetProc, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
                if(WriteProcessMemory(hTargetProc,
                                   (LPVOID)allocatedMemory,
                                   dllPath.toStdString().c_str(),
                                   dllPath.toStdString().length() + 1,
                                   NULL)){
                    if(CreateRemoteThread(hTargetProc,
                                          NULL,
                                          NULL,
                                          (LPTHREAD_START_ROUTINE)dwLoadLibAddr,
                                          (LPVOID)allocatedMemory,
                                          NULL,
                                          NULL)){
                        lbInjectStatus->setStyleSheet("color: #1EBC61;");
                        lbInjectStatus->setText("Successful");
                        return EXIT_SUCCESS;
                    }else{
                        logging->messageHandler(QtWarningMsg, "Write memory fail");
                        lbInjectStatus->setStyleSheet("color: #F75C4C;");
                        lbInjectStatus->setText("Unsuccessfully");
                        return EXIT_FAILURE;
                    }

                }else{
                    logging->messageHandler(QtWarningMsg, "Create remote thread fail");
                    lbInjectStatus->setStyleSheet("color: #F75C4C;");
                    lbInjectStatus->setText("Unsuccessfully");
                    return EXIT_FAILURE;
                }

        }

    }

}
