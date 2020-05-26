#include "runningprocessestable.h"

RunningProcessesTable::RunningProcessesTable(QWidget *parent) : QWidget(parent)
{
    horizontalLayout = new QHBoxLayout(this);
    runningProcesses = new RunningProcesses();
    runningProcesses->Initialize(TH32CS_SNAPPROCESS);

    table = new QTableWidget(1, 2, this);
    table->setHorizontalHeaderLabels(QStringList() << "PID" << "Name");

    table->setMinimumSize(QSize(500, 500));

    connect(runningProcesses, &RunningProcesses::resultReady,
            this, &RunningProcessesTable::fillTable);

    table->verticalHeader()->setVisible(false);

    table->horizontalScrollBar()->hide();

    for (int i = 0; i < table->horizontalHeader()->count(); i++) {
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    runningProcesses->getAllProcesses();

    horizontalLayout->addWidget(table);
    setLayout(horizontalLayout);
}

void RunningProcessesTable::fillTable(QVector<QPair<QString, QString>> allProcesses){
    for(int i = 0; i < allProcesses.length(); i++){
        table->setRowCount(i + 1);
        qDebug() << allProcesses.at(i);
        table->setItem(i, 0, new QTableWidgetItem(allProcesses.at(i).first));
        table->setItem(i, 1, new QTableWidgetItem(allProcesses.at(i).second));
    }

}
