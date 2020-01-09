/********************************************************************************
** Form generated from reading UI file 'QYDlgCameraHomeHardCfg.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QYDLGCAMERAHOMEHARDCFG_H
#define UI_QYDLGCAMERAHOMEHARDCFG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "qydlgtitle.h"

QT_BEGIN_NAMESPACE

class Ui_QYDlgCameraHomeHardCfg
{
public:
    QLineEdit *lineEdit_name;
    QLabel *label_24;
    QLineEdit *lineEdit_Password;
    QLabel *label_28;
    QLabel *label_22;
    QLabel *label_27;
    QLineEdit *lineEdit_UserName;
    QLineEdit *lineEdit_IP;
    QLabel *label_29;
    QLineEdit *lineEdit_Port;
    QYDlgTitle *wd_title;
    QPushButton *but_OK;

    void setupUi(QDialog *QYDlgCameraHomeHardCfg)
    {
        if (QYDlgCameraHomeHardCfg->objectName().isEmpty())
            QYDlgCameraHomeHardCfg->setObjectName(QStringLiteral("QYDlgCameraHomeHardCfg"));
        QYDlgCameraHomeHardCfg->resize(640, 188);
        QYDlgCameraHomeHardCfg->setStyleSheet(QString::fromUtf8("QWidget{\n"
"color:rgba(200,207,217,255);\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"font-weight:bold;\n"
"background-color:rgba(102, 102, 102, 255);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-radius:0px;\n"
"border-image:url(\"\");\n"
"border-color:rgba(16, 18, 13,255);\n"
"}\n"
""));
        QYDlgCameraHomeHardCfg->setProperty("KeepAspect", QVariant(1));
        lineEdit_name = new QLineEdit(QYDlgCameraHomeHardCfg);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(84, 48, 160, 24));
        lineEdit_name->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_name->setFrame(true);
        lineEdit_name->setEchoMode(QLineEdit::Normal);
        label_24 = new QLabel(QYDlgCameraHomeHardCfg);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(20, 80, 42, 24));
        label_24->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_Password = new QLineEdit(QYDlgCameraHomeHardCfg);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        lineEdit_Password->setGeometry(QRect(384, 112, 160, 24));
        lineEdit_Password->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_Password->setFrame(true);
        lineEdit_Password->setEchoMode(QLineEdit::Password);
        label_28 = new QLabel(QYDlgCameraHomeHardCfg);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(20, 112, 42, 24));
        label_28->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_22 = new QLabel(QYDlgCameraHomeHardCfg);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 48, 42, 24));
        label_22->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_27 = new QLabel(QYDlgCameraHomeHardCfg);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(320, 80, 42, 24));
        label_27->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_UserName = new QLineEdit(QYDlgCameraHomeHardCfg);
        lineEdit_UserName->setObjectName(QStringLiteral("lineEdit_UserName"));
        lineEdit_UserName->setGeometry(QRect(84, 112, 160, 24));
        lineEdit_UserName->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_UserName->setFrame(true);
        lineEdit_UserName->setEchoMode(QLineEdit::Normal);
        lineEdit_IP = new QLineEdit(QYDlgCameraHomeHardCfg);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(84, 80, 160, 24));
        lineEdit_IP->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_IP->setFrame(true);
        lineEdit_IP->setEchoMode(QLineEdit::Normal);
        label_29 = new QLabel(QYDlgCameraHomeHardCfg);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(320, 112, 42, 24));
        label_29->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_Port = new QLineEdit(QYDlgCameraHomeHardCfg);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(384, 80, 160, 24));
        lineEdit_Port->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_Port->setFrame(true);
        lineEdit_Port->setEchoMode(QLineEdit::Normal);
        wd_title = new QYDlgTitle(QYDlgCameraHomeHardCfg);
        wd_title->setObjectName(QStringLiteral("wd_title"));
        wd_title->setGeometry(QRect(0, 0, 640, 32));
        wd_title->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(16, 18, 13,255);\n"
"border-width:0px;\n"
"font-size:14px;\n"
"}"));
        but_OK = new QPushButton(QYDlgCameraHomeHardCfg);
        but_OK->setObjectName(QStringLiteral("but_OK"));
        but_OK->setGeometry(QRect(518, 155, 102, 24));
        but_OK->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));

        retranslateUi(QYDlgCameraHomeHardCfg);

        QMetaObject::connectSlotsByName(QYDlgCameraHomeHardCfg);
    } // setupUi

    void retranslateUi(QDialog *QYDlgCameraHomeHardCfg)
    {
        QYDlgCameraHomeHardCfg->setWindowTitle(QApplication::translate("QYDlgCameraHomeHardCfg", "Dialog", 0));
        label_24->setText(QApplication::translate("QYDlgCameraHomeHardCfg", "IP\345\234\260\345\235\200", 0));
        label_28->setText(QApplication::translate("QYDlgCameraHomeHardCfg", "\347\224\250\346\210\267\345\220\215", 0));
        label_22->setText(QApplication::translate("QYDlgCameraHomeHardCfg", "\345\244\207\346\263\250\345\220\215", 0));
        label_27->setText(QApplication::translate("QYDlgCameraHomeHardCfg", "\347\253\257\345\217\243", 0));
        label_29->setText(QApplication::translate("QYDlgCameraHomeHardCfg", "\345\257\206\347\240\201", 0));
        but_OK->setText(QApplication::translate("QYDlgCameraHomeHardCfg", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class QYDlgCameraHomeHardCfg: public Ui_QYDlgCameraHomeHardCfg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QYDLGCAMERAHOMEHARDCFG_H
