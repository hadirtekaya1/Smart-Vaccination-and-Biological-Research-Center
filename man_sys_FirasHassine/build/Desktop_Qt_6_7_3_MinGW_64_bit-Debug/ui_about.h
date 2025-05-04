/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QPushButton *pushButton;
    QLabel *label_14;
    QLabel *label_15;
    QTextEdit *textEdit;
    QLabel *label_pic;

    void setupUi(QWidget *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName("About");
        About->resize(1080, 600);
        About->setStyleSheet(QString::fromUtf8("#About\n"
"{\n"
"	background:#2D2D2D;\n"
"	background-color: #b2d6e5;;\n"
"}"));
        pushButton = new QPushButton(About);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(450, 530, 180, 36));
        QFont font;
        font.setPointSize(11);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton\n"
"{\n"
"	border:none;\n"
"	background:#F33253;\n"
"	color:white;\n"
"	border-radius:16px;\n"
"    background-color: #164978;\n"
"}\n"
"\n"
"#pushButton:hover\n"
"{\n"
"	border:2px solid #F33253;\n"
"	background:#2D2D2D;\n"
"	color:#F33253;\n"
"	border-radius:16px;\n"
"}"));
        label_14 = new QLabel(About);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(390, 150, 311, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label_14->setFont(font1);
        label_15 = new QLabel(About);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(390, 180, 311, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        label_15->setFont(font2);
        textEdit = new QTextEdit(About);
        textEdit->setObjectName("textEdit");
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(210, 220, 651, 291));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setPointSize(14);
        textEdit->setFont(font3);
        textEdit->setStyleSheet(QString::fromUtf8("#textEfit{\n"
"color:#fff;\n"
"border:none;\n"
"background:#2D2D2D;\n"
"background-color: #dbecf5;\n"
"}"));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        label_pic = new QLabel(About);
        label_pic->setObjectName("label_pic");
        label_pic->setGeometry(QRect(490, 10, 131, 141));
        label_pic->setPixmap(QPixmap(QString::fromUtf8(":/images/VaxEra.jpg")));
        label_pic->setScaledContents(true);

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QWidget *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("About", "Back", nullptr));
        label_14->setText(QCoreApplication::translate("About", "<html><head/><body><p align=\"center\"><span style=\" color:#ffffff;\">Management System</span></p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("About", "<html><head/><body><p align=\"center\"><span style=\" color:#ffffff;\">About</span></p></body></html>", nullptr));
        textEdit->setHtml(QCoreApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">A vaccination and research center's equipment and infrastructure management system prioritizes precise inventory control of temperature-sensitive vaccines, meticulous tracking of research equipment calibration, and secure data management for clinical trials. It would feature real-time monitoring of storage conditions, automated maintenance scheduling for lab equipment, and robust rep"
                        "orting tools for regulatory compliance and research analysis, ensuring both operational efficiency and data integrity.</p></body></html>", nullptr));
        label_pic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
