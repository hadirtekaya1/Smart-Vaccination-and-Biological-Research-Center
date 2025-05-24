/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hboxLayout;
    QSpacerItem *horizontalSpacerLeft;
    QLabel *iconLabel;
    QSpacerItem *horizontalSpacerRight;
    QTextEdit *chatDisplay;
    QHBoxLayout *horizontalLayout;
    QLineEdit *userInput;
    QPushButton *sendButton;
    QHBoxLayout *optionsLayout;
    QPushButton *option1Button;
    QPushButton *option2Button;
    QPushButton *option3Button;
    QPushButton *option4Button;
    QPushButton *option5Button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(480, 520);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("\n"
"     QWidget {\n"
"         background-color: #e6f0fa;\n"
"         font-family: \"Segoe UI\";\n"
"         font-size: 12pt;\n"
"     }\n"
"\n"
"     QPushButton#sendButton {\n"
"         background-color: #6ac479;\n"
"         color: white;\n"
"         padding: 6px 12px;\n"
"         border-radius: 10px;\n"
"         font-weight: bold;\n"
"     }\n"
"\n"
"     QPushButton#sendButton:hover {\n"
"         background-color: #5bb869;\n"
"     }\n"
"\n"
"     QPushButton#option1Button,\n"
"     QPushButton#option2Button,\n"
"     QPushButton#option3Button,\n"
"     QPushButton#option4Button,\n"
"     QPushButton#option5Button {\n"
"         background-color: #193870;\n"
"         color: white;\n"
"         padding: 6px 12px;\n"
"         border-radius: 10px;\n"
"         font-weight: bold;\n"
"     }\n"
"\n"
"     QPushButton#option1Button:hover,\n"
"     QPushButton#option2Button:hover,\n"
"     QPushButton#option3Button:hover,\n"
"     QPushButton#option4Button:hover,\n"
"     QPushButton#option5Button:hov"
                        "er {\n"
"         background-color: #142d5d;\n"
"     }\n"
"\n"
"     QLineEdit {\n"
"         padding: 6px;\n"
"         border: 1px solid #ccc;\n"
"         border-radius: 6px;\n"
"         background-color: white;\n"
"     }\n"
"\n"
"     QTextEdit {\n"
"         background-color: white;\n"
"         border-radius: 6px;\n"
"         padding: 6px;\n"
"     }\n"
"    "));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        horizontalSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(horizontalSpacerLeft);

        iconLabel = new QLabel(centralwidget);
        iconLabel->setObjectName("iconLabel");
        iconLabel->setMinimumSize(QSize(64, 64));
        iconLabel->setMaximumSize(QSize(64, 64));
        iconLabel->setScaledContents(true);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setPixmap(QPixmap(QString::fromUtf8(":/Downloads/chatbot.png")));

        hboxLayout->addWidget(iconLabel);

        horizontalSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(horizontalSpacerRight);


        verticalLayout->addLayout(hboxLayout);

        chatDisplay = new QTextEdit(centralwidget);
        chatDisplay->setObjectName("chatDisplay");
        chatDisplay->setReadOnly(true);

        verticalLayout->addWidget(chatDisplay);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        userInput = new QLineEdit(centralwidget);
        userInput->setObjectName("userInput");

        horizontalLayout->addWidget(userInput);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout);

        optionsLayout = new QHBoxLayout();
        optionsLayout->setObjectName("optionsLayout");
        option1Button = new QPushButton(centralwidget);
        option1Button->setObjectName("option1Button");

        optionsLayout->addWidget(option1Button);

        option2Button = new QPushButton(centralwidget);
        option2Button->setObjectName("option2Button");

        optionsLayout->addWidget(option2Button);

        option3Button = new QPushButton(centralwidget);
        option3Button->setObjectName("option3Button");

        optionsLayout->addWidget(option3Button);


        verticalLayout->addLayout(optionsLayout);

        option4Button = new QPushButton(centralwidget);
        option4Button->setObjectName("option4Button");

        verticalLayout->addWidget(option4Button);

        option5Button = new QPushButton(centralwidget);
        option5Button->setObjectName("option5Button");

        verticalLayout->addWidget(option5Button);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Smart Vaccine Chatbot", nullptr));
        chatDisplay->setPlaceholderText(QCoreApplication::translate("MainWindow", "Hello, how can I help you ?", nullptr));
        userInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Type your question here...", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        option1Button->setText(QCoreApplication::translate("MainWindow", "What are the side effects ?", nullptr));
        option2Button->setText(QCoreApplication::translate("MainWindow", "Which vaccine is best ?", nullptr));
        option3Button->setText(QCoreApplication::translate("MainWindow", "Can kids be vaccinated ?", nullptr));
        option4Button->setText(QCoreApplication::translate("MainWindow", "Difference between mRNA and vector ?", nullptr));
        option5Button->setText(QCoreApplication::translate("MainWindow", "How to book an appointment ?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
