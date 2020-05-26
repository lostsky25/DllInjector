#ifndef INJECTORWINDOW_H
#define INJECTORWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "runningprocessestable.h"
#include "dlldirectorydialog.h"
#include "loaddll.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InjectorWindow; }
QT_END_NAMESPACE

class InjectorWindow : public QMainWindow
{
    Q_OBJECT

public:
    InjectorWindow(QWidget *parent = nullptr);
    ~InjectorWindow();

private:
    //Custom widgets
    RunningProcessesTable *runningProcessesTable;
    DllDirectoryDialog *dllDirectoryDialog;
    LoadDLL *loadDll;
    //!Custom widgets

    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    Ui::InjectorWindow *ui;
};
#endif // INJECTORWINDOW_H
