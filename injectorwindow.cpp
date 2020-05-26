#include "injectorwindow.h"
#include "ui_injectorwindow.h"

#include <QDebug>

InjectorWindow::InjectorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InjectorWindow)
{
    ui->setupUi(this);
    this->setMinimumWidth(1000);
    QFile f( "styles\\main_styles.qss" );

    runningProcessesTable = new RunningProcessesTable(this);
    dllDirectoryDialog = new DllDirectoryDialog(this);
    loadDll = new LoadDLL(this);

    connect(runningProcessesTable->table, &QTableWidget::cellClicked, [=](int row, int column){
        loadDll->updateProcInfo(runningProcessesTable->table->item(row, 0)->text().toUInt());
    });

    if( f.open( QFile::ReadOnly ) )
    {
        QString sheet = QLatin1String( f.readAll() );
        dllDirectoryDialog->setStyleSheet(sheet);
        runningProcessesTable->setStyleSheet(sheet);
        loadDll->setStyleSheet(sheet);
        this->setStyleSheet("background-color: #fff;");
    }


    horizontalLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout();

    connect(dllDirectoryDialog->pathToFileEditLine, &QLineEdit::textChanged, [=](QString path){
        loadDll->setDllPath(path);
    });

    connect(runningProcessesTable->table, &QTableWidget::cellClicked, [=](int row, int column){
        loadDll->setProcID(runningProcessesTable->table->item(row, 0)->text().toUInt());
    });

    horizontalLayout->addWidget(runningProcessesTable);
    verticalLayout->addWidget(dllDirectoryDialog);
    verticalLayout->addWidget(loadDll);

    horizontalLayout->addLayout(verticalLayout);

    centralWidget()->setLayout(horizontalLayout);
}

InjectorWindow::~InjectorWindow()
{
    delete ui;
}

