#include "PanelTitle.h"
#include "ui_PanelTitle.h"
#include <QMouseEvent>

#include <QtGui/QPainter.h>
#include <QTimer>
#include <QDateTime>

#include "AppZZB.h"
#include "PageMain.h"
#include "ComTool.h"

PanelTitle::PanelTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelTitle)
{
    ui->setupUi(this);
    mbDown = false;

    mPageList.push_back(ui->butA);
    mPageList.push_back(ui->butB);
    mPageList.push_back(ui->butC);

    mButShowList.push_back(ui->butShow11);
    mButShowList.push_back(ui->butShow22);
    mButShowList.push_back(ui->butShow33);
    mButShowList.push_back(ui->butShow44);
    mButShowList.push_back(ui->butShow55);

    mButShowList_BK.push_back(ui->butB_A);
    mButShowList_BK.push_back(ui->butB_B);

    connect(AppZZB::getInstance(), SIGNAL(chanagedSize(bool)), this, SLOT(oChanagedSize(bool)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedPage(int)), this, SLOT(oChanagedPage(int)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedShow(int, int)), this, SLOT(oChanagedShow(int, int)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedShowUserLeft(int)), this, SLOT(oChanagedShowUserLeft(int)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedShowBKSubPage(int)), this, SLOT(oChanagedShowBKSubPage(int)));

    QTimer *timer = new QTimer(this);   //声明一个定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(oTimer()));  //连接信号槽，定时器超时触发窗体更新
    timer->start(1000);   //启动定时器
}
PanelTitle::~PanelTitle()
{
    delete ui;
}
void PanelTitle::oTimer()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy/MM/dd hh:mm:ss "); //设置显示格式
    ui->label_time->setText(str);//在标签上显示时间
}
void PanelTitle::TurnSmall(int w){
    int dw = 0;
    {
        QRect rt = this->geometry();
        dw = rt.width() - w;
    }
    {
        QRect rt = ui->butMin->geometry();
        ui->butMin->setGeometry(rt.left()-dw, rt.top(), rt.width(), rt.height());
    }
//    {
//        QRect rt = ui->butMax->geometry();
//        ui->butMax->setGeometry(rt.left()-dw, rt.top(), rt.width(), rt.height());
//    }
    {
        QRect rt = ui->butClose->geometry();
        ui->butClose->setGeometry(rt.left()-dw, rt.top(), rt.width(), rt.height());
    }
//    bool small = AppZZB::getInstance()->IsSmall();
//    ui->butLogo->setEnabled(!small);
//    ui->butMax->setEnabled(!small);
}
void PanelTitle::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}

void PanelTitle::on_butClose_clicked()
{
    AppZZB::getInstance()->Exit();
}
//void PanelTitle::on_butLogo_clicked()
//{
//    bool small = AppZZB::getInstance()->IsSmall();
//    if(small){return;}
//    //AppZZB::getInstance()->pageMain->TurnAniLeft(ui->butLogo->isChecked());
//}
void PanelTitle::on_butMin_clicked()
{
    AppZZB::getInstance()->ShowMin();
}

void PanelTitle::on_butA_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnPage(0);
}
void PanelTitle::on_butB_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnPage(1);
}
void PanelTitle::on_butC_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnPage(2);
}
void PanelTitle::oChanagedPage(int curPage)
{
    static const QString ssDown = QString().sprintf("rgba(56,82,72,255)");
    static const QString ssUp = QString().sprintf("rgba(102,102,102,255)");
    for(int i=0, l=mPageList.size(); i<l; ++i){
        QWidget* pWd = mPageList.at(i);
        ComTool::Tool::updateSS_bkColor(pWd, (curPage==i) ? ssDown : ssUp);
    }
    ui->wdPanel_A->setVisible(0==curPage);
    ui->wdPanel_B->setVisible(1==curPage);
}
void PanelTitle::oChanagedShow(int curShow, int flag)
{
    static const QString ssDown = QString().sprintf("rgba(220,220,220,255)");
    static const QString ssUp = QString().sprintf("rgba(128,128,128,255)");

    for(int i=0, l=mButShowList.size(); i<l; ++i){
        QWidget* pWd = mButShowList.at(i);
        ComTool::Tool::updateSS_bkColor(pWd, (curShow==(i+1)) ? ssDown : ssUp);
    }
}
void PanelTitle::oChanagedShowUserLeft(int modeUserLeft)
{
    ui->wdPanel_A->setVisible(0 == modeUserLeft);
    ui->wdPanel_A_QQ->setVisible(1 == modeUserLeft);
}
void PanelTitle::oChanagedShowBKSubPage(int subPage)
{
    static const QString ssDown = QString().sprintf("rgba(56,82,72,255)");
    static const QString ssUp = QString().sprintf("rgba(102,102,102,255)");

    for(int i=0, l=mButShowList_BK.size(); i<l; ++i){
        QWidget* pWd = mButShowList_BK.at(i);
        ComTool::Tool::updateSS_bkColor(pWd, (subPage==i) ? ssDown : ssUp);
    }
}

//void PanelTitle::on_butMax_clicked()
//{
//    bool small = AppZZB::getInstance()->IsSmall();
//    if(small){return;}
//    bool bMax = !AppZZB::getInstance()->ReSizeMax();
//    AppZZB::getInstance()->ReSizeAny(bMax);
//    ui->butLogo->setChecked(true);
//}
void PanelTitle::oChanagedSize(bool bMax)
{
//    std::string ssCur = AppZZB::getInstance()->StyleCur().toStdString();
//    QString ssA = QString().sprintf("QWidget{\n"
//    "background-color:rgba(0,0,0,0);\n"
//    "border-image:url(\":/%s/016_0\");\n"
//    "}\n"
//    "QPushButton:hover{\n"
//    "border-image:url(\":/%s/016_1\");\n"
//    "}\n"
//    "QPushButton:pressed{\n"
//    "border-image:url(\":/%s/016_2\");\n"
//    "}", ssCur.c_str(), ssCur.c_str(), ssCur.c_str());
//    QString ssB = QString().sprintf("QWidget{\n"
//    "background-color:rgba(0,0,0,0);\n"
//    "border-image:url(\":/%s/016_3\");\n"
//    "}\n"
//    "QPushButton:hover{\n"
//    "border-image:url(\":/%s/016_4\");\n"
//    "}\n"
//    "QPushButton:pressed{\n"
//    "border-image:url(\":/%s/016_5\");\n"
//    "}", ssCur.c_str(), ssCur.c_str(), ssCur.c_str());
//    ui->butMax->setStyleSheet(bMax ? ssB : ssA);
}
void PanelTitle::mouseDoubleClickEvent(QMouseEvent *event){
//    bool small = AppZZB::getInstance()->IsSmall();
//    if(small){return;}
//    bool bMax = AppZZB::getInstance()->ReSizeMax();
//    AppZZB::getInstance()->ReSizeAny(!bMax);
//    ui->butLogo->setChecked(true);
}
void PanelTitle::mouseMoveEvent(QMouseEvent *e)
{
//    if(mbDown){
//        //bool small = AppZZB::getInstance()->IsSmall();!small &&
//        if(AppZZB::getInstance()->ReSizeMax()){
//           AppZZB::getInstance()->ReSizeAny(false);
//        }
//       AppZZB::getInstance()->Move(e->globalPos() - m_pointStart);
//    }
    return QWidget::mouseMoveEvent(e);
}
void PanelTitle::mousePressEvent(QMouseEvent *e)
{
//    mbDown = true;
//    m_pointStart = e->globalPos() - QWidget::mapToGlobal(pos());
    return QWidget::mousePressEvent(e);
}
void PanelTitle::mouseReleaseEvent(QMouseEvent *e)
{
//    mbDown = false;
    return QWidget::mouseReleaseEvent(e);
}


void PanelTitle::on_butShow11_clicked()
{
    AppZZB::getInstance()->TurnShow(1);
}

void PanelTitle::on_butShow22_clicked()
{
    AppZZB::getInstance()->TurnShow(2);
}

void PanelTitle::on_butShow33_clicked()
{
    AppZZB::getInstance()->TurnShow(3);
}

void PanelTitle::on_butShow44_clicked()
{
    AppZZB::getInstance()->TurnShow(4);
}

void PanelTitle::on_butShow55_clicked()
{
    AppZZB::getInstance()->TurnShow(5);
}
void PanelTitle::on_butCloseCamera_clicked()
{
    AppZZB::getInstance()->TurnCloseCamera();
}
void PanelTitle::on_butFullScreen_clicked()
{
    AppZZB::getInstance()->TurnFullScreen(true);
}
void PanelTitle::on_butCloseCamera_QQ_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnCloseCamera();
}
void PanelTitle::on_butFullScreen_QQ_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnFullScreen(true);
}

void PanelTitle::on_butB_A_clicked()
{
    AppZZB::getInstance()->TurnPlayBackSubPage(0);
}
void PanelTitle::on_butB_B_clicked()
{
    AppZZB::getInstance()->TurnPlayBackSubPage(1);
}
void PanelTitle::on_butAbout_clicked()
{
    AppZZB::getInstance()->TurnShowDlgAboutUs(true);
}
