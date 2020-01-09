/********************************************************************************
** Form generated from reading UI file 'QYDlgCameraAddHome.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QYDLGCAMERAADDHOME_H
#define UI_QYDLGCAMERAADDHOME_H

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

class Ui_QYDlgCameraAddHome
{
public:
    QLineEdit *lineEdit_name;
    QLabel *label_22;
    QYDlgTitle *wd_title;
    QPushButton *but_Add;

    void setupUi(QDialog *QYDlgCameraAddHome)
    {
        if (QYDlgCameraAddHome->objectName().isEmpty())
            QYDlgCameraAddHome->setObjectName(QStringLiteral("QYDlgCameraAddHome"));
        QYDlgCameraAddHome->resize(640, 111);
        QYDlgCameraAddHome->setStyleSheet(QString::fromUtf8("QWidget{\n"
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
        QYDlgCameraAddHome->setProperty("StopAspect", QVariant(1));
        lineEdit_name = new QLineEdit(QYDlgCameraAddHome);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(84, 48, 536, 24));
        lineEdit_name->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_name->setFrame(true);
        lineEdit_name->setEchoMode(QLineEdit::Normal);
        label_22 = new QLabel(QYDlgCameraAddHome);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 48, 50, 24));
        label_22->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        wd_title = new QYDlgTitle(QYDlgCameraAddHome);
        wd_title->setObjectName(QStringLiteral("wd_title"));
        wd_title->setGeometry(QRect(0, 0, 640, 32));
        wd_title->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(16, 18, 13,255);\n"
"border-width:0px;\n"
"font-size:14px;\n"
"}"));
        but_Add = new QPushButton(QYDlgCameraAddHome);
        but_Add->setObjectName(QStringLiteral("but_Add"));
        but_Add->setGeometry(QRect(518, 79, 102, 24));
        but_Add->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));

        retranslateUi(QYDlgCameraAddHome);

        QMetaObject::connectSlotsByName(QYDlgCameraAddHome);
    } // setupUi

    void retranslateUi(QDialog *QYDlgCameraAddHome)
    {
        QYDlgCameraAddHome->setWindowTitle(QApplication::translate("QYDlgCameraAddHome", "Dialog", 0));
        label_22->setText(QApplication::translate("QYDlgCameraAddHome", "\345\214\272\345\237\237\345\220\215", 0));
        but_Add->setText(QApplication::translate("QYDlgCameraAddHome", "\346\267\273\345\212\240", 0));
    } // retranslateUi

};

namespace Ui {
    class QYDlgCameraAddHome: public Ui_QYDlgCameraAddHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QYDLGCAMERAADDHOME_H
