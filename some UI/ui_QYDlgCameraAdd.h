/********************************************************************************
** Form generated from reading UI file 'QYDlgCameraAdd.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QYDLGCAMERAADD_H
#define UI_QYDLGCAMERAADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "qydlgtitle.h"

QT_BEGIN_NAMESPACE

class Ui_QYDlgCameraAdd
{
public:
    QGroupBox *groupBox_4;
    QLineEdit *lineEdit_name;
    QLabel *label_22;
    QLabel *label_24;
    QLineEdit *lineEdit_IP;
    QLabel *label_parent;
    QComboBox *comboBox_node;
    QLabel *label_27;
    QLineEdit *lineEdit_Port;
    QLabel *label_28;
    QLineEdit *lineEdit_Password;
    QLineEdit *lineEdit_UserName;
    QLabel *label_29;
    QPushButton *butAdd;
    QWidget *widget;
    QTableWidget *tableWidget;
    QPushButton *butAA_Add_A_2;
    QYDlgTitle *wd_title;

    void setupUi(QDialog *QYDlgCameraAdd)
    {
        if (QYDlgCameraAdd->objectName().isEmpty())
            QYDlgCameraAdd->setObjectName(QStringLiteral("QYDlgCameraAdd"));
        QYDlgCameraAdd->resize(640, 480);
        QYDlgCameraAdd->setFocusPolicy(Qt::NoFocus);
        QYDlgCameraAdd->setStyleSheet(QString::fromUtf8("QWidget{\n"
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
        groupBox_4 = new QGroupBox(QYDlgCameraAdd);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 36, 624, 436));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}\n"
"QGroupBox::title {\n"
"subcontrol-origin: margin;\n"
"subcontrol-position: left top;\n"
"left:4ex;\n"
"padding-top:-1ex;\n"
"}\n"
"#groupBox_4{\n"
"margin-top: 2ex;\n"
"}"));
        groupBox_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_4->setFlat(false);
        groupBox_4->setCheckable(false);
        lineEdit_name = new QLineEdit(groupBox_4);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(68, 20, 160, 24));
        lineEdit_name->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_name->setFrame(true);
        lineEdit_name->setEchoMode(QLineEdit::Normal);
        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 20, 42, 24));
        label_22->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(20, 52, 42, 24));
        label_24->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_IP = new QLineEdit(groupBox_4);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(68, 52, 160, 24));
        lineEdit_IP->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_IP->setFrame(true);
        lineEdit_IP->setEchoMode(QLineEdit::Normal);
        label_parent = new QLabel(groupBox_4);
        label_parent->setObjectName(QStringLiteral("label_parent"));
        label_parent->setGeometry(QRect(260, 20, 60, 24));
        label_parent->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        comboBox_node = new QComboBox(groupBox_4);
        comboBox_node->setObjectName(QStringLiteral("comboBox_node"));
        comboBox_node->setGeometry(QRect(324, 20, 80, 24));
        sizePolicy.setHeightForWidth(comboBox_node->sizePolicy().hasHeightForWidth());
        comboBox_node->setSizePolicy(sizePolicy);
        comboBox_node->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
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
        comboBox_node->setEditable(false);
        comboBox_node->setFrame(false);
        comboBox_node->setProperty("StopAspect", QVariant(2));
        label_27 = new QLabel(groupBox_4);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(260, 52, 42, 24));
        label_27->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_Port = new QLineEdit(groupBox_4);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(324, 52, 160, 24));
        lineEdit_Port->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_Port->setFrame(true);
        lineEdit_Port->setEchoMode(QLineEdit::Normal);
        label_28 = new QLabel(groupBox_4);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(20, 84, 42, 24));
        label_28->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_Password = new QLineEdit(groupBox_4);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        lineEdit_Password->setGeometry(QRect(324, 84, 160, 24));
        lineEdit_Password->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_Password->setFrame(true);
        lineEdit_Password->setEchoMode(QLineEdit::Password);
        lineEdit_UserName = new QLineEdit(groupBox_4);
        lineEdit_UserName->setObjectName(QStringLiteral("lineEdit_UserName"));
        lineEdit_UserName->setGeometry(QRect(68, 84, 160, 24));
        lineEdit_UserName->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        lineEdit_UserName->setFrame(true);
        lineEdit_UserName->setEchoMode(QLineEdit::Normal);
        label_29 = new QLabel(groupBox_4);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(260, 84, 42, 24));
        label_29->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        butAdd = new QPushButton(groupBox_4);
        butAdd->setObjectName(QStringLiteral("butAdd"));
        butAdd->setGeometry(QRect(510, 20, 102, 24));
        butAdd->setStyleSheet(QLatin1String("QWidget{\n"
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
        widget = new QWidget(groupBox_4);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(2, 116, 616, 4));
        widget->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        tableWidget = new QTableWidget(groupBox_4);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 152, 624, 284));
        tableWidget->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(72,72,72,255);\n"
"}"));
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(7);
        tableWidget->setProperty("StopAspect", QVariant(2));
        tableWidget->horizontalHeader()->setDefaultSectionSize(90);
        tableWidget->horizontalHeader()->setMinimumSectionSize(90);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(32);
        tableWidget->verticalHeader()->setMinimumSectionSize(32);
        butAA_Add_A_2 = new QPushButton(groupBox_4);
        butAA_Add_A_2->setObjectName(QStringLiteral("butAA_Add_A_2"));
        butAA_Add_A_2->setGeometry(QRect(510, 124, 102, 24));
        butAA_Add_A_2->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        wd_title = new QYDlgTitle(QYDlgCameraAdd);
        wd_title->setObjectName(QStringLiteral("wd_title"));
        wd_title->setGeometry(QRect(0, 0, 640, 32));
        wd_title->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(16, 18, 13,255);\n"
"border-width:0px;\n"
"font-size:14px;\n"
"}"));

        retranslateUi(QYDlgCameraAdd);

        QMetaObject::connectSlotsByName(QYDlgCameraAdd);
    } // setupUi

    void retranslateUi(QDialog *QYDlgCameraAdd)
    {
        QYDlgCameraAdd->setProperty("StopAspect", QVariant(QApplication::translate("QYDlgCameraAdd", "1", 0)));
        groupBox_4->setTitle(QApplication::translate("QYDlgCameraAdd", "\350\256\276\345\244\207\347\256\241\347\220\206", 0));
        label_22->setText(QApplication::translate("QYDlgCameraAdd", "\345\244\207\346\263\250\345\220\215", 0));
        label_24->setText(QApplication::translate("QYDlgCameraAdd", "IP\345\234\260\345\235\200", 0));
        label_parent->setText(QApplication::translate("QYDlgCameraAdd", "\344\270\212\347\272\247\345\214\272\345\237\237", 0));
        comboBox_node->clear();
        comboBox_node->insertItems(0, QStringList()
         << QApplication::translate("QYDlgCameraAdd", "Root", 0)
        );
        comboBox_node->setCurrentText(QApplication::translate("QYDlgCameraAdd", "Root", 0));
        label_27->setText(QApplication::translate("QYDlgCameraAdd", "\347\253\257\345\217\243", 0));
        label_28->setText(QApplication::translate("QYDlgCameraAdd", "\347\224\250\346\210\267\345\220\215", 0));
        label_29->setText(QApplication::translate("QYDlgCameraAdd", "\345\257\206\347\240\201", 0));
        butAdd->setText(QApplication::translate("QYDlgCameraAdd", "\346\267\273\345\212\240\350\256\276\345\244\207", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QYDlgCameraAdd", "\346\230\257\345\220\246\345\267\262\346\267\273\345\212\240", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QYDlgCameraAdd", "IP\345\234\260\345\235\200", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QYDlgCameraAdd", "\347\253\257\345\217\243", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QYDlgCameraAdd", "\345\201\234\346\255\242\346\227\266\351\227\264", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QYDlgCameraAdd", "\350\256\276\345\244\207\347\263\273\345\210\227\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QYDlgCameraAdd", "\346\216\251\347\240\201", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("QYDlgCameraAdd", "Mac\345\234\260\345\235\200", 0));
        butAA_Add_A_2->setText(QApplication::translate("QYDlgCameraAdd", "\346\220\234\347\264\242\350\256\276\345\244\207", 0));
    } // retranslateUi

};

namespace Ui {
    class QYDlgCameraAdd: public Ui_QYDlgCameraAdd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QYDLGCAMERAADD_H
