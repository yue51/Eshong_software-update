#ifndef QYVIDEOSHOW_H
#define QYVIDEOSHOW_H

#include <QWidget>

namespace Ui {
class QYVideoShow;
}

class QYVideoShow : public QWidget
{
    Q_OBJECT

public:
    explicit QYVideoShow(QWidget *parent = 0);
    ~QYVideoShow();

protected:
//    virtual void showEvent(QShowEvent *);
//    virtual void focusInEvent(QFocusEvent *);
//    virtual void focusOutEvent(QFocusEvent *);
    virtual void paintEvent(QPaintEvent* event);

//    virtual void mouseMoveEvent(QMouseEvent *e);
//    virtual void mousePressEvent(QMouseEvent *e);
//    virtual void mouseReleaseEvent(QMouseEvent *e);


private:
    Ui::QYVideoShow *ui;
};

#endif // QYVIDEOSHOW_H
