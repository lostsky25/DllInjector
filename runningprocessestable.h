#ifndef RUNNINGPROCESSESTABLE_H
#define RUNNINGPROCESSESTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVector>
#include <QThread>
#include <QDebug>
#include <QScrollBar>
#include <QHeaderView>

#include "runningprocesses.h"

class RunningProcessesTable : public QWidget
{
    Q_OBJECT
public:
    explicit RunningProcessesTable(QWidget *parent = nullptr);
    void fillTable(QVector<QPair<QString, QString>> allProcesses);

    QTableWidget *table;

private:
    QHBoxLayout *horizontalLayout;
    QThread *fillTableThread;
    RunningProcesses *runningProcesses;

};

#endif // RUNNINGPROCESSESTABLE_H
