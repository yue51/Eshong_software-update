#include "GLPanoWidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

#include <QtGui/QPainter.h>
#include <QQueue>
#include <QStyleOption>
#include <QWindow>
#include <string>
#include <QReadWriteLock>

#include "FullSceneAPI.h"
#include "FullSceneListener.h"


static const char* vertexShaderCodeVideoYUV = "attribute vec4 vPosition;\n"
                "attribute vec4 vTexCoordinate;\n"
                "uniform mat4  u_MatWorld;\n"
                "varying vec2 v_Tex;\n"
                "void main() {\n"
                "   v_Tex = vTexCoordinate.xy;\n"
                "   gl_Position = u_MatWorld*vPosition;\n"
                "}\n";

static const char* fragmentShaderCodeVideoYUV = "varying highp vec2 v_Tex;\n"
            " uniform sampler2D s_texture_y;\n"
            " uniform sampler2D s_texture_u;\n"
            " uniform sampler2D s_texture_v;\n"
            " void main()\n"
            " {\n"
            "     highp float y = texture2D(s_texture_y, v_Tex).r;\n"
            "     highp float u = texture2D(s_texture_u, v_Tex).r - 0.5;\n"
            "     highp float v = texture2D(s_texture_v, v_Tex).r - 0.5;\n"
            "     highp float r = y +             1.402 * v;\n"
            "     highp float g = y - 0.344 * u - 0.714 * v;\n"
            "     highp float b = y + 1.772 * u;   \n"
            "     gl_FragColor = vec4(b,g,r,1.0);\n"
            " }\n";

//static const char* fragmentShaderCodeVideoYUV = "varying highp vec2 v_Tex;\n"
//            " uniform sampler2D s_texture_y;\n"
//            " uniform sampler2D s_texture_u;\n"
//            " uniform sampler2D s_texture_v;\n"
//            " void main()\n"
//            " {\n"
//            "     gl_FragColor = texture2D(s_texture_y, v_Tex);\n"
//            " }\n";


class WinListener: public FS::FullSceneListener
{
public:
    WinListener(){}
    virtual ~WinListener(){}
};

class QYApi{
  public:
    QYApi(){}
    ~QYApi(){}
public:
    static void MoveCameraStep(long handle, float _dPitch, float _dYaw, float _dRoll)
    {
        float fPitch;
        float fYaw;
        float fRoll;
        FS::GetCameraParam(handle, &fPitch, &fYaw, &fRoll);
        float flag = (FS::PSTO_SPHERE_IN == FS::GetShowType(handle)) ? -1.0f : +1.0f;
        fPitch += -flag*_dPitch;
        fYaw   += flag*_dYaw;
        fRoll  += _dRoll;
        FS::MoveCamera(handle, fPitch, fYaw, fRoll);
    }
    static void MoveCameraEx(long handle, float _fPitch, float _fYaw, float _fRoll)
    {
        float flag = -1.0f;
        FS::MoveCamera(handle, flag*_fPitch, flag*_fYaw, _fRoll);
    }
    static void SetCameraPitchMinMax(long handle, float _fMin, float _fMax)
    {
        float fPitchMin = 0.0f;
        float fPitchMax = 0.0f;
        float fYawMin	= 0.0f;
        float fYawMax	= 0.0f;
        float fRollMin	= 0.0f;
        float fRollMax	= 0.0f;
        FS::GetCameraParamLimited(handle, &fPitchMin, &fPitchMax, &fYawMin, &fYawMax, &fRollMin, &fRollMax);
        FS::SetCameraParamLimited(handle, _fMin, _fMax, fYawMin, fYawMax, fRollMin, fRollMax);
    }
    static void SetCameraRollMinMax(long handle, float _fMin, float _fMax)
    {
        float fPitchMin = 0.0f;
        float fPitchMax = 0.0f;
        float fYawMin	= 0.0f;
        float fYawMax	= 0.0f;
        float fRollMin	= 0.0f;
        float fRollMax	= 0.0f;
        FS::GetCameraParamLimited(handle, &fPitchMin, &fPitchMax, &fYawMin, &fYawMax, &fRollMin, &fRollMax);
        FS::SetCameraParamLimited(handle, fPitchMin, fPitchMax, fYawMin, fYawMax, _fMin, _fMax);
    }
    static float GetCameraPitch(long handle)
    {
        float flag   = -1.0f;
        float fPitch = 0.0f;
        FS::GetCameraParam(handle, &fPitch, 0, 0);
        return flag*fPitch;
    }
    static float GetCameraYaw(long handle)
    {
        float flag   = -1.0f;
        float fYaw = 0.0f;
        FS::GetCameraParam(handle, 0, &fYaw, 0);
        return flag*fYaw;
    }
    static float GetCameraRoll(long handle)
    {
        float fRoll = 0.0f;
        FS::GetCameraParam(handle, 0, 0, &fRoll);
        return fRoll;
    }
    static void _ChangeShowType(long handle, int nType)
    {
        FS::SetShowType(handle, nType);
        if(1 == nType){
            FS::SetInv(handle, true);
            MoveCameraEx(handle, 90.0f, 0.0f, 0.0f);
        }else{
            MoveCameraEx(handle, 0.0f, 0.0f, 0.0f);
        }
    }
    static int NUM;

};
int QYApi::NUM = 9;


class yuvData{
public:
    int w;
    int h;
    char* y;
    char* u;
    char* v;
public:
    yuvData(){
        w = 0;
        h = 0;
        y = 0;
        u = 0;
        v = 0;
    }
    yuvData(int _w, int _h, char* buf, long nLen){
        fiilData(_w, _h, buf, nLen);
    }
    void fiilData(int _w, int _h, char* buf, long nLen){
        w = _w;
        h = _h;
        int nL = 0;
        int nS =  w*h;
        y = new char[nS];
        memcpy(y, buf+nL, nS);

        nL += nS;
        nS =  (w/2)*(h/2);
        u = new char[nS];
        memcpy(u, buf+nL, nS);

        nL += nS;
        nS =  (w/2)*(h/2);
        v = new char[nS];
        memcpy(v, buf+nL, nS);
    }
    void clear(){
        qWarning()<<"~yuv: ";
        if(0 != y){delete[] y; y=0;}
        if(0 != u){delete[] u; u=0;}
        if(0 != v){delete[] v; v=0;}
    }
    ~yuvData(){
       clear();
    }
private:
    int t;
};
GLPanoWidget::GLPanoWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_program(0)
{
    _InitAttr();
    rwLock = new QReadWriteLock();
}

GLPanoWidget::~GLPanoWidget()
{
    ClearDataQueue();

    cleanup();

    delete rwLock;
    rwLock = 0;
}
void GLPanoWidget::ClearDataQueue()
{
    qWarning()<<"GLPanoWidget::ClearDatas: "<<dataQueue.length();
    while(dataQueue.length() > 0){
        rwLock->lockForRead();
        yuvData* yuv = dataQueue.dequeue();
        rwLock->unlock();
        if(0 != yuv){
            delete yuv;
            yuv = 0;
        }
    }
}
QSize GLPanoWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

//QSize GLPanoWidget::sizeHint() const
//{
//    return QSize(400, 400);
//}

void GLPanoWidget::cleanup()
{
    qWarning()<<"GLPanoWidget::cleanup()";
    m_bInit = false;

    makeCurrent();

    if(0 != m_program){
        delete m_program;
        m_program = 0;
    }

    glDeleteBuffers(1, &vertexBufferHandle);
    vertexBufferHandle = 0;

    glDeleteBuffers(1, &indexBufferHandle);
    indexBufferHandle = 0;

    glDeleteTextures(3, texIDYUV);
    texIDYUV[0] = 0; texIDYUV[1] = 0; texIDYUV[2] = 0;

    glDeleteTextures(1, &mOffscreenTexture);
    mOffscreenTexture = 0;

    glDeleteFramebuffers(1, &mFramebuffer);
    mFramebuffer = 0;
    mFramebufferWidth = 1024;
    mFramebufferHeight = 1024;

    FS::Destroy(glHandle);
    glHandle = 0;
    FS::FullSceneListener* &pFSListener = FS::FullSceneListener::GetSingleton();
    if(0 != pFSListener){
        delete pFSListener;
        pFSListener = 0;
    }

    doneCurrent();

    viewW 	= 0;
    viewH	= 0;
}

void GLPanoWidget::_InitAttr()
{
    {
        float * sq = squareCoords;
        float s = 1.0f;
        int j = 0;
        sq[5*j+0]= -s; sq[5*j+1]= +s; sq[5*j+2]= 0.0f; sq[5*j+3]= 1.0f; sq[5*j+4]= 0.0f;// top left
        j = 1;
        sq[5*j+0]= -s; sq[5*j+1]= -s; sq[5*j+2]= 0.0f; sq[5*j+3]= 1.0f; sq[5*j+4]= 1.0f;// bottom left
        j = 2;
        sq[5*j+0]= +s; sq[5*j+1]= -s; sq[5*j+2]= 0.0f; sq[5*j+3]= 0.0f; sq[5*j+4]= 1.0f;// bottom right
        j = 3;
        sq[5*j+0]= +s; sq[5*j+1]= +s; sq[5*j+2]= 0.0f; sq[5*j+3]= 0.0f; sq[5*j+4]= 0.0f;// top right
    }

    {
        unsigned short* d = drawOrder;
        int j = 0;
        d[3*j+0] = 0; d[3*j+1] = 1; d[3*j+2] = 2;
        j = 1;
        d[3*j+0] = 0; d[3*j+1] = 2; d[3*j+2] = 3;
    }

    numPri = 6;

    vertexBufferHandle = 0;
    indexBufferHandle = 0;

    videoPosHandle = 0;
    videoTexCoordHandle =  0;

    texIDYUV[0] = 0; texIDYUV[1] = 0; texIDYUV[2] = 0;

    glHandle = 0;

    mOffscreenTexture = 0;
    mFramebuffer = 0;

    mFramebufferWidth = 1024;
    mFramebufferHeight = 1024;

    videoWidth  = 640;
    videoHeight = 480;
    videoAspect = videoWidth*1.0/videoHeight;

    m_bInit = false;

    viewW 	= 0;
    viewH	= 0;
    //viewRadius  = 0;

    viewType = 5;//5;

    mbDown = false;
    mFirstMove = true;
    mFirstWheel= true;
    lastMoveX = 0;
    lastMoveY = 0;

    mPower = false;

    lr[0] = lr[1] = lr[2] = 0.5;
    ag = 180.0;
}

void GLPanoWidget::setupVertexBuffer()
{
    glGenBuffers(1, &vertexBufferHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*20, squareCoords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &indexBufferHandle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*6, drawOrder, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLPanoWidget::drawVideoQuad()
{
    // Attribute
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
    glEnableVertexAttribArray(videoPosHandle);
    glVertexAttribPointer(videoPosHandle, 3, GL_FLOAT, GL_FALSE, 20, 0);
    glEnableVertexAttribArray(videoTexCoordHandle);
    glVertexAttribPointer(videoTexCoordHandle, 2, GL_FLOAT, GL_FALSE, 20, reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
    glDrawElements(GL_TRIANGLES, numPri,GL_UNSIGNED_SHORT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(videoPosHandle);
    glDisableVertexAttribArray(videoTexCoordHandle);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLPanoWidget::setFrameToTexture(int w, int h, const char* y, const char* u, const char* v)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (0 == texIDYUV[0]){
        glGenTextures(3, texIDYUV);
    }

    for (int i = 0; i < 3; ++i)
    {
        int nw = w;
        int nh = h;

        const char* p = y;
        if(1 == i){p=u; nw=w/2; nh=h/2;}
        else if(2 == i){p=v; nw=w/2; nh=h/2;}

        //
        glBindTexture(GL_TEXTURE_2D, texIDYUV[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, nw, nh, 0,
                GL_LUMINANCE, GL_UNSIGNED_BYTE, p);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

}

void GLPanoWidget::prepareFramebuffer(int width, int height) {

    // Create a texture object and bind it.  This will be the color buffer.
    glGenTextures(1, &mOffscreenTexture);
    glBindTexture(GL_TEXTURE_2D, mOffscreenTexture);
    // Create texture storage.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, 0);

    // Set parameters.  We're probably using non-power-of-two dimensions, so
    // some values may not be available for use.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    // Create framebuffer object and bind it.
    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, mOffscreenTexture, 0);

    // See if GLES is happy with all this.
    int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        //throw new RuntimeException("Framebuffer not complete, status=" + status);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    mFramebufferWidth   = width;
    mFramebufferHeight  = height;
}
void GLPanoWidget::updateFramebuffer(int width, int height)
{
    if(width == mFramebufferWidth && height == mFramebufferHeight && !mPower){
        return;
    }
    mPower = false;
    mFramebufferWidth  = width;
    mFramebufferHeight = height;

    videoMatWorld.setToIdentity();
//    float f = +mFramebufferWidth*1.0f/mFramebufferHeight;
//    float fs = 1.0;
//    if(f>1.0){
//       fs = 1.0/f;
//    }
    //videoMatWorld.scale(f*fs, -fs);

    glBindTexture(GL_TEXTURE_2D, mOffscreenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFramebufferWidth, mFramebufferHeight, 0,GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    QString strParams = QString().sprintf("TXTID::%d||Width::%d||Height::%d",mOffscreenTexture, mFramebufferWidth, mFramebufferHeight);
    if(1==viewType){
        FS::MakeCurrent(glHandle, 0);
        FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
        FS::MakeCurrent(glHandle, 1);
        FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
    }else if(5 == viewType){
        FS::MakeCurrent(glHandle, 0);
        FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
    }else if(2 == viewType){
        for(int i=0; i<4; ++i){
            FS::MakeCurrent(glHandle, i);
            FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
        }
    }else if(3 == viewType){
        for(int i=0; i<5; ++i){
            FS::MakeCurrent(glHandle, i);
            FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
        }
    }else if(4 == viewType){
        for(int i=0; i<2; ++i){
            FS::MakeCurrent(glHandle, i);
            FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
        }
    }else if(6 == viewType){
        for(int i=0; i<4; ++i){
            FS::MakeCurrent(glHandle, i);
            FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
        }
    }else if(7 == viewType){
        for(int i=0; i<7; ++i){
            FS::MakeCurrent(glHandle, i);
            FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
        }
    }else if(8 == viewType){
        for(int i=0; i<9; ++i){
            FS::MakeCurrent(glHandle, i);
            FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
        }
    }else if(9 == viewType){
        FS::MakeCurrent(glHandle, 0);
        FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
    }else if(10 == viewType){
        FS::MakeCurrent(glHandle, 0);
        FS::ChangeCurFScene(glHandle, strParams.toStdString().c_str());
    }
}

void GLPanoWidget::RenderFBO(){
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    glViewport(0, 0, mFramebufferWidth, mFramebufferHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    {
         m_program->bind();
         m_program->setUniformValue(videoMatWorldUniHandle, videoMatWorld);
         for (int i = 0; i < 3; ++i) {
             glActiveTexture(GL_TEXTURE0 + i);
             glBindTexture(GL_TEXTURE_2D, texIDYUV[i]);
             m_program->setUniformValue(videoTexYUVuniHandle[i], i);
         }
         drawVideoQuad();
         glBindTexture(GL_TEXTURE_2D, 0);
         m_program->release();
     }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void GLPanoWidget::initializeGL()
{
    qWarning("initializeGL");
    //connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLPanoWidget::cleanup);

    initializeOpenGLFunctions();
    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(cleanup()), Qt::DirectConnection);

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderCodeVideoYUV);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderCodeVideoYUV);
    m_program->link();
    m_program->bind();
    videoPosHandle          = m_program->attributeLocation("vPosition");
    videoTexCoordHandle     = m_program->attributeLocation("vTexCoordinate");

    videoMatWorldUniHandle  = m_program->uniformLocation("u_MatWorld");
    videoTexYUVuniHandle[0] = m_program->uniformLocation("s_texture_y");
    videoTexYUVuniHandle[1] = m_program->uniformLocation("s_texture_u");
    videoTexYUVuniHandle[2] = m_program->uniformLocation("s_texture_v");
    
    m_program->release();

    videoMatWorld.setToIdentity();
    setupVertexBuffer();
    //setFrameToTexture(0,0,0,0,0);
    prepareFramebuffer(640, 480);

    if (0 == texIDYUV[0]){
        glGenTextures(3, texIDYUV);
    }
    if(0){
        QImage img;
        img.load("assets/image/Top_220.jpg");
        QImage imgRGB = img.convertToFormat(QImage::Format_RGB888);
        for(int i =0; i<3; ++i)
        {
            glBindTexture(GL_TEXTURE_2D, texIDYUV[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgRGB.width(), imgRGB.height(), 0,
                    GL_RGB, GL_UNSIGNED_BYTE, imgRGB.bits());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
    }
    if(1){
        unsigned char y[16*16];
        unsigned char u[16*16];
        unsigned char v[16*16];
        memset(y, 0, 16*16);
        memset(u, 128, 16*16);
        memset(v, 128, 16*16);

        unsigned char* p[3] = {y,u,v};
        for(int i =0; i<3; ++i){
            glBindTexture(GL_TEXTURE_2D, texIDYUV[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 16, 16, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, p[i]);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
    }

    //FS
    FS::FullSceneListener::GetSingleton(new WinListener());
    glHandle = FS::InitializeEx("./assets/");
    FS::SetViewport(glHandle, 4, 4);
    FS::Render(glHandle);

    glClearColor(0, 0, 0, 1);

   // FS::ChangeCurFScene(glHandle, QString().sprintf("TXTID::%d||Width::%d||Height::%d",mOffscreenTexture, videoWidth, videoHeight).toStdString().c_str());
   // FS::ChangeCurFScene(glHandle, "IMGID::image/Top_220.jpg");
    for(int i=0; i<QYApi::NUM; ++i){
        FS::MakeCurrent(glHandle, i);
        FS::SetAg(glHandle, ag);
        FS::SetSr(glHandle, lr[0]);
        FS::SetDx(glHandle, lr[1]);
        FS::SetDy(glHandle, lr[2]);
        FS::SetPow(glHandle, true);
    }
    TurnViewType(viewType);

    updateFramebuffer(640, 480);
    RenderFBO();

    m_bInit = true;
}

void GLPanoWidget::SetParams(const qreal *plr, qreal _ag){
    lr[0] = plr[0];
    lr[1] = 1.0-plr[1];
    lr[2] = 1.0-plr[2];
    ag    = _ag;
//    FS::SetAg(glHandle, 220.0);
//    FS::SetSr(glHandle, lr[0]);
//    FS::SetDx(glHandle, lr[1]);
//    FS::SetDy(glHandle, 1.0-lr[2]);
//    FS::SetPow(glHandle, true);
    qDebug()<<lr[0]<<" "<<lr[1]<<" "<<lr[2]<<" "<<ag;
}
void GLPanoWidget::TurnViewType(int type){

    viewType = type;

    if(1 == viewType){
        float w1 = viewW*0.425;
        float t1 = (viewH - w1)*0.5;
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0; mViewInfo[0].t = t1; mViewInfo[0].w = w1; mViewInfo[0].h = w1;
        mViewInfo[1].show = true;
        mViewInfo[1].l = w1; mViewInfo[1].t = t1; mViewInfo[1].w = viewW-w1; mViewInfo[1].h = w1;
        for(int i=2; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(5 == viewType){
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0; mViewInfo[0].t = 0; mViewInfo[0].w = viewW; mViewInfo[0].h = viewH;
        for(int i=1; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(2 == viewType){
        float hW = viewW/2;
        float hH = viewH/2;
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0;     mViewInfo[0].t = 0;     mViewInfo[0].w = hW; mViewInfo[0].h = hH;
        mViewInfo[1].show = true;
        mViewInfo[1].l = hW;    mViewInfo[1].t = 0;     mViewInfo[1].w = hW; mViewInfo[1].h = hH;
        mViewInfo[2].show = true;
        mViewInfo[2].l = 0;     mViewInfo[2].t = hH;    mViewInfo[2].w = hW; mViewInfo[2].h = hH;
        mViewInfo[3].show = true;
        mViewInfo[3].l = hW;    mViewInfo[3].t = hH;    mViewInfo[3].w = hW; mViewInfo[3].h = hH;
        for(int i=4; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(3 == viewType){
        float w1 = viewW*0.425;
        float t1 = (viewH-w1)*0.5;
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0; mViewInfo[0].t = t1; mViewInfo[0].w = w1; mViewInfo[0].h = w1;

        float hW = (viewW-w1)/2;
        float hH = w1/2;
        mViewInfo[1].show = true;
        mViewInfo[1].l = w1+0;     mViewInfo[1].t = t1+0;     mViewInfo[1].w = hW; mViewInfo[1].h = hH;
        mViewInfo[2].show = true;
        mViewInfo[2].l = w1+hW;    mViewInfo[2].t = t1+0;     mViewInfo[2].w = hW; mViewInfo[2].h = hH;
        mViewInfo[3].show = true;
        mViewInfo[3].l = w1+0;     mViewInfo[3].t = t1+hH;    mViewInfo[3].w = hW; mViewInfo[3].h = hH;
        mViewInfo[4].show = true;
        mViewInfo[4].l = w1+hW;    mViewInfo[4].t = t1+hH;    mViewInfo[4].w = hW; mViewInfo[4].h = hH;
        for(int i=5; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(4 == viewType){
        float h1 = viewH*0.725;
        float h2 = viewH - h1;
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0; mViewInfo[0].t = 0;  mViewInfo[0].w = viewW; mViewInfo[0].h = h1;
        mViewInfo[1].show = true;
        mViewInfo[1].l = 0; mViewInfo[1].t = h1; mViewInfo[1].w = viewW; mViewInfo[1].h = h2;
        for(int i=2; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(6 == viewType){
        float hW = viewW/2;
        float hH = viewH/2;
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0;     mViewInfo[0].t = 0;     mViewInfo[0].w = hW; mViewInfo[0].h = hH;
        mViewInfo[1].show = true;
        mViewInfo[1].l = hW;    mViewInfo[1].t = 0;     mViewInfo[1].w = hW; mViewInfo[1].h = hH;
        mViewInfo[2].show = true;
        mViewInfo[2].l = 0;     mViewInfo[2].t = hH;    mViewInfo[2].w = hW; mViewInfo[2].h = hH;
        mViewInfo[3].show = true;
        mViewInfo[3].l = hW;    mViewInfo[3].t = hH;    mViewInfo[3].w = hW; mViewInfo[3].h = hH;
        for(int i=4; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(7 == viewType){
        float h1 = viewH*0.725;
        float h2 = viewH - h1;
        float hW = viewW/3;
        float hH = h1/2;
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0;     mViewInfo[0].t = 0;     mViewInfo[0].w = hW; mViewInfo[0].h = hH;
        mViewInfo[1].show = true;
        mViewInfo[1].l = hW;    mViewInfo[1].t = 0;     mViewInfo[1].w = hW; mViewInfo[1].h = hH;
        mViewInfo[2].show = true;
        mViewInfo[2].l = hW*2;  mViewInfo[2].t = 0;     mViewInfo[2].w = hW; mViewInfo[2].h = hH;

        mViewInfo[3].show = true;
        mViewInfo[3].l = 0;     mViewInfo[3].t = hH;    mViewInfo[3].w = hW; mViewInfo[3].h = hH;
        mViewInfo[4].show = true;
        mViewInfo[4].l = hW;    mViewInfo[4].t = hH;    mViewInfo[4].w = hW; mViewInfo[4].h = hH;
        mViewInfo[5].show = true;
        mViewInfo[5].l = hW*2;  mViewInfo[5].t = hH;    mViewInfo[5].w = hW; mViewInfo[5].h = hH;

        mViewInfo[6].show = true;
        mViewInfo[6].l = 0;  mViewInfo[6].t = h1;    mViewInfo[6].w = viewW; mViewInfo[6].h = h2;

        for(int i=7; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(8 == viewType){
        float hW = viewW/3;
        float hH = viewH/3;
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0;     mViewInfo[0].t = 0;     mViewInfo[0].w = hW; mViewInfo[0].h = hH;
        mViewInfo[1].show = true;
        mViewInfo[1].l = hW;    mViewInfo[1].t = 0;     mViewInfo[1].w = hW; mViewInfo[1].h = hH;
        mViewInfo[2].show = true;
        mViewInfo[2].l = hW*2;  mViewInfo[2].t = 0;     mViewInfo[2].w = hW; mViewInfo[2].h = hH;

        mViewInfo[3].show = true;
        mViewInfo[3].l = 0;     mViewInfo[3].t = hH;    mViewInfo[3].w = hW; mViewInfo[3].h = hH;
        mViewInfo[4].show = true;
        mViewInfo[4].l = hW;    mViewInfo[4].t = hH;    mViewInfo[4].w = hW; mViewInfo[4].h = hH;
        mViewInfo[5].show = true;
        mViewInfo[5].l = hW*2;  mViewInfo[5].t = hH;    mViewInfo[5].w = hW; mViewInfo[5].h = hH;

        mViewInfo[6].show = true;
        mViewInfo[6].l = 0;     mViewInfo[6].t = hH*2;  mViewInfo[6].w = hW; mViewInfo[6].h = hH;
        mViewInfo[7].show = true;
        mViewInfo[7].l = hW;    mViewInfo[7].t = hH*2;  mViewInfo[7].w = hW; mViewInfo[7].h = hH;
        mViewInfo[8].show = true;
        mViewInfo[8].l = hW*2;  mViewInfo[8].t = hH*2;  mViewInfo[8].w = hW; mViewInfo[8].h = hH;
    }else if(9 == viewType){
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0; mViewInfo[0].t = 0; mViewInfo[0].w = viewW; mViewInfo[0].h = viewH;
        for(int i=1; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }else if(10 == viewType){
        mViewInfo[0].show = true;
        mViewInfo[0].l = 0; mViewInfo[0].t = 0; mViewInfo[0].w = viewW; mViewInfo[0].h = viewH;
        for(int i=1; i<QYApi::NUM; ++i){
            mViewInfo[i].show = false;
            mViewInfo[i].l = 0; mViewInfo[i].t = 0; mViewInfo[i].w = 2; mViewInfo[i].h = 2;
        }
    }

    for(int i=0; i<QYApi::NUM; ++i){
        float lt_y = mViewInfo[i].t + mViewInfo[i].h;
        FS::MakeViewPort(glHandle, i, mViewInfo[i].show, mViewInfo[i].l, viewH - lt_y, mViewInfo[i].w, mViewInfo[i].h);
    }

    if(1 == viewType){
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(3, mViewInfo[0].w, mViewInfo[0].h);

        FS::MakeCurrent(glHandle, 1);
        _TurnShowType(5, mViewInfo[1].w, mViewInfo[1].h);

    }else if(5 == viewType){
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(5, mViewInfo[0].w, mViewInfo[0].h);
    }else if(2 == viewType){
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(3, 0, 0);
        FS::MakeCurrent(glHandle, 1);
        float fAspect = mViewInfo[0].w*1.0/mViewInfo[0].h;
        _TurnShowType(6, 0, 0, 0, 60.0*0.8*fAspect);//60.0*fAspect
        FS::MakeCurrent(glHandle, 2);
        _TurnShowType(6, 0, 0, 120, 60.0*0.8*fAspect);//60.0*fAspect
        FS::MakeCurrent(glHandle, 3);
        _TurnShowType(6, 0, 0, 240, 60.0*0.8*fAspect);//60.0*fAspect
    }else if(3 == viewType){
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(3, 0, 0);
        FS::MakeCurrent(glHandle, 1);
        float fAspect = mViewInfo[1].w*1.0/mViewInfo[1].h;
        _TurnShowType(6, 0, 0, 0, 45*fAspect);
        FS::MakeCurrent(glHandle, 2);
        _TurnShowType(6, 0, 0, 90, 45*fAspect);
        FS::MakeCurrent(glHandle, 3);
        _TurnShowType(6, 0, 0, 180, 45*fAspect);
        FS::MakeCurrent(glHandle, 4);
        _TurnShowType(6, 0, 0, 270, 45*fAspect);
    }else if(4 == viewType){
        float fAspect = mViewInfo[0].w*1.0/mViewInfo[0].h;
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(6, 0, 0, 0, 45.0*0.8*fAspect);//45.0*fAspect
        FS::MakeCurrent(glHandle, 1);
        _TurnShowType(8, mViewInfo[1].w, mViewInfo[1].h);
    }else if(6 == viewType){
        float fAspect = mViewInfo[0].w*1.0/mViewInfo[0].h;
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(6, 0, 0, 0, 45.0*fAspect);
        FS::MakeCurrent(glHandle, 1);
        _TurnShowType(6, 0, 0, 90, 45.0*fAspect);
        FS::MakeCurrent(glHandle, 2);
        _TurnShowType(6, 0, 0, 180, 45.0*fAspect);
        FS::MakeCurrent(glHandle, 3);
        _TurnShowType(6, 0, 0, 270, 45.0*fAspect);
    }else if(7 == viewType){
        float fAspect = mViewInfo[0].w*1.0/mViewInfo[0].h;
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(6, 0, 0, 0, 30.0*fAspect);
        FS::MakeCurrent(glHandle, 1);
        _TurnShowType(6, 0, 0, 60, 30.0*fAspect);
        FS::MakeCurrent(glHandle, 2);
        _TurnShowType(6, 0, 0, 120, 30.0*fAspect);
        FS::MakeCurrent(glHandle, 3);
        _TurnShowType(6, 0, 0, 180, 30.0*fAspect);
        FS::MakeCurrent(glHandle, 4);
        _TurnShowType(6, 0, 0, 240, 30.0*fAspect);
        FS::MakeCurrent(glHandle, 5);
        _TurnShowType(6, 0, 0, 300, 30.0*fAspect);
        FS::MakeCurrent(glHandle, 6);
        _TurnShowType(8, mViewInfo[6].w, mViewInfo[6].h);
    }else if(8 == viewType){
        float fAspect = mViewInfo[0].w*1.0/mViewInfo[0].h;
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(6, 0, 0, 0, 22.5*fAspect);
        FS::MakeCurrent(glHandle, 1);
        _TurnShowType(6, 0, 0, 45, 22.5*fAspect);
        FS::MakeCurrent(glHandle, 2);
        _TurnShowType(6, 0, 0, 90, 22.5*fAspect);
        FS::MakeCurrent(glHandle, 3);
        _TurnShowType(6, 0, 0, 135, 22.5*fAspect);

        FS::MakeCurrent(glHandle, 4);
        _TurnShowType(3, 0, 0);

        FS::MakeCurrent(glHandle, 5);
        _TurnShowType(6, 0, 0, 180, 22.5*fAspect);
        FS::MakeCurrent(glHandle, 6);
        _TurnShowType(6, 0, 0, 225, 22.5*fAspect);
        FS::MakeCurrent(glHandle, 7);
        _TurnShowType(6, 0, 0, 270, 22.5*fAspect);
        FS::MakeCurrent(glHandle, 8);
        _TurnShowType(6, 0, 0, 315, 22.5*fAspect);
    }else if(9 == viewType){
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(2, mViewInfo[0].w, mViewInfo[0].h);
    }else if(10 == viewType){
        FS::MakeCurrent(glHandle, 0);
        _TurnShowType(33, mViewInfo[0].w, mViewInfo[0].h);
    }
    mPower = true;
    update();
}
void GLPanoWidget::_TurnShowType(int type, int w, int h, float rot, float targetFov)
{
    if(5 == type){
        FS::SetOutXY(glHandle, 1.0f);
        FS::SetStep(glHandle, 0.0f);
        FS::SetSpanAg(glHandle, 360.0f);
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, +90.0f);
        QYApi::SetCameraRollMinMax(glHandle, -0.0f, +0.0f);

        FS::SetCameraPos(glHandle, 0.0f,0.0f,-0.01f);
        FS::SetCameraLookAt(glHandle, 0.0,0,+1.0);
        FS::SetOrth(glHandle, true);

        QYApi::_ChangeShowType(glHandle, 1);

        float vR = h*0.5;
        float disLimit = vR * 1.0f;
        float sf = w*1.0f/h;
        float sg = 2.0;
        if(w<h){
            sf = h*1.0/w;
            sg *= sf;
            sf = sf > 1.0 ? 1.0 : sf;
        }
        FS::MoveTarget(glHandle, 0.0f, disLimit, 0.0f);
        FS::ScaleTarget(glHandle, -sf,sg,1.0f);
        QYApi::MoveCameraEx(glHandle, 0.0, 0.0, 0.0);
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0);
        FS::Scale(glHandle, 1.0f);

       }else if(7 == type){

        FS::SetOutXY(glHandle, 0.0f);
        FS::SetStep(glHandle, 0.0f);
        FS::SetSpanAg(glHandle, 0.0f);
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, +90.0f);
        QYApi::SetCameraRollMinMax(glHandle, -0.0f, +0.0f);

        QYApi::_ChangeShowType(glHandle, 3);

        FS::MoveTarget(glHandle, 0.0f, 0.0f, 0.0f);
        FS::ScaleTarget(glHandle, 1.0f,1.0,1.0f);
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0);
        FS::Scale(glHandle, 1.0f);

    }else if(3 == type){
        FS::SetOutXY(glHandle, 0.0f);
        FS::SetStep(glHandle, 0.0f);
        FS::SetSpanAg(glHandle, 0.0f);
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, +90.0f);
        QYApi::SetCameraRollMinMax(glHandle, 0.0f, +360.0f);

        FS::SetCameraPos(glHandle, 0.0,0,-0.01);
        FS::SetCameraLookAt(glHandle, 0.0,0,+1.0);
        FS::SetOrth(glHandle, true);

        QYApi::_ChangeShowType(glHandle, 0);

        FS::MoveTarget(glHandle, 0.0f, 0.0f, 0.0f);
        FS::ScaleTarget(glHandle, 1.0f,1.0f,1.0f);
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0);
        FS::Scale(glHandle, 1.0f);
        QYApi::MoveCameraEx(glHandle, 0.0f, 0.0, 180.0f);

    }else if(6 == type){
        FS::SetOutXY(glHandle, 0.0f);
        FS::SetStep(glHandle, 0.0f);
        FS::SetSpanAg(glHandle, 0.0f);
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0);
        FS::Scale(glHandle, 1.0f);

        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, +90.0f);
        QYApi::SetCameraRollMinMax(glHandle, -0.0f, +0.0f);

        FS::SetCameraPos(glHandle, 0.0,0,-0.01);
        FS::SetCameraLookAt(glHandle, 0.0,0,+1.0);
        FS::SetOrth(glHandle, false);

        QYApi::_ChangeShowType(glHandle, 1);

        FS::Scale(glHandle, 1.0);
        float fov = FS::GetCameraFov(glHandle);
        //qDebug()<<"fov1: "<<fov<<" targetFov: "<<targetFov<<" w: "<<w<<" h: "<<h;
        float fScale = fov *1.0 / targetFov;
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0/fScale);
        FS::Scale(glHandle, fScale);
        fov = FS::GetCameraFov(glHandle);
        //qDebug()<<"fov2: "<<fov<<" targetFov: "<<targetFov<<" w: "<<w<<" h: "<<h;
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
        QYApi::SetCameraRollMinMax(glHandle, -0.0f, +0.0f);
        QYApi::MoveCameraEx(glHandle, fov*0.5, rot, 0.0f);
        FS::MoveTarget(glHandle, 0.0f, 0.0f, 0.0f);
        FS::ScaleTarget(glHandle, 1.0f,1.0f,1.0f);

    }if(8 == type){
        FS::SetOutXY(glHandle, 1.0f);
        FS::SetStep(glHandle, 0.0f);
        FS::SetSpanAg(glHandle, 720.0f);
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, +90.0f);
        QYApi::SetCameraRollMinMax(glHandle, -0.0f, +0.0f);

        FS::SetCameraPos(glHandle, 0.0,0,-0.01);
        FS::SetCameraLookAt(glHandle, 0.0,0,+1.0);
        FS::SetOrth(glHandle, true);

        QYApi::_ChangeShowType(glHandle, 1);

        float vR = h*0.5;
        float disLimit = vR * 1.0f;
        FS::MoveTarget(glHandle, 0.0f, disLimit, 0.0f);
        float sf = w*1.0f/h;
        FS::ScaleTarget(glHandle, -sf,2.0,1.0f);
        QYApi::MoveCameraEx(glHandle, 0.0, 0.0, 0.0);
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0);
        FS::Scale(glHandle, 1.0f);

    }else if(2 == type){
        FS::SetOutXY(glHandle, 0.0f);
        FS::SetStep(glHandle, 0.0f);
        FS::SetSpanAg(glHandle, 0.0f);
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, +90.0f);
        QYApi::SetCameraRollMinMax(glHandle, -90.0f, +90.0f);

        FS::SetCameraPos(glHandle, 0.0,0,-h*0.0-0.01);
        FS::SetCameraLookAt(glHandle, 0.0,0,+1.0);
        FS::SetOrth(glHandle, false);

        QYApi::_ChangeShowType(glHandle, 1);
        FS::Scale(glHandle, 1.0f);

        QYApi::SetCameraPitchMinMax(glHandle, -155.0f, -25.0f);
        QYApi::SetCameraRollMinMax(glHandle, -50.0, +50.0);

        FS::MoveTarget(glHandle, 0.0f, 0.0f, 0.0f);
        float fs = w*1.0/h;
        if(w<h){
            fs = h*1.0/w;
        }
        FS::ScaleTarget(glHandle, fs, fs,1.0f);
        QYApi::MoveCameraEx(glHandle, 90.0, 0.0, 0.0);
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0);
        FS::Scale(glHandle, 1.0f);

    }else if(33 == type){
        FS::SetOutXY(glHandle, 0.0f);
        FS::SetStep(glHandle, 0.0f);
        FS::SetSpanAg(glHandle, 0.0f);
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, +90.0f);
        QYApi::SetCameraRollMinMax(glHandle, -90.0f, +90.0f);

        FS::SetCameraPos(glHandle, 0.0,0,-0.01);
        FS::SetCameraLookAt(glHandle, 0.0,0,+1.0);
        FS::SetOrth(glHandle, true);

        QYApi::_ChangeShowType(glHandle, 0);
        QYApi::SetCameraRollMinMax(glHandle, -0.0f, +0.0f);

        FS::MoveTarget(glHandle, 0.0f, 0.0f, 0.0f);

        float fsx = 1.0f*w/h;
        float fsy = 1.0f;
        if(w<h){
            fsx = 1.0f;
            fsy = 1.0f*h/w;
        }
        FS::ScaleTarget(glHandle, -fsx,-fsy,1.0f);
        FS::SetCameraScaleLimited(glHandle, 0.1, 1.0);
        FS::Scale(glHandle, 1.0f);
        FS::SetStep(glHandle, 1.0f);
    }
}

bool GLPanoWidget::StreamIn(char* pBuf, long nSize, int w, int h)
{
    //return false;
    if(!m_bInit || !isVisible()){
        qWarning()<<"StreamIn: "<<isVisible();
        return false;
    }

    bool bRes = false;

    yuvData* yuv = 0;
    qWarning()<<"lockForWrite: "<<dataQueue.length();
    if(dataQueue.length() < 30){
        yuv = new yuvData(w,h,pBuf,nSize);
    }

    if(0 != yuv){
        bRes = true;
        rwLock->lockForWrite();
        dataQueue.enqueue(yuv);
        rwLock->unlock();
    }

    update();

    return bRes;
}
void GLPanoWidget::paintGL()
{
    if(!m_bInit){return;}

    yuvData* yuv = 0;

    int n = dataQueue.length();
    qWarning()<<"lockForRead: "<<n;
    if(0<n){
        rwLock->lockForRead();
        yuv = dataQueue.dequeue();
        rwLock->unlock();

        if(28 < n){
            ClearDataQueue();
        }
    }

    bool bRes = false;
    if(0 != yuv){
        videoWidth  = yuv->w;
        videoHeight = yuv->h;
        videoAspect = videoWidth*1.0/videoHeight;
        qWarning()<<"videoWidth: "<<videoWidth;
        qWarning()<<"videoHeight: "<<videoHeight;
        //qWarning()<<"videoAspect: "<<videoAspect;
        setFrameToTexture(videoWidth, videoHeight, yuv->y, yuv->u, yuv->v);

        delete yuv;
        yuv = 0;
        if(videoWidth > 10 && videoHeight > 10){
            bRes = true;
        }
    }

    //Render to FBO
    if(bRes){
        updateFramebuffer(videoWidth, videoHeight);

        RenderFBO();
   }

   FS::Render(glHandle);
}

void GLPanoWidget::resizeGL(int w, int h)
{
    if(viewW == w && viewH == h){
        return;
    }
   // FS::SetViewport(w,h);

    viewW 	= w;
    viewH	= h;

    if(!m_bInit){
        return;
    }
    //viewRadius  = (viewW < viewH ? viewW : viewH)/2+1;

    TurnViewType(viewType);
}

void GLPanoWidget::mousePressEvent(QMouseEvent *event)
{
    mFirstMove = true;
    mFirstWheel = true;
    mbDown = true;
    QWidget::mousePressEvent(event);
}

void GLPanoWidget::mouseMoveEvent(QMouseEvent *event)
{
    mFirstWheel = true;
    mbDown = false;
    float x = event->x();
    float y = event->y();

    if(mFirstMove){
        mViewNo = -1;
        for(int i=0; i<QYApi::NUM; ++i){
            if(!mViewInfo[i].show){continue;}
            QRect rt = QRect(mViewInfo[i].l,mViewInfo[i].t,mViewInfo[i].w,mViewInfo[i].h);
            if(rt.contains(x, y)){
                mViewNo = i;
                break;
            }
        }
        if(-1 == mViewNo){
            return;
        }
        mFirstMove = false;

        lastMoveX = x;
        lastMoveY = y;

        QRect rt = QRect(mViewInfo[mViewNo].l,mViewInfo[mViewNo].t,mViewInfo[mViewNo].w,mViewInfo[mViewNo].h);
        m_panCenterPt 		= rt.center();
        m_panLastCenterDir	= normalDir(QPointF(x,y)-m_panCenterPt);

        return;
    }

    if(-1 == mViewNo){
        return;
    }

    int dx = x - lastMoveX;
    int dy = y - lastMoveY;

    lastMoveX = x;
    lastMoveY = y;

    //距离
    float _fDistance = (float)sqrt(dx * dx *1.0 + dy * dy *1.0);
    if(1000>(int)(_fDistance*1000)){
        return;
    }

    QPointF curDir = normalDir(QPointF(x,y)-m_panCenterPt);
    float dRoll = angleDir(m_panLastCenterDir, curDir);
    m_panLastCenterDir = curDir;

    if(1 == viewType){
        if(1 ==  mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
            float fStep = FS::GetStep(glHandle);
            fStep += -dx*0.5/viewW;
            FS::SetStep(glHandle, fStep);
            update();
        }else if(0 == mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
            QYApi::MoveCameraStep(glHandle, 0.0, 0.0, dRoll);
            update();
        }
    }else if(5 == viewType && 0 ==  mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
            float fStep = FS::GetStep(glHandle);
            fStep += +dx*0.5/viewW;
            FS::SetStep(glHandle, fStep);
            update();
    }else if(2 == viewType && (0<=mViewNo && mViewNo<4)){
        if(0 == mViewNo){
            FS::MakeCurrent(glHandle, 0);
            QYApi::MoveCameraStep(glHandle, 0.0, 0.0, dRoll);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            QYApi::MoveCameraStep(glHandle, -dy*45.0/mViewInfo[mViewNo].h, -dx*90.0/mViewInfo[mViewNo].w, 0.0f);
        }
        update();
    }else if(3 == viewType && (0<=mViewNo && mViewNo<5)){
        if(0 == mViewNo){
            FS::MakeCurrent(glHandle, 0);
            QYApi::MoveCameraStep(glHandle, 0.0, 0.0, dRoll);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            QYApi::MoveCameraStep(glHandle, -dy*45.0/mViewInfo[mViewNo].h, -dx*90.0/mViewInfo[mViewNo].w, 0.0f);
        }
        update();
    }else if(4 == viewType && (0<=mViewNo && mViewNo<2)){
        if(0 ==  mViewNo){
            FS::MakeCurrent(glHandle, 0);
            QYApi::MoveCameraStep(glHandle, -dy*45.0/mViewInfo[0].h, -dx*90.0/mViewInfo[0].w, 0.0f);
        }else if(1 == mViewNo){
            FS::MakeCurrent(glHandle, 1);
            float fStep = FS::GetStep(glHandle);
            fStep += +dx*1.0/mViewInfo[1].w;
            FS::SetStep(glHandle, fStep);
        }
        update();
    }else if(6 == viewType && (0<=mViewNo && mViewNo<4)){
        FS::MakeCurrent(glHandle, mViewNo);
        QYApi::MoveCameraStep(glHandle, -dy*45.0/mViewInfo[mViewNo].h, -dx*90.0/mViewInfo[mViewNo].w, 0.0f);
        update();
    }else if(7 == viewType && (0<=mViewNo && mViewNo<7)){
        if(6 == mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
            float fStep = FS::GetStep(glHandle);
            fStep += +dx*1.0/mViewInfo[mViewNo].w;
            FS::SetStep(glHandle, fStep);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            QYApi::MoveCameraStep(glHandle, -dy*45.0/mViewInfo[mViewNo].h, -dx*90.0/mViewInfo[mViewNo].w, 0.0f);
        }
        update();
    }else if(8 == viewType && (0<=mViewNo && mViewNo<9)){
        if(4 == mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
            QYApi::MoveCameraStep(glHandle, 0.0, 0.0, dRoll);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            QYApi::MoveCameraStep(glHandle, -dy*45.0/mViewInfo[mViewNo].h, -dx*90.0/mViewInfo[mViewNo].w, 0.0f);
        }
        update();
    }else if(9 == viewType){
        if(0 == mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
            QYApi::MoveCameraStep(glHandle, -dy*45.0/mViewInfo[mViewNo].h, 0.0, +dx*90.0/mViewInfo[mViewNo].w);
        }
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void GLPanoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mFirstMove = true;
    mFirstWheel = true;
    QWidget::mouseReleaseEvent(event);
}

void GLPanoWidget::wheelEvent(QWheelEvent *event)
{
    float x = event->x();
    float y = event->y();
    {
        mViewNo = -1;
        for(int i=0; i<QYApi::NUM; ++i){
            if(!mViewInfo[i].show){continue;}
            QRect rt = QRect(mViewInfo[i].l,mViewInfo[i].t,mViewInfo[i].w,mViewInfo[i].h);
            if(rt.contains(x, y)){
                mViewNo = i;
                break;
            }
        }
        mFirstWheel = false;
    }

    if(-1 == mViewNo){
        return;
    }

    int zDelta = event->delta();
    int nFlag  = (int)(zDelta*1.0)/abs(zDelta);
    int nTurn  = zDelta / 120;

    float _fScale = FS::GetScale(glHandle);
    _fScale *= (1.0+nTurn * 0.2);

    if(2 == viewType && (0<=mViewNo && mViewNo<4)){
        if(0 == mViewNo){
            FS::MakeCurrent(glHandle, 0);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            FS::Scale(glHandle, _fScale);
            float fov = FS::GetCameraFov(glHandle);
            QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
        }
        update();
    }else if(3 == viewType && (0<=mViewNo && mViewNo<5)){
        if(0 == mViewNo){
            FS::MakeCurrent(glHandle, 0);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            FS::Scale(glHandle, _fScale);
            float fov = FS::GetCameraFov(glHandle);
            QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
        }
        update();
    }else if(4 == viewType && (0<=mViewNo && mViewNo<2)){
        if(0 ==  mViewNo){
            FS::MakeCurrent(glHandle, 0);
            FS::Scale(glHandle, _fScale);
            float fov = FS::GetCameraFov(glHandle);
            QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
        }else if(1 == mViewNo){
            FS::MakeCurrent(glHandle, 1);
        }
        update();
    }else if(6 == viewType && (0<=mViewNo && mViewNo<4)){
        FS::MakeCurrent(glHandle, mViewNo);
        FS::Scale(glHandle, _fScale);
        float fov = FS::GetCameraFov(glHandle);
        QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
        update();
    }else if(7 == viewType && (0<=mViewNo && mViewNo<7)){
        if(6 == mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            FS::Scale(glHandle, _fScale);
            float fov = FS::GetCameraFov(glHandle);
            QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
        }
        update();
    }else if(8 == viewType && (0<=mViewNo && mViewNo<9)){
        if(4 == mViewNo){
            FS::MakeCurrent(glHandle, mViewNo);
        }else{
            FS::MakeCurrent(glHandle, mViewNo);
            FS::Scale(glHandle, _fScale);
            float fov = FS::GetCameraFov(glHandle);
            QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
        }
        update();
//    }else if(9 == viewType){
//        if(0 == mViewNo){
//            FS::MakeCurrent(glHandle, mViewNo);
//            FS::Scale(glHandle, _fScale);
//            float fov = FS::GetCameraFov(glHandle, );
//            QYApi::SetCameraPitchMinMax(glHandle, -90.0f, -fov*0.5);
//        }
//        update();
    }
QWidget::wheelEvent(event);




}

QPointF GLPanoWidget::normalDir(QPointF dir){
    float l    = (float) sqrt(dir.x() * dir.x() + dir.y() * dir.y());
    if(l > -1.0e-6 && l < 1.0e-6){
        l = (float) 1.0e-6;
    }
    float lInv = (float) (1.0/l);
    dir.setX(dir.x() * lInv);
    dir.setY(dir.y() * lInv);
    return dir;
}
float GLPanoWidget::angleDir(QPointF dirA, QPointF dirB)
{
    float t = dirA.x() * dirB.x() + dirA.y() * dirB.y();
    float theta = (float) acos(t);
    float tt =  (float) abs(abs(t) - 1.0);
    if(tt > -1.0e-6 && tt < 1.0e-6){
        theta = 0.0f;
    }
    float flag  = -1;
    if((dirA.y()*dirB.x() - dirA.x()*dirB.y())>=0.0){
        flag = +1;
    }
    float f = (float) (flag*theta*180.0/3.1415926);
    return f;
}
