/********************************************************************************
** Form generated from reading UI file 'QYDlgAboutUs.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QYDLGABOUTUS_H
#define UI_QYDLGABOUTUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qydlgtitle.h"

QT_BEGIN_NAMESPACE

class Ui_QYDlgAboutUs
{
public:
    QYDlgTitle *wd_title;
    QPushButton *butOK;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QWidget *widget;

    void setupUi(QDialog *QYDlgAboutUs)
    {
        if (QYDlgAboutUs->objectName().isEmpty())
            QYDlgAboutUs->setObjectName(QStringLiteral("QYDlgAboutUs"));
        QYDlgAboutUs->resize(640, 360);
        QYDlgAboutUs->setFocusPolicy(Qt::ClickFocus);
        QYDlgAboutUs->setStyleSheet(QString::fromUtf8("QWidget{\n"
"color:rgba(200,207,217,255);\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:14px;\n"
"font-weight:bold;\n"
"background-color:rgba(102, 102, 102, 255);\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-radius:0px;\n"
"border-image:url(\"\");\n"
"border-color:rgba(16, 18, 13,255);\n"
"}\n"
""));
        QYDlgAboutUs->setProperty("KeepAspect", QVariant(1));
        QYDlgAboutUs->setProperty("StopAspect", QVariant(1));
        wd_title = new QYDlgTitle(QYDlgAboutUs);
        wd_title->setObjectName(QStringLiteral("wd_title"));
        wd_title->setGeometry(QRect(0, 0, 640, 32));
        wd_title->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(16, 18, 13,255);\n"
"border-width:0px;\n"
"font-size:14px;\n"
"}"));
        butOK = new QPushButton(QYDlgAboutUs);
        butOK->setObjectName(QStringLiteral("butOK"));
        butOK->setGeometry(QRect(468, 308, 132, 32));
        butOK->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}\n"
""));
        label_26 = new QLabel(QYDlgAboutUs);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(60, 190, 300, 24));
        label_26->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_27 = new QLabel(QYDlgAboutUs);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(60, 264, 372, 24));
        label_27->setStyleSheet(QLatin1String("QWidget{\n"
"color:rgba(160,207,217,128);\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_28 = new QLabel(QYDlgAboutUs);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(60, 222, 300, 24));
        label_28->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_29 = new QLabel(QYDlgAboutUs);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(60, 80, 128, 24));
        label_29->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"font-size:20px;\n"
"}"));
        widget = new QWidget(QYDlgAboutUs);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(400, 72, 160, 160));
        widget->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"border-image:url(\":images/ap2000/001_0\");\n"
"}"));

        retranslateUi(QYDlgAboutUs);

        QMetaObject::connectSlotsByName(QYDlgAboutUs);
    } // setupUi

    void retranslateUi(QDialog *QYDlgAboutUs)
    {
        QYDlgAboutUs->setWindowTitle(QApplication::translate("QYDlgAboutUs", "Dialog", 0));
        butOK->setText(QApplication::translate("QYDlgAboutUs", "\347\241\256\345\256\232", 0));
        label_26->setText(QApplication::translate("QYDlgAboutUs", "\344\270\273\347\211\210\346\234\254\345\217\267\357\274\2321 (1.6.8.0)", 0));
        label_27->setText(QApplication::translate("QYDlgAboutUs", "Copyright(c) EShong All Rights Reserved", 0));
        label_28->setText(QApplication::translate("QYDlgAboutUs", "\345\215\207\347\272\247\346\227\245\346\234\237\357\274\2322017.10.31", 0));
        label_29->setText(QApplication::translate("QYDlgAboutUs", "\345\205\250\346\231\257\347\233\221\346\216\247", 0));
    } // retranslateUi

};

namespace Ui {
    class QYDlgAboutUs: public Ui_QYDlgAboutUs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QYDLGABOUTUS_H
