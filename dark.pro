QT += core gui widgets printsupport
QT += charts
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    connection.cpp \
    historydialog.cpp \
    main.cpp \
    mainwindow.cpp \
    statsdialog.cpp \
    pdfexporter.cpp \
    vaccine.cpp

HEADERS += \
    connection.h \
    historydialog.h \
    mainwindow.h \
    statsdialog.h \
    pdfexporter.h \
    vaccine.h

FORMS += \
    historydialog.ui \
    mainwindow.ui \
    statsdialog.ui

RESOURCES += \
    images/a.qrc

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
