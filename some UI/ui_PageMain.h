/********************************************************************************
** Form generated from reading UI file 'PageMain.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEMAIN_H
#define UI_PAGEMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "pageplaybacklocal.h"
#include "pageplaybacknet.h"
#include "paneltitle.h"
#include "qypanelvideo.h"

QT_BEGIN_NAMESPACE

class Ui_PageMain
{
public:
    QWidget *wdBK;
    PanelTitle *panelTitle;
    QWidget *wdLeft;
    QWidget *tabA;
    QPushButton *butAA;
    QPushButton *butAA_Add_A;
    QPushButton *butAA_Add_B;
    QPushButton *butAA_A;
    QPushButton *butAA_B;
    QWidget *wdLeft_UserPanel;
    QTreeWidget *treeWidget;
    QWidget *wdLeft_QQPanel;
    QPushButton *butAA_B_A;
    QPushButton *butAA_B_B;
    QWidget *widget;
    QTableWidget *tableWidget_qq;
    QWidget *tabB;
    QPushButton *butAB;
    QPushButton *butAB_1;
    QPushButton *butAB_2;
    QPushButton *butAB_0;
    QPushButton *butAB_6;
    QPushButton *butAB_7;
    QPushButton *butAB_5;
    QPushButton *butAB_3;
    QPushButton *butAB_4;
    QPushButton *butAB_9;
    QPushButton *butAB_8;
    QLabel *label_16;
    QPushButton *butAB_10;
    QLabel *label_17;
    QPushButton *butAB_11;
    QPushButton *butAB_12;
    QPushButton *butAB_13;
    QLabel *label_18;
    QLabel *label_19;
    QComboBox *comboBox_Speed;
    QWidget *wdLeft_YunA;
    QTableWidget *tableWidget_YunA;
    QPushButton *butOpenImage_32;
    QPushButton *butOpenImage_33;
    QPushButton *butOpenImage_34;
    QPushButton *butAB_A;
    QPushButton *butAB_B;
    QWidget *wdLeft_YunB;
    QTableWidget *tableWidget_YunB;
    QWidget *widget_6;
    QComboBox *comboBox_outSize_5;
    QPushButton *butOpenImage_37;
    QPushButton *butOpenImage_35;
    QPushButton *butOpenImage_36;
    QWidget *tabC;
    QPushButton *butAC;
    QSlider *horizontalSlider_3;
    QLabel *label_9;
    QLabel *label_10;
    QSlider *horizontalSlider_4;
    QLabel *label_14;
    QSlider *horizontalSlider_5;
    QLabel *label_15;
    QSlider *horizontalSlider_6;
    QPushButton *butOpenImage_13;
    QWidget *wdRight;
    QWidget *wdRPageA;
    QYPanelVideo *panelvideos;
    QWidget *panelvideos_QQ;
    QYPanelVideo *wdRPageA_Top;
    QYPanelVideo *wdRPageA_Bot;
    QGroupBox *groupBox_4;
    QLabel *label_20;
    QComboBox *cboBox_Row;
    QLabel *label_21;
    QDoubleSpinBox *dSpinBox_Ag;
    QLabel *label_23;
    QDoubleSpinBox *dSpinBox_AgR_L;
    QPushButton *butRQQ_Calc;
    QCheckBox *cb_Linked;
    QLabel *label_24;
    QDoubleSpinBox *dSpinBox_AgR_R;
    QLabel *label_25;
    QComboBox *cboBox_Col;
    QCheckBox *cb_shadow;
    QWidget *wdRPageB;
    PagePlayBackNet *wdPlayBack_Net;
    PagePlayBackLocal *wdPlayBack_Local;
    QWidget *wdRPageC;
    QGroupBox *groupBox_2;
    QCheckBox *cbJPEG;
    QLabel *label;
    QGroupBox *groupBox_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_PathImage;
    QPushButton *butOpenImage;
    QLabel *label_PathVideo;
    QPushButton *butOpenVideo;
    QPushButton *butSaveCfg;

    void setupUi(QWidget *PageMain)
    {
        if (PageMain->objectName().isEmpty())
            PageMain->setObjectName(QStringLiteral("PageMain"));
        PageMain->resize(1280, 720);
        PageMain->setAutoFillBackground(false);
        PageMain->setStyleSheet(QString::fromUtf8("QWidget{\n"
"color:rgba(200,207,217,255);\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"font-weight:bold;\n"
"background-color: rgba(0, 0, 0, 255);\n"
"border-width: 0px;\n"
"border-style: solid;\n"
"border-radius:0px;\n"
"border-image:url(\"\");\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        wdBK = new QWidget(PageMain);
        wdBK->setObjectName(QStringLiteral("wdBK"));
        wdBK->setGeometry(QRect(0, 0, 1280, 720));
        wdBK->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0.0, stop:0 rgba(124, 124, 124, 255), stop:1 rgba(0, 0, 0, 255));\n"
"}"));
        panelTitle = new PanelTitle(wdBK);
        panelTitle->setObjectName(QStringLiteral("panelTitle"));
        panelTitle->setGeometry(QRect(0, 0, 1280, 76));
        panelTitle->setMinimumSize(QSize(0, 0));
        panelTitle->setMaximumSize(QSize(16777215, 16777215));
        wdLeft = new QWidget(wdBK);
        wdLeft->setObjectName(QStringLiteral("wdLeft"));
        wdLeft->setGeometry(QRect(12, 76, 228, 636));
        wdLeft->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(102, 102, 102,255);\n"
"border-width:1px;\n"
"}\n"
""));
        tabA = new QWidget(wdLeft);
        tabA->setObjectName(QStringLiteral("tabA"));
        tabA->setGeometry(QRect(0, 0, 228, 572));
        tabA->setStyleSheet(QStringLiteral(""));
        butAA = new QPushButton(tabA);
        butAA->setObjectName(QStringLiteral("butAA"));
        butAA->setGeometry(QRect(0, 0, 228, 28));
        butAA->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-left-color:rgba(255,255,255,255);\n"
"border-top-color:rgba(255,255,255,255);\n"
"text-align: left;\n"
"font-size:14px;\n"
"background-color:rgba(0,0,0,0);\n"
"background-image:url(\":images/ap2000/036_0\");\n"
"background-repeat:no-repeat;\n"
"background-position:right center;\n"
"}\n"
""));
        butAA->setFlat(true);
        butAA_Add_A = new QPushButton(tabA);
        butAA_Add_A->setObjectName(QStringLiteral("butAA_Add_A"));
        butAA_Add_A->setGeometry(QRect(4, 32, 106, 24));
        butAA_Add_A->setStyleSheet(QLatin1String("QWidget{\n"
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
        butAA_Add_B = new QPushButton(tabA);
        butAA_Add_B->setObjectName(QStringLiteral("butAA_Add_B"));
        butAA_Add_B->setGeometry(QRect(118, 32, 106, 24));
        butAA_Add_B->setStyleSheet(QLatin1String("QWidget{\n"
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
        butAA_A = new QPushButton(tabA);
        butAA_A->setObjectName(QStringLiteral("butAA_A"));
        butAA_A->setGeometry(QRect(2, 64, 54, 20));
        butAA_A->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-bottom-width:0px;\n"
"background-color:rgba(56,82,72,255);\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
""));
        butAA_B = new QPushButton(tabA);
        butAA_B->setObjectName(QStringLiteral("butAA_B"));
        butAA_B->setGeometry(QRect(56, 64, 54, 20));
        butAA_B->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-bottom-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
""));
        wdLeft_UserPanel = new QWidget(tabA);
        wdLeft_UserPanel->setObjectName(QStringLiteral("wdLeft_UserPanel"));
        wdLeft_UserPanel->setGeometry(QRect(2, 84, 224, 488));
        wdLeft_UserPanel->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"background-color:rgba(1,0,0,1);\n"
"}"));
        treeWidget = new QTreeWidget(wdLeft_UserPanel);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(0, 1, 224, 488));
        treeWidget->setFocusPolicy(Qt::NoFocus);
        treeWidget->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}\n"
"QWidget:focus{outline: none;}\n"
"QTreeView::branch:has-siblings:!adjoins-item {\n"
"    border-image: url(\":/images/ap2000/vline\") 0;\n"
"}\n"
"QTreeView::branch:has-siblings:adjoins-item {\n"
"    border-image: url(\":/images/ap2000/branch-more\") 0;\n"
"}\n"
"QTreeView::branch:!has-children:!has-siblings:adjoins-item {\n"
"    border-image: url(\":/images/ap2000/branch-end\") 0;\n"
"}\n"
"QTreeView::branch:has-children:!has-siblings:closed,\n"
"QTreeView::branch:closed:has-children:has-siblings {\n"
"        border-image: none;\n"
"        image: url(\":/images/ap2000/branch-closed\");\n"
"}\n"
"QTreeView::branch:open:has-children:!has-siblings,\n"
"QTreeView::branch:open:has-children:has-siblings  {\n"
"        border-image: none;\n"
"        image: url(\":/images/ap2000/branch-open\");\n"
"}\n"
"QTreeView::item:hover {\n"
"    background-color:rgba(94,165,225,64);\n"
"}\n"
"QTreeView::item:selected {\n"
"    background-col"
                        "or:rgba(94,165,225,168);\n"
"}"));
        treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        treeWidget->setColumnCount(1);
        treeWidget->header()->setVisible(false);
        wdLeft_QQPanel = new QWidget(tabA);
        wdLeft_QQPanel->setObjectName(QStringLiteral("wdLeft_QQPanel"));
        wdLeft_QQPanel->setGeometry(QRect(2, 84, 224, 488));
        wdLeft_QQPanel->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        butAA_B_A = new QPushButton(wdLeft_QQPanel);
        butAA_B_A->setObjectName(QStringLiteral("butAA_B_A"));
        butAA_B_A->setGeometry(QRect(2, 464, 106, 20));
        butAA_B_A->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(56,82,72,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}\n"
""));
        butAA_B_B = new QPushButton(wdLeft_QQPanel);
        butAA_B_B->setObjectName(QStringLiteral("butAA_B_B"));
        butAA_B_B->setGeometry(QRect(116, 464, 106, 20));
        butAA_B_B->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(56,82,72,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}\n"
""));
        widget = new QWidget(wdLeft_QQPanel);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 1, 224, 458));
        widget->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"border-bottom-width:1px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        tableWidget_qq = new QTableWidget(widget);
        if (tableWidget_qq->columnCount() < 3)
            tableWidget_qq->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_qq->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_qq->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_qq->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget_qq->setObjectName(QStringLiteral("tableWidget_qq"));
        tableWidget_qq->setGeometry(QRect(0, 0, 224, 458));
        tableWidget_qq->setFocusPolicy(Qt::NoFocus);
        tableWidget_qq->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        tableWidget_qq->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_qq->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_qq->setGridStyle(Qt::SolidLine);
        tableWidget_qq->setWordWrap(true);
        tableWidget_qq->setRowCount(0);
        tableWidget_qq->setColumnCount(3);
        tableWidget_qq->setProperty("StopAspect", QVariant(2));
        tableWidget_qq->horizontalHeader()->setDefaultSectionSize(120);
        tableWidget_qq->horizontalHeader()->setHighlightSections(false);
        tableWidget_qq->horizontalHeader()->setMinimumSectionSize(120);
        tableWidget_qq->verticalHeader()->setVisible(false);
        tableWidget_qq->verticalHeader()->setDefaultSectionSize(24);
        tableWidget_qq->verticalHeader()->setMinimumSectionSize(24);
        butAA->raise();
        butAA_Add_A->raise();
        butAA_Add_B->raise();
        butAA_A->raise();
        butAA_B->raise();
        wdLeft_QQPanel->raise();
        wdLeft_UserPanel->raise();
        tabB = new QWidget(wdLeft);
        tabB->setObjectName(QStringLiteral("tabB"));
        tabB->setGeometry(QRect(0, 32, 228, 572));
        tabB->setStyleSheet(QStringLiteral(""));
        butAB = new QPushButton(tabB);
        butAB->setObjectName(QStringLiteral("butAB"));
        butAB->setGeometry(QRect(0, 0, 228, 28));
        butAB->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-left-color:rgba(255,255,255,255);\n"
"border-top-color:rgba(255,255,255,255);\n"
"text-align: left;\n"
"font-size:14px;\n"
"background-color:rgba(0,0,0,0);\n"
"background-image:url(\":images/ap2000/036_0\");\n"
"background-repeat:no-repeat;\n"
"background-position:right center;\n"
"}\n"
""));
        butAB->setFlat(true);
        butAB_1 = new QPushButton(tabB);
        butAB_1->setObjectName(QStringLiteral("butAB_1"));
        butAB_1->setGeometry(QRect(96, 36, 32, 24));
        butAB_1->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/038_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_1->setProperty("KeepAspect", QVariant(1));
        butAB_2 = new QPushButton(tabB);
        butAB_2->setObjectName(QStringLiteral("butAB_2"));
        butAB_2->setGeometry(QRect(162, 36, 32, 24));
        butAB_2->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/039_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_2->setProperty("KeepAspect", QVariant(1));
        butAB_0 = new QPushButton(tabB);
        butAB_0->setObjectName(QStringLiteral("butAB_0"));
        butAB_0->setGeometry(QRect(30, 36, 32, 24));
        butAB_0->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/037_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_0->setProperty("KeepAspect", QVariant(1));
        butAB_6 = new QPushButton(tabB);
        butAB_6->setObjectName(QStringLiteral("butAB_6"));
        butAB_6->setGeometry(QRect(96, 92, 32, 24));
        butAB_6->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/043_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_6->setProperty("KeepAspect", QVariant(1));
        butAB_7 = new QPushButton(tabB);
        butAB_7->setObjectName(QStringLiteral("butAB_7"));
        butAB_7->setGeometry(QRect(162, 92, 32, 24));
        butAB_7->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/044_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_7->setProperty("KeepAspect", QVariant(1));
        butAB_5 = new QPushButton(tabB);
        butAB_5->setObjectName(QStringLiteral("butAB_5"));
        butAB_5->setGeometry(QRect(30, 92, 32, 24));
        butAB_5->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/042_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_5->setProperty("KeepAspect", QVariant(1));
        butAB_3 = new QPushButton(tabB);
        butAB_3->setObjectName(QStringLiteral("butAB_3"));
        butAB_3->setGeometry(QRect(30, 64, 32, 24));
        butAB_3->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/040_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_3->setProperty("KeepAspect", QVariant(1));
        butAB_4 = new QPushButton(tabB);
        butAB_4->setObjectName(QStringLiteral("butAB_4"));
        butAB_4->setGeometry(QRect(162, 64, 32, 24));
        butAB_4->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/041_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_4->setProperty("KeepAspect", QVariant(1));
        butAB_9 = new QPushButton(tabB);
        butAB_9->setObjectName(QStringLiteral("butAB_9"));
        butAB_9->setGeometry(QRect(162, 124, 32, 24));
        butAB_9->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/046_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_9->setProperty("KeepAspect", QVariant(1));
        butAB_8 = new QPushButton(tabB);
        butAB_8->setObjectName(QStringLiteral("butAB_8"));
        butAB_8->setGeometry(QRect(30, 124, 32, 24));
        butAB_8->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/045_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_8->setProperty("KeepAspect", QVariant(1));
        label_16 = new QLabel(tabB);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(92, 124, 40, 24));
        label_16->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_16->setAlignment(Qt::AlignCenter);
        butAB_10 = new QPushButton(tabB);
        butAB_10->setObjectName(QStringLiteral("butAB_10"));
        butAB_10->setGeometry(QRect(30, 152, 32, 24));
        butAB_10->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/047_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_10->setProperty("KeepAspect", QVariant(1));
        label_17 = new QLabel(tabB);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(92, 152, 40, 24));
        label_17->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_17->setAlignment(Qt::AlignCenter);
        butAB_11 = new QPushButton(tabB);
        butAB_11->setObjectName(QStringLiteral("butAB_11"));
        butAB_11->setGeometry(QRect(162, 152, 32, 24));
        butAB_11->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/048_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_11->setProperty("KeepAspect", QVariant(1));
        butAB_12 = new QPushButton(tabB);
        butAB_12->setObjectName(QStringLiteral("butAB_12"));
        butAB_12->setGeometry(QRect(30, 180, 32, 24));
        butAB_12->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/049_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_12->setProperty("KeepAspect", QVariant(1));
        butAB_13 = new QPushButton(tabB);
        butAB_13->setObjectName(QStringLiteral("butAB_13"));
        butAB_13->setGeometry(QRect(162, 180, 32, 24));
        butAB_13->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(240,240,240,160);\n"
"border-image:url(\":images/ap2000/050_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(240,240,240,220);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(180,180,180,200);\n"
"}"));
        butAB_13->setProperty("KeepAspect", QVariant(1));
        label_18 = new QLabel(tabB);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(92, 180, 40, 24));
        label_18->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_18->setAlignment(Qt::AlignCenter);
        label_19 = new QLabel(tabB);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(30, 212, 58, 20));
        label_19->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBox_Speed = new QComboBox(tabB);
        comboBox_Speed->setObjectName(QStringLiteral("comboBox_Speed"));
        comboBox_Speed->setGeometry(QRect(94, 212, 100, 20));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_Speed->sizePolicy().hasHeightForWidth());
        comboBox_Speed->setSizePolicy(sizePolicy);
        comboBox_Speed->setStyleSheet(QLatin1String("QWidget{\n"
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
        comboBox_Speed->setEditable(false);
        comboBox_Speed->setFrame(false);
        comboBox_Speed->setProperty("StopAspect", QVariant(2));
        wdLeft_YunA = new QWidget(tabB);
        wdLeft_YunA->setObjectName(QStringLiteral("wdLeft_YunA"));
        wdLeft_YunA->setGeometry(QRect(8, 240, 212, 308));
        wdLeft_YunA->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"#wdLeft_YunA{border-width:1px;}"));
        tableWidget_YunA = new QTableWidget(wdLeft_YunA);
        if (tableWidget_YunA->columnCount() < 1)
            tableWidget_YunA->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_YunA->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        if (tableWidget_YunA->rowCount() < 15)
            tableWidget_YunA->setRowCount(15);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(8, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(9, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(10, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(11, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(12, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(13, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget_YunA->setVerticalHeaderItem(14, __qtablewidgetitem18);
        tableWidget_YunA->setObjectName(QStringLiteral("tableWidget_YunA"));
        tableWidget_YunA->setGeometry(QRect(1, 1, 210, 282));
        tableWidget_YunA->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(72,72,72,255);\n"
"}"));
        tableWidget_YunA->setRowCount(15);
        tableWidget_YunA->setColumnCount(1);
        tableWidget_YunA->setProperty("StopAspect", QVariant(2));
        tableWidget_YunA->horizontalHeader()->setDefaultSectionSize(212);
        tableWidget_YunA->horizontalHeader()->setMinimumSectionSize(212);
        tableWidget_YunA->verticalHeader()->setVisible(false);
        tableWidget_YunA->verticalHeader()->setDefaultSectionSize(32);
        tableWidget_YunA->verticalHeader()->setMinimumSectionSize(32);
        butOpenImage_32 = new QPushButton(wdLeft_YunA);
        butOpenImage_32->setObjectName(QStringLiteral("butOpenImage_32"));
        butOpenImage_32->setGeometry(QRect(1, 284, 70, 20));
        butOpenImage_32->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"border-right-width:1px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        butOpenImage_33 = new QPushButton(wdLeft_YunA);
        butOpenImage_33->setObjectName(QStringLiteral("butOpenImage_33"));
        butOpenImage_33->setGeometry(QRect(71, 284, 70, 20));
        butOpenImage_33->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"border-right-width:1px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        butOpenImage_34 = new QPushButton(wdLeft_YunA);
        butOpenImage_34->setObjectName(QStringLiteral("butOpenImage_34"));
        butOpenImage_34->setGeometry(QRect(141, 284, 70, 20));
        butOpenImage_34->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        butAB_A = new QPushButton(tabB);
        butAB_A->setObjectName(QStringLiteral("butAB_A"));
        butAB_A->setGeometry(QRect(8, 548, 54, 20));
        butAB_A->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-top-width:0px;\n"
"background-color:rgba(56,82,72,255);\n"
"}"));
        butAB_B = new QPushButton(tabB);
        butAB_B->setObjectName(QStringLiteral("butAB_B"));
        butAB_B->setGeometry(QRect(62, 548, 54, 20));
        butAB_B->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-top-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        wdLeft_YunB = new QWidget(tabB);
        wdLeft_YunB->setObjectName(QStringLiteral("wdLeft_YunB"));
        wdLeft_YunB->setGeometry(QRect(8, 240, 212, 308));
        wdLeft_YunB->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"#wdLeft_YunB{border-width:1px;}"));
        tableWidget_YunB = new QTableWidget(wdLeft_YunB);
        if (tableWidget_YunB->columnCount() < 2)
            tableWidget_YunB->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget_YunB->setHorizontalHeaderItem(0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_YunB->setHorizontalHeaderItem(1, __qtablewidgetitem20);
        if (tableWidget_YunB->rowCount() < 15)
            tableWidget_YunB->setRowCount(15);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(3, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(4, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(5, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(6, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(7, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(8, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(9, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(10, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(11, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(12, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(13, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_YunB->setVerticalHeaderItem(14, __qtablewidgetitem35);
        tableWidget_YunB->setObjectName(QStringLiteral("tableWidget_YunB"));
        tableWidget_YunB->setGeometry(QRect(1, 1, 210, 282));
        tableWidget_YunB->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(72,72,72,255);\n"
"}"));
        tableWidget_YunB->setRowCount(15);
        tableWidget_YunB->setColumnCount(2);
        tableWidget_YunB->setProperty("StopAspect", QVariant(2));
        tableWidget_YunB->horizontalHeader()->setDefaultSectionSize(108);
        tableWidget_YunB->horizontalHeader()->setMinimumSectionSize(108);
        tableWidget_YunB->verticalHeader()->setVisible(false);
        tableWidget_YunB->verticalHeader()->setDefaultSectionSize(32);
        tableWidget_YunB->verticalHeader()->setMinimumSectionSize(32);
        widget_6 = new QWidget(wdLeft_YunB);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setGeometry(QRect(1, 284, 210, 20));
        widget_6->setStyleSheet(QLatin1String("QWidget{\n"
"border-top-width:1px;\n"
"}"));
        comboBox_outSize_5 = new QComboBox(widget_6);
        comboBox_outSize_5->setObjectName(QStringLiteral("comboBox_outSize_5"));
        comboBox_outSize_5->setGeometry(QRect(0, 0, 40, 20));
        sizePolicy.setHeightForWidth(comboBox_outSize_5->sizePolicy().hasHeightForWidth());
        comboBox_outSize_5->setSizePolicy(sizePolicy);
        comboBox_outSize_5->setStyleSheet(QLatin1String("QWidget{\n"
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
        comboBox_outSize_5->setEditable(false);
        comboBox_outSize_5->setFrame(false);
        comboBox_outSize_5->setProperty("StopAspect", QVariant(2));
        butOpenImage_37 = new QPushButton(widget_6);
        butOpenImage_37->setObjectName(QStringLiteral("butOpenImage_37"));
        butOpenImage_37->setGeometry(QRect(156, 0, 54, 20));
        butOpenImage_37->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        butOpenImage_35 = new QPushButton(widget_6);
        butOpenImage_35->setObjectName(QStringLiteral("butOpenImage_35"));
        butOpenImage_35->setGeometry(QRect(48, 0, 54, 20));
        butOpenImage_35->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"border-right-width:1px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        butOpenImage_36 = new QPushButton(widget_6);
        butOpenImage_36->setObjectName(QStringLiteral("butOpenImage_36"));
        butOpenImage_36->setGeometry(QRect(102, 0, 54, 20));
        butOpenImage_36->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-top-width:1px;\n"
"border-right-width:1px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        butAB->raise();
        butAB_1->raise();
        butAB_2->raise();
        butAB_0->raise();
        butAB_6->raise();
        butAB_7->raise();
        butAB_5->raise();
        butAB_3->raise();
        butAB_4->raise();
        butAB_9->raise();
        butAB_8->raise();
        label_16->raise();
        butAB_10->raise();
        label_17->raise();
        butAB_11->raise();
        butAB_12->raise();
        butAB_13->raise();
        label_18->raise();
        label_19->raise();
        comboBox_Speed->raise();
        butAB_A->raise();
        butAB_B->raise();
        wdLeft_YunA->raise();
        wdLeft_YunB->raise();
        tabC = new QWidget(wdLeft);
        tabC->setObjectName(QStringLiteral("tabC"));
        tabC->setGeometry(QRect(0, 64, 228, 572));
        tabC->setStyleSheet(QStringLiteral(""));
        butAC = new QPushButton(tabC);
        butAC->setObjectName(QStringLiteral("butAC"));
        butAC->setGeometry(QRect(0, 0, 228, 28));
        butAC->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-left-color:rgba(255,255,255,255);\n"
"border-top-color:rgba(255,255,255,255);\n"
"text-align: left;\n"
"font-size:14px;\n"
"background-color:rgba(0,0,0,0);\n"
"background-image:url(\":images/ap2000/036_0\");\n"
"background-repeat:no-repeat;\n"
"background-position:right center;\n"
"}\n"
""));
        butAC->setFlat(true);
        horizontalSlider_3 = new QSlider(tabC);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(56, 47, 162, 26));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalSlider_3->sizePolicy().hasHeightForWidth());
        horizontalSlider_3->setSizePolicy(sizePolicy1);
        horizontalSlider_3->setMinimumSize(QSize(0, 0));
        horizontalSlider_3->setMaximumSize(QSize(16777215, 16777215));
        horizontalSlider_3->setBaseSize(QSize(868, 40));
        horizontalSlider_3->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"QSlider::groove:horizontal {                                \n"
"left:  8px;\n"
"right: 8px;\n"
"height:4px;\n"
"background-color:rgba(212,212,212,255);\n"
"}                                                     \n"
"QSlider::handle:horizontal {\n"
"width: 8px;                    \n"
"background-color:rgba(0,122,217,255);\n"
"margin:-6px;\n"
"}                                                                                                           \n"
"QSlider::sub-page:horizontal{                               \n"
"background-color:rgba(32, 123, 193, 255);\n"
"                  \n"
"}"));
        horizontalSlider_3->setPageStep(10);
        horizontalSlider_3->setValue(50);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        horizontalSlider_3->setProperty("StopAspect", QVariant(2));
        label_9 = new QLabel(tabC);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(8, 48, 42, 24));
        label_9->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        label_10 = new QLabel(tabC);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(8, 84, 42, 24));
        label_10->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        horizontalSlider_4 = new QSlider(tabC);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setGeometry(QRect(56, 83, 162, 26));
        sizePolicy1.setHeightForWidth(horizontalSlider_4->sizePolicy().hasHeightForWidth());
        horizontalSlider_4->setSizePolicy(sizePolicy1);
        horizontalSlider_4->setMinimumSize(QSize(0, 0));
        horizontalSlider_4->setMaximumSize(QSize(16777215, 16777215));
        horizontalSlider_4->setBaseSize(QSize(868, 40));
        horizontalSlider_4->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"QSlider::groove:horizontal {                                \n"
"left:  8px;\n"
"right: 8px;\n"
"height:4px;\n"
"background-color:rgba(212,212,212,255);\n"
"}                                                     \n"
"QSlider::handle:horizontal {\n"
"width: 8px;                    \n"
"background-color:rgba(0,122,217,255);\n"
"margin:-6px;\n"
"}                                                                                                           \n"
"QSlider::sub-page:horizontal{                               \n"
"background-color:rgba(32, 123, 193, 255);\n"
"                  \n"
"}"));
        horizontalSlider_4->setPageStep(10);
        horizontalSlider_4->setValue(50);
        horizontalSlider_4->setOrientation(Qt::Horizontal);
        horizontalSlider_4->setProperty("StopAspect", QVariant(2));
        label_14 = new QLabel(tabC);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(8, 120, 42, 24));
        label_14->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        horizontalSlider_5 = new QSlider(tabC);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setGeometry(QRect(56, 119, 162, 26));
        sizePolicy1.setHeightForWidth(horizontalSlider_5->sizePolicy().hasHeightForWidth());
        horizontalSlider_5->setSizePolicy(sizePolicy1);
        horizontalSlider_5->setMinimumSize(QSize(0, 0));
        horizontalSlider_5->setMaximumSize(QSize(16777215, 16777215));
        horizontalSlider_5->setBaseSize(QSize(868, 40));
        horizontalSlider_5->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"QSlider::groove:horizontal {                                \n"
"left:  8px;\n"
"right: 8px;\n"
"height:4px;\n"
"background-color:rgba(212,212,212,255);\n"
"}                                                     \n"
"QSlider::handle:horizontal {\n"
"width: 8px;                    \n"
"background-color:rgba(0,122,217,255);\n"
"margin:-6px;\n"
"}                                                                                                           \n"
"QSlider::sub-page:horizontal{                               \n"
"background-color:rgba(32, 123, 193, 255);\n"
"                  \n"
"}"));
        horizontalSlider_5->setPageStep(10);
        horizontalSlider_5->setValue(50);
        horizontalSlider_5->setOrientation(Qt::Horizontal);
        horizontalSlider_5->setProperty("StopAspect", QVariant(2));
        label_15 = new QLabel(tabC);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(8, 156, 42, 24));
        label_15->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        horizontalSlider_6 = new QSlider(tabC);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setGeometry(QRect(56, 155, 162, 26));
        sizePolicy1.setHeightForWidth(horizontalSlider_6->sizePolicy().hasHeightForWidth());
        horizontalSlider_6->setSizePolicy(sizePolicy1);
        horizontalSlider_6->setMinimumSize(QSize(0, 0));
        horizontalSlider_6->setMaximumSize(QSize(16777215, 16777215));
        horizontalSlider_6->setBaseSize(QSize(868, 40));
        horizontalSlider_6->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"QSlider::groove:horizontal {                                \n"
"left:  8px;\n"
"right: 8px;\n"
"height:4px;\n"
"background-color:rgba(212,212,212,255);\n"
"}                                                     \n"
"QSlider::handle:horizontal {\n"
"width: 8px;                    \n"
"background-color:rgba(0,122,217,255);\n"
"margin:-6px;\n"
"}                                                                                                           \n"
"QSlider::sub-page:horizontal{                               \n"
"background-color:rgba(32, 123, 193, 255);\n"
"                  \n"
"}"));
        horizontalSlider_6->setPageStep(10);
        horizontalSlider_6->setValue(50);
        horizontalSlider_6->setOrientation(Qt::Horizontal);
        horizontalSlider_6->setProperty("StopAspect", QVariant(2));
        butOpenImage_13 = new QPushButton(tabC);
        butOpenImage_13->setObjectName(QStringLiteral("butOpenImage_13"));
        butOpenImage_13->setGeometry(QRect(152, 192, 66, 24));
        butOpenImage_13->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        wdRight = new QWidget(wdBK);
        wdRight->setObjectName(QStringLiteral("wdRight"));
        wdRight->setGeometry(QRect(244, 76, 1028, 636));
        wdRight->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(102, 102, 102, 255);\n"
"border-width:1px;\n"
"border-color:rgba(0,0,0,255);\n"
"}"));
        wdRPageA = new QWidget(wdRight);
        wdRPageA->setObjectName(QStringLiteral("wdRPageA"));
        wdRPageA->setGeometry(QRect(1, 1, 1026, 634));
        wdRPageA->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        panelvideos = new QYPanelVideo(wdRPageA);
        panelvideos->setObjectName(QStringLiteral("panelvideos"));
        panelvideos->setGeometry(QRect(1, 1, 1024, 632));
        panelvideos->setStyleSheet(QStringLiteral(""));
        panelvideos_QQ = new QWidget(wdRPageA);
        panelvideos_QQ->setObjectName(QStringLiteral("panelvideos_QQ"));
        panelvideos_QQ->setGeometry(QRect(1, 1, 1024, 632));
        panelvideos_QQ->setStyleSheet(QStringLiteral(""));
        wdRPageA_Top = new QYPanelVideo(panelvideos_QQ);
        wdRPageA_Top->setObjectName(QStringLiteral("wdRPageA_Top"));
        wdRPageA_Top->setGeometry(QRect(0, 52, 1024, 384));
        wdRPageA_Top->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(220,220,220,100);\n"
"}\n"
""));
        wdRPageA_Bot = new QYPanelVideo(panelvideos_QQ);
        wdRPageA_Bot->setObjectName(QStringLiteral("wdRPageA_Bot"));
        wdRPageA_Bot->setGeometry(QRect(0, 436, 1024, 196));
        wdRPageA_Bot->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        groupBox_4 = new QGroupBox(panelvideos_QQ);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(0, 2, 1024, 46));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"margin-top: 2ex;\n"
"}\n"
"QGroupBox::title {\n"
"subcontrol-origin: margin;\n"
"subcontrol-position: left top;\n"
"left:4ex;\n"
"padding-top:-1ex;\n"
"}\n"
""));
        groupBox_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_4->setFlat(false);
        label_20 = new QLabel(groupBox_4);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(412, 14, 48, 24));
        label_20->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_20->setProperty("KeepAspect", QVariant(4));
        cboBox_Row = new QComboBox(groupBox_4);
        cboBox_Row->setObjectName(QStringLiteral("cboBox_Row"));
        cboBox_Row->setGeometry(QRect(462, 14, 32, 24));
        sizePolicy.setHeightForWidth(cboBox_Row->sizePolicy().hasHeightForWidth());
        cboBox_Row->setSizePolicy(sizePolicy);
        cboBox_Row->setStyleSheet(QLatin1String("QWidget{\n"
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
        cboBox_Row->setEditable(false);
        cboBox_Row->setFrame(false);
        cboBox_Row->setProperty("StopAspect", QVariant(2));
        cboBox_Row->setProperty("KeepAspect", QVariant(4));
        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(36, 14, 48, 24));
        label_21->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_21->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_21->setProperty("KeepAspect", QVariant(4));
        dSpinBox_Ag = new QDoubleSpinBox(groupBox_4);
        dSpinBox_Ag->setObjectName(QStringLiteral("dSpinBox_Ag"));
        dSpinBox_Ag->setGeometry(QRect(86, 14, 72, 24));
        dSpinBox_Ag->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
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
        dSpinBox_Ag->setMinimum(160);
        dSpinBox_Ag->setMaximum(240);
        dSpinBox_Ag->setValue(180);
        dSpinBox_Ag->setProperty("StopAspect", QVariant(2));
        dSpinBox_Ag->setProperty("KeepAspect", QVariant(4));
        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(188, 14, 48, 24));
        label_23->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_23->setProperty("KeepAspect", QVariant(4));
        dSpinBox_AgR_L = new QDoubleSpinBox(groupBox_4);
        dSpinBox_AgR_L->setObjectName(QStringLiteral("dSpinBox_AgR_L"));
        dSpinBox_AgR_L->setGeometry(QRect(238, 14, 60, 24));
        dSpinBox_AgR_L->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
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
        dSpinBox_AgR_L->setMinimum(10);
        dSpinBox_AgR_L->setMaximum(30);
        dSpinBox_AgR_L->setSingleStep(0.5);
        dSpinBox_AgR_L->setValue(22);
        dSpinBox_AgR_L->setProperty("StopAspect", QVariant(2));
        dSpinBox_AgR_L->setProperty("KeepAspect", QVariant(4));
        butRQQ_Calc = new QPushButton(groupBox_4);
        butRQQ_Calc->setObjectName(QStringLiteral("butRQQ_Calc"));
        butRQQ_Calc->setGeometry(QRect(906, 14, 106, 24));
        butRQQ_Calc->setStyleSheet(QLatin1String("QWidget{\n"
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
        cb_Linked = new QCheckBox(groupBox_4);
        cb_Linked->setObjectName(QStringLiteral("cb_Linked"));
        cb_Linked->setGeometry(QRect(780, 14, 80, 24));
        cb_Linked->setStyleSheet(QLatin1String("QWidget{\n"
"margin:0px;\n"
"border-width:0px;\n"
"}"));
        cb_Linked->setProperty("StopAspect", QVariant(2));
        cb_Linked->setProperty("KeepAspect", QVariant(4));
        label_24 = new QLabel(groupBox_4);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(302, 14, 16, 24));
        label_24->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_24->setAlignment(Qt::AlignCenter);
        label_24->setProperty("KeepAspect", QVariant(4));
        dSpinBox_AgR_R = new QDoubleSpinBox(groupBox_4);
        dSpinBox_AgR_R->setObjectName(QStringLiteral("dSpinBox_AgR_R"));
        dSpinBox_AgR_R->setGeometry(QRect(322, 14, 60, 24));
        dSpinBox_AgR_R->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
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
        dSpinBox_AgR_R->setMinimum(60);
        dSpinBox_AgR_R->setMaximum(120);
        dSpinBox_AgR_R->setSingleStep(0.5);
        dSpinBox_AgR_R->setValue(77.5);
        dSpinBox_AgR_R->setProperty("StopAspect", QVariant(2));
        dSpinBox_AgR_R->setProperty("KeepAspect", QVariant(4));
        label_25 = new QLabel(groupBox_4);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(498, 14, 16, 24));
        label_25->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_25->setAlignment(Qt::AlignCenter);
        label_25->setProperty("KeepAspect", QVariant(4));
        cboBox_Col = new QComboBox(groupBox_4);
        cboBox_Col->setObjectName(QStringLiteral("cboBox_Col"));
        cboBox_Col->setGeometry(QRect(518, 14, 32, 24));
        sizePolicy.setHeightForWidth(cboBox_Col->sizePolicy().hasHeightForWidth());
        cboBox_Col->setSizePolicy(sizePolicy);
        cboBox_Col->setStyleSheet(QLatin1String("QWidget{\n"
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
        cboBox_Col->setEditable(false);
        cboBox_Col->setFrame(false);
        cboBox_Col->setProperty("StopAspect", QVariant(2));
        cboBox_Col->setProperty("KeepAspect", QVariant(4));
        cb_shadow = new QCheckBox(groupBox_4);
        cb_shadow->setObjectName(QStringLiteral("cb_shadow"));
        cb_shadow->setGeometry(QRect(620, 14, 80, 24));
        cb_shadow->setStyleSheet(QLatin1String("QWidget{\n"
"margin:0px;\n"
"border-width:0px;\n"
"}"));
        cb_shadow->setProperty("StopAspect", QVariant(2));
        cb_shadow->setProperty("KeepAspect", QVariant(4));
        wdRPageB = new QWidget(wdRight);
        wdRPageB->setObjectName(QStringLiteral("wdRPageB"));
        wdRPageB->setGeometry(QRect(1, 1, 1026, 634));
        wdRPageB->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        wdPlayBack_Net = new PagePlayBackNet(wdRPageB);
        wdPlayBack_Net->setObjectName(QStringLiteral("wdPlayBack_Net"));
        wdPlayBack_Net->setGeometry(QRect(0, 0, 1026, 634));
        wdPlayBack_Local = new PagePlayBackLocal(wdRPageB);
        wdPlayBack_Local->setObjectName(QStringLiteral("wdPlayBack_Local"));
        wdPlayBack_Local->setGeometry(QRect(0, 0, 1026, 634));
        wdRPageC = new QWidget(wdRight);
        wdRPageC->setObjectName(QStringLiteral("wdRPageC"));
        wdRPageC->setGeometry(QRect(1, 1, 1026, 634));
        wdRPageC->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        groupBox_2 = new QGroupBox(wdRPageC);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(8, 2, 1010, 56));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"margin-top: 2ex;\n"
"}\n"
"QGroupBox::title {\n"
"subcontrol-origin: margin;\n"
"subcontrol-position: left top;\n"
"left:4ex;\n"
"padding-top:-1ex;\n"
"}\n"
""));
        groupBox_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        cbJPEG = new QCheckBox(groupBox_2);
        cbJPEG->setObjectName(QStringLiteral("cbJPEG"));
        cbJPEG->setGeometry(QRect(36, 16, 124, 28));
        cbJPEG->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 16, 240, 28));
        label->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        groupBox_3 = new QGroupBox(wdRPageC);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(8, 82, 1010, 112));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        groupBox_3->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"margin-top: 2ex;\n"
"}\n"
"QGroupBox::title {\n"
"subcontrol-origin: margin;\n"
"subcontrol-position: left top;\n"
"left:4ex;\n"
"padding-top:-1ex;\n"
"}\n"
""));
        groupBox_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_3->setFlat(false);
        groupBox_3->setCheckable(false);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(36, 20, 132, 28));
        label_2->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(36, 62, 132, 28));
        label_3->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        label_PathImage = new QLabel(groupBox_3);
        label_PathImage->setObjectName(QStringLiteral("label_PathImage"));
        label_PathImage->setEnabled(false);
        label_PathImage->setGeometry(QRect(180, 20, 600, 28));
        label_PathImage->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        butOpenImage = new QPushButton(groupBox_3);
        butOpenImage->setObjectName(QStringLiteral("butOpenImage"));
        butOpenImage->setGeometry(QRect(792, 20, 80, 28));
        butOpenImage->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        label_PathVideo = new QLabel(groupBox_3);
        label_PathVideo->setObjectName(QStringLiteral("label_PathVideo"));
        label_PathVideo->setEnabled(false);
        label_PathVideo->setGeometry(QRect(180, 62, 600, 28));
        label_PathVideo->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}"));
        butOpenVideo = new QPushButton(groupBox_3);
        butOpenVideo->setObjectName(QStringLiteral("butOpenVideo"));
        butOpenVideo->setGeometry(QRect(792, 62, 80, 28));
        butOpenVideo->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}"));
        butSaveCfg = new QPushButton(wdRPageC);
        butSaveCfg->setObjectName(QStringLiteral("butSaveCfg"));
        butSaveCfg->setGeometry(QRect(938, 234, 80, 28));
        butSaveCfg->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"background-color:rgba(64,64,64,255);\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        wdRPageC->raise();
        wdRPageB->raise();
        wdRPageA->raise();

        retranslateUi(PageMain);

        QMetaObject::connectSlotsByName(PageMain);
    } // setupUi

    void retranslateUi(QWidget *PageMain)
    {
        PageMain->setWindowTitle(QApplication::translate("PageMain", "PageMain", 0));
#ifndef QT_NO_TOOLTIP
        wdBK->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        butAA->setText(QApplication::translate("PageMain", "  \350\256\276\345\244\207\345\210\227\350\241\250", 0));
        butAA_Add_A->setText(QApplication::translate("PageMain", "\346\267\273\345\212\240\350\256\276\345\244\207", 0));
        butAA_Add_B->setText(QApplication::translate("PageMain", "\346\267\273\345\212\240\345\214\272\345\237\237", 0));
        butAA_A->setText(QApplication::translate("PageMain", "\347\224\250\346\210\267\345\210\227\350\241\250", 0));
        butAA_B->setText(QApplication::translate("PageMain", "\350\201\224\345\212\250\345\210\227\350\241\250", 0));
        butAA_B_A->setText(QApplication::translate("PageMain", "\344\270\200\351\224\256\345\274\200\345\220\257", 0));
        butAA_B_B->setText(QApplication::translate("PageMain", "\344\270\200\351\224\256\345\205\263\351\227\255", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_qq->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PageMain", "\350\201\224\345\212\250\345\210\206\347\273\204", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_qq->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PageMain", "\345\205\250\346\231\257\347\233\270\346\234\272", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_qq->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PageMain", "\347\220\203\346\234\272", 0));
        butAB->setText(QApplication::translate("PageMain", "  \344\272\221\345\217\260\346\216\247\345\210\266", 0));
        butAB_1->setText(QString());
        butAB_2->setText(QString());
        butAB_0->setText(QString());
        butAB_6->setText(QString());
        butAB_7->setText(QString());
        butAB_5->setText(QString());
        butAB_3->setText(QString());
        butAB_4->setText(QString());
        butAB_9->setText(QString());
        butAB_8->setText(QString());
        label_16->setText(QApplication::translate("PageMain", "\347\204\246\350\267\235", 0));
        label_16->setProperty("KeepAspect", QVariant(QApplication::translate("PageMain", "2", 0)));
        butAB_10->setText(QString());
        label_17->setText(QApplication::translate("PageMain", "\347\204\246\347\202\271", 0));
        label_17->setProperty("KeepAspect", QVariant(QApplication::translate("PageMain", "2", 0)));
        butAB_11->setText(QString());
        butAB_12->setText(QString());
        butAB_13->setText(QString());
        label_18->setText(QApplication::translate("PageMain", "\345\205\211\345\234\210", 0));
        label_18->setProperty("KeepAspect", QVariant(QApplication::translate("PageMain", "2", 0)));
        label_19->setText(QApplication::translate("PageMain", "\344\272\221\345\217\260\351\200\237\345\272\246", 0));
        label_19->setProperty("KeepAspect", QVariant(QApplication::translate("PageMain", "4", 0)));
        comboBox_Speed->clear();
        comboBox_Speed->insertItems(0, QStringList()
         << QApplication::translate("PageMain", "1", 0)
         << QApplication::translate("PageMain", "2", 0)
         << QApplication::translate("PageMain", "3", 0)
         << QApplication::translate("PageMain", "4", 0)
         << QApplication::translate("PageMain", "5", 0)
         << QApplication::translate("PageMain", "6", 0)
         << QApplication::translate("PageMain", "7", 0)
        );
        comboBox_Speed->setCurrentText(QApplication::translate("PageMain", "1", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_YunA->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("PageMain", "\351\242\204\347\275\256\347\202\271\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_YunA->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("PageMain", "1", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_YunA->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("PageMain", "2", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_YunA->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("PageMain", "3", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_YunA->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("PageMain", "4", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_YunA->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("PageMain", "5", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_YunA->verticalHeaderItem(5);
        ___qtablewidgetitem9->setText(QApplication::translate("PageMain", "6", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_YunA->verticalHeaderItem(6);
        ___qtablewidgetitem10->setText(QApplication::translate("PageMain", "7", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_YunA->verticalHeaderItem(7);
        ___qtablewidgetitem11->setText(QApplication::translate("PageMain", "8", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_YunA->verticalHeaderItem(8);
        ___qtablewidgetitem12->setText(QApplication::translate("PageMain", "9", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_YunA->verticalHeaderItem(9);
        ___qtablewidgetitem13->setText(QApplication::translate("PageMain", "10", 0));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget_YunA->verticalHeaderItem(10);
        ___qtablewidgetitem14->setText(QApplication::translate("PageMain", "11", 0));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget_YunA->verticalHeaderItem(11);
        ___qtablewidgetitem15->setText(QApplication::translate("PageMain", "12", 0));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget_YunA->verticalHeaderItem(12);
        ___qtablewidgetitem16->setText(QApplication::translate("PageMain", "13", 0));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget_YunA->verticalHeaderItem(13);
        ___qtablewidgetitem17->setText(QApplication::translate("PageMain", "14", 0));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_YunA->verticalHeaderItem(14);
        ___qtablewidgetitem18->setText(QApplication::translate("PageMain", "16", 0));
        butOpenImage_32->setText(QApplication::translate("PageMain", "\350\260\203\347\224\250", 0));
        butOpenImage_33->setText(QApplication::translate("PageMain", "\346\267\273\345\212\240", 0));
        butOpenImage_34->setText(QApplication::translate("PageMain", "\345\210\240\351\231\244", 0));
        butAB_A->setText(QApplication::translate("PageMain", "\351\242\204\347\275\256", 0));
        butAB_B->setText(QApplication::translate("PageMain", "\345\267\241\350\210\252", 0));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_YunB->horizontalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("PageMain", "\351\242\204\347\275\256", 0));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_YunB->horizontalHeaderItem(1);
        ___qtablewidgetitem20->setText(QApplication::translate("PageMain", "\346\227\266\351\227\264", 0));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_YunB->verticalHeaderItem(0);
        ___qtablewidgetitem21->setText(QApplication::translate("PageMain", "1", 0));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_YunB->verticalHeaderItem(1);
        ___qtablewidgetitem22->setText(QApplication::translate("PageMain", "2", 0));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_YunB->verticalHeaderItem(2);
        ___qtablewidgetitem23->setText(QApplication::translate("PageMain", "3", 0));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_YunB->verticalHeaderItem(3);
        ___qtablewidgetitem24->setText(QApplication::translate("PageMain", "4", 0));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_YunB->verticalHeaderItem(4);
        ___qtablewidgetitem25->setText(QApplication::translate("PageMain", "5", 0));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_YunB->verticalHeaderItem(5);
        ___qtablewidgetitem26->setText(QApplication::translate("PageMain", "6", 0));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_YunB->verticalHeaderItem(6);
        ___qtablewidgetitem27->setText(QApplication::translate("PageMain", "7", 0));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_YunB->verticalHeaderItem(7);
        ___qtablewidgetitem28->setText(QApplication::translate("PageMain", "8", 0));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_YunB->verticalHeaderItem(8);
        ___qtablewidgetitem29->setText(QApplication::translate("PageMain", "9", 0));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_YunB->verticalHeaderItem(9);
        ___qtablewidgetitem30->setText(QApplication::translate("PageMain", "10", 0));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_YunB->verticalHeaderItem(10);
        ___qtablewidgetitem31->setText(QApplication::translate("PageMain", "11", 0));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_YunB->verticalHeaderItem(11);
        ___qtablewidgetitem32->setText(QApplication::translate("PageMain", "12", 0));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_YunB->verticalHeaderItem(12);
        ___qtablewidgetitem33->setText(QApplication::translate("PageMain", "13", 0));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_YunB->verticalHeaderItem(13);
        ___qtablewidgetitem34->setText(QApplication::translate("PageMain", "14", 0));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_YunB->verticalHeaderItem(14);
        ___qtablewidgetitem35->setText(QApplication::translate("PageMain", "16", 0));
        comboBox_outSize_5->clear();
        comboBox_outSize_5->insertItems(0, QStringList()
         << QApplication::translate("PageMain", "1", 0)
         << QApplication::translate("PageMain", "2", 0)
         << QApplication::translate("PageMain", "3", 0)
         << QApplication::translate("PageMain", "4", 0)
         << QApplication::translate("PageMain", "5", 0)
         << QApplication::translate("PageMain", "6", 0)
         << QApplication::translate("PageMain", "7", 0)
         << QApplication::translate("PageMain", "8", 0)
         << QApplication::translate("PageMain", "9", 0)
        );
        comboBox_outSize_5->setCurrentText(QApplication::translate("PageMain", "1", 0));
        butOpenImage_37->setText(QApplication::translate("PageMain", "\346\226\260\345\242\236", 0));
        butOpenImage_35->setText(QApplication::translate("PageMain", "\345\274\200\345\247\213", 0));
        butOpenImage_36->setText(QApplication::translate("PageMain", "\345\201\234\346\255\242", 0));
        butAC->setText(QApplication::translate("PageMain", "  \350\247\206\351\242\221\345\217\202\346\225\260", 0));
        label_9->setText(QApplication::translate("PageMain", "\346\230\216\344\272\256\345\272\246", 0));
        label_10->setText(QApplication::translate("PageMain", "\345\257\271\346\257\224\345\272\246", 0));
        label_14->setText(QApplication::translate("PageMain", "\351\245\261\345\222\214\345\272\246", 0));
        label_15->setText(QApplication::translate("PageMain", "\350\211\262\345\272\246", 0));
        butOpenImage_13->setText(QApplication::translate("PageMain", "\351\273\230\350\256\244", 0));
        groupBox_4->setTitle(QApplication::translate("PageMain", "\350\201\224\345\212\250\350\260\203\346\240\241", 0));
        label_20->setText(QApplication::translate("PageMain", "\347\275\221\346\240\274\345\210\206\346\256\265", 0));
        cboBox_Row->clear();
        cboBox_Row->insertItems(0, QStringList()
         << QApplication::translate("PageMain", "5", 0)
         << QApplication::translate("PageMain", "6", 0)
         << QApplication::translate("PageMain", "7", 0)
         << QApplication::translate("PageMain", "8", 0)
        );
        cboBox_Row->setCurrentText(QApplication::translate("PageMain", "5", 0));
        label_21->setText(QApplication::translate("PageMain", "\345\205\250\346\231\257\345\271\277\350\247\222", 0));
        label_23->setText(QApplication::translate("PageMain", "\345\276\204\345\220\221\350\247\222\345\272\246", 0));
        butRQQ_Calc->setText(QApplication::translate("PageMain", "\346\240\241\345\207\206", 0));
        cb_Linked->setText(QApplication::translate("PageMain", "\345\274\200\345\220\257\350\201\224\345\212\250", 0));
        label_24->setText(QApplication::translate("PageMain", "\345\210\260", 0));
        label_25->setText(QApplication::translate("PageMain", "X", 0));
        cboBox_Col->clear();
        cboBox_Col->insertItems(0, QStringList()
         << QApplication::translate("PageMain", "12", 0)
         << QApplication::translate("PageMain", "14", 0)
         << QApplication::translate("PageMain", "16", 0)
         << QApplication::translate("PageMain", "18", 0)
        );
        cboBox_Col->setCurrentText(QApplication::translate("PageMain", "12", 0));
        cb_shadow->setText(QApplication::translate("PageMain", "\344\275\277\347\224\250\350\231\232\347\202\271", 0));
        groupBox_2->setTitle(QApplication::translate("PageMain", "\345\237\272\346\234\254\350\256\276\347\275\256", 0));
        cbJPEG->setText(QApplication::translate("PageMain", "\351\207\207\347\224\250JPEG\346\212\223\345\233\276", 0));
        label->setText(QApplication::translate("PageMain", "\357\274\210\346\234\252\351\200\211\344\270\255\345\210\231\351\273\230\350\256\244\344\277\235\345\255\230\346\210\220bmp\346\240\274\345\274\217\357\274\211", 0));
        groupBox_3->setTitle(QApplication::translate("PageMain", "\350\267\257\345\212\262\350\256\276\347\275\256", 0));
        label_2->setText(QApplication::translate("PageMain", "\345\233\276\347\211\207\346\212\223\345\217\226\346\226\207\344\273\266\344\277\235\345\255\230\350\267\257\345\276\204", 0));
        label_3->setText(QApplication::translate("PageMain", "\350\247\206\351\242\221\346\226\207\344\273\266\344\270\213\350\275\275\344\277\235\345\255\230\350\267\257\345\276\204", 0));
        label_PathImage->setText(QApplication::translate("PageMain", "C:/EShong/Pic", 0));
        butOpenImage->setText(QApplication::translate("PageMain", "\346\265\217\350\247\210", 0));
        label_PathVideo->setText(QApplication::translate("PageMain", "C:/EShong/Record", 0));
        butOpenVideo->setText(QApplication::translate("PageMain", "\346\265\217\350\247\210", 0));
        butSaveCfg->setText(QApplication::translate("PageMain", "\344\277\235\345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class PageMain: public Ui_PageMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEMAIN_H
