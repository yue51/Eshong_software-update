/********************************************************************************
** Form generated from reading UI file 'PagePlayBackNet.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEPLAYBACKNET_H
#define UI_PAGEPLAYBACKNET_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>
#include "qyvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_PagePlayBackNet
{
public:
    QGroupBox *groupBox;
    QLabel *label_4;
    QComboBox *comboBox_RecType;
    QLabel *label_5;
    QDateEdit *dateEdit_Start;
    QTimeEdit *timeEdit_Start;
    QDateEdit *dateEdit_Stop;
    QTimeEdit *timeEdit_Stop;
    QLabel *label_6;
    QWidget *widget;
    QPushButton *butDownload;
    QPushButton *butFind;
    QWidget *wd_timeline;
    QProgressBar *progressBar_Download;
    QWidget *widget_2;
    QSlider *Slider_BK;
    QPushButton *butBK_Play;
    QPushButton *butBK_Stop;
    QPushButton *butBK_Full;
    QPushButton *butBK_Back;
    QPushButton *butBK_Slow;
    QPushButton *butBK_Fast;
    QPushButton *butBK_Step;
    QPushButton *butBK_Capture;
    QPushButton *butBK_Audio;
    QSlider *slider_audio;
    QWidget *wd_timeline2;
    QYVideoWidget *wdB_video;
    QWidget *widget_3;
    QTableWidget *tableWidget;

    void setupUi(QWidget *PagePlayBackNet)
    {
        if (PagePlayBackNet->objectName().isEmpty())
            PagePlayBackNet->setObjectName(QStringLiteral("PagePlayBackNet"));
        PagePlayBackNet->resize(1026, 634);
        PagePlayBackNet->setStyleSheet(QString::fromUtf8("QWidget{\n"
"color:rgba(200,207,217,255);\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"font-weight:bold;\n"
"background-color:rgba(102, 102, 102, 255);\n"
"border-width:0px;\n"
"border-style: solid;\n"
"border-radius:0px;\n"
"border-image:url(\"\");\n"
"border-color:rgba(0,0,0,255);\n"
"}"));
        groupBox = new QGroupBox(PagePlayBackNet);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(8, 2, 1010, 56));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setStyleSheet(QLatin1String("QWidget{\n"
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
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(36, 16, 60, 28));
        label_4->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        comboBox_RecType = new QComboBox(groupBox);
        comboBox_RecType->setObjectName(QStringLiteral("comboBox_RecType"));
        comboBox_RecType->setGeometry(QRect(100, 16, 80, 28));
        sizePolicy.setHeightForWidth(comboBox_RecType->sizePolicy().hasHeightForWidth());
        comboBox_RecType->setSizePolicy(sizePolicy);
        comboBox_RecType->setStyleSheet(QLatin1String("QWidget{\n"
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
        comboBox_RecType->setEditable(false);
        comboBox_RecType->setFrame(false);
        comboBox_RecType->setProperty("StopAspect", QVariant(2));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(240, 16, 60, 28));
        label_5->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        dateEdit_Start = new QDateEdit(groupBox);
        dateEdit_Start->setObjectName(QStringLiteral("dateEdit_Start"));
        dateEdit_Start->setGeometry(QRect(304, 16, 108, 28));
        dateEdit_Start->setStyleSheet(QLatin1String("QDateEdit{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}\n"
"QDateEdit::drop-down {\n"
"	 subcontrol-origin: padding;\n"
"     subcontrol-position: right;\n"
"     border-width: 0px;\n"
"}\n"
"QDateEdit::down-arrow {\n"
"     image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QDateEdit::down-arrow:pressed {\n"
"     background-color: rgba(200,200,200,255);\n"
"}"));
        dateEdit_Start->setWrapping(false);
        dateEdit_Start->setFrame(true);
        dateEdit_Start->setAlignment(Qt::AlignCenter);
        dateEdit_Start->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        dateEdit_Start->setAccelerated(false);
        dateEdit_Start->setProperty("showGroupSeparator", QVariant(false));
        dateEdit_Start->setMaximumDateTime(QDateTime(QDate(2117, 7, 23), QTime(23, 59, 59)));
        dateEdit_Start->setMaximumDate(QDate(2117, 7, 23));
        dateEdit_Start->setCurrentSection(QDateTimeEdit::YearSection);
        dateEdit_Start->setCalendarPopup(true);
        timeEdit_Start = new QTimeEdit(groupBox);
        timeEdit_Start->setObjectName(QStringLiteral("timeEdit_Start"));
        timeEdit_Start->setGeometry(QRect(416, 16, 108, 28));
        timeEdit_Start->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}\n"
"QTimeEdit::down-arrow {\n"
"    image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QTimeEdit::up-arrow {\n"
"    image: url(\":/images/ap2000/004_1\");\n"
"}\n"
"QTimeEdit::up-button {\n"
"      subcontrol-origin: border;\n"
"      subcontrol-position: top right;\n"
"      border-width: 0px;\n"
"\n"
"}\n"
"QTimeEdit::up-button:pressed{\n"
"	background-color: rgba(200,200,200,255);\n"
"}\n"
"QTimeEdit::down-button {\n"
"      subcontrol-origin: border;\n"
"      subcontrol-position: bottom right;\n"
"      border-width: 0px;\n"
"\n"
"}\n"
"QTimeEdit::down-button:pressed{\n"
"	background-color: rgba(200,200,200,255);\n"
"}\n"
""));
        timeEdit_Start->setAlignment(Qt::AlignCenter);
        timeEdit_Start->setProperty("StopAspect", QVariant(2));
        dateEdit_Stop = new QDateEdit(groupBox);
        dateEdit_Stop->setObjectName(QStringLiteral("dateEdit_Stop"));
        dateEdit_Stop->setGeometry(QRect(668, 16, 108, 28));
        dateEdit_Stop->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}\n"
"QDateEdit::drop-down {\n"
"	 subcontrol-origin: padding;\n"
"     subcontrol-position: right;\n"
"     border-width: 0px;\n"
"}\n"
"QDateEdit::down-arrow {\n"
"     image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QDateEdit::down-arrow:pressed {\n"
"     background-color: rgba(200,200,200,255);\n"
"}"));
        dateEdit_Stop->setAlignment(Qt::AlignCenter);
        dateEdit_Stop->setMaximumDateTime(QDateTime(QDate(2117, 12, 31), QTime(23, 59, 59)));
        dateEdit_Stop->setCurrentSection(QDateTimeEdit::YearSection);
        dateEdit_Stop->setCalendarPopup(true);
        timeEdit_Stop = new QTimeEdit(groupBox);
        timeEdit_Stop->setObjectName(QStringLiteral("timeEdit_Stop"));
        timeEdit_Stop->setGeometry(QRect(780, 16, 108, 28));
        timeEdit_Stop->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"margin: 0px;\n"
"}\n"
"QTimeEdit::down-arrow {\n"
"    image: url(\":/images/ap2000/004_0\");\n"
"}\n"
"QTimeEdit::up-arrow {\n"
"    image: url(\":/images/ap2000/004_1\");\n"
"}\n"
"QTimeEdit::up-button {\n"
"      subcontrol-origin: border;\n"
"      subcontrol-position: top right;\n"
"      border-width: 0px;\n"
"\n"
"}\n"
"QTimeEdit::up-button:pressed{\n"
"	background-color: rgba(200,200,200,255);\n"
"}\n"
"QTimeEdit::down-button {\n"
"      subcontrol-origin: border;\n"
"      subcontrol-position: bottom right;\n"
"      border-width: 0px;\n"
"\n"
"}\n"
"QTimeEdit::down-button:pressed{\n"
"	background-color: rgba(200,200,200,255);\n"
"}\n"
""));
        timeEdit_Stop->setAlignment(Qt::AlignCenter);
        timeEdit_Stop->setProperty("StopAspect", QVariant(2));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(604, 16, 60, 28));
        label_6->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"margin: 0px;\n"
"}"));
        widget = new QWidget(PagePlayBackNet);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(8, 546, 350, 84));
        widget->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        butDownload = new QPushButton(widget);
        butDownload->setObjectName(QStringLiteral("butDownload"));
        butDownload->setGeometry(QRect(276, 2, 66, 24));
        butDownload->setStyleSheet(QLatin1String("QWidget{\n"
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
        butFind = new QPushButton(widget);
        butFind->setObjectName(QStringLiteral("butFind"));
        butFind->setGeometry(QRect(202, 2, 66, 24));
        butFind->setStyleSheet(QLatin1String("QWidget{\n"
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
        wd_timeline = new QWidget(widget);
        wd_timeline->setObjectName(QStringLiteral("wd_timeline"));
        wd_timeline->setGeometry(QRect(8, 56, 334, 20));
        wd_timeline->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(230,230,230,255);\n"
"}"));
        progressBar_Download = new QProgressBar(wd_timeline);
        progressBar_Download->setObjectName(QStringLiteral("progressBar_Download"));
        progressBar_Download->setGeometry(QRect(0, 0, 334, 20));
        progressBar_Download->setStyleSheet(QLatin1String("QWidget{\n"
"color:rgba(16,16,16,255);\n"
"}"));
        progressBar_Download->setValue(0);
        progressBar_Download->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        progressBar_Download->setTextVisible(false);
        progressBar_Download->setProperty("StopAspect", QVariant(2));
        widget_2 = new QWidget(PagePlayBackNet);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(366, 546, 652, 84));
        widget_2->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:1px;\n"
"border-color:rgba(160,160,160,255);\n"
"}"));
        Slider_BK = new QSlider(widget_2);
        Slider_BK->setObjectName(QStringLiteral("Slider_BK"));
        Slider_BK->setGeometry(QRect(8, 1, 636, 26));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Slider_BK->sizePolicy().hasHeightForWidth());
        Slider_BK->setSizePolicy(sizePolicy1);
        Slider_BK->setMinimumSize(QSize(0, 0));
        Slider_BK->setMaximumSize(QSize(16777215, 16777215));
        Slider_BK->setBaseSize(QSize(868, 40));
        Slider_BK->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"QSlider::groove:horizontal {                                \n"
"left:  10px;\n"
"right: 10px;\n"
"height:4px;\n"
"background-color:rgba(212,212,212,255);\n"
"}                                                     \n"
"QSlider::handle:horizontal {\n"
"width: 10px;                    \n"
"background-color:rgba(0,122,217,255);\n"
"margin:-10px;\n"
"}                                                                                                           \n"
"QSlider::sub-page:horizontal{                               \n"
"background-color:rgba(32, 123, 193, 255);\n"
"                  \n"
"}"));
        Slider_BK->setMaximum(100);
        Slider_BK->setPageStep(10);
        Slider_BK->setValue(0);
        Slider_BK->setOrientation(Qt::Horizontal);
        Slider_BK->setProperty("StopAspect", QVariant(2));
        butBK_Play = new QPushButton(widget_2);
        butBK_Play->setObjectName(QStringLiteral("butBK_Play"));
        butBK_Play->setGeometry(QRect(8, 28, 40, 24));
        butBK_Play->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/027_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}\n"
""));
        butBK_Play->setProperty("KeepAspect", QVariant(1));
        butBK_Stop = new QPushButton(widget_2);
        butBK_Stop->setObjectName(QStringLiteral("butBK_Stop"));
        butBK_Stop->setGeometry(QRect(56, 28, 40, 24));
        butBK_Stop->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/028_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Stop->setProperty("KeepAspect", QVariant(1));
        butBK_Full = new QPushButton(widget_2);
        butBK_Full->setObjectName(QStringLiteral("butBK_Full"));
        butBK_Full->setGeometry(QRect(104, 28, 40, 24));
        butBK_Full->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/029_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Full->setProperty("KeepAspect", QVariant(1));
        butBK_Back = new QPushButton(widget_2);
        butBK_Back->setObjectName(QStringLiteral("butBK_Back"));
        butBK_Back->setGeometry(QRect(152, 28, 40, 24));
        butBK_Back->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/030_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Back->setProperty("KeepAspect", QVariant(1));
        butBK_Slow = new QPushButton(widget_2);
        butBK_Slow->setObjectName(QStringLiteral("butBK_Slow"));
        butBK_Slow->setGeometry(QRect(200, 28, 40, 24));
        butBK_Slow->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/031_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Slow->setProperty("KeepAspect", QVariant(1));
        butBK_Fast = new QPushButton(widget_2);
        butBK_Fast->setObjectName(QStringLiteral("butBK_Fast"));
        butBK_Fast->setGeometry(QRect(248, 28, 40, 24));
        butBK_Fast->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/032_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Fast->setProperty("KeepAspect", QVariant(1));
        butBK_Step = new QPushButton(widget_2);
        butBK_Step->setObjectName(QStringLiteral("butBK_Step"));
        butBK_Step->setGeometry(QRect(296, 28, 40, 24));
        butBK_Step->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/033_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Step->setProperty("KeepAspect", QVariant(1));
        butBK_Capture = new QPushButton(widget_2);
        butBK_Capture->setObjectName(QStringLiteral("butBK_Capture"));
        butBK_Capture->setGeometry(QRect(344, 28, 40, 24));
        butBK_Capture->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/034_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Capture->setProperty("KeepAspect", QVariant(1));
        butBK_Audio = new QPushButton(widget_2);
        butBK_Audio->setObjectName(QStringLiteral("butBK_Audio"));
        butBK_Audio->setGeometry(QRect(392, 28, 40, 24));
        butBK_Audio->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(64,64,64,255);\n"
"border-image:url(\":images/ap2000/035_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(84,84,84,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(48,48,48,255);\n"
"}"));
        butBK_Audio->setProperty("KeepAspect", QVariant(1));
        slider_audio = new QSlider(widget_2);
        slider_audio->setObjectName(QStringLiteral("slider_audio"));
        slider_audio->setGeometry(QRect(440, 29, 204, 26));
        sizePolicy1.setHeightForWidth(slider_audio->sizePolicy().hasHeightForWidth());
        slider_audio->setSizePolicy(sizePolicy1);
        slider_audio->setMinimumSize(QSize(0, 0));
        slider_audio->setMaximumSize(QSize(16777215, 16777215));
        slider_audio->setBaseSize(QSize(868, 40));
        slider_audio->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}\n"
"QSlider::groove:horizontal {                                \n"
"left:  10px;\n"
"right: 10px;\n"
"height:4px;\n"
"background-color:rgba(212,212,212,255);\n"
"}                                                     \n"
"QSlider::handle:horizontal {\n"
"width: 10px;                    \n"
"background-color:rgba(0,122,217,255);\n"
"margin:-8px;\n"
"}                                                                                                           \n"
"QSlider::sub-page:horizontal{                               \n"
"background-color:rgba(32, 123, 193, 255);\n"
"                  \n"
"}"));
        slider_audio->setMaximum(65535);
        slider_audio->setSingleStep(128);
        slider_audio->setPageStep(256);
        slider_audio->setValue(32767);
        slider_audio->setOrientation(Qt::Horizontal);
        slider_audio->setProperty("StopAspect", QVariant(2));
        wd_timeline2 = new QWidget(widget_2);
        wd_timeline2->setObjectName(QStringLiteral("wd_timeline2"));
        wd_timeline2->setGeometry(QRect(8, 56, 636, 20));
        wd_timeline2->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"background-color:rgba(230,230,230,255);\n"
"}"));
        wdB_video = new QYVideoWidget(PagePlayBackNet);
        wdB_video->setObjectName(QStringLiteral("wdB_video"));
        wdB_video->setGeometry(QRect(366, 66, 652, 476));
        wdB_video->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(26,26,26,255);\n"
"}"));
        widget_3 = new QWidget(PagePlayBackNet);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(8, 66, 350, 476));
        widget_3->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(72,72,72,255);\n"
"border-width:0px;\n"
"}"));
        tableWidget = new QTableWidget(widget_3);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 350, 476));
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setStyleSheet(QStringLiteral(""));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(4);
        tableWidget->setProperty("StopAspect", QVariant(2));
        tableWidget->horizontalHeader()->setDefaultSectionSize(160);
        tableWidget->horizontalHeader()->setMinimumSectionSize(160);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(32);
        tableWidget->verticalHeader()->setMinimumSectionSize(32);

        retranslateUi(PagePlayBackNet);

        QMetaObject::connectSlotsByName(PagePlayBackNet);
    } // setupUi

    void retranslateUi(QWidget *PagePlayBackNet)
    {
        groupBox->setTitle(QApplication::translate("PagePlayBackNet", "\346\237\245\350\257\242\346\235\241\344\273\266", 0));
        label_4->setText(QApplication::translate("PagePlayBackNet", "\345\275\225\345\203\217\347\261\273\345\236\213", 0));
        comboBox_RecType->clear();
        comboBox_RecType->insertItems(0, QStringList()
         << QApplication::translate("PagePlayBackNet", "\345\205\250\351\203\250\345\275\225\345\203\217", 0)
         << QApplication::translate("PagePlayBackNet", "\345\256\232\346\227\266\345\275\225\345\203\217", 0)
         << QApplication::translate("PagePlayBackNet", "\346\211\213\345\212\250\345\275\225\345\203\217", 0)
        );
        comboBox_RecType->setCurrentText(QApplication::translate("PagePlayBackNet", "\345\205\250\351\203\250\345\275\225\345\203\217", 0));
        label_5->setText(QApplication::translate("PagePlayBackNet", "\345\274\200\345\247\213\346\227\266\351\227\264", 0));
        dateEdit_Start->setDisplayFormat(QApplication::translate("PagePlayBackNet", "yyyy/MM/dd", 0));
        dateEdit_Start->setProperty("StopAspect", QVariant(QApplication::translate("PagePlayBackNet", "2", 0)));
        timeEdit_Start->setDisplayFormat(QApplication::translate("PagePlayBackNet", "HH:mm:ss", 0));
        dateEdit_Stop->setDisplayFormat(QApplication::translate("PagePlayBackNet", "yyyy/MM/dd", 0));
        dateEdit_Stop->setProperty("StopAspect", QVariant(QApplication::translate("PagePlayBackNet", "2", 0)));
        timeEdit_Stop->setDisplayFormat(QApplication::translate("PagePlayBackNet", "HH:mm:ss", 0));
        label_6->setText(QApplication::translate("PagePlayBackNet", "\347\273\223\346\235\237\346\227\266\351\227\264", 0));
        butDownload->setText(QApplication::translate("PagePlayBackNet", "\344\270\213\350\275\275", 0));
        butFind->setText(QApplication::translate("PagePlayBackNet", "\346\237\245\346\211\276", 0));
        butBK_Play->setText(QString());
        butBK_Stop->setText(QString());
        butBK_Full->setText(QString());
        butBK_Back->setText(QString());
        butBK_Slow->setText(QString());
        butBK_Fast->setText(QString());
        butBK_Step->setText(QString());
        butBK_Capture->setText(QString());
        butBK_Audio->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PagePlayBackNet", "\346\226\207\344\273\266\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PagePlayBackNet", "\345\244\247\345\260\217", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PagePlayBackNet", "\345\274\200\345\247\213\346\227\266\351\227\264", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PagePlayBackNet", "\345\201\234\346\255\242\346\227\266\351\227\264", 0));
        Q_UNUSED(PagePlayBackNet);
    } // retranslateUi

};

namespace Ui {
    class PagePlayBackNet: public Ui_PagePlayBackNet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEPLAYBACKNET_H
