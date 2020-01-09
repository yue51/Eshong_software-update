#include "QYVideoWidget.h"
#include "ui_QYVideoWidget.h"

#include <QtGui/QPainter.h>
#include <QDebug>
#include <QScreen>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QPushButton>
#include <QPropertyAnimation>
#include "QYPixViewer.h"
#include "../../ComTool.h"
#include "../../AppZZB.h"

//static QYDlgHotBar* s_dlgHotBar = 0;

QYVideoWidget::QYVideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QYVideoWidget)
{
    ui->setupUi(this);
    mbDown = false;

    mVWidth     = 640;
    mVHeight    = 360;
    mAspect     = -1;

    lastX       = -1;
    lastY       = -1;
    lastW       = -1;
    lastH       = -1;

    ui->wd_pix->setVisible(false);
    ui->wd_cross->setVisible(false);
    ui->wd_ctrl->setVisible(false);

    //ui->wd_hotbar->setVisible(false);

    //connect(ui->wd_hotbar, SIGNAL(sigClicked(int,QPushButton*)), this, SLOT(oSigHotBarClicked(int,QPushButton*)));

    //ui->wd_pano->setWindowFlags(Qt::Widget | Qt::Popup);
    //ui->wd_pano->setVisible(false);
    //ui->wd_ctrl->setVisible(false);

    pixCircle   = 0;
    pixPoint    = 0;
    pixViewer   = ui->wd_pix;
    lr[0] = 0.5;
    lr[1] = 0.5;
    lr[2] = 0.5;
    ag    = 180.0;
    ui->wd_show->setVisible(false);
    ui->wd_show->installEventFilter(this); 
    ui->wd->installEventFilter(this);

    mEnableTrack = false;
    mEnableClick = false;
    mDownLB = false;
    mEnableWheel = false;

    m_pAniwd_Ctrl = 0;
}

QYVideoWidget::~QYVideoWidget()
{
    ComTool::CCommon<QPropertyAnimation>::DeleteA(&m_pAniwd_Ctrl);
    ui->wd_show->removeEventFilter(this);
    ComTool::CCommon<QYPixCircle>::DeleteA(&pixCircle);
    ComTool::CCommon<QYPixPoint>::DeleteA(&pixPoint);

    delete ui;
}
void QYVideoWidget::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;
    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);

  //  qWarning()<<"sdsf12: "<<" "<<lr[0]<<" "<<lr[1]<<" "<<lr[2];
   // painter->setRenderHints(QPainter::Antialiasing, true);
    //painter->setPen(QColor(255,0,0,255));
    //painter->fillRect(0,0,400,400,QColor(255,0,0,255));

    //QPixmap scaledPixmap = QApplication::primaryScreen()->grabWindow(ui->wd_show->winId());
    //QPixmap scaledPixmap(QPixmap::grabWindow(ui->wd_show->winId());
   //QPixmap scaledPixmap(ui->wd_show->size());
   //ui->wd_show->render(&scaledPixmap);//保存当前窗口
    //painter->drawPixmap(0, 0, scaledPixmap.width(), scaledPixmap.height(), scaledPixmap);
}
bool QYVideoWidget::eventFilter(QObject *watched, QEvent *event)
{
    unsigned int nType = event->type();
    if (QEvent::MouseMove == nType){
        AppZZB::getInstance()->SetFocusVideo(this);
        //showHotBar(true);
    }
    if(mEnableTrack && watched->inherits("QYVideoShow")){
        QYVideoShow* wdShow = (QYVideoShow*)watched;
        unsigned int nType = event->type();
        if (QEvent::MouseMove == nType){
            QMouseEvent* e = (QMouseEvent*)event;
            QPoint pos   = e->pos();
            QRectF rt    = wdShow->geometry();
            QVector2D uv = QVector2D(pos.x()/rt.width(), pos.y()/rt.height());
            QVector2D dd = uv - QVector2D(lr[1],lr[2]);
            dd.setX(dd.x()*rt.width());
            dd.setY(dd.y()*rt.height());
            if(dd.length() < lr[0]*rt.height()){
                setCursor(Qt::CrossCursor);
            }else{
                setCursor(Qt::ArrowCursor);
            }
        }
    }

    if(mEnableClick && watched->inherits("QYVideoShow")){

        QYVideoShow* wdShow = (QYVideoShow*)watched;
        unsigned int nType = event->type();
        if(QEvent::MouseButtonPress == nType){
            QMouseEvent* e = (QMouseEvent*)event;
            if(Qt::LeftButton == e->button()){
                mLastDownPt = e->pos();
                mDownLB = true;
            }
        }else if(QEvent::MouseMove == nType){
            mDownLB = false;
        }else if(QEvent::MouseButtonRelease == nType){
            QMouseEvent* e = (QMouseEvent*)event;
            if(Qt::LeftButton == e->button()){
                QPoint pos   = e->pos();
                QRectF rt    = wdShow->geometry();
                QVector2D uv = QVector2D(pos.x()/rt.width(), pos.y()/rt.height());
                QVector2D uvDown = QVector2D(mLastDownPt.x()/rt.width(), mLastDownPt.y()/rt.height());

                if(mDownLB){
                    emit sigTrackClicked(this, uv);
                }else{
                    emit sigTrackRect(this, uvDown, uv);
                }
//                QVector2D dd = uv - QVector2D(lr[1],lr[2]);
//                dd.setX(dd.x()*rt.width());
//                dd.setY(dd.y()*rt.height());
//                if(dd.length() < lr[0]*rt.height()){
//                    mDownPos = uv;
//                    emit sigTrackClicked(this, mDownPos);
//                }
            }
            mDownLB = false;
        }

    }

    if(mEnableWheel && watched->inherits("QYVideoShow")){
        QYVideoShow* wdShow = (QYVideoShow*)watched;
        unsigned int nType = event->type();
        if(QEvent::Wheel == nType){
            QWheelEvent* e = (QWheelEvent*)event;
            //qWarning()<<"QWheelEvent: "<<e->delta();
            qreal fTurn = e->delta() / 120.0;
            //if(nTurn != 0){
                emit sigTrackWheel(this, fTurn);
            //}
        }
    }

    return QWidget::eventFilter(watched, event);
}
void QYVideoWidget::mouseMoveEvent(QMouseEvent *e)
{
    mbDown = false;
    AppZZB::getInstance()->SetFocusVideo(this);
    //showHotBar(true);
    QWidget::mouseMoveEvent(e);
}
void QYVideoWidget::mousePressEvent(QMouseEvent *e)
{
    mbDown = true;
    QWidget::mousePressEvent(e);
}
void QYVideoWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(mbDown){//Clicked
        AppZZB::getInstance()->SetFocusVideo(this, 2);
        emit sigClicked(this);
    }
    mbDown = false;
    QWidget::mouseReleaseEvent(e);
}
void QYVideoWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit sigDoubleClicked();
    QWidget::mouseDoubleClickEvent(e);
}
void QYVideoWidget::resizeEvent(QResizeEvent *e)
{
    QRect gmo = geometry();
    QRect rt(4,4,gmo.width()-8, gmo.height()-8);
    int ww = rt.width();
    int hh = rt.height();

    if(lastX != gmo.left() ||
       lastY != gmo.top() ||
       lastW != ww ||
       lastH != hh){

        lastX = gmo.left();
        lastY = gmo.top();
        lastW = ww;
        lastH = hh;

        _UpdatePosSize();
        AppZZB::getInstance()->SetFocusVideo(this, 1);
//        qreal r = ComTool::Tool::rectForCroppingVal(QSizeF(mVWidth,mVHeight),QSizeF(ww,hh));
//        rt = ComTool::Tool::ScaleRt(rt, mVWidth*r,mVHeight*r, 0);
//        ComTool::Tool::ReSizeAny(rt.width(),rt.height(), ui->wd);
//        ui->wd->setGeometry(rt);

//        bool isV = ui->wd_hotbar->isVisible();
//        ui->wd_hotbar->setVisible(false);
//        rt = QRect(width()-48, 8, 40, height()-16);
//        ComTool::Tool::ReSizeAny(rt.width(),rt.height(), ui->wd_hotbar);
//        ui->wd_hotbar->setGeometry(rt);
//        showHotBar(isV);
    }
}
void QYVideoWidget::enterEvent(QEvent *e)
{
//    if(!ui->wd_show->isVisible()){
//        QWidget::enterEvent(e);
//        return;
//    }
//    if(s_dlgHotBar != ui->wd_hotbar){
//        if(0 != s_dlgHotBar){
//            s_dlgHotBar->setVisible(false);
//        }
//        s_dlgHotBar = ui->wd_hotbar;
//        showHotBar(true);
//    }
    QWidget::enterEvent(e);
}
void QYVideoWidget::leaveEvent(QEvent *e)
{
//    if(!ui->wd_show->isVisible()){
//        QWidget::leaveEvent(e);
//        return;
//    }
    QPoint pt = QCursor::pos();
    QPoint lt = this->mapToGlobal(QPoint(4,4));
    QPoint rb = this->mapToGlobal(QPoint(width()-4,height()-4));

    QRect rt(lt, rb);
    if(!rt.contains(pt)){
        AppZZB::getInstance()->SetFocusVideo(0, 2);
        //showHotBar(false);
    }
    QWidget::leaveEvent(e);
}

QWidget* QYVideoWidget::showWidget(){
    return ui->wd_show;
}
QWidget* QYVideoWidget::rootWidget(){
    return ui->wd;
}
void QYVideoWidget::_UpdatePosSize()
{
    QRect gmo = geometry();
    QRect rt(4,4,gmo.width()-8, gmo.height()-8);

    if(0 == mAspect){
        int vW = 640;
        int vH = 360;
        int ww = rt.width();
        int hh = rt.height();
        qreal r = ComTool::Tool::rectForCroppingVal(QSizeF(vW,vH),QSizeF(ww,hh));
        rt = ComTool::Tool::ScaleRt(rt, vW*r,vH*r, 0);
    }else if(1 == mAspect){
        int vW = 640;
        int vH = 480;
        int ww = rt.width();
        int hh = rt.height();
        qreal r = ComTool::Tool::rectForCroppingVal(QSizeF(vW,vH),QSizeF(ww,hh));
        rt = ComTool::Tool::ScaleRt(rt, vW*r,vH*r, 0);
    }else if(2 == mAspect){

    }else if(3 == mAspect){
        int ww = rt.width();
        int hh = rt.height();
        qreal r = ComTool::Tool::rectForCroppingVal(QSizeF(mVWidth,mVHeight),QSizeF(ww,hh));
        rt = ComTool::Tool::ScaleRt(rt, mVWidth*r,mVHeight*r, 0);
        rt = QRect(rt.left()-ww*0.1, rt.top()-hh*0.1, ww*1.2, hh*1.2);
    }else{
        int ww = rt.width();
        int hh = rt.height();
        qreal r = ComTool::Tool::rectForCroppingVal(QSizeF(mVWidth,mVHeight),QSizeF(ww,hh));
        rt = ComTool::Tool::ScaleRt(rt, mVWidth*r,mVHeight*r, 0);
    }

    ComTool::Tool::ReSizeAny(rt.width(),rt.height(), ui->wd);
    ui->wd->setGeometry(rt);
    ui->wd_show->setGeometry(QRect(0,0,rt.width(),rt.height()));
    ui->wd_pix->setGeometry(QRect(0,0,rt.width(),rt.height()));
//    ui->wd->setStyleSheet("QWidget{background-color:#ffffff;}");
//    //ui->wd_show->setGeometry(ui->wd_show->geometry());
//    ui->wd_show->setVisible(ui->wd_show->isVisible());

//    qDebug()<<"show: "<<(long)this<<ui->wd_show->geometry()<<" "<<ui->wd->geometry();
//    {
//        bool isV = ui->wd_hotbar->isVisible();
//        ui->wd_hotbar->setVisible(false);
//        rt = QRect(width()-48, 8, 40, height()-16);
//        ComTool::Tool::ReSizeAny(rt.width(),rt.height(), ui->wd_hotbar);
//        ui->wd_hotbar->setGeometry(rt);
//        showHotBar(isV);
//    }
}

void QYVideoWidget::onShowVideo(int w, int h, int aspect)
{
    mVWidth  = w;
    mVHeight = h;
    mAspect  = aspect;
    if(!isVisible()){return;}

    _UpdatePosSize();
//    QRect rt(4,4,width()-8, height()-8);
//    int ww = rt.width();
//    int hh = rt.height();
//    qreal r = ComTool::Tool::rectForCroppingVal(QSizeF(mVWidth,mVHeight),QSizeF(ww,hh));
//    rt = ComTool::Tool::ScaleRt(rt, mVWidth*r,mVHeight*r, 0);

//    ui->wd_pano->setVisible(false);
//    ui->wd_pano->move(0,0);

//    ComTool::Tool::ReSizeAny(rt.width(),rt.height(), ui->wd);
//    ui->wd->setGeometry(rt);

//    {
//        bool isV = ui->wd_hotbar->isVisible();
//        ui->wd_hotbar->setVisible(false);
//        rt = QRect(width()-48, 8, 40, height()-16);
//        ComTool::Tool::ReSizeAny(rt.width(),rt.height(), ui->wd_hotbar);
//        ui->wd_hotbar->setGeometry(rt);
//        showHotBar(isV);
//    }
}

QYPixViewer* QYVideoWidget::showPixTool(const QImage &image)
{
//    if(0 != filepath){
//        //pixViewer->openImageFile("C:\\Users\\GF\\Desktop\\FishEye\\[20170730]EShong_src12\\testt.jpg");
//    }
    pixViewer->fromImage(image);
//    if(0 == pixPoint){
//        pixPoint  = new QYPixPoint();
//        pixViewer->addHelper(pixPoint);
//    }
    if(0 == pixCircle){
        pixCircle = new QYPixCircle();
        pixViewer->addHelper(pixCircle);
    }
    _UpdatePosSize();
    //ui->wd_pix->setGeometry(QRect(0,0, ui->wd->width(), ui->wd->height()));
    qDebug()<<"ui->wd_pix:"<<ui->wd->width()<<" "<<ui->wd->height();
    ui->wd_pix->setVisible(true);
    ui->wd_ctrl->setVisible(true);
    //ui->wd_pix->raise();
    oChanagedLR();
    return ui->wd_pix;
}
QYPixViewer* QYVideoWidget::hidePixTool()
{
    if(0 != pixCircle){
        pixViewer->removeHelper(pixCircle);
        ComTool::CCommon<QYPixCircle>::DeleteA(&pixCircle);
    }
    //ui->wd_pix->closeImage();
    ui->wd_pix->setVisible(false);
    ui->wd_ctrl->setVisible(false);
    return ui->wd_pix;
}
void QYVideoWidget::showCross(bool show)
{
    QPoint pt = ui->wd->mapToGlobal(QPoint(ui->wd->width()*0.5, ui->wd->height()*0.5));
    ui->wd_cross->move(pt.x()-ui->wd_cross->width()*0.5, pt.y()-ui->wd_cross->height()*0.5);
    ui->wd_cross->setVisible(show);

//    ui->wd_hotbar->move(pt.x(), pt.y());
//    ui->wd_hotbar->setVisible(true);
}
void QYVideoWidget::showHotBar(bool show)
{
//    if(!show){
//        s_dlgHotBar = 0;
//        ui->wd_hotbar->setVisible(false);
//        return;
//    }

//    if(s_dlgHotBar == ui->wd_hotbar){
//         return;
//   }

//    if(0 != s_dlgHotBar){
//        s_dlgHotBar->setVisible(false);
//    }
//    s_dlgHotBar = ui->wd_hotbar;

//    QPoint pt = this->mapToGlobal(QPoint(width()-8.0, 8.0));
//    ui->wd_hotbar->move(pt.x()-ui->wd_hotbar->width(), pt.y());
//    ui->wd_hotbar->setVisible(true);
}
void QYVideoWidget::enableTrack(bool enable)
{
    mEnableTrack = enable;
}
void QYVideoWidget::enableClick(bool enable)
{
    mEnableClick = enable;
}
void QYVideoWidget::enableWheel(bool enable)
{
    mEnableWheel = enable;
}
//void QYVideoWidget::oSigHotBarClicked(int butNo, QPushButton* but)
//{
////    if(ComTool::BN_PANO == butNo){
////        if(!ui->wd_pano->isVisible()){
////            QPoint ptGolbal(ui->wd_hotbar->x()+but->x(), ui->wd_hotbar->y()+but->y()+but->height());
////            ui->wd_pano->move(ptGolbal.x()-ui->wd_pano->width()-4, ptGolbal.y()-ui->wd_pano->height());
////            ui->wd_pano->setVisible(true);
////        }
////    }
//}
void QYVideoWidget::on_spin_dr_valueChanged(double arg1)
{
    if(fabs(lr[0] - arg1) < 1.0e-6){
        return;
    }
    lr[0] = arg1;
    oChanagedLR();
}

void QYVideoWidget::on_spin_dx_valueChanged(double arg1)
{
    if(fabs(lr[1] - arg1) < 1.0e-6){
        return;
    }
    lr[1] = arg1;
    oChanagedLR();
}

void QYVideoWidget::on_spin_dy_valueChanged(double arg1)
{
    if(fabs(lr[2] - arg1) < 1.0e-6){
        return;
    }
    lr[2] = arg1;
    oChanagedLR();
}
void QYVideoWidget::oChanagedLR()
{
    if(0 != pixCircle){
        pixCircle->radius = lr[0];
        pixCircle->center.setX(lr[1]);
        pixCircle->center.setY(lr[2]);
        pixViewer->update();
    }
}

void QYVideoWidget::on_butCtrlShow_clicked()
{
    QRect pixRt = QRect(0,0,ui->wd->width(), ui->wd->height());
    QRect butRt = ui->butCtrlShow->geometry();
    QRect rtCur = ui->wd_ctrl->geometry();
    QRect rtDst = rtCur;
    bool bShow = pixRt.contains(rtCur.center());
    if(bShow){
        qreal l = pixRt.left() - butRt.left();
        qreal t = pixRt.bottom() - butRt.bottom();
        rtDst = QRect(l, t, rtCur.width(), rtCur.height());
    }else{
        qreal l = pixRt.left();
        qreal t = pixRt.bottom() - rtCur.height();
        rtDst = QRect(l, t, rtCur.width(), rtCur.height());
    }

    QWidget* pWd  = ui->wd_ctrl;
    QPropertyAnimation* &pAniwd = m_pAniwd_Ctrl;
    if(0 == pAniwd){
        pAniwd = new QPropertyAnimation(pWd, "geometry");
    }
    pAniwd->setDuration(ComTool::Def::DURATION);
    pAniwd->setStartValue(rtCur);
    pAniwd->setEndValue(rtDst);
    pAniwd->start();
}
