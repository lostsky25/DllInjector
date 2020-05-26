#include "dlldirectorydialog.h"

DllDirectoryDialog::DllDirectoryDialog(QWidget *parent)
    : QWidget(parent)
{
    logging = new Logging();
    btnPathToFile = new QPushButton("...", this);
    pathToFileEditLine = new QLineEdit();

    horizontalLayout = new QHBoxLayout();

    pathToFileEditLine->setPlaceholderText("Path to dll");
    pathToFileEditLine->setMinimumSize(QSize(5, 20));

    horizontalLayout->addWidget(pathToFileEditLine);
    horizontalLayout->addWidget(btnPathToFile);

    connect(btnPathToFile, &QPushButton::clicked, this, &DllDirectoryDialog::openFile);

    setLayout(horizontalLayout);
}

void DllDirectoryDialog::openFile(){
    pathToFile = QFileDialog::getOpenFileName(this, "Get Any File");

    if( pathToFile.isNull() )
    {
        logging->messageHandler(QtWarningMsg, QString("Can\'t open a file"));
    }else{
        pathToFileEditLine->setText(pathToFile);
    }
}
