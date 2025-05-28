QT += core gui widgets printsupport
QT += charts
QT += sql
QT += core gui sql printsupport
QT += multimedia
QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    connection.cpp \
    historydialog.cpp \
    main.cpp \
    mainwindow.cpp \
    patient.cpp \
    statsdialog.cpp \
    pdfexporter.cpp

HEADERS += \
    connection.h \
    historydialog.h \
    mainwindow.h \
    patient.h \
    statsdialog.h \
    pdfexporter.h

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
