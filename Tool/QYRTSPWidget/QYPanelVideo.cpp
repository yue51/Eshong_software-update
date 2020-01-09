#include "QYPanelVideo.h"
#include <qmath.h>
#include <QVariant>
#include <QtGui/QPainter.h>
#include <QtWidgets/qstyleoption.h>

#include "../../ComTool.h"
QYPanelVideo::QYPanelVideo(QWidget *parent) : QWidget(parent)
{
    _InitAttr();
}
QYPanelVideo::~QYPanelVideo()
{

}
void QYPanelVideo::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}
//
void QYPanelVideo::setSizeLabVideo(const int& sizeLabVideo){if(sizeLabVideo < 1){return;} m_sizeLabVideo = sizeLabVideo; _CreateVideo();}

void QYPanelVideo::UpdateGeometry(int nRow, int nCol)
{
    _UpdateGeometry(nRow, nCol);
}
void QYPanelVideo::_UpdateGeometry()
{
    _UpdateGeometry(m_nRow, m_nCol);
}
int QYPanelVideo::numVideo()const
{
    return mListVideo.size();
}
QYVideoWidget* QYPanelVideo::at(int n)
{
    if(n < 0 || mListVideo.size() <= n){
        return 0;
    }
    return mListVideo.at(n);
}
void QYPanelVideo::setFlagUI(int flagUI)
{
    if(flagUI == m_FlagUI){return;}
    m_FlagUI = flagUI;
}
void QYPanelVideo::select(int sel)
{
    static const QString ssDown = QString().sprintf("rgba(0,255,0,255)");
    static const QString ssUp = QString().sprintf("rgba(220,220,220,100)");

    int nSize = mListVideo.size();
    if(nSize < 1 || sel == m_curSel){
        return;
    }
    if(sel<0 || sel>= nSize){
        m_lastSel = m_curSel;
        m_curSel = -1;
        emit sigSel(m_curSel);

        if(1 == m_FlagUI){return;}
        if(m_lastSel>=0 && m_lastSel< nSize){
            QYVideoWidget* wd = mListVideo[m_lastSel];
            ComTool::Tool::updateSS_brColor(wd, ssUp);
        }

        return;
    }
    m_lastSel = m_curSel;
    m_curSel = sel;

    emit sigSel(m_curSel);
    if(1 == m_FlagUI){return;}

    if(m_lastSel>=0 && m_lastSel< nSize){
        QYVideoWidget* wd = mListVideo[m_lastSel];
        ComTool::Tool::updateSS_brColor(wd, ssUp);
    }

    {
        QYVideoWidget* wd = mListVideo[m_curSel];
        ComTool::Tool::updateSS_brColor(wd, ssDown);
    }
}
void QYPanelVideo::_CreateVideo()
{
    int nSize = mListVideo.size();
    if(m_sizeLabVideo <= nSize){
        return;
    }
    for(int i=nSize; i<m_sizeLabVideo; ++i){
        mListVideo.push_back(new QYVideoWidget(this));
        QYVideoWidget* wd = mListVideo[i];
        wd->setObjectName(QString().sprintf("labVideo_%d", i));
        QVariant qyIndex = QVariant((int)(mListVideo.size()-1));
        wd->setProperty(ComTool::Def::PRO_QYINDEX, qyIndex);
        wd->setProperty(ComTool::Def::PRO_QYINDEXSTART, QVariant((int)m_nStart));
        connect(wd, SIGNAL(sigClicked(QWidget*)), this, SLOT(oClickedVideoWidget(QWidget*)));
    }
}
void QYPanelVideo::_UpdateGeometry(int nRow, int nCol)
{
    int nSize = mListVideo.size();
    if(nSize < 1){
        return;
    }
    qreal dl= 1;
    qreal dt= 1;
    qreal w = this->width()-dl*2;
    qreal h = this->height()-dt*2;

    qreal divW = w / nCol;
    qreal divH = h / nRow;

    //qWarning("labVideo Resize w:%f h:%f", divW, divH);

    int k = 0;
    for(int j=0; j<nRow; ++j){
        for(int i=0; i<nCol; ++i){
            k = j*nCol+i;
            if(k>=nSize){
                break;
            }
            QYVideoWidget* pWdVideo = mListVideo[k];
            //ComTool::Tool::ReSizeAny(divW, divH, pWdVideo);
            pWdVideo->setGeometry(QRect(dl+divW*i, dt+divH*j, divW, divH));
            pWdVideo->setVisible(true);
        }
    }
    for(int i=k+1; i<nSize; ++i){
        QYVideoWidget* pWdVideo = mListVideo[i];
        pWdVideo->setVisible(false);
    }
    m_nCol = nCol;
    m_nRow = nRow;
}

void QYPanelVideo::oClickedVideoWidget(QWidget* wd)
{
    int i = wd->property(ComTool::Def::PRO_QYINDEX).value<int>();
    select(i);
}
