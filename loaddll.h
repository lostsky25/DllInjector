#ifndef LOADDLL_H
#define LOADDLL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "injectdll.h"
#include "logging.h"
#include <Windows.h>

class LoadDLL : public QWidget, InjectDLL
{
    Q_OBJECT
public:
    explicit LoadDLL(QWidget *parent = nullptr);

    int Initialize(QString, QString) override;
    int injectDLL(QString, DWORD) override;
public slots:
    void setDllPath(QString);
    void setProcID(DWORD);
    void updateProcInfo(DWORD);

private:
    void load();


    Logging *logging;

    QPushButton *btnInjectDLL;
    QLabel *lbInjectStatus;
    QString pathToDll;
    DWORD procId;
    QLabel *lbProcInfo;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;


};

#endif // LOADDLL_H
