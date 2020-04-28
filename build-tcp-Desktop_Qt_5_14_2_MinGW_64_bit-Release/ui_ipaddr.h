/********************************************************************************
** Form generated from reading UI file 'ipaddr.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPADDR_H
#define UI_IPADDR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IPaddr
{
public:
    QTextEdit *IPtext;
    QLabel *label;
    QPushButton *exitButton;

    void setupUi(QWidget *IPaddr)
    {
        if (IPaddr->objectName().isEmpty())
            IPaddr->setObjectName(QString::fromUtf8("IPaddr"));
        IPaddr->resize(400, 308);
        IPtext = new QTextEdit(IPaddr);
        IPtext->setObjectName(QString::fromUtf8("IPtext"));
        IPtext->setGeometry(QRect(30, 50, 341, 191));
        label = new QLabel(IPaddr);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 101, 16));
        exitButton = new QPushButton(IPaddr);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(160, 260, 93, 28));

        retranslateUi(IPaddr);

        QMetaObject::connectSlotsByName(IPaddr);
    } // setupUi

    void retranslateUi(QWidget *IPaddr)
    {
        IPaddr->setWindowTitle(QCoreApplication::translate("IPaddr", "Form", nullptr));
        label->setText(QCoreApplication::translate("IPaddr", "\346\234\254\346\234\272\345\234\260\345\235\200\357\274\232", nullptr));
        exitButton->setText(QCoreApplication::translate("IPaddr", "\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IPaddr: public Ui_IPaddr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPADDR_H
