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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *leftWidget;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *label_pic;
    QLabel *label_12;
    QStackedWidget *stackedWidget;
    QWidget *Home;
    QPushButton *searchButton;
    QPushButton *updateEquipButton;
    QPushButton *addEquipButton;
    QPushButton *deleteEquipButton;
    QPushButton *aboutButton;
    QPushButton *QR;
    QWidget *searchWidget;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *searchTextBox;
    QTableView *equipmentTableView;
    QLabel *label_11;
    QLabel *label_16;
    QPushButton *export_2;
    QPushButton *satistics;
    QWidget *statsPage;
    QWidget *widget;
    QWidget *about;
    QLabel *label_pic_3;
    QLabel *label_14;
    QTextEdit *textEdit;
    QWidget *equipAdd;
    QLabel *id_5;
    QLineEdit *equipName;
    QLabel *PD;
    QLabel *DNM;
    QLabel *label_41;
    QDateEdit *equipPurchaseDate;
    QLabel *priice;
    QLabel *Name_2;
    QLineEdit *equipPrice;
    QDateEdit *equipDOM;
    QPushButton *pushButton_11;
    QLabel *state;
    QComboBox *equipState;
    QComboBox *equipType;
    QLabel *state_2;
    QComboBox *equipType_3;
    QLabel *Name_3;
    QComboBox *equipType_4;
    QLineEdit *equipQuantity;
    QLabel *priice_2;
    QLabel *label_13;
    QWidget *equipUpdate;
    QLineEdit *searchTextBox_3;
    QTableView *tableView_3;
    QLabel *label_44;
    QPushButton *pushButton_13;
    QDateEdit *equipDOM_2;
    QComboBox *equipState_2;
    QLabel *DNM_2;
    QComboBox *equipType_6;
    QLabel *id_39;
    QLabel *id_37;
    QComboBox *equipDanger;
    QComboBox *equipConsum;
    QLineEdit *equipName_3;
    QLabel *state_3;
    QLabel *id_41;
    QLabel *id_34;
    QDateEdit *equipPurchase_2;
    QLabel *Name_4;
    QLabel *id_33;
    QLineEdit *equipQuantity_2;
    QLabel *priice_3;
    QLineEdit *equipPrice_2;
    QLabel *label_15;
    QWidget *equipDelete;
    QLineEdit *searchTextBox_2;
    QTableView *tableView_4;
    QPushButton *deleteEquipButton_2;
    QLabel *label_10;
    QLabel *label_pic_2;
    QPushButton *goBack_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1357, 826);
        QFont font;
        font.setBold(true);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow\n"
"{\n"
"	background-color: #b2d6e5;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        leftWidget = new QWidget(centralwidget);
        leftWidget->setObjectName("leftWidget");
        leftWidget->setGeometry(QRect(0, -40, 281, 951));
        leftWidget->setStyleSheet(QString::fromUtf8("#leftWidget\n"
"{\n"
"    width:260px;\n"
"	background-color: rgba(40,94,140,255);\n"
"}"));
        label_3 = new QLabel(leftWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 330, 261, 31));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        label_3->setFont(font1);
        label_2 = new QLabel(leftWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 260, 271, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(15);
        font2.setBold(true);
        label_2->setFont(font2);
        label_9 = new QLabel(leftWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(40, 610, 131, 21));
        label_pic = new QLabel(leftWidget);
        label_pic->setObjectName("label_pic");
        label_pic->setGeometry(QRect(40, 60, 181, 191));
        label_pic->setPixmap(QPixmap(QString::fromUtf8(":/images/images/VaxEra (2).png")));
        label_pic->setScaledContents(true);
        label_12 = new QLabel(leftWidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(70, 190, 141, 41));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        label_12->setFont(font3);
        label_12->setStyleSheet(QString::fromUtf8("#label_12\n"
"\n"
"{\n"
"color: #163360;\n"
"}"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(290, 150, 1000, 631));
        stackedWidget->setFont(font);
        stackedWidget->setStyleSheet(QString::fromUtf8("#stackedWidget\n"
"{\n"
"     \n"
"	background-color: #dbecf5;\n"
"}"));
        Home = new QWidget();
        Home->setObjectName("Home");
        searchButton = new QPushButton(Home);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(90, 110, 270, 44));
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        searchButton->setFont(font4);
        searchButton->setStyleSheet(QString::fromUtf8("#searchButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:20px;\n"
"	border:none;\n"
"	color:white;	\n"
"	background:#333333;\n"
"	background-color: #164978;\n"
"    font-weight: bold;\n"
"\n"
"}\n"
"#searchButton:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;	\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333333;\n"
"    font-weight: bold;\n"
"}"));
        searchButton->setIconSize(QSize(32, 32));
        updateEquipButton = new QPushButton(Home);
        updateEquipButton->setObjectName("updateEquipButton");
        updateEquipButton->setGeometry(QRect(510, 110, 270, 44));
        updateEquipButton->setFont(font4);
        updateEquipButton->setStyleSheet(QString::fromUtf8("#updateEquipButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#1F1F1F;\n"
"    font-weight: bold;\n"
"	background-color: #164978;\n"
"}\n"
"#updateEquipButton:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;	\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333333;\n"
"    font-weight: bold;\n"
"}"));
        updateEquipButton->setIconSize(QSize(32, 32));
        addEquipButton = new QPushButton(Home);
        addEquipButton->setObjectName("addEquipButton");
        addEquipButton->setGeometry(QRect(90, 220, 270, 44));
        addEquipButton->setFont(font4);
        addEquipButton->setStyleSheet(QString::fromUtf8("#addEquipButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#1F1F1F;\n"
"    font-weight: bold;\n"
"	background-color:  #164978;\n"
"}\n"
"#addEquipButton:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333;\n"
"}"));
        addEquipButton->setIconSize(QSize(32, 32));
        deleteEquipButton = new QPushButton(Home);
        deleteEquipButton->setObjectName("deleteEquipButton");
        deleteEquipButton->setGeometry(QRect(510, 220, 270, 44));
        deleteEquipButton->setFont(font4);
        deleteEquipButton->setStyleSheet(QString::fromUtf8("#deleteEquipButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#1F1F1F;\n"
"    font-weight: bold;\n"
"	background-color:  #164978;\n"
"}\n"
"#deleteEquipButton:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333;\n"
"    font-weight: bold;\n"
"}"));
        deleteEquipButton->setIconSize(QSize(32, 32));
        aboutButton = new QPushButton(Home);
        aboutButton->setObjectName("aboutButton");
        aboutButton->setGeometry(QRect(90, 330, 270, 44));
        aboutButton->setFont(font4);
        aboutButton->setStyleSheet(QString::fromUtf8("#aboutButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#164978;\n"
"    font-weight: bold;\n"
"}\n"
"#aboutButton:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;	\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333333;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/icons8_Money_50px_1.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        aboutButton->setIcon(icon);
        aboutButton->setIconSize(QSize(32, 32));
        QR = new QPushButton(Home);
        QR->setObjectName("QR");
        QR->setGeometry(QRect(510, 330, 270, 44));
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(true);
        QR->setFont(font5);
        QR->setStyleSheet(QString::fromUtf8("#QR\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#164978;\n"
"    font-weight: bold;\n"
"}\n"
"#QR:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;	\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333333;\n"
"}"));
        QR->setIcon(icon);
        QR->setIconSize(QSize(32, 32));
        stackedWidget->addWidget(Home);
        searchWidget = new QWidget();
        searchWidget->setObjectName("searchWidget");
        label = new QLabel(searchWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 0, 210, 150));
        label->setFont(font4);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("#label\n"
"{\n"
"    background-color: rgba(22,73,120,255);;\n"
"}"));
        label_4 = new QLabel(searchWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(260, 0, 210, 150));
        label_4->setFont(font4);
        label_4->setStyleSheet(QString::fromUtf8("#label_4\n"
"{\n"
"background-color:  rgba(22,73,120,255);\n"
"}"));
        label_5 = new QLabel(searchWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(490, 0, 210, 150));
        label_5->setFont(font4);
        label_5->setStyleSheet(QString::fromUtf8("#label_5\n"
"{\n"
"background-color: rgba(22,73,120,255);\n"
"}"));
        label_6 = new QLabel(searchWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(90, 100, 41, 31));
        QFont font6;
        font6.setPointSize(15);
        font6.setBold(false);
        font6.setItalic(true);
        label_6->setFont(font6);
        label_7 = new QLabel(searchWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(330, 100, 51, 31));
        label_7->setFont(font6);
        label_8 = new QLabel(searchWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(560, 100, 51, 31));
        label_8->setFont(font6);
        searchTextBox = new QLineEdit(searchWidget);
        searchTextBox->setObjectName("searchTextBox");
        searchTextBox->setGeometry(QRect(30, 170, 901, 41));
        searchTextBox->setStyleSheet(QString::fromUtf8("#searchTextBox\n"
"{\n"
"    font-weight: bold;\n"
"    color:rgb(107, 107, 107);\n"
"	padding-left:8px;\n"
"	border:none;\n"
"    background-color:white;\n"
"}\n"
""));
        equipmentTableView = new QTableView(searchWidget);
        equipmentTableView->setObjectName("equipmentTableView");
        equipmentTableView->setGeometry(QRect(30, 230, 901, 261));
        QFont font7;
        font7.setPointSize(12);
        font7.setBold(true);
        equipmentTableView->setFont(font7);
        equipmentTableView->setStyleSheet(QString::fromUtf8("#equipmentTableView\n"
"{\n"
"    \n"
"	color: rgb(0, 0, 0);\n"
"	background-color:rgb(255, 255, 255);\n"
"}"));
        label_11 = new QLabel(searchWidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(720, 0, 210, 150));
        label_11->setFont(font4);
        label_11->setStyleSheet(QString::fromUtf8("#label_11\n"
"{\n"
"background-color: rgba(22,73,120,255);\n"
"}"));
        label_16 = new QLabel(searchWidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(800, 100, 41, 31));
        label_16->setFont(font6);
        export_2 = new QPushButton(searchWidget);
        export_2->setObjectName("export_2");
        export_2->setGeometry(QRect(760, 510, 161, 44));
        export_2->setFont(font4);
        export_2->setStyleSheet(QString::fromUtf8("#export_2\n"
"{\n"
"	text-align:left;\n"
"	padding-left:20px;\n"
"	border:none;\n"
"	color:white;	\n"
"	background:#333333;\n"
"	background-color: #164978;\n"
"    font-weight: bold;\n"
"\n"
"}\n"
"#export_2:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;	\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333333;\n"
"    font-weight: bold;\n"
"}"));
        export_2->setIconSize(QSize(32, 32));
        satistics = new QPushButton(searchWidget);
        satistics->setObjectName("satistics");
        satistics->setGeometry(QRect(560, 510, 161, 44));
        satistics->setFont(font4);
        satistics->setStyleSheet(QString::fromUtf8("#satistics\n"
"{\n"
"	text-align:left;\n"
"	padding-left:20px;\n"
"	border:none;\n"
"	color:white;	\n"
"	background:#333333;\n"
"	background-color: #164978;\n"
"    font-weight: bold;\n"
"\n"
"}\n"
"#satistics:hover\n"
"{\n"
"	text-align:left;\n"
"	padding-left:26px;	\n"
"	border:none;	\n"
"	color:white;	\n"
"	background:#333333;\n"
"    font-weight: bold;\n"
"}"));
        satistics->setIconSize(QSize(32, 32));
        stackedWidget->addWidget(searchWidget);
        statsPage = new QWidget();
        statsPage->setObjectName("statsPage");
        widget = new QWidget(statsPage);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 60, 821, 451));
        stackedWidget->addWidget(statsPage);
        about = new QWidget();
        about->setObjectName("about");
        label_pic_3 = new QLabel(about);
        label_pic_3->setObjectName("label_pic_3");
        label_pic_3->setGeometry(QRect(320, 10, 131, 141));
        label_pic_3->setPixmap(QPixmap(QString::fromUtf8(":/images/VaxEra.jpg")));
        label_pic_3->setScaledContents(true);
        label_14 = new QLabel(about);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(270, 80, 441, 81));
        label_14->setFont(font3);
        textEdit = new QTextEdit(about);
        textEdit->setObjectName("textEdit");
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(150, 190, 651, 341));
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Segoe UI")});
        font8.setPointSize(14);
        font8.setBold(true);
        textEdit->setFont(font8);
        textEdit->setStyleSheet(QString::fromUtf8("#textEdit{\n"
"color: rgb(165, 165, 165);\n"
"border:none;\n"
"background:#2D2D2D;\n"
"background-color: #b2d6e5;\n"
"}"));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        stackedWidget->addWidget(about);
        equipAdd = new QWidget();
        equipAdd->setObjectName("equipAdd");
        id_5 = new QLabel(equipAdd);
        id_5->setObjectName("id_5");
        id_5->setGeometry(QRect(30, 150, 141, 21));
        id_5->setFont(font5);
        equipName = new QLineEdit(equipAdd);
        equipName->setObjectName("equipName");
        equipName->setGeometry(QRect(30, 110, 240, 32));
        QFont font9;
        font9.setFamilies({QString::fromUtf8("Arial")});
        font9.setPointSize(10);
        font9.setBold(false);
        equipName->setFont(font9);
        equipName->setStyleSheet(QString::fromUtf8("#equipName\n"
"{\n"
"    background-color: white;\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        PD = new QLabel(equipAdd);
        PD->setObjectName("PD");
        PD->setGeometry(QRect(420, 80, 141, 21));
        PD->setFont(font5);
        DNM = new QLabel(equipAdd);
        DNM->setObjectName("DNM");
        DNM->setGeometry(QRect(420, 250, 231, 21));
        DNM->setFont(font5);
        label_41 = new QLabel(equipAdd);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(30, 50, 241, 31));
        QFont font10;
        font10.setFamilies({QString::fromUtf8("Arial")});
        font10.setPointSize(12);
        font10.setBold(true);
        label_41->setFont(font10);
        equipPurchaseDate = new QDateEdit(equipAdd);
        equipPurchaseDate->setObjectName("equipPurchaseDate");
        equipPurchaseDate->setGeometry(QRect(420, 110, 240, 32));
        equipPurchaseDate->setFont(font9);
        equipPurchaseDate->setStyleSheet(QString::fromUtf8("#equipPurchaseDate\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipPurchaseDate->setMaximumDateTime(QDateTime(QDate(2050, 4, 22), QTime(14, 59, 59)));
        equipPurchaseDate->setMinimumDateTime(QDateTime(QDate(2000, 1, 1), QTime(16, 0, 0)));
        equipPurchaseDate->setMaximumDate(QDate(2050, 4, 22));
        equipPurchaseDate->setMinimumDate(QDate(2000, 1, 1));
        equipPurchaseDate->setCurrentSection(QDateTimeEdit::Section::YearSection);
        priice = new QLabel(equipAdd);
        priice->setObjectName("priice");
        priice->setGeometry(QRect(420, 150, 101, 21));
        priice->setFont(font5);
        Name_2 = new QLabel(equipAdd);
        Name_2->setObjectName("Name_2");
        Name_2->setGeometry(QRect(30, 85, 141, 21));
        Name_2->setFont(font5);
        equipPrice = new QLineEdit(equipAdd);
        equipPrice->setObjectName("equipPrice");
        equipPrice->setGeometry(QRect(420, 180, 131, 32));
        equipPrice->setFont(font9);
        equipPrice->setStyleSheet(QString::fromUtf8("#equipPrice\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipDOM = new QDateEdit(equipAdd);
        equipDOM->setObjectName("equipDOM");
        equipDOM->setGeometry(QRect(420, 290, 240, 32));
        equipDOM->setFont(font9);
        equipDOM->setStyleSheet(QString::fromUtf8("#equipDOM\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipDOM->setMaximumDateTime(QDateTime(QDate(2030, 12, 31), QTime(14, 59, 59)));
        equipDOM->setMinimumDateTime(QDateTime(QDate(2025, 4, 21), QTime(16, 0, 0)));
        pushButton_11 = new QPushButton(equipAdd);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(560, 440, 150, 32));
        QFont font11;
        font11.setPointSize(10);
        font11.setBold(false);
        pushButton_11->setFont(font11);
        pushButton_11->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_11->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        pushButton_11->setStyleSheet(QString::fromUtf8("#pushButton_11\n"
"{\n"
"	background:#00855C;\n"
"	border:none;\n"
"	color:white;\n"
"}\n"
"\n"
"#pushButton_11:hover\n"
"{\n"
"	background:#2D2D2D;\n"
"	border:2px solid #00855C;\n"
"	color:#00855C;\n"
"}"));
        state = new QLabel(equipAdd);
        state->setObjectName("state");
        state->setGeometry(QRect(30, 250, 201, 21));
        state->setFont(font5);
        equipState = new QComboBox(equipAdd);
        equipState->addItem(QString());
        equipState->addItem(QString());
        equipState->addItem(QString());
        equipState->addItem(QString());
        equipState->setObjectName("equipState");
        equipState->setGeometry(QRect(30, 290, 240, 32));
        equipState->setFont(font9);
        equipState->setStyleSheet(QString::fromUtf8("#equipState\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipType = new QComboBox(equipAdd);
        equipType->addItem(QString());
        equipType->addItem(QString());
        equipType->addItem(QString());
        equipType->addItem(QString());
        equipType->addItem(QString());
        equipType->addItem(QString());
        equipType->setObjectName("equipType");
        equipType->setGeometry(QRect(30, 190, 240, 32));
        equipType->setFont(font9);
        equipType->setStyleSheet(QString::fromUtf8("#equipType\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        state_2 = new QLabel(equipAdd);
        state_2->setObjectName("state_2");
        state_2->setGeometry(QRect(30, 340, 201, 21));
        state_2->setFont(font5);
        equipType_3 = new QComboBox(equipAdd);
        equipType_3->addItem(QString());
        equipType_3->addItem(QString());
        equipType_3->setObjectName("equipType_3");
        equipType_3->setGeometry(QRect(30, 370, 240, 32));
        equipType_3->setFont(font9);
        equipType_3->setStyleSheet(QString::fromUtf8("#equipType_3\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        Name_3 = new QLabel(equipAdd);
        Name_3->setObjectName("Name_3");
        Name_3->setGeometry(QRect(420, 340, 141, 21));
        Name_3->setFont(font5);
        equipType_4 = new QComboBox(equipAdd);
        equipType_4->addItem(QString());
        equipType_4->addItem(QString());
        equipType_4->setObjectName("equipType_4");
        equipType_4->setGeometry(QRect(420, 370, 240, 32));
        equipType_4->setFont(font9);
        equipType_4->setStyleSheet(QString::fromUtf8("#equipType_4\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipQuantity = new QLineEdit(equipAdd);
        equipQuantity->setObjectName("equipQuantity");
        equipQuantity->setGeometry(QRect(560, 180, 101, 32));
        equipQuantity->setFont(font9);
        equipQuantity->setStyleSheet(QString::fromUtf8("#equipQuantity\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        priice_2 = new QLabel(equipAdd);
        priice_2->setObjectName("priice_2");
        priice_2->setGeometry(QRect(550, 150, 81, 21));
        priice_2->setFont(font5);
        label_13 = new QLabel(equipAdd);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(512, 179, 41, 31));
        label_13->setStyleSheet(QString::fromUtf8("#label_13\n"
"{\n"
"	color: rgb(0, 0, 0);\n"
"}"));
        stackedWidget->addWidget(equipAdd);
        equipUpdate = new QWidget();
        equipUpdate->setObjectName("equipUpdate");
        searchTextBox_3 = new QLineEdit(equipUpdate);
        searchTextBox_3->setObjectName("searchTextBox_3");
        searchTextBox_3->setGeometry(QRect(30, 70, 811, 41));
        searchTextBox_3->setStyleSheet(QString::fromUtf8("#searchTextBox_3\n"
"{\n"
"    font-weight: bold;\n"
"    color:rgb(107, 107, 107);\n"
"	padding-left:8px;\n"
"	border:none;\n"
"    background-color:white;\n"
"}\n"
""));
        tableView_3 = new QTableView(equipUpdate);
        tableView_3->setObjectName("tableView_3");
        tableView_3->setGeometry(QRect(30, 130, 811, 141));
        tableView_3->setFont(font);
        tableView_3->setStyleSheet(QString::fromUtf8(" #tableView_3\n"
"{\n"
"	color: rgb(0, 0, 0);\n"
"	background-color:rgb(255, 255, 255);\n"
"}\n"
"#tableView_3::item:selected {\n"
"    background-color: #a8d8ff; \n"
"    color: black;\n"
"}"));
        label_44 = new QLabel(equipUpdate);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(30, 30, 241, 31));
        label_44->setFont(font10);
        pushButton_13 = new QPushButton(equipUpdate);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(640, 500, 150, 32));
        pushButton_13->setFont(font11);
        pushButton_13->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_13->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        pushButton_13->setStyleSheet(QString::fromUtf8("#pushButton_13\n"
"{\n"
"	background:#00855C;\n"
"	border:none;\n"
"	color:white;\n"
"}\n"
"\n"
"#pushButton_13:hover\n"
"{\n"
"	background:#2D2D2D;\n"
"	border:2px solid #00855C;\n"
"	color:#00855C;\n"
"}"));
        equipDOM_2 = new QDateEdit(equipUpdate);
        equipDOM_2->setObjectName("equipDOM_2");
        equipDOM_2->setGeometry(QRect(290, 345, 211, 32));
        equipDOM_2->setFont(font9);
        equipDOM_2->setStyleSheet(QString::fromUtf8("#equipDOM_2\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipDOM_2->setMaximumDate(QDate(2030, 12, 31));
        equipDOM_2->setMinimumDate(QDate(2025, 4, 22));
        equipState_2 = new QComboBox(equipUpdate);
        equipState_2->addItem(QString());
        equipState_2->addItem(QString());
        equipState_2->addItem(QString());
        equipState_2->addItem(QString());
        equipState_2->setObjectName("equipState_2");
        equipState_2->setGeometry(QRect(210, 430, 211, 32));
        equipState_2->setFont(font9);
        equipState_2->setStyleSheet(QString::fromUtf8("#equipState_2\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        DNM_2 = new QLabel(equipUpdate);
        DNM_2->setObjectName("DNM_2");
        DNM_2->setGeometry(QRect(290, 295, 231, 21));
        DNM_2->setFont(font5);
        equipType_6 = new QComboBox(equipUpdate);
        equipType_6->addItem(QString());
        equipType_6->addItem(QString());
        equipType_6->addItem(QString());
        equipType_6->addItem(QString());
        equipType_6->addItem(QString());
        equipType_6->addItem(QString());
        equipType_6->setObjectName("equipType_6");
        equipType_6->setGeometry(QRect(30, 435, 161, 32));
        equipType_6->setFont(font9);
        equipType_6->setStyleSheet(QString::fromUtf8("#equipType_6\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        id_39 = new QLabel(equipUpdate);
        id_39->setObjectName("id_39");
        id_39->setGeometry(QRect(210, 400, 201, 21));
        id_39->setFont(font5);
        id_37 = new QLabel(equipUpdate);
        id_37->setObjectName("id_37");
        id_37->setGeometry(QRect(30, 400, 141, 21));
        id_37->setFont(font5);
        equipDanger = new QComboBox(equipUpdate);
        equipDanger->addItem(QString());
        equipDanger->addItem(QString());
        equipDanger->setObjectName("equipDanger");
        equipDanger->setGeometry(QRect(570, 430, 101, 32));
        equipDanger->setFont(font9);
        equipDanger->setStyleSheet(QString::fromUtf8("#equipDanger\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipConsum = new QComboBox(equipUpdate);
        equipConsum->addItem(QString());
        equipConsum->addItem(QString());
        equipConsum->setObjectName("equipConsum");
        equipConsum->setGeometry(QRect(440, 430, 111, 32));
        equipConsum->setFont(font9);
        equipConsum->setStyleSheet(QString::fromUtf8("#equipConsum\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipName_3 = new QLineEdit(equipUpdate);
        equipName_3->setObjectName("equipName_3");
        equipName_3->setGeometry(QRect(30, 340, 181, 32));
        equipName_3->setFont(font9);
        equipName_3->setStyleSheet(QString::fromUtf8("#equipName_3\n"
"{\n"
"    background-color: white;\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        state_3 = new QLabel(equipUpdate);
        state_3->setObjectName("state_3");
        state_3->setGeometry(QRect(440, 400, 121, 21));
        state_3->setFont(font5);
        id_41 = new QLabel(equipUpdate);
        id_41->setObjectName("id_41");
        id_41->setGeometry(QRect(680, 400, 141, 21));
        id_41->setFont(font5);
        id_34 = new QLabel(equipUpdate);
        id_34->setObjectName("id_34");
        id_34->setGeometry(QRect(30, 300, 141, 21));
        id_34->setFont(font5);
        equipPurchase_2 = new QDateEdit(equipUpdate);
        equipPurchase_2->setObjectName("equipPurchase_2");
        equipPurchase_2->setGeometry(QRect(680, 430, 131, 32));
        equipPurchase_2->setFont(font9);
        equipPurchase_2->setStyleSheet(QString::fromUtf8("#equipPurchase_2\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        equipPurchase_2->setMaximumDate(QDate(2025, 4, 22));
        equipPurchase_2->setMinimumDate(QDate(2000, 9, 14));
        equipPurchase_2->setCurrentSection(QDateTimeEdit::Section::YearSection);
        Name_4 = new QLabel(equipUpdate);
        Name_4->setObjectName("Name_4");
        Name_4->setGeometry(QRect(570, 400, 141, 21));
        Name_4->setFont(font5);
        id_33 = new QLabel(equipUpdate);
        id_33->setObjectName("id_33");
        id_33->setGeometry(QRect(570, 290, 121, 21));
        id_33->setFont(font5);
        equipQuantity_2 = new QLineEdit(equipUpdate);
        equipQuantity_2->setObjectName("equipQuantity_2");
        equipQuantity_2->setGeometry(QRect(710, 340, 101, 32));
        equipQuantity_2->setFont(font9);
        equipQuantity_2->setStyleSheet(QString::fromUtf8("#equipQuantity_2\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        priice_3 = new QLabel(equipUpdate);
        priice_3->setObjectName("priice_3");
        priice_3->setGeometry(QRect(720, 290, 81, 21));
        priice_3->setFont(font5);
        equipPrice_2 = new QLineEdit(equipUpdate);
        equipPrice_2->setObjectName("equipPrice_2");
        equipPrice_2->setGeometry(QRect(570, 340, 131, 32));
        equipPrice_2->setFont(font9);
        equipPrice_2->setStyleSheet(QString::fromUtf8("#equipPrice_2\n"
"{\n"
"	background:white;\n"
"	color:black;\n"
"	border:none;\n"
"	padding-left:6px;\n"
"}"));
        label_15 = new QLabel(equipUpdate);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(660, 340, 41, 31));
        label_15->setStyleSheet(QString::fromUtf8("#label_15\n"
"{\n"
"	color: rgb(0, 0, 0);\n"
"}"));
        stackedWidget->addWidget(equipUpdate);
        equipDelete = new QWidget();
        equipDelete->setObjectName("equipDelete");
        searchTextBox_2 = new QLineEdit(equipDelete);
        searchTextBox_2->setObjectName("searchTextBox_2");
        searchTextBox_2->setGeometry(QRect(50, 60, 751, 41));
        searchTextBox_2->setStyleSheet(QString::fromUtf8("#searchTextBox_2\n"
"{\n"
"    font-weight: bold;\n"
"    color:rgb(107, 107, 107);\n"
"	padding-left:8px;\n"
"	border:none;\n"
"    background-color:white;\n"
"}\n"
""));
        tableView_4 = new QTableView(equipDelete);
        tableView_4->setObjectName("tableView_4");
        tableView_4->setGeometry(QRect(50, 140, 747, 421));
        tableView_4->setFont(font);
        tableView_4->setStyleSheet(QString::fromUtf8("#tableView_4\n"
"{\n"
"	color: rgb(0, 0, 0);\n"
"	background-color:rgb(255, 255, 255);\n"
"}\n"
"#tableView_4::item:selected {\n"
"    background-color: #a8d8ff; \n"
"    color: black;\n"
"}"));
        deleteEquipButton_2 = new QPushButton(equipDelete);
        deleteEquipButton_2->setObjectName("deleteEquipButton_2");
        deleteEquipButton_2->setGeometry(QRect(650, 580, 150, 32));
        deleteEquipButton_2->setFont(font11);
        deleteEquipButton_2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        deleteEquipButton_2->setFocusPolicy(Qt::FocusPolicy::TabFocus);
        deleteEquipButton_2->setStyleSheet(QString::fromUtf8("#deleteEquipButton_2\n"
"{\n"
"	background:#EC3245;\n"
"	border:none;\n"
"	color:white;\n"
"}\n"
"\n"
"#deleteEquipButton_2:hover\n"
"{\n"
"	background:#2d2d2d;\n"
"	border:2px solid #EC3245;\n"
"	color:#EC3245;\n"
"}"));
        stackedWidget->addWidget(equipDelete);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(430, 20, 611, 111));
        label_10->setFont(font3);
        label_10->setStyleSheet(QString::fromUtf8("#label_10\n"
"{\n"
"    color:#008080;\n"
"}"));
        label_pic_2 = new QLabel(centralwidget);
        label_pic_2->setObjectName("label_pic_2");
        label_pic_2->setGeometry(QRect(1090, 10, 191, 131));
        label_pic_2->setPixmap(QPixmap(QString::fromUtf8(":/images/images/bed.jpg")));
        label_pic_2->setScaledContents(true);
        goBack_5 = new QPushButton(centralwidget);
        goBack_5->setObjectName("goBack_5");
        goBack_5->setGeometry(QRect(320, 100, 61, 41));
        goBack_5->setStyleSheet(QString::fromUtf8("#goBack_5\n"
"{\n"
"      \n"
"	background-color:#007bea;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/left.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        goBack_5->setIcon(icon1);
        goBack_5->setIconSize(QSize(35, 35));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1357, 25));
        menubar->setStyleSheet(QString::fromUtf8("#menubar\n"
"{\n"
"    border: none;\n"
"    border-bottom: none;\n"
"}"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        QFont font12;
        font12.setKerning(false);
        toolBar->setFont(font12);
        toolBar->setStyleSheet(QString::fromUtf8("#toolBar{\n"
"    border: none;\n"
"    border-bottom: none;\n"
"}"));
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:10pt; font-style:italic; color:#ffffff;\">Optimizing work productivity</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#ffffff;\">Management System</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#ffffff;\">App Version: 1.0.0</span></p></body></html>", nullptr));
        label_pic->setText(QString());
        label_12->setText(QCoreApplication::translate("MainWindow", "VaxEra", nullptr));
        searchButton->setText(QCoreApplication::translate("MainWindow", "  Search", nullptr));
        updateEquipButton->setText(QCoreApplication::translate("MainWindow", "  Update Equipment info", nullptr));
        addEquipButton->setText(QCoreApplication::translate("MainWindow", "  Add Equipment", nullptr));
        deleteEquipButton->setText(QCoreApplication::translate("MainWindow", "  Delete Equipment info", nullptr));
        aboutButton->setText(QCoreApplication::translate("MainWindow", "  About App", nullptr));
        QR->setText(QCoreApplication::translate("MainWindow", "code QR scan and generation", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Number of equipments</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">   Non-functional equipments</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "    Under Maintenance", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "000", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "000", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "000", nullptr));
        searchTextBox->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "       Consumables", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "000", nullptr));
        export_2->setText(QCoreApplication::translate("MainWindow", "      Export ", nullptr));
        satistics->setText(QCoreApplication::translate("MainWindow", "Satistics", nullptr));
        label_pic_3->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#006c6c;\">Management System</span></p></body></html>", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:14pt; font-weight:700; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">A vaccination and research center's equipment and infrastructure management system prioritizes precise inventory control of temperature-sensitive vaccines, meticulous tracking of research equipment calibration, and secure data management for clinical trials. It would feature real-time monitoring of storage conditions, automated maintenance scheduling for lab equipment, and robust rep"
                        "orting tools for regulatory compliance and research analysis, ensuring both operational efficiency and data integrity.</p></body></html>", nullptr));
        id_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">type</span></p></body></html>", nullptr));
        PD->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Purchase date </p></body></html>", nullptr));
        DNM->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Date of next maintenance</span></p></body></html>", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline; color:#55aaff;\">Equipement Info</span></p></body></html>", nullptr));
        priice->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">initial price</span></p></body></html>", nullptr));
        Name_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Name</span></p></body></html>", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        state->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">State</span></p></body></html>", nullptr));
        equipState->setItemText(0, QCoreApplication::translate("MainWindow", "not working", nullptr));
        equipState->setItemText(1, QCoreApplication::translate("MainWindow", "working", nullptr));
        equipState->setItemText(2, QCoreApplication::translate("MainWindow", "under maintenance", nullptr));
        equipState->setItemText(3, QCoreApplication::translate("MainWindow", "irrelevant", nullptr));

        equipType->setItemText(0, QCoreApplication::translate("MainWindow", "Patient Care", nullptr));
        equipType->setItemText(1, QCoreApplication::translate("MainWindow", "Storage", nullptr));
        equipType->setItemText(2, QCoreApplication::translate("MainWindow", "Diagnostic", nullptr));
        equipType->setItemText(3, QCoreApplication::translate("MainWindow", "Administrative", nullptr));
        equipType->setItemText(4, QCoreApplication::translate("MainWindow", "Sterilization", nullptr));
        equipType->setItemText(5, QCoreApplication::translate("MainWindow", "(IT) & Software", nullptr));

        state_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Consumable ?</p></body></html>", nullptr));
        equipType_3->setItemText(0, QCoreApplication::translate("MainWindow", "No", nullptr));
        equipType_3->setItemText(1, QCoreApplication::translate("MainWindow", "Yes", nullptr));

        Name_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Dangerous ?</span></p></body></html>", nullptr));
        equipType_4->setItemText(0, QCoreApplication::translate("MainWindow", "Yes", nullptr));
        equipType_4->setItemText(1, QCoreApplication::translate("MainWindow", "No", nullptr));

        priice_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Quantity</p></body></html>", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "TND", nullptr));
        searchTextBox_3->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-style:italic; text-decoration: underline; color:#55aaff;\">Equipement Info</span></p></body></html>", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        equipState_2->setItemText(0, QCoreApplication::translate("MainWindow", "not working", nullptr));
        equipState_2->setItemText(1, QCoreApplication::translate("MainWindow", "working", nullptr));
        equipState_2->setItemText(2, QCoreApplication::translate("MainWindow", "under maintenance", nullptr));
        equipState_2->setItemText(3, QCoreApplication::translate("MainWindow", "irrelevant", nullptr));

        DNM_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Date of next maintenance</span></p></body></html>", nullptr));
        equipType_6->setItemText(0, QCoreApplication::translate("MainWindow", "Patient Care", nullptr));
        equipType_6->setItemText(1, QCoreApplication::translate("MainWindow", "Storage", nullptr));
        equipType_6->setItemText(2, QCoreApplication::translate("MainWindow", "Diagnostic", nullptr));
        equipType_6->setItemText(3, QCoreApplication::translate("MainWindow", "Administrative", nullptr));
        equipType_6->setItemText(4, QCoreApplication::translate("MainWindow", "Sterilization", nullptr));
        equipType_6->setItemText(5, QCoreApplication::translate("MainWindow", "(IT) & Software", nullptr));

        id_39->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">State</span></p></body></html>", nullptr));
        id_37->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Type</span></p></body></html>", nullptr));
        equipDanger->setItemText(0, QCoreApplication::translate("MainWindow", "Yes", nullptr));
        equipDanger->setItemText(1, QCoreApplication::translate("MainWindow", "No", nullptr));

        equipConsum->setItemText(0, QCoreApplication::translate("MainWindow", "No", nullptr));
        equipConsum->setItemText(1, QCoreApplication::translate("MainWindow", "Yes", nullptr));

        state_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Consumable ?</p></body></html>", nullptr));
        id_41->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Purchase Date</p></body></html>", nullptr));
        id_34->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Name</span></p></body></html>", nullptr));
        Name_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">Dangerous ?</span></p></body></html>", nullptr));
        id_33->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ffffff;\">initial price</span></p></body></html>", nullptr));
        priice_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Quantity</p></body></html>", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "TND", nullptr));
        searchTextBox_2->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        deleteEquipButton_2->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Equipment Management System", nullptr));
        label_pic_2->setText(QString());
        goBack_5->setText(QString());
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
