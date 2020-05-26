QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/x86" -ladvapi32

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dlldirectorydialog.cpp \
    injectdll.cpp \
    loaddll.cpp \
    logging.cpp \
    main.cpp \
    injectorwindow.cpp \
    runningprocesses.cpp \
    runningprocessestable.cpp

HEADERS += \
    dlldirectorydialog.h \
    injectdll.h \
    injectorwindow.h \
    loaddll.h \
    logging.h \
    runningprocesses.h \
    runningprocessestable.h

FORMS += \
    injectorwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-Injector-Desktop_Qt_5_14_2_MSVC2017_32bit-Debug/styles/main_styles.qss
