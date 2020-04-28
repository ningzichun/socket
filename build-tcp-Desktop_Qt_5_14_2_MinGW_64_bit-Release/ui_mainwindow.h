/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGetIP;
    QAction *actionAbout;
    QAction *actionsettings;
    QWidget *centralwidget;
    QTextEdit *logText;
    QLabel *label;
    QTextEdit *inputText;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *imgButton;
    QPushButton *fileButton;
    QPushButton *sendButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *targetIP;
    QLabel *label_4;
    QLineEdit *targetPort;
    QPushButton *connectButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *listeningPort;
    QLabel *label_6;
    QLabel *myIP;
    QPushButton *startButton;
    QLabel *selectedFile;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(859, 558);
        actionGetIP = new QAction(MainWindow);
        actionGetIP->setObjectName(QString::fromUtf8("actionGetIP"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionsettings = new QAction(MainWindow);
        actionsettings->setObjectName(QString::fromUtf8("actionsettings"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        logText = new QTextEdit(centralwidget);
        logText->setObjectName(QString::fromUtf8("logText"));
        logText->setGeometry(QRect(20, 100, 781, 191));
        logText->setReadOnly(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 66, 91, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        label->setFont(font);
        inputText = new QTextEdit(centralwidget);
        inputText->setObjectName(QString::fromUtf8("inputText"));
        inputText->setGeometry(QRect(20, 340, 781, 111));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 306, 121, 20));
        label_2->setFont(font);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(230, 470, 311, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        imgButton = new QPushButton(horizontalLayoutWidget);
        imgButton->setObjectName(QString::fromUtf8("imgButton"));
        imgButton->setFont(font);

        horizontalLayout->addWidget(imgButton);

        fileButton = new QPushButton(horizontalLayoutWidget);
        fileButton->setObjectName(QString::fromUtf8("fileButton"));
        fileButton->setFont(font);

        horizontalLayout->addWidget(fileButton);

        sendButton = new QPushButton(horizontalLayoutWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setFont(font);

        horizontalLayout->addWidget(sendButton);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 421, 34));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        horizontalLayout_2->addWidget(label_3);

        targetIP = new QLineEdit(horizontalLayoutWidget_2);
        targetIP->setObjectName(QString::fromUtf8("targetIP"));
        targetIP->setFont(font);

        horizontalLayout_2->addWidget(targetIP);

        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        horizontalLayout_2->addWidget(label_4);

        targetPort = new QLineEdit(horizontalLayoutWidget_2);
        targetPort->setObjectName(QString::fromUtf8("targetPort"));
        targetPort->setFont(font);
        targetPort->setMaxLength(5);

        horizontalLayout_2->addWidget(targetPort);

        connectButton = new QPushButton(horizontalLayoutWidget_2);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setFont(font);

        horizontalLayout_2->addWidget(connectButton);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(449, 10, 271, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        listeningPort = new QLineEdit(gridLayoutWidget);
        listeningPort->setObjectName(QString::fromUtf8("listeningPort"));
        listeningPort->setMaximumSize(QSize(150, 16777215));
        listeningPort->setFont(font);
        listeningPort->setLayoutDirection(Qt::LeftToRight);
        listeningPort->setMaxLength(5);
        listeningPort->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(listeningPort, 0, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        myIP = new QLabel(gridLayoutWidget);
        myIP->setObjectName(QString::fromUtf8("myIP"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(myIP->sizePolicy().hasHeightForWidth());
        myIP->setSizePolicy(sizePolicy);
        myIP->setFont(font);
        myIP->setAcceptDrops(true);
        myIP->setAutoFillBackground(false);
        myIP->setTextFormat(Qt::PlainText);
        myIP->setScaledContents(false);
        myIP->setWordWrap(true);
        myIP->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(myIP, 1, 1, 1, 1);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(710, 20, 91, 51));
        startButton->setFont(font);
        selectedFile = new QLabel(centralwidget);
        selectedFile->setObjectName(QString::fromUtf8("selectedFile"));
        selectedFile->setGeometry(QRect(20, 460, 671, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 859, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionGetIP);
        menu->addAction(actionsettings);
        menu->addSeparator();
        menu->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionGetIP->setText(QCoreApplication::translate("MainWindow", "\346\234\254\346\234\272\345\234\260\345\235\200", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        actionsettings->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\350\256\260\345\275\225:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\344\277\241\346\201\257:", nullptr));
        imgButton->setText(QCoreApplication::translate("MainWindow", "\345\233\276\347\211\207", nullptr));
        fileButton->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\257\271\346\226\271IP", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\347\233\221\345\220\254\347\253\257\345\217\243", nullptr));
        listeningPort->setText(QCoreApplication::translate("MainWindow", "10080", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\234\254\346\234\272IP", nullptr));
        myIP->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\344\270\255...", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\347\233\221\345\220\254", nullptr));
        selectedFile->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\232\204\346\226\207\344\273\266", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
