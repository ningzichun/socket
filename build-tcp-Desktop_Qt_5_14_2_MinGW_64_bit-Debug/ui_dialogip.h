/********************************************************************************
** Form generated from reading UI file 'dialogip.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGIP_H
#define UI_DIALOGIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogIP
{
public:
    QLabel *label;
    QPushButton *exitButton;
    QTextEdit *IPtext;

    void setupUi(QDialog *DialogIP)
    {
        if (DialogIP->objectName().isEmpty())
            DialogIP->setObjectName(QString::fromUtf8("DialogIP"));
        DialogIP->resize(400, 300);
        label = new QLabel(DialogIP);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 101, 16));
        exitButton = new QPushButton(DialogIP);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(150, 250, 93, 28));
        IPtext = new QTextEdit(DialogIP);
        IPtext->setObjectName(QString::fromUtf8("IPtext"));
        IPtext->setGeometry(QRect(30, 50, 341, 191));

        retranslateUi(DialogIP);

        QMetaObject::connectSlotsByName(DialogIP);
    } // setupUi

    void retranslateUi(QDialog *DialogIP)
    {
        DialogIP->setWindowTitle(QCoreApplication::translate("DialogIP", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DialogIP", "\346\234\254\346\234\272\345\234\260\345\235\200\357\274\232", nullptr));
        exitButton->setText(QCoreApplication::translate("DialogIP", "\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogIP: public Ui_DialogIP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGIP_H
