#ifndef QYPIXVIEWER_H_
#define QYPIXVIEWER_H_  1

#include <QGraphicsItem>
#include <QPixmap>
#include <QWidget>
#include <QImage>

QT_BEGIN_NAMESPACE
    class QGraphicsScene;
    class QGraphicsView;
QT_END_NAMESPACE

class QYPixItem;
class QYPixHelper:public QObject
{
public:
    Q_OBJECT
public:
    explicit QYPixHelper(QObject *parent=0):QObject(parent){pixItem=0;}
    virtual ~QYPixHelper(){}
public:
    virtual int HitObj(QPointF pt, qreal s, int flag){return 0;}

    virtual bool mousePressEvent(QPointF pt, qreal s, int flag){return false;}
    virtual bool mouseMoveEvent(QPointF pt, qreal s, int flag){return false;}
    virtual bool mouseReleaseEvent(QPointF pt, qreal s, int flag){return false;}
public:
    virtual void paint(QPainter *painter){}
public:
    QYPixItem* pixItem;
};
typedef std::vector<QYPixHelper*> QYPixHelperVec;

class QYPixCircle:public QYPixHelper
{
public:
    explicit QYPixCircle(QObject *parent=0):QYPixHelper(parent){center=QPointF(0.5,0.5); radius=0.5;}
    QYPixCircle(QPointF c, qreal r,QObject *parent=0):QYPixHelper(parent){center=c; radius=r;}
    virtual ~QYPixCircle(){}

public:
    virtual void paint(QPainter *painter);

public:
    QPointF center;
    qreal   radius;
};
typedef std::vector<QPointF> PointFVec;
class QYPixPoint:public QYPixHelper
{
public:
   explicit QYPixPoint(QObject *parent=0):QYPixHelper(parent){}
    virtual ~QYPixPoint(){}

public:
    virtual void paint(QPainter *painter);

public:
    PointFVec pts;
};

///
/// \brief 图片显示Item
///
class QYPixItem : public QGraphicsItem  //继承自图元类,实现自定义的图元，，，qt预置的有直线，椭圆，文本图元，矩形图元等
{
public:
    QYPixItem(QPixmap *pixmap); //构造函数初始化了变量pix

public:
    virtual QRectF boundingRect() const;  //实现自己的boundingRect 图元边界方法，完成以图元坐标系为基础增加两个像素点的冗余的工作
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //重画图形函数
    virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);


public:
    void Reset();
    void Move(qreal dx, qreal dy);
    void Scale(qreal s);
    void SetScaleMin(qreal smin);
    void addHelper(QYPixHelper* helper);
    void removeHelper(QYPixHelper* helper);
    qreal getScale()const;

    void UpdateView(bool pow=false);
public:
    QGraphicsView* view;
private:
    void Scale(qreal s, const QPointF& pos);
private:
    QPixmap     pix;    //作为图元显示的图片

    qreal       m_fScaleMin;
    qreal       m_fScale;
    QPointF     m_posScale;

    bool        m_isMove;
    bool        m_bLBDown;
    QPointF     m_posLastMove;

    QYPixHelperVec  pixHelperVec;

    QImage      imgCross;

public:
    QPointF     downPos;
    bool        showDownPos;
};

class QYPixViewer : public QWidget
{
    Q_OBJECT

public:
    explicit QYPixViewer(QWidget *parent = 0);
    ~QYPixViewer();

public:
    void fromImage(const QImage &image);
    void openImageFile(const QString& filepath);
    void closeImage();
    void reset();
    void addHelper(QYPixHelper* helper);
    void removeHelper(QYPixHelper* helper);
    QYPixItem* GetPixItem();
protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent *event);
private:
    void updateViewRect();

private:
    QYPixItem       *pixItem;       //自定义的图元类
    QGraphicsScene  *gpScene;       //场景
    QGraphicsView   *gpView;
};
inline QYPixItem* QYPixViewer::GetPixItem(){
    return pixItem;
}
inline qreal QYPixItem::getScale()const{
    return m_fScale;
}
#endif // PIXITEM_H
