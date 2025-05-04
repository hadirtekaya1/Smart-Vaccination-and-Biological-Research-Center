/********************************************************************************
** Form generated from reading UI file 'about2.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT2_H
#define UI_ABOUT2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_About2
{
public:

    void setupUi(QDialog *About2)
    {
        if (About2->objectName().isEmpty())
            About2->setObjectName("About2");
        About2->resize(1060, 673);

        retranslateUi(About2);

        QMetaObject::connectSlotsByName(About2);
    } // setupUi

    void retranslateUi(QDialog *About2)
    {
        About2->setWindowTitle(QCoreApplication::translate("About2", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About2: public Ui_About2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT2_H
