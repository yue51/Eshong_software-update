#include "QYPixViewer.h"

#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <math.h>

#include <QGraphicsView>

#include <QtGui/QPainter.h>
#include <qstyleoption.h>

#include <QtMath>
#include <QDebug>
void QYPixCircle::paint(QPainter *painter)
{
    if(0 == pixItem){return;}
    QRectF rt = pixItem->boundingRect();
    qreal w = rt.width();
    qreal h = rt.height();

    QPen oldPen = painter->pen();
    painter->setPen(QPen(QColor(255, 0, 0), 4));
    painter->drawEllipse(QPointF(center.x()*w,center.y()*h), radius*h, radius*h);
    painter->drawEllipse(QPointF(center.x()*w,center.y()*h), 8, 8);
    painter->setPen(oldPen);
    //qWarning("123sd");
}

void QYPixPoint::paint(QPainter *painter)
{
    if(0 == pixItem || pts.size()<1){return;}
    QRectF rt = pixItem->boundingRect();
    qreal w = rt.width();
    qreal h = rt.height();

    QPen oldPen = painter->pen();
    painter->setPen(QPen(QColor(0, 255, 0), 4));

    PointFVec tempPts;
    for(int i=0, l=pts.size(); i<l; ++i){
        tempPts.push_back(QPointF(pts[i].x()*w, pts[i].y()*h));
    }
    painter->drawPoints(&tempPts[0], tempPts.size());

    painter->setPen(oldPen);
}

//构造函数初始化了变量pix
QYPixItem::QYPixItem(QPixmap *pixmap)
{
    pix         = *pixmap;
    Reset();
    imgCross.load(":/QYRTSPWidget/3_3");

}

//实现自己的图元边界函数
QRectF QYPixItem::boundingRect() const
{
    return QRectF(0, 0, pix.width(), pix.height());
}

//只需QPainter的drawPixmap()函数将图元图片绘出即可
void QYPixItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *)
{
    painter->drawPixmap(0, 0, pix);
    for(int i=pixHelperVec.size()-1; i>=0; --i){
        QYPixHelper* helper = pixHelperVec[i];
        helper->paint(painter);
    }

    if(showDownPos){
        QRectF rt = boundingRect();
        qreal w = rt.width();
        qreal h = rt.height();

//        QPen oldPen = painter->pen();
//        painter->setPen(QPen(QColor(255, 0, 0), 4));
//        painter->drawPoint(QPointF(downPos.x()*w, downPos.y()*h));
//        painter->setPen(oldPen);
        qreal wi = 8.0 * (4.0/m_fScale);//rt.width();
        qreal hi = 8.0 * (4.0/m_fScale);//rt.height();
        painter->drawImage(QRectF(downPos.x()*w-wi*0.5,downPos.y()*h-hi*0.5, wi,hi), imgCross);
    }
}

//鼠标点击事件  局部缩放
void QYPixItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    bool ret = false;
//    QPointF pos = transform().inverted().map(e->scenePos());
//    QRectF rt = boundingRect();
//    QRectF dnPos = QPointF(pos.x()/rt.width(), pos.y()/rt.height());
//    qreal wi = 4.0 * (4.0/m_fScale);//rt.width();
//    qreal hi = 4.0 * (4.0/m_fScale);//rt.height();
//    for(int i=pixHelperVec.size()-1; i>=0; --i){
//        QYPixHelper* helper = pixHelperVec[i];
//        ret = helper->mousePressEvent(dnPos, hi/rt.height(), 1);
//        if(ret){break;}
//    }
//    if(ret){return;}

    m_posLastMove   = event->pos();
    m_bLBDown       = true;
    m_isMove        = false;
}

void QYPixItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    bool ret = false;
//    QPointF pos = transform().inverted().map(e->scenePos());
//    QRectF rt = boundingRect();
//    QRectF dnPos = QPointF(pos.x()/rt.width(), pos.y()/rt.height());
//    qreal wi = 4.0 * (4.0/m_fScale);//rt.width();
//    qreal hi = 4.0 * (4.0/m_fScale);//rt.height();
//    for(int i=pixHelperVec.size()-1; i>=0; --i){
//        QYPixHelper* helper = pixHelperVec[i];
//        ret = helper->mouseMoveEvent(dnPos, hi/rt.height(), 1);
//        if(ret){break;}
//    }
//    if(ret){return;}

    if(m_bLBDown && !m_isMove){
        m_isMove = true;
    }
    if(m_isMove){
        QPointF ptd = event->pos() - m_posLastMove;
        float dx = ptd.x();
        float dy = ptd.y();

        QTransform mat;
        mat = mat*QTransform().translate(dx,dy);
        mat = mat*transform();

        setTransform(mat);
        UpdateView();
    }
}

void QYPixItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
//    bool ret = false;
//    QPointF pos = transform().inverted().map(e->scenePos());
//    QRectF rt = boundingRect();
//    downPos = QPointF(pos.x()/rt.width(), pos.y()/rt.height());
//    qreal wi = 4.0 * (4.0/m_fScale);//rt.width();
//    qreal hi = 4.0 * (4.0/m_fScale);//rt.height();
//    for(int i=pixHelperVec.size()-1; i>=0; --i){
//        QYPixHelper* helper = pixHelperVec[i];
//        ret = helper->mouseReleaseEvent(downPos, hi/rt.height(), 1);
//        if(ret){break;}
//    }
//    if(ret){return;}

    if(m_bLBDown && !m_isMove){
        QPointF pos = transform().inverted().map(e->scenePos());
        QRectF rt = boundingRect();
        downPos = QPointF(pos.x()/rt.width(), pos.y()/rt.height());
        qreal wi = 4.0 * (4.0/m_fScale);//rt.width();
        qreal hi = 4.0 * (4.0/m_fScale);//rt.height();
        for(int i=pixHelperVec.size()-1; i>=0; --i){
            QYPixHelper* helper = pixHelperVec[i];
            helper->HitObj(downPos, hi/rt.height(), 1);
        }
        UpdateView();
        //qWarning()<<"ad: "<<pos<<" rt: "<<rt<<" down: "<<downPos;
    }
    m_bLBDown   = false;
    m_isMove    = false;
}
//void QYPixItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
//{
////    QPointF pos = transform().inverted().map(e->scenePos());
////    QRectF rt = boundingRect();
////    QPointF pt = QPointF(pos.x()/rt.width(), pos.y()/rt.height());

////    qreal wi = 4.0 * (4.0/m_fScale);//rt.width();
////    qreal hi = 4.0 * (4.0/m_fScale);//rt.height();
////    QPointF d = pt - downPos;
////    if(qAbs(d.x()) < wi && qAbs(d.y())<hi){
////        for(int i=pixHelperVec.size()-1; i>=0; --i){
////            QYPixHelper* helper = pixHelperVec[i];
////            helper->HitObj(downPos, wi, 0);
////        }
////        downPos = QPointF(0.5, 0.5);
////        update();
////    }
//}
void QYPixItem::Reset()
{
    m_fScale    = 1.0;
    m_fScaleMin = 0.0625;
    m_isMove    = false;
    m_bLBDown   = false;
    m_posScale  = boundingRect().center();
    downPos     = QPointF(0.5,0.5);
    showDownPos = false;
    resetTransform();
    UpdateView();
}
void QYPixItem::Move(qreal dx, qreal dy)
{
    QTransform mat;
    mat = mat*QTransform().translate(dx,dy);
    mat = mat*transform();

    setTransform(mat);
    UpdateView();
}
void QYPixItem::SetScaleMin(qreal smin)
{
    m_fScaleMin = smin;
}
void QYPixItem::addHelper(QYPixHelper* helper)
{
    helper->pixItem = this;
    pixHelperVec.push_back(helper);
    UpdateView();
}
void QYPixItem::removeHelper(QYPixHelper* helper)
{
    QYPixHelperVec::iterator it = std::find(pixHelperVec.begin(), pixHelperVec.end(), helper);
    if(it != pixHelperVec.end()){
        pixHelperVec.erase(it);
        UpdateView(true);
    }
}
void QYPixItem::UpdateView(bool pow)
{
    if(0 != view && (pow || pixHelperVec.size() > 0)){
         view->viewport()->update();
    }
}
void QYPixItem::Scale(qreal s)
{
    Scale(s, m_posScale);
}
void QYPixItem::Scale(qreal s, const QPointF& pos)
{
    qreal fs = s;
    if(fs > 4.0){
        fs = 4.0;
    }else if(fs < m_fScaleMin){
        fs = m_fScaleMin;
    }
    qreal ds = fs / m_fScale;
    m_fScale = fs;

    m_posScale = pos;
    QTransform mat;
    float dx = m_posScale.x();
    float dy = m_posScale.y();
    mat = mat*QTransform().translate(-dx, -dy);
    mat = mat*QTransform().scale(ds,ds);
    mat = mat*QTransform().translate(dx, dy);
    mat = mat*transform();

    setTransform(mat);
    UpdateView();
}

//使用滚轮整体缩放
void QYPixItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    //qreal ds = event->delta() > 0 ? 1.1 : 1.0/1.1;
    //qreal fs = m_fScale * ds;
    int nTurn = event->delta() / 120;
    if(nTurn == 0){
        return;
    }
    qreal fScale = 1.1;
    if(nTurn < 0){
        fScale = 0.909091;
    }
    qreal ds = qPow(fScale, qAbs(nTurn));
    qreal fs = m_fScale * ds;
    Scale(fs, event->pos());
}

///////////////////////////////////////////////////////////

QYPixViewer::QYPixViewer(QWidget *parent) :
    QWidget(parent)
{
    {
        gpView = new QGraphicsView(this);
        QRect rt = this->geometry();
        gpView->setGeometry(QRect(0,0,rt.width(),rt.height()));
        gpView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gpView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush white(QColor(26,26,26));
        gpView->setBackgroundBrush(white);
    }
    {
        gpScene = new QGraphicsScene(this);  //new 一个新的场景对象
        QRect rt = gpView->geometry();
        gpScene->setSceneRect(0,0,rt.width(),rt.height());     //限定场景对象的显示区域
        gpView->setScene(gpScene);          //将视图对象于场景相连
    }
    pixItem = 0;
}
QYPixViewer::~QYPixViewer()
{
}
void QYPixViewer::updateViewRect()
{
    {
        QRect rt = this->geometry();
        gpView->setGeometry(QRect(0,0,rt.width(),rt.height()));
        qWarning(QString().sprintf("A: %d,%d,%d,%d", rt.left(),rt.top(),rt.width(),rt.height()).toStdString().c_str());
    }
    {
        QRect rt = gpView->geometry();
        gpScene->setSceneRect(0,0,rt.width(),rt.height());
        qWarning(QString().sprintf("B: %d,%d,%d,%d", rt.left(),rt.top(),rt.width(),rt.height()).toStdString().c_str());
    }
}
void QYPixViewer::closeImage(){
    if(0 != pixItem){
        gpScene->removeItem(pixItem);   //将上一个图元从场景中移除,重新添加新的图元
        pixItem = 0;
    }
    if(0 != gpView){
        delete gpView;
        gpView = 0;
    }
    if(0 != gpScene){
        delete gpScene;
        gpScene = 0;
    }
}
void QYPixViewer::fromImage(const QImage &image)
{
    //closeImage();
    if(0 != gpView){
        delete gpView;
        gpView = 0;
    }
    if(0 != gpScene){
        delete gpScene;
        gpScene = 0;
    }
    if(0 == gpView)
    {
        gpView = new QGraphicsView(this);
        QRect rt = this->geometry();
        gpView->setGeometry(QRect(0,0,rt.width(),rt.height()));
        gpView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        gpView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush white(QColor(26,26,26));
        gpView->setBackgroundBrush(white);
    }
    if(0 == gpScene)
    {
        gpScene = new QGraphicsScene(this);  //new 一个新的场景对象
        QRect rt = gpView->geometry();
        gpScene->setSceneRect(0,0,rt.width(),rt.height());     //限定场景对象的显示区域
        gpView->setScene(gpScene);          //将视图对象于场景相连
    }
    if(0 != pixItem){
        gpScene->removeItem(pixItem);   //将上一个图元从场景中移除,重新添加新的图元
        pixItem = 0;
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    pixItem = new QYPixItem(&pixmap);          //实例化自定义类的一个对象,传入一个图片用于显示
    gpScene->addItem(pixItem);       //将该图元对象添加到场景中，并设置此图元在场景中的位置为中心(0,0)
    pixItem->view = gpView;
    updateViewRect();
    reset();
}
void QYPixViewer::openImageFile(const QString& filepath)
{
    if(0 != pixItem){
        gpScene->removeItem(pixItem);   //将上一个图元从场景中移除,重新添加新的图元
        pixItem = 0;
    }

    QPixmap *pixmap = new QPixmap(filepath);
    pixItem = new QYPixItem(pixmap);          //实例化自定义类的一个对象,传入一个图片用于显示
    gpScene->addItem(pixItem);       //将该图元对象添加到场景中，并设置此图元在场景中的位置为中心(0,0)
    reset();
}

qreal rectForCropping(QSizeF textureAspectRatio, QSizeF croppingAspectRatio)
{
    QSizeF cropScaleAmount(croppingAspectRatio.width() / textureAspectRatio.width(), croppingAspectRatio.height() / textureAspectRatio.height());
    return std::min(cropScaleAmount.width(), cropScaleAmount.height());
}
void QYPixViewer::reset(){
    gpView->resetMatrix();          //重置图片
    if(0 != pixItem){
        pixItem->setPos(0, 0);

        QRect rtItem;{
            QRectF rt = pixItem->boundingRect();
            rtItem = QRect((int)rt.left(), (int)rt.top(), (int)rt.width(), (int)rt.height());
            //qWarning(QString().sprintf("AA: %f,%f,%f,%f", rt.left(),rt.top(),rt.width(),rt.height()).toStdString().c_str());
        }
        QRect rtScene;{
            QRect rt = gpView->geometry();
            rtScene = QRect(0,0,rt.width(),rt.height());
            //qWarning(QString().sprintf("BB: %d,%d,%d,%d", rt.left(),rt.top(),rt.width(),rt.height()).toStdString().c_str());
        }

        QPoint ptD = rtScene.center() - rtItem.center();
        pixItem->Reset();
        pixItem->Move(ptD.x(), ptD.y());
        qreal f4 = rectForCropping(QSizeF(rtItem.width(),rtItem.height()), QSizeF(rtScene.width()*0.5, rtScene.height()*0.5));
        qreal f  = rectForCropping(QSizeF(rtItem.width(),rtItem.height()), QSizeF(rtScene.width(), rtScene.height()));
        pixItem->SetScaleMin(f4);
        pixItem->Scale(f);

    }
}
void QYPixViewer::addHelper(QYPixHelper* helper)
{
    if(0 != pixItem){
        pixItem->addHelper(helper);
    }
}
void QYPixViewer::removeHelper(QYPixHelper* helper)
{
    if(0 != pixItem){
        pixItem->removeHelper(helper);
    }
}
void QYPixViewer::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}
void QYPixViewer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateViewRect();
    reset();
}

