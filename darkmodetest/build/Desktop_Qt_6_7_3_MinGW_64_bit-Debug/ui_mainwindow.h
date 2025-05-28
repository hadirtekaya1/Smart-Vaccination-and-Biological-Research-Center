/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_9;
    QLineEdit *lineEdit_2;
    QDateEdit *dateEdit_2;
    QPushButton *pushButton;
    QRadioButton *radioButton;
    QLineEdit *lineEdit_3;
    QRadioButton *radioButton_2;
    QLineEdit *lastnameln;
    QLineEdit *emailln;
    QLineEdit *phoneln;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QPushButton *pushButton_4;
    QLabel *label_10;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_10;
    QPushButton *pushButton_7;
    QPushButton *addAppointmentButton;
    QPushButton *viewAppointmentsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(2241, 1946);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #cbe5f2\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 100, 351, 521));
        groupBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border:none;"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 80, 141, 31));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 130, 81, 31));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 180, 171, 31));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 230, 161, 31));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 330, 121, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 280, 141, 31));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 380, 151, 31));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(204, 80, 113, 28));
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit_2 = new QDateEdit(groupBox);
        dateEdit_2->setObjectName("dateEdit_2");
        dateEdit_2->setGeometry(QRect(204, 230, 110, 29));
        dateEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        dateEdit_2->setProperty("showGroupSeparator", QVariant(false));
        dateEdit_2->setCalendarPopup(true);
        dateEdit_2->setDate(QDate(2025, 1, 1));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(120, 450, 101, 31));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: #144976"));
        pushButton->setAutoDefault(false);
        pushButton->setFlat(false);
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(80, 490, 112, 26));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        radioButton->setFont(font1);
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(204, 280, 113, 28));
        lineEdit_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setGeometry(QRect(190, 490, 112, 26));
        radioButton_2->setFont(font1);
        lastnameln = new QLineEdit(groupBox);
        lastnameln->setObjectName("lastnameln");
        lastnameln->setGeometry(QRect(204, 130, 113, 28));
        lastnameln->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        emailln = new QLineEdit(groupBox);
        emailln->setObjectName("emailln");
        emailln->setGeometry(QRect(204, 330, 113, 28));
        emailln->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        phoneln = new QLineEdit(groupBox);
        phoneln->setObjectName("phoneln");
        phoneln->setGeometry(QRect(204, 380, 113, 28));
        phoneln->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(205, 180, 111, 31));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_2->raise();
        label_3->raise();
        label_5->raise();
        label_6->raise();
        label_7->raise();
        label_4->raise();
        label_9->raise();
        lineEdit_2->raise();
        dateEdit_2->raise();
        pushButton->raise();
        lineEdit_3->raise();
        radioButton->raise();
        radioButton_2->raise();
        lastnameln->raise();
        emailln->raise();
        phoneln->raise();
        comboBox_2->raise();
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(340, 150, 1101, 491));
        groupBox_2->setStyleSheet(QString::fromUtf8("border:none;"));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QFont font2;
        font2.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font2);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font3;
        font3.setBold(true);
        font3.setItalic(true);
        font3.setUnderline(false);
        font3.setStrikeOut(false);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font3);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QFont font4;
        font4.setBold(true);
        font4.setItalic(true);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font4);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QFont font5;
        font5.setPointSize(9);
        font5.setBold(true);
        font5.setItalic(true);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font5);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font5);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font4);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font4);
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QFont font6;
        font6.setPointSize(8);
        font6.setBold(true);
        font6.setItalic(true);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font6);
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font4);
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 30, 861, 401));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: #144976"));
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(810, 120, 101, 31));
        QFont font7;
        font7.setPointSize(10);
        font7.setBold(true);
        pushButton_2->setFont(font7);
        pushButton_2->setMouseTracking(false);
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: #144976\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/chercher.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon);
        comboBox_3 = new QComboBox(centralwidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(340, 120, 151, 31));
        comboBox_3->setFont(font7);
        comboBox_3->setAutoFillBackground(false);
        comboBox_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: #144976\n"
""));
        comboBox_4 = new QComboBox(centralwidget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(340, 77, 151, 31));
        comboBox_4->setFont(font7);
        comboBox_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: #144976\n"
""));
        comboBox_4->setDuplicatesEnabled(false);
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(1160, 0, 101, 29));
        pushButton_4->setFont(font7);
        pushButton_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: #144976\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/maison.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_4->setIcon(icon1);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 0, 331, 141));
        label_10->setStyleSheet(QString::fromUtf8("color: #144976\n"
""));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(510, 120, 291, 31));
        lineEdit_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"border-radious:5ppx;"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(610, 30, 71, 51));
        pushButton_5->setStyleSheet(QString::fromUtf8("border: none;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/fichier-pdf.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_5->setIcon(icon2);
        pushButton_5->setIconSize(QSize(50, 50));
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(920, 115, 51, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/tourner.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_6->setIcon(icon3);
        pushButton_6->setIconSize(QSize(45, 35));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(520, 30, 83, 51));
        pushButton_8->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/bar.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_8->setIcon(icon4);
        pushButton_8->setIconSize(QSize(50, 50));
        pushButton_9 = new QPushButton(centralwidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(1110, 0, 51, 31));
        pushButton_9->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/sombre.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_9->setIcon(icon5);
        pushButton_9->setIconSize(QSize(35, 35));
        pushButton_delete = new QPushButton(pushButton_9);
        pushButton_delete->setObjectName("pushButton_delete");
        pushButton_delete->setGeometry(QRect(120, 520, 101, 31));
        pushButton_delete->setFont(font);
        pushButton_delete->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"    background-color: #dc3545"));
        pushButton_10 = new QPushButton(centralwidget);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(690, 30, 81, 51));
        pushButton_10->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/new/prefix1/alarme.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_10->setIcon(icon6);
        pushButton_10->setIconSize(QSize(50, 50));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(770, 30, 83, 51));
        pushButton_7->setStyleSheet(QString::fromUtf8("border:none;\n"
""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/new/prefix1/histoire.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_7->setIcon(icon7);
        pushButton_7->setIconSize(QSize(50, 50));
        addAppointmentButton = new QPushButton(centralwidget);
        addAppointmentButton->setObjectName("addAppointmentButton");
        addAppointmentButton->setGeometry(QRect(990, 70, 121, 31));
        addAppointmentButton->setFont(font2);
        addAppointmentButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: #144976\n"
""));
        addAppointmentButton->setText(QString::fromUtf8("Add Appointment"));
        viewAppointmentsButton = new QPushButton(centralwidget);
        viewAppointmentsButton->setObjectName("viewAppointmentsButton");
        viewAppointmentsButton->setGeometry(QRect(990, 120, 121, 31));
        viewAppointmentsButton->setFont(font2);
        viewAppointmentsButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: #144976\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        groupBox->raise();
        groupBox_2->raise();
        pushButton_2->raise();
        pushButton_5->raise();
        pushButton_6->raise();
        pushButton_8->raise();
        pushButton_9->raise();
        pushButton_10->raise();
        pushButton_4->raise();
        pushButton_7->raise();
        lineEdit_4->raise();
        label_10->raise();
        comboBox_3->raise();
        comboBox_4->raise();
        addAppointmentButton->raise();
        viewAppointmentsButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 2241, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">First Name</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Last name</span></p><p><br/></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Gender</span></p><p><br/></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Date of birth</span></p><p><br/></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Email</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Adress</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:700;\">Phone number</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Modify", nullptr));
        groupBox_2->setTitle(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Patient ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "First Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Last Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Gender", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Date of birth", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Adress", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Phone number", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Action", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "research", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "search by", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Patient ID", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "First name", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("MainWindow", "Last name", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("MainWindow", "Gender", nullptr));
        comboBox_3->setItemText(5, QCoreApplication::translate("MainWindow", "Date of birth", nullptr));
        comboBox_3->setItemText(6, QCoreApplication::translate("MainWindow", "Adress", nullptr));
        comboBox_3->setItemText(7, QCoreApplication::translate("MainWindow", "Email", nullptr));
        comboBox_3->setItemText(8, QCoreApplication::translate("MainWindow", "Phone number", nullptr));

#if QT_CONFIG(accessibility)
        comboBox_3->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        comboBox_3->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        comboBox_3->setCurrentText(QString());
        comboBox_3->setPlaceholderText(QCoreApplication::translate("MainWindow", "search by  ", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "sort by", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "Vaccine Name", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "Manufacturing Date", nullptr));
        comboBox_4->setItemText(3, QCoreApplication::translate("MainWindow", "Expiration Date", nullptr));
        comboBox_4->setItemText(4, QCoreApplication::translate("MainWindow", "Stock Quantity", nullptr));

        comboBox_4->setPlaceholderText(QCoreApplication::translate("MainWindow", "sort by ", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:36pt; font-weight:700; font-style:italic;\">Patients</span></p><p><span style=\" font-size:36pt; font-weight:700; font-style:italic;\">Management</span></p></body></html>", nullptr));
        lineEdit_4->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter search text...", nullptr));
        pushButton_5->setText(QString());
        pushButton_6->setText(QString());
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        pushButton_delete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        pushButton_10->setText(QString());
        pushButton_7->setText(QString());
        viewAppointmentsButton->setText(QCoreApplication::translate("MainWindow", "View Appointments", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
