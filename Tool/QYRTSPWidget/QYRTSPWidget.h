#ifndef QYRTSPWIDGET_H
#define QYRTSPWIDGET_H

#include <QGLWidget>
#include <QList>
#include <QThread>
#include <QMutex>

class QLabel;
class QYFFMpeg;
class QWidgetResizeHandler;
class QYRTSPWidget  : public QWidget //public QGLWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)

public:
    QYRTSPWidget(QWidget *parent=0, Qt::WindowFlags f=0);
    virtual ~QYRTSPWidget();

public:
    bool play(const QString& url=QString(""));
    bool pause();
    bool stop();

    //
    QString title() const;
    void setTitle(const QString& title);

    QString url() const;

    void turnMoveable(bool enable);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private slots:
    void FFStream(void* pData, int videoW, int videoH, unsigned int format);
private:
    void _InitAttr(void);
    void _Release(void);

private:
    void makeObject();

    QColor clearColor;
    GLuint texID;
    QVector<QVector3D> vertices;
    QVector<QVector2D> texCoords;

private:
     QYFFMpeg*              m_pFFMpeg;
//     QWidgetResizeHandler*  m_pHandler;
     QLabel*                m_pLab;
     QWidget* pp;
     QString                m_title;
     QList<QImage*>         mFrameQue;
     QMutex                 mutex;
};

inline void QYRTSPWidget::_InitAttr(void)
{
    m_pFFMpeg           = 0;
    //m_pHandler          = 0;
    m_pLab              = 0;

    clearColor          = Qt::yellow;
    texID               = 0;
}

#endif // QYRTSPWIDGET_H
