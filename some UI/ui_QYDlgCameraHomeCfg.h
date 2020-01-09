/********************************************************************************
** Form generated from reading UI file 'QYDlgCameraHomeCfg.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QYDLGCAMERAHOMECFG_H
#define UI_QYDLGCAMERAHOMECFG_H

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

class Ui_QYDlgCameraHomeCfg
{
public:
    QLineEdit *lineEdit_name;
    QLabel *label_22;
    QYDlgTitle *wd_title;
    QPushButton *but_OK;

    void setupUi(QDialog *QYDlgCameraHomeCfg)
    {
        if (QYDlgCameraHomeCfg->objectName().isEmpty())
            QYDlgCameraHomeCfg->setObjectName(QStringLiteral("QYDlgCameraHomeCfg"));
        QYDlgCameraHomeCfg->resize(640, 111);
        QYDlgCameraHomeCfg->setStyleSheet(QString::fromUtf8("QWidget{\n"
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
        QYDlgCameraHomeCfg->setProperty("KeepAspect", QVariant(1));
        lineEdit_name = new QLineEdit(QYDlgCameraHomeCfg);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(84, 48, 536, 24));
        lineEdit_name->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_name->setFrame(true);
        lineEdit_name->setEchoMode(QLineEdit::Normal);
        label_22 = new QLabel(QYDlgCameraHomeCfg);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 48, 42, 24));
        label_22->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        wd_title = new QYDlgTitle(QYDlgCameraHomeCfg);
        wd_title->setObjectName(QStringLiteral("wd_title"));
        wd_title->setGeometry(QRect(0, 0, 640, 32));
        wd_title->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(16, 18, 13,255);\n"
"border-width:0px;\n"
"font-size:14px;\n"
"}"));
        but_OK = new QPushButton(QYDlgCameraHomeCfg);
        but_OK->setObjectName(QStringLiteral("but_OK"));
        but_OK->setGeometry(QRect(518, 80, 102, 24));
        but_OK->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));

        retranslateUi(QYDlgCameraHomeCfg);

        QMetaObject::connectSlotsByName(QYDlgCameraHomeCfg);
    } // setupUi

    void retranslateUi(QDialog *QYDlgCameraHomeCfg)
    {
        QYDlgCameraHomeCfg->setWindowTitle(QApplication::translate("QYDlgCameraHomeCfg", "Dialog", 0));
        label_22->setText(QApplication::translate("QYDlgCameraHomeCfg", "\345\244\207\346\263\250\345\220\215", 0));
        but_OK->setText(QApplication::translate("QYDlgCameraHomeCfg", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class QYDlgCameraHomeCfg: public Ui_QYDlgCameraHomeCfg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QYDLGCAMERAHOMECFG_H
