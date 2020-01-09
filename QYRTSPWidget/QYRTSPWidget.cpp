#include "QYRTSPWidget.h"
#include <QLabel>
#include <QtGui/QPainter.h>

#include <math.h>
#include <QVector2D>
#include <QVector3D>

#include "QYFFMpeg.h"

#include "QYVideoWidget.h"

#include <QApplication>
#define MAX_FRAME   100
#define MIN_FRAME   10

QYRTSPWidget::QYRTSPWidget(QWidget *parent, Qt::WindowFlags f)
  : QWidget(parent, f)//QWidget(parent, 0, f)
{
    _InitAttr();

    m_pLab = new QLabel(this);
    m_pLab->setVisible(false);

    pp = new QYVideoWidget(this);
    pp->setGeometry(0,0,100,100);

//    m_pFFMpeg = new QYFFMpeg(this);
//    connect(m_pFFMpeg, SIGNAL(ffStream(void*, int, int, unsigned int)), this, SLOT(FFStream(void*, int, int, unsigned int)));
}
QYRTSPWidget::~QYRTSPWidget()
{
    _Release();
}
void QYRTSPWidget::_Release(void)
{
    if(0 != m_pFFMpeg){
        m_pFFMpeg->setParent(0);
        delete m_pFFMpeg;
        m_pFFMpeg = 0;
    }
}
bool QYRTSPWidget::play(const QString& url)
{
    if(url.size() < 1){
        if(0 != m_pFFMpeg){
            m_pFFMpeg->play();
        }
        return true;
    }

    if(url == m_pFFMpeg->Url()){
        if(0 != m_pFFMpeg){
            m_pFFMpeg->play();
        }
        return true;
    }

    if(0 != m_pFFMpeg){
        m_pFFMpeg->stop();
    }

    m_pFFMpeg->preload(url);
    m_pFFMpeg->play();
    return true;
}

bool QYRTSPWidget::pause()
{
    if(0 != m_pFFMpeg){
        m_pFFMpeg->pause();
    }
    return false;
}

bool QYRTSPWidget::stop()
{
    if(0 != m_pFFMpeg){
        m_pFFMpeg->stop();
    }
    return false;
}


QString QYRTSPWidget::title() const {
    return m_title;
}
void QYRTSPWidget::setTitle(const QString& title){
    m_title = title;
    if(m_title.size() < 1){
        m_pLab->setVisible(false);
        return;
    }
    m_pLab->setVisible(false);
    m_pLab->setText(m_title+"02");
    m_pLab->setVisible(true);
    m_pLab->move(0, 0);

    pp->move(80,0);
}
QString QYRTSPWidget::url() const{
    if(0 != m_pFFMpeg){
        return m_pFFMpeg->Url();
    }
    return "";
}
void QYRTSPWidget::turnMoveable(bool enable)
{
    //m_pHandler->setActive(enable);
}
void QYRTSPWidget::FFStream(void* pData, int videoW, int videoH, unsigned int format){

    mutex.lock();
    mFrameQue.push_back(new QImage((uchar*)pData, videoW, videoH, (QImage::Format)format));
    mutex.unlock();
}

//void QYRTSPWidget::initializeGL()
//{
//    makeObject();

//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_TEXTURE_2D);
//}

//void QYRTSPWidget::paintGL()
//{
//    QMetaObject::invokeMethod(this, "updateGL", Qt::QueuedConnection);
//    qglClearColor(clearColor);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, -1.0f);
//    glScalef(1.0f, 1.0f, 1.0f);

//    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
//    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//    //
//    if(0 != m_pFFMpeg)
//    {
//      mutex.lock();
//      int ns = mFrameQue.size();
//      qWarning("FFStream out %d",ns);
//      if(1 < ns){
//          QImage* const &t = mFrameQue.at(0);
//          if(t->width() > 0){
//              glBindTexture(GL_TEXTURE_2D, texID);
//              glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t->width(),t->height(),
//                               0, GL_RGB, GL_UNSIGNED_BYTE,t->constBits());
//          }
//          delete t;
//          mFrameQue.pop_front();
//      }
//      mutex.unlock();
//    }

//    glBindTexture(GL_TEXTURE_2D, texID);
//    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//    //this->swapBuffers();
//}

//void QYRTSPWidget::resizeGL(int width, int height)
//{
//    glViewport(0,0,width, height);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-0.5, +0.5, +0.5, -0.5, 0.1, 15.0);
//    glMatrixMode(GL_MODELVIEW);
//}

//void QYRTSPWidget::makeObject()
//{
//    static const int coords[4][3] = {
//        { +1, -1, -1 },
//        { -1, -1, -1 },
//        { -1, +1, -1 },
//        { +1, +1, -1 } };

//    texID = bindTexture(QImage(":/QYRTSPWidget/bg"), GL_TEXTURE_2D);

//    for (int j = 0; j < 4; ++j) {
//        texCoords.append(QVector2D(j == 0 || j == 3, j == 2 || j == 3));
//        vertices.append(QVector3D(0.5 * coords[j][0], 0.5 * coords[j][1], 0.5 * coords[j][2]));
//    }
//}
