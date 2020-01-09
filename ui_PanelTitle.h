/********************************************************************************
** Form generated from reading UI file 'PanelTitle.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANELTITLE_H
#define UI_PANELTITLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelTitle
{
public:
    QPushButton *butClose;
    QPushButton *butMin;
    QLabel *label_16;
    QPushButton *butAbout;
    QWidget *wdTop;
    QPushButton *butA;
    QPushButton *butB;
    QPushButton *butC;
    QPushButton *butMin_11;
    QLabel *label_time;
    QWidget *wdPanel_A;
    QPushButton *butMin_8;
    QWidget *widget_3;
    QPushButton *butShow11;
    QPushButton *butShow22;
    QPushButton *butShow33;
    QPushButton *butShow44;
    QPushButton *butShow55;
    QPushButton *butFullScreen;
    QPushButton *butCloseCamera;
    QWidget *wdPanel_A_QQ;
    QPushButton *butMin_9;
    QPushButton *butFullScreen_QQ;
    QPushButton *butCloseCamera_QQ;
    QWidget *wdPanel_BLayout;
    QWidget *wdPanel_B;
    QPushButton *butB_B;
    QPushButton *butB_A;

    void setupUi(QWidget *PanelTitle)
    {
        if (PanelTitle->objectName().isEmpty())
            PanelTitle->setObjectName(QStringLiteral("PanelTitle"));
        PanelTitle->resize(1280, 76);
        PanelTitle->setStyleSheet(QLatin1String("QWidget{\n"
"color:rgba(200,207,217,255);\n"
"font-size:12px;\n"
"font-weight:bold;\n"
"background-color: rgba(16, 18, 13,255);\n"
"border-width: 0px;\n"
"border-style: solid;\n"
"border-radius:0px;\n"
"border-image:url(\"\");\n"
"}\n"
""));
        butClose = new QPushButton(PanelTitle);
        butClose->setObjectName(QStringLiteral("butClose"));
        butClose->setGeometry(QRect(1248, 3, 24, 18));
        butClose->setMinimumSize(QSize(0, 0));
        butClose->setMaximumSize(QSize(16777215, 16777215));
        butClose->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/002_0\");\n"
"}\n"
"QPushButton:hover{\n"
"border-image:url(\":/images/ap2000/002_1\");\n"
"}\n"
"QPushButton:pressed{\n"
"border-image:url(\":/images/ap2000/002_2\");\n"
"}"));
        butClose->setAutoDefault(false);
        butClose->setFlat(false);
        butClose->setProperty("KeepAspect", QVariant(2));
        butMin = new QPushButton(PanelTitle);
        butMin->setObjectName(QStringLiteral("butMin"));
        butMin->setGeometry(QRect(1200, 3, 24, 18));
        butMin->setMinimumSize(QSize(0, 0));
        butMin->setMaximumSize(QSize(16777215, 16777215));
        butMin->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/015_0\");\n"
"}\n"
"QPushButton:hover{\n"
"border-image:url(\":/images/ap2000/015_1\");\n"
"}\n"
"QPushButton:pressed{\n"
"border-image:url(\":/images/ap2000/015_2\");\n"
"}"));
        butMin->setAutoDefault(false);
        butMin->setFlat(false);
        butMin->setProperty("KeepAspect", QVariant(2));
        label_16 = new QLabel(PanelTitle);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(12, 0, 200, 24));
        label_16->setStyleSheet(QLatin1String("QWidget{\n"
"color:rgba(200,207,217,255);\n"
"background-color:rgba(0,0,0,0);\n"
"font-size:16px;\n"
"font-weight:bold;\n"
"border:none;\n"
"}\n"
""));
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        butAbout = new QPushButton(PanelTitle);
        butAbout->setObjectName(QStringLiteral("butAbout"));
        butAbout->setGeometry(QRect(1152, 3, 24, 18));
        butAbout->setMinimumSize(QSize(0, 0));
        butAbout->setMaximumSize(QSize(16777215, 16777215));
        butAbout->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/017_0\");\n"
"}\n"
"QPushButton:hover{\n"
"border-image:url(\":/images/ap2000/017_1\");\n"
"}\n"
"QPushButton:pressed{\n"
"border-image:url(\":/images/ap2000/017_2\");\n"
"}"));
        butAbout->setAutoDefault(false);
        butAbout->setFlat(false);
        butAbout->setProperty("KeepAspect", QVariant(2));
        wdTop = new QWidget(PanelTitle);
        wdTop->setObjectName(QStringLiteral("wdTop"));
        wdTop->setGeometry(QRect(12, 24, 196, 26));
        wdTop->setStyleSheet(QStringLiteral(""));
        butA = new QPushButton(wdTop);
        butA->setObjectName(QStringLiteral("butA"));
        butA->setGeometry(QRect(0, 2, 60, 20));
        butA->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(56,82,72,255);\n"
"border-width:0px;\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(122,122,122,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
"\n"
""));
        butB = new QPushButton(wdTop);
        butB->setObjectName(QStringLiteral("butB"));
        butB->setGeometry(QRect(68, 2, 60, 20));
        butB->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(102,102,102,255);\n"
"border-width:0px;\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(122,122,122,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
""));
        butC = new QPushButton(wdTop);
        butC->setObjectName(QStringLiteral("butC"));
        butC->setGeometry(QRect(136, 2, 60, 20));
        butC->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(102,102,102,255);\n"
"border-width:0px;\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(122,122,122,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
""));
        butMin_11 = new QPushButton(PanelTitle);
        butMin_11->setObjectName(QStringLiteral("butMin_11"));
        butMin_11->setGeometry(QRect(1248, 48, 24, 24));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(butMin_11->sizePolicy().hasHeightForWidth());
        butMin_11->setSizePolicy(sizePolicy);
        butMin_11->setMinimumSize(QSize(0, 0));
        butMin_11->setMaximumSize(QSize(16777215, 16777215));
        butMin_11->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/026_0\");\n"
"}\n"
""));
        butMin_11->setAutoDefault(false);
        butMin_11->setFlat(false);
        butMin_11->setProperty("KeepAspect", QVariant(2));
        label_time = new QLabel(PanelTitle);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setGeometry(QRect(1110, 20, 160, 24));
        label_time->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"}\n"
""));
        label_time->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wdPanel_A = new QWidget(PanelTitle);
        wdPanel_A->setObjectName(QStringLiteral("wdPanel_A"));
        wdPanel_A->setGeometry(QRect(208, 48, 324, 28));
        wdPanel_A->setStyleSheet(QLatin1String("QWidget{\n"
"border-top-width:2px;\n"
"border-top-color:rgba(255,255,255,255);\n"
"}\n"
""));
        butMin_8 = new QPushButton(wdPanel_A);
        butMin_8->setObjectName(QStringLiteral("butMin_8"));
        butMin_8->setGeometry(QRect(236, 2, 24, 24));
        butMin_8->setMinimumSize(QSize(0, 0));
        butMin_8->setMaximumSize(QSize(16777215, 16777215));
        butMin_8->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/023_0\");\n"
"}\n"
""));
        butMin_8->setAutoDefault(false);
        butMin_8->setFlat(false);
        butMin_8->setProperty("KeepAspect", QVariant(2));
        widget_3 = new QWidget(wdPanel_A);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(36, 2, 184, 26));
        widget_3->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:2px;\n"
"border-top-width:0px;\n"
"}\n"
""));
        butShow11 = new QPushButton(widget_3);
        butShow11->setObjectName(QStringLiteral("butShow11"));
        butShow11->setGeometry(QRect(16, 1, 24, 24));
        butShow11->setMinimumSize(QSize(0, 0));
        butShow11->setMaximumSize(QSize(16777215, 16777215));
        butShow11->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(128,128,128,255);\n"
"border-image:url(\":/images/ap2000/018_0\");\n"
"}\n"
""));
        butShow11->setAutoDefault(false);
        butShow11->setFlat(false);
        butShow11->setProperty("KeepAspect", QVariant(2));
        butShow22 = new QPushButton(widget_3);
        butShow22->setObjectName(QStringLiteral("butShow22"));
        butShow22->setGeometry(QRect(48, 1, 24, 24));
        butShow22->setMinimumSize(QSize(0, 0));
        butShow22->setMaximumSize(QSize(16777215, 16777215));
        butShow22->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(128,128,128,255);\n"
"border-image:url(\":/images/ap2000/019_0\");\n"
"}\n"
""));
        butShow22->setAutoDefault(false);
        butShow22->setFlat(false);
        butShow22->setProperty("KeepAspect", QVariant(2));
        butShow33 = new QPushButton(widget_3);
        butShow33->setObjectName(QStringLiteral("butShow33"));
        butShow33->setGeometry(QRect(80, 1, 24, 24));
        butShow33->setMinimumSize(QSize(0, 0));
        butShow33->setMaximumSize(QSize(16777215, 16777215));
        butShow33->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(128,128,128,255);\n"
"border-image:url(\":/images/ap2000/020_0\");\n"
"}\n"
""));
        butShow33->setAutoDefault(false);
        butShow33->setFlat(false);
        butShow33->setProperty("KeepAspect", QVariant(2));
        butShow44 = new QPushButton(widget_3);
        butShow44->setObjectName(QStringLiteral("butShow44"));
        butShow44->setGeometry(QRect(112, 1, 24, 24));
        butShow44->setMinimumSize(QSize(0, 0));
        butShow44->setMaximumSize(QSize(16777215, 16777215));
        butShow44->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(128,128,128,255);\n"
"border-image:url(\":/images/ap2000/021_0\");\n"
"}\n"
""));
        butShow44->setAutoDefault(false);
        butShow44->setFlat(false);
        butShow44->setProperty("KeepAspect", QVariant(2));
        butShow55 = new QPushButton(widget_3);
        butShow55->setObjectName(QStringLiteral("butShow55"));
        butShow55->setGeometry(QRect(144, 1, 24, 24));
        butShow55->setMinimumSize(QSize(0, 0));
        butShow55->setMaximumSize(QSize(16777215, 16777215));
        butShow55->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(128,128,128,255);\n"
"border-image:url(\":/images/ap2000/022_0\");\n"
"}\n"
""));
        butShow55->setAutoDefault(false);
        butShow55->setFlat(false);
        butShow55->setProperty("KeepAspect", QVariant(2));
        butFullScreen = new QPushButton(wdPanel_A);
        butFullScreen->setObjectName(QStringLiteral("butFullScreen"));
        butFullScreen->setGeometry(QRect(300, 2, 24, 24));
        butFullScreen->setMinimumSize(QSize(0, 0));
        butFullScreen->setMaximumSize(QSize(16777215, 16777215));
        butFullScreen->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/025_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(0,0,0,255);\n"
"}\n"
"\n"
""));
        butFullScreen->setAutoDefault(false);
        butFullScreen->setFlat(false);
        butFullScreen->setProperty("KeepAspect", QVariant(2));
        butCloseCamera = new QPushButton(wdPanel_A);
        butCloseCamera->setObjectName(QStringLiteral("butCloseCamera"));
        butCloseCamera->setGeometry(QRect(268, 2, 24, 24));
        butCloseCamera->setMinimumSize(QSize(0, 0));
        butCloseCamera->setMaximumSize(QSize(16777215, 16777215));
        butCloseCamera->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/024_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(0,0,0,255);\n"
"}\n"
"\n"
""));
        butCloseCamera->setAutoDefault(false);
        butCloseCamera->setFlat(false);
        butCloseCamera->setProperty("KeepAspect", QVariant(2));
        wdPanel_A_QQ = new QWidget(PanelTitle);
        wdPanel_A_QQ->setObjectName(QStringLiteral("wdPanel_A_QQ"));
        wdPanel_A_QQ->setGeometry(QRect(208, 48, 124, 28));
        wdPanel_A_QQ->setStyleSheet(QLatin1String("QWidget{\n"
"border-top-width:2px;\n"
"border-top-color:rgba(255,255,255,255);\n"
"}\n"
""));
        butMin_9 = new QPushButton(wdPanel_A_QQ);
        butMin_9->setObjectName(QStringLiteral("butMin_9"));
        butMin_9->setGeometry(QRect(36, 2, 24, 24));
        butMin_9->setMinimumSize(QSize(0, 0));
        butMin_9->setMaximumSize(QSize(16777215, 16777215));
        butMin_9->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/023_0\");\n"
"}\n"
""));
        butMin_9->setAutoDefault(false);
        butMin_9->setFlat(false);
        butMin_9->setProperty("KeepAspect", QVariant(2));
        butFullScreen_QQ = new QPushButton(wdPanel_A_QQ);
        butFullScreen_QQ->setObjectName(QStringLiteral("butFullScreen_QQ"));
        butFullScreen_QQ->setGeometry(QRect(100, 2, 24, 24));
        butFullScreen_QQ->setMinimumSize(QSize(0, 0));
        butFullScreen_QQ->setMaximumSize(QSize(16777215, 16777215));
        butFullScreen_QQ->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/025_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(0,0,0,255);\n"
"}\n"
"\n"
""));
        butFullScreen_QQ->setAutoDefault(false);
        butFullScreen_QQ->setFlat(false);
        butFullScreen_QQ->setProperty("KeepAspect", QVariant(2));
        butCloseCamera_QQ = new QPushButton(wdPanel_A_QQ);
        butCloseCamera_QQ->setObjectName(QStringLiteral("butCloseCamera_QQ"));
        butCloseCamera_QQ->setGeometry(QRect(68, 2, 24, 24));
        butCloseCamera_QQ->setMinimumSize(QSize(0, 0));
        butCloseCamera_QQ->setMaximumSize(QSize(16777215, 16777215));
        butCloseCamera_QQ->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgba(0, 0, 0, 0);\n"
"border-image:url(\":/images/ap2000/024_0\");\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(0,0,0,255);\n"
"}\n"
"\n"
""));
        butCloseCamera_QQ->setAutoDefault(false);
        butCloseCamera_QQ->setFlat(false);
        butCloseCamera_QQ->setProperty("KeepAspect", QVariant(2));
        wdPanel_BLayout = new QWidget(PanelTitle);
        wdPanel_BLayout->setObjectName(QStringLiteral("wdPanel_BLayout"));
        wdPanel_BLayout->setGeometry(QRect(12, 48, 196, 28));
        wdPanel_BLayout->setStyleSheet(QLatin1String("QWidget{\n"
"border-top-width:2px;\n"
"border-top-color:rgba(255,255,255,255);\n"
"}"));
        wdPanel_B = new QWidget(wdPanel_BLayout);
        wdPanel_B->setObjectName(QStringLiteral("wdPanel_B"));
        wdPanel_B->setGeometry(QRect(0, 2, 196, 26));
        wdPanel_B->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"}"));
        butB_B = new QPushButton(wdPanel_B);
        butB_B->setObjectName(QStringLiteral("butB_B"));
        butB_B->setGeometry(QRect(64, 4, 64, 20));
        butB_B->setStyleSheet(QLatin1String("QWidget{\n"
"border-width:0px;\n"
"border-left-width:1px;\n"
"background-color:rgba(102,102,102,255);\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(122,122,122,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
""));
        butB_A = new QPushButton(wdPanel_B);
        butB_A->setObjectName(QStringLiteral("butB_A"));
        butB_A->setGeometry(QRect(0, 4, 64, 20));
        butB_A->setStyleSheet(QLatin1String("QWidget{\n"
"background-color:rgba(56,82,72,255);\n"
"border-width:0px;\n"
"border-right-width:1px;\n"
"}\n"
"QPushButton:hover{\n"
"background-color:rgba(122,122,122,255);\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgba(82,82,82,255);\n"
"}\n"
""));
        wdPanel_A_QQ->raise();
        butClose->raise();
        butMin->raise();
        label_16->raise();
        butAbout->raise();
        wdTop->raise();
        butMin_11->raise();
        label_time->raise();
        wdPanel_A->raise();
        wdPanel_BLayout->raise();

        retranslateUi(PanelTitle);

        butClose->setDefault(false);
        butMin->setDefault(false);
        butAbout->setDefault(false);
        butMin_11->setDefault(false);
        butMin_8->setDefault(false);
        butShow11->setDefault(false);
        butShow22->setDefault(false);
        butShow33->setDefault(false);
        butShow44->setDefault(false);
        butShow55->setDefault(false);
        butFullScreen->setDefault(false);
        butCloseCamera->setDefault(false);
        butMin_9->setDefault(false);
        butFullScreen_QQ->setDefault(false);
        butCloseCamera_QQ->setDefault(false);


        QMetaObject::connectSlotsByName(PanelTitle);
    } // setupUi

    void retranslateUi(QWidget *PanelTitle)
    {
        PanelTitle->setWindowTitle(QApplication::translate("PanelTitle", "Form", 0));
        butClose->setText(QString());
        butMin->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_16->setToolTip(QApplication::translate("PanelTitle", "Copyright SophTour.com", 0));
#endif // QT_NO_TOOLTIP
        label_16->setText(QApplication::translate("PanelTitle", "EShong V2.0.0", 0));
        butAbout->setText(QString());
        butA->setText(QApplication::translate("PanelTitle", "\345\256\236\346\227\266\350\247\206\351\242\221", 0));
        butB->setText(QApplication::translate("PanelTitle", "\345\233\236\346\224\276", 0));
        butC->setText(QApplication::translate("PanelTitle", "\350\256\276\347\275\256", 0));
        butMin_11->setText(QString());
        label_time->setText(QApplication::translate("PanelTitle", "2017/07/23 17:10:28", 0));
        butMin_8->setText(QString());
        butShow11->setText(QString());
        butShow22->setText(QString());
        butShow33->setText(QString());
        butShow44->setText(QString());
        butShow55->setText(QString());
        butFullScreen->setText(QString());
        butCloseCamera->setText(QString());
        butMin_9->setText(QString());
        butFullScreen_QQ->setText(QString());
        butCloseCamera_QQ->setText(QString());
        butB_B->setText(QApplication::translate("PanelTitle", "\350\277\234\347\250\213\346\226\207\344\273\266", 0));
        butB_A->setText(QApplication::translate("PanelTitle", "\346\234\254\345\234\260\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class PanelTitle: public Ui_PanelTitle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANELTITLE_H
