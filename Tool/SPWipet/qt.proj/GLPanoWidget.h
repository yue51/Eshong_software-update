#ifndef GLPANOWIDGET_H_
#define GLPANOWIDGET_H_

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QQueue>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class QReadWriteLock;
class yuvData;
class GLPanoWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLPanoWidget(QWidget *parent = 0);
    ~GLPanoWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
//  QSize sizeHint() const Q_DECL_OVERRIDE;

    void SetParams(const qreal *lr, qreal ag);

    void TurnViewType(int type);

    bool StreamIn(char* pBuf, long nSize, int w, int h);
private:
    void _TurnShowType(int viewType, int w, int h, float rot=0.0, float targetFov=45.0);
public slots:
    void cleanup();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    //void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    //bool event(QEvent *e) Q_DECL_OVERRIDE;
private:
    void setupVertexBuffer();
    void drawVideoQuad();
    void setFrameToTexture(int w, int h, const char* y, const char* u, const char* v);
    void prepareFramebuffer(int width, int height) ;
    void updateFramebuffer(int width, int height);
    void RenderFBO();
    void ClearDataQueue();

    static QPointF normalDir(QPointF dir);
    static float angleDir(QPointF dirA, QPointF dirB);
private:
    void _InitAttr();
private:
    float lr[3];
    float ag;
 //   void setupVertexAttribs();

//    bool m_core;
//    int m_xRot;
//    int m_yRot;
//    int m_zRot;
//    QPoint m_lastPos;
//    Logo m_logo;
//    QOpenGLVertexArrayObject m_vao;
//    QOpenGLBuffer m_logoVbo;
//    QOpenGLBuffer* m_logoibo;
    QOpenGLShaderProgram *m_program;

    int videoMatWorldUniHandle;
    int videoTexYUVuniHandle[3];

    long glHandle;

    float squareCoords[20];

    unsigned short drawOrder[6];
    int numPri;

    QMatrix4x4 videoMatWorld;

    GLuint vertexBufferHandle;
    GLuint indexBufferHandle;

    GLuint videoPosHandle;
    GLuint videoTexCoordHandle;

    GLuint texIDYUV[3];

    GLuint mOffscreenTexture;
    GLuint mFramebuffer;

    int mFramebufferWidth;
    int mFramebufferHeight;
    int mPower;

    int videoWidth;
    int videoHeight;
    float videoAspect;

    bool m_bInit;

    int viewW;
    int viewH;
    //int viewRadius;

    int viewType;

    QQueue<yuvData*> dataQueue;

    typedef struct _ViewInfo{
        bool show;
        int  l;
        int  t;
        int  w;
        int  h;
        _ViewInfo(){
            show = false;
            l = 0;
            t = 0;
            w = 2;
            h = 2;
        }
    }ViewInfo;
    ViewInfo mViewInfo[9];
    int mViewNo;
private:
    bool mbDown;
    bool mFirstMove;
    int lastMoveX;
    int lastMoveY;

    bool mFirstWheel;

    QPointF m_panCenterPt;
    QPointF m_panLastCenterDir;

    QReadWriteLock* rwLock;
};

#endif
