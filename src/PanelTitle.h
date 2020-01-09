#ifndef PANELTITLE_H
#define PANELTITLE_H

#include <QWidget>

namespace Ui {
class PanelTitle;
}
///\brief Title页
class PanelTitle : public QWidget
{
    Q_OBJECT
    
public:
    explicit PanelTitle(QWidget *parent = 0);
    ~PanelTitle();
public:
    void TurnSmall(int w);
protected:
    virtual void paintEvent(QPaintEvent* event);

    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private slots:
    void oTimer();
    void oChanagedSize(bool bMax);

    void on_butClose_clicked();
 //   void on_butLogo_clicked();
    void on_butMin_clicked();
 //   void on_butMax_clicked();

    void oChanagedPage(int curPage);
    void oChanagedShow(int curShow, int flag);
    void oChanagedShowUserLeft(int modeUserLeft);
    void oChanagedShowBKSubPage(int subPage);

    void on_butA_clicked();
    void on_butB_clicked();
    void on_butC_clicked();

    void on_butShow11_clicked();
    void on_butShow22_clicked();
    void on_butShow33_clicked();
    void on_butShow44_clicked();
    void on_butShow55_clicked();


    void on_butCloseCamera_clicked();
    void on_butFullScreen_clicked();

    void on_butCloseCamera_QQ_clicked();
    void on_butFullScreen_QQ_clicked();

    void on_butB_A_clicked();
    void on_butB_B_clicked();

    void on_butAbout_clicked();
private:
    Ui::PanelTitle *ui;

    typedef QList<QWidget*> ListPanel;
    ListPanel mPageList;
    ListPanel mButShowList;
    ListPanel mButShowList_BK;

    QPoint m_pointStart;
    bool mbDown;
};

#endif // PANELTITLE_H
