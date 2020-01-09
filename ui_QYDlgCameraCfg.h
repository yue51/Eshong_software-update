/********************************************************************************
** Form generated from reading UI file 'QYDlgCameraCfg.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QYDLGCAMERACFG_H
#define UI_QYDLGCAMERACFG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qydlgtitle.h"

QT_BEGIN_NAMESPACE

class Ui_QYDlgCameraCfg
{
public:
    QLabel *label_26;
    QLineEdit *lineEdit_name;
    QLabel *label_24;
    QLineEdit *lineEdit_Password;
    QLabel *label_28;
    QLabel *label_22;
    QLabel *label_27;
    QLineEdit *lineEdit_UserName;
    QLineEdit *lineEdit_IP;
    QLabel *label_29;
    QComboBox *comboBox_tree;
    QLineEdit *lineEdit_Port;
    QLabel *label_30;
    QComboBox *comboBox_imgType;
    QYDlgTitle *wd_title;
    QWidget *widget;
    QPushButton *but_OK;
    QDoubleSpinBox *dSpinBox_AgH;
    QLabel *label_21;
    QLabel *label_31;
    QComboBox *comboBox_panoType;

    void setupUi(QDialog *QYDlgCameraCfg)
    {
        if (QYDlgCameraCfg->objectName().isEmpty())
            QYDlgCameraCfg->setObjectName(QStringLiteral("QYDlgCameraCfg"));
        QYDlgCameraCfg->resize(640, 271);
        QYDlgCameraCfg->setStyleSheet(QString::fromUtf8("QWidget{\n"
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
        QYDlgCameraCfg->setProperty("KeepAspect", QVariant(1));
        label_26 = new QLabel(QYDlgCameraCfg);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(320, 48, 60, 24));
        label_26->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_name = new QLineEdit(QYDlgCameraCfg);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(84, 48, 160, 24));
        lineEdit_name->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_name->setFrame(true);
        lineEdit_name->setEchoMode(QLineEdit::Normal);
        label_24 = new QLabel(QYDlgCameraCfg);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(20, 80, 42, 24));
        label_24->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_Password = new QLineEdit(QYDlgCameraCfg);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        lineEdit_Password->setGeometry(QRect(384, 112, 160, 24));
        lineEdit_Password->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_Password->setFrame(true);
        lineEdit_Password->setEchoMode(QLineEdit::Password);
        label_28 = new QLabel(QYDlgCameraCfg);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(20, 112, 42, 24));
        label_28->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_22 = new QLabel(QYDlgCameraCfg);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 48, 42, 24));
        label_22->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_27 = new QLabel(QYDlgCameraCfg);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(320, 80, 42, 24));
        label_27->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_UserName = new QLineEdit(QYDlgCameraCfg);
        lineEdit_UserName->setObjectName(QStringLiteral("lineEdit_UserName"));
        lineEdit_UserName->setGeometry(QRect(84, 112, 160, 24));
        lineEdit_UserName->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_UserName->setFrame(true);
        lineEdit_UserName->setEchoMode(QLineEdit::Normal);
        lineEdit_IP = new QLineEdit(QYDlgCameraCfg);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(84, 80, 160, 24));
        lineEdit_IP->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_IP->setFrame(true);
        lineEdit_IP->setEchoMode(QLineEdit::Normal);
        label_29 = new QLabel(QYDlgCameraCfg);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(320, 112, 42, 24));
        label_29->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        comboBox_tree = new QComboBox(QYDlgCameraCfg);
        comboBox_tree->setObjectName(QStringLiteral("comboBox_tree"));
        comboBox_tree->setGeometry(QRect(384, 48, 80, 24));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_tree->sizePolicy().hasHeightForWidth());
        comboBox_tree->setSizePolicy(sizePolicy);
        comboBox_tree->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}\n"
"QComboBox::drop-down {\n"
"	 subcontrol-origin: padding;\n"
"     subcontrol-position: right;\n"
"     border-width: 0px;\n"
" }\n"
"QComboBox::down-arrow {\n"
"     image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QComboBox::down-arrow:pressed {\n"
"     background-color: rgba(200,200,200,255);\n"
"}"));
        comboBox_tree->setEditable(false);
        comboBox_tree->setFrame(false);
        comboBox_tree->setProperty("StopAspect", QVariant(2));
        lineEdit_Port = new QLineEdit(QYDlgCameraCfg);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(384, 80, 160, 24));
        lineEdit_Port->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        lineEdit_Port->setFrame(true);
        lineEdit_Port->setEchoMode(QLineEdit::Normal);
        label_30 = new QLabel(QYDlgCameraCfg);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(20, 172, 60, 24));
        label_30->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        comboBox_imgType = new QComboBox(QYDlgCameraCfg);
        comboBox_imgType->setObjectName(QStringLiteral("comboBox_imgType"));
        comboBox_imgType->setGeometry(QRect(84, 172, 80, 24));
        sizePolicy.setHeightForWidth(comboBox_imgType->sizePolicy().hasHeightForWidth());
        comboBox_imgType->setSizePolicy(sizePolicy);
        comboBox_imgType->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}\n"
"QComboBox::drop-down {\n"
"	 subcontrol-origin: padding;\n"
"     subcontrol-position: right;\n"
"     border-width: 0px;\n"
" }\n"
"QComboBox::down-arrow {\n"
"     image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QComboBox::down-arrow:pressed {\n"
"     background-color: rgba(200,200,200,255);\n"
"}"));
        comboBox_imgType->setEditable(false);
        comboBox_imgType->setFrame(false);
        comboBox_imgType->setProperty("StopAspect", QVariant(2));
        wd_title = new QYDlgTitle(QYDlgCameraCfg);
        wd_title->setObjectName(QStringLiteral("wd_title"));
        wd_title->setGeometry(QRect(0, 0, 640, 32));
        wd_title->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(16, 18, 13,255);\n"
"border-width:0px;\n"
"font-size:14px;\n"
"}"));
        widget = new QWidget(QYDlgCameraCfg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 152, 616, 4));
        widget->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        but_OK = new QPushButton(QYDlgCameraCfg);
        but_OK->setObjectName(QStringLiteral("but_OK"));
        but_OK->setGeometry(QRect(518, 230, 102, 24));
        but_OK->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        dSpinBox_AgH = new QDoubleSpinBox(QYDlgCameraCfg);
        dSpinBox_AgH->setObjectName(QStringLiteral("dSpinBox_AgH"));
        dSpinBox_AgH->setGeometry(QRect(453, 172, 72, 24));
        dSpinBox_AgH->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}\n"
"QDoubleSpinBox::down-arrow {\n"
"    image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QDoubleSpinBox::up-arrow {\n"
"    image: url(\":/images/ap2000/004_1\");\n"
"}\n"
"QDoubleSpinBox::up-button {\n"
"      subcontrol-origin: border;\n"
"      subcontrol-position: top right;\n"
"      border-width: 0px;\n"
"\n"
"}\n"
"QDoubleSpinBox::up-button:pressed{\n"
"	background-color: rgba(200,200,200,255);\n"
"}\n"
"QDoubleSpinBox::down-button {\n"
"      subcontrol-origin: border;\n"
"      subcontrol-position: bottom right;\n"
"      border-width: 0px;\n"
"\n"
"}\n"
"QDoubleSpinBox::down-button:pressed{\n"
"	background-color: rgba(200,200,200,255);\n"
"}\n"
""));
        dSpinBox_AgH->setMinimum(0);
        dSpinBox_AgH->setMaximum(90);
        dSpinBox_AgH->setValue(90);
        dSpinBox_AgH->setProperty("StopAspect", QVariant(2));
        dSpinBox_AgH->setProperty("KeepAspect", QVariant(4));
        label_21 = new QLabel(QYDlgCameraCfg);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(389, 172, 60, 24));
        label_21->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_21->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_21->setProperty("KeepAspect", QVariant(4));
        label_31 = new QLabel(QYDlgCameraCfg);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(200, 172, 60, 24));
        label_31->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        comboBox_panoType = new QComboBox(QYDlgCameraCfg);
        comboBox_panoType->setObjectName(QStringLiteral("comboBox_panoType"));
        comboBox_panoType->setGeometry(QRect(264, 172, 80, 24));
        sizePolicy.setHeightForWidth(comboBox_panoType->sizePolicy().hasHeightForWidth());
        comboBox_panoType->setSizePolicy(sizePolicy);
        comboBox_panoType->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}\n"
"QComboBox::drop-down {\n"
"	 subcontrol-origin: padding;\n"
"     subcontrol-position: right;\n"
"     border-width: 0px;\n"
" }\n"
"QComboBox::down-arrow {\n"
"     image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QComboBox::down-arrow:pressed {\n"
"     background-color: rgba(200,200,200,255);\n"
"}"));
        comboBox_panoType->setEditable(false);
        comboBox_panoType->setFrame(false);
        comboBox_panoType->setProperty("StopAspect", QVariant(2));

        retranslateUi(QYDlgCameraCfg);

        QMetaObject::connectSlotsByName(QYDlgCameraCfg);
    } // setupUi

    void retranslateUi(QDialog *QYDlgCameraCfg)
    {
        QYDlgCameraCfg->setWindowTitle(QApplication::translate("QYDlgCameraCfg", "Dialog", 0));
        label_26->setText(QApplication::translate("QYDlgCameraCfg", "\344\270\212\347\272\247\345\214\272\345\237\237", 0));
        label_24->setText(QApplication::translate("QYDlgCameraCfg", "IP\345\234\260\345\235\200", 0));
        label_28->setText(QApplication::translate("QYDlgCameraCfg", "\347\224\250\346\210\267\345\220\215", 0));
        label_22->setText(QApplication::translate("QYDlgCameraCfg", "\345\244\207\346\263\250\345\220\215", 0));
        label_27->setText(QApplication::translate("QYDlgCameraCfg", "\347\253\257\345\217\243", 0));
        label_29->setText(QApplication::translate("QYDlgCameraCfg", "\345\257\206\347\240\201", 0));
        comboBox_tree->clear();
        comboBox_tree->insertItems(0, QStringList()
         << QApplication::translate("QYDlgCameraCfg", "Root", 0)
        );
        comboBox_tree->setCurrentText(QApplication::translate("QYDlgCameraCfg", "Root", 0));
        label_30->setText(QApplication::translate("QYDlgCameraCfg", "\350\256\276\345\244\207\347\261\273\345\236\213", 0));
        comboBox_imgType->clear();
        comboBox_imgType->insertItems(0, QStringList()
         << QApplication::translate("QYDlgCameraCfg", "\346\234\252\347\237\245", 0)
         << QApplication::translate("QYDlgCameraCfg", "\345\205\250\346\231\257\346\234\272", 0)
         << QApplication::translate("QYDlgCameraCfg", "\347\220\203\346\234\272", 0)
        );
        comboBox_imgType->setCurrentText(QApplication::translate("QYDlgCameraCfg", "\346\234\252\347\237\245", 0));
        but_OK->setText(QApplication::translate("QYDlgCameraCfg", "\347\241\256\345\256\232", 0));
        label_21->setText(QApplication::translate("QYDlgCameraCfg", "\346\260\264\345\271\263\345\200\276\350\247\222", 0));
        label_31->setText(QApplication::translate("QYDlgCameraCfg", "\345\205\250\346\231\257\347\261\273\345\236\213", 0));
        comboBox_panoType->clear();
        comboBox_panoType->insertItems(0, QStringList()
         << QApplication::translate("QYDlgCameraCfg", "\345\205\250\346\231\257", 0)
         << QApplication::translate("QYDlgCameraCfg", "\345\271\277\350\247\222", 0)
        );
        comboBox_panoType->setCurrentText(QApplication::translate("QYDlgCameraCfg", "\345\205\250\346\231\257", 0));
    } // retranslateUi

};

namespace Ui {
    class QYDlgCameraCfg: public Ui_QYDlgCameraCfg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QYDLGCAMERACFG_H
