#ifndef QYVIDEOWIDGET_H
#define QYVIDEOWIDGET_H

#include <QWidget>
#include <QVector2D>

namespace Ui {
class QYVideoWidget;
}
class QPropertyAnimation;
class QPushButton;

class QYPixCircle;
class QYPixPoint;
class QYPixViewer;

class QYVideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QYVideoWidget(QWidget *parent = 0);
    ~QYVideoWidget();

    QWidget* showWidget();
    QWidget* rootWidget();

    void onShowVideo(int w, int h, int aspect);
    void _UpdatePosSize();

    QYPixViewer* showPixTool(const QImage &image);
    QYPixViewer* hidePixTool();

    void showCross(bool show);
    void showHotBar(bool show);
    void enableTrack(bool enable);
    void enableClick(bool enable);
    void enableWheel(bool enable);

signals:
    void sigClicked(QWidget*);
    void sigTrackClicked(QWidget*, QVector2D uv);
    void sigTrackRect(QWidget*, QVector2D uvStart, QVector2D uvEnd);
    void sigTrackWheel(QWidget*, qreal fTurn);
    void sigDoubleClicked();
protected:
    virtual void paintEvent(QPaintEvent* event);

    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);

    virtual void resizeEvent(QResizeEvent *e);

    virtual void enterEvent(QEvent *e);
    virtual void leaveEvent(QEvent *e);

private slots:
    //void oSigHotBarClicked(int butNo, QPushButton* but);

    void on_spin_dr_valueChanged(double arg1);

    void on_spin_dx_valueChanged(double arg1);

    void on_spin_dy_valueChanged(double arg1);

    void on_butCtrlShow_clicked();
private:

    void oChanagedLR();
private:
    virtual bool eventFilter(QObject *, QEvent *);
private:
    Ui::QYVideoWidget *ui;
    bool mbDown;
    int mVWidth;
    int mVHeight;
    int mAspect;

    int lastX;
    int lastY;
    int lastW;
    int lastH;

    QYPixCircle* pixCircle;
    QYPixPoint*  pixPoint;
    QYPixViewer* pixViewer;

    bool mEnableTrack;
    bool mEnableClick;
    bool mEnableWheel;

    //QVector2D mDownPos;
    QPoint mLastDownPt;
    bool mDownLB;

    QPropertyAnimation* m_pAniwd_Ctrl;
public:
    qreal        lr[3];
    qreal        ag;
};

#endif // QYVIDEOWIDGET_H
