#ifndef DLLDIRECTORYDIALOG_H
#define DLLDIRECTORYDIALOG_H

#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDebug>

#include "logging.h"

class DllDirectoryDialog : public QWidget
{
    Q_OBJECT
public:
    DllDirectoryDialog(QWidget *parent = nullptr);

    QLineEdit *pathToFileEditLine;

private:
    void openFile();

    Logging *logging;

    QString pathToFile;
    QPushButton *btnPathToFile;
    QHBoxLayout *horizontalLayout;

};

#endif // DLLDIRECTORYDIALOG_H
