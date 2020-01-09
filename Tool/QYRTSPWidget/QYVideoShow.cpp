#include "QYVideoShow.h"
#include "ui_QYVideoShow.h"
#include <QtGui/QPainter.h>
#include <QMouseEvent>
#include <QDebug>

QYVideoShow::QYVideoShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QYVideoShow)
{
    ui->setupUi(this);
    setUpdatesEnabled(false);

    //setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_DontCreateNativeAncestors);
    setStyleSheet("QWidget { background-color: rgba(255,26,26,255);}");//transparent
}

QYVideoShow::~QYVideoShow()
{
    delete ui;
}

//void QYVideoShow::showEvent(QShowEvent *)
//{

//}
//void QYVideoShow::focusInEvent(QFocusEvent *)
//{

//}
//void QYVideoShow::focusOutEvent(QFocusEvent *)
//{

//}
void QYVideoShow::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}

//void QYVideoShow::mouseMoveEvent(QMouseEvent *e)
//{
//    qWarning()<<"dsfsdgd: "<<e->pos();
//}
//void QYVideoShow::mousePressEvent(QMouseEvent *e)
//{

//}
//void QYVideoShow::mouseReleaseEvent(QMouseEvent *e)
//{

//}
