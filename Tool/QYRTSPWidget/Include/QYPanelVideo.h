#ifndef QYPANELVIDEO_H
#define QYPANELVIDEO_H

#include <QWidget>
#include <QList>
#include "QYVideoWidget.h"

class QYPanelVideo : public QWidget
{
    Q_OBJECT
    //Q_PROPERTY(int sizeLabVideo READ sizeLabVideo WRITE setSizeLabVideo)
public:
    explicit QYPanelVideo(QWidget *parent = 0);
    ~QYPanelVideo();

    //
    void setSizeLabVideo(const int& sizeLabVideo);
    void UpdateGeometry(int nRow, int nCol);
    void _UpdateGeometry();
    int row()const;
    int col()const;

    int numVideo()const;
    QYVideoWidget* at(int n);

    void select(int i);
    int curSel()const;

    void setFlagUI(int flagUI);
    void setIndexStart(int nStart);
signals:
    void sigSel(int sel);

protected:
    virtual void paintEvent(QPaintEvent* event);
private:
    void _CreateVideo();
    void _UpdateGeometry(int nRow, int nCol);
private:
    void _InitAttr(void);

private slots:
    void oClickedVideoWidget(QWidget* wd);

private:
    QList<QYVideoWidget*> mListVideo;
    //
    int m_sizeLabVideo;
    int m_curSel;
    int m_lastSel;

    int m_nCol;
    int m_nRow;
    int m_FlagUI;
    int m_nStart;
};

inline void QYPanelVideo::_InitAttr(void){
    m_sizeLabVideo  = 0;
    m_curSel        = -1;
    m_lastSel       = m_curSel;
    m_nCol          = 0;
    m_nRow          = 0;
    m_FlagUI        = 0;
    m_nStart        = 0;
}
inline int QYPanelVideo::curSel()const{
    return m_curSel;
}
inline int QYPanelVideo::row()const{
    return m_nRow;
}
inline int QYPanelVideo::col()const{
    return m_nCol;
}
inline void QYPanelVideo::setIndexStart(int nStart){
    m_nStart = nStart;
}
#endif // QYPANELVIDEO_H
