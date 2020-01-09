#ifndef PAGEMAIN_H
#define PAGEMAIN_H

#include <QWidget>
#include <qpropertyanimation.h>
#include <QMap>
#include <QVector2D>
#include <QThread>
#include <QMovie>
#include <QMutex>
#include <QTimer>

#include "ComTool.h"

#include "QYPixViewer.h"

namespace Ui {
class PageMain;
}
//class QTreeWidgetItem;
class QYDialogLoading;
class QYDialogMessage;
class PanelTitle;
class QTreeWidgetItem;
class QMenu;
class QAction;
class QTableWidgetItem;
class QTreeWidgetItem;

class QYVideoWidget;
namespace ComTool {
typedef struct _NODE_DATA NODE_DATA;
typedef struct _LINK_DATA LINK_DATA;
}

class HCStreamCB;


class QYPixPointEx:public QYPixHelper
{
    Q_OBJECT
public:
    explicit QYPixPointEx(ComTool::LINK_DATA* l, QObject *parent=0);
    virtual ~QYPixPointEx();
public:
   virtual int HitObj(QPointF pt, qreal s, int flag);

//        int AddCurDownPos();
    int SetCurDownPos();
    void Calc(const qreal* wdlr);

    void ReCreatePts();
    void enableHit(bool enable);

    bool ShowShadow(bool show);
signals:
    void hitPt(int cur);

public:
    virtual void paint(QPainter *painter);
public:
    ComTool::PixPointVec pts;
    int curHitted;
    ComTool::LINK_DATA* link;

private:
    QImage imgCrossA;
    QImage imgCrossB;
    QImage imgCross;

    QVector2D linkCross;
    QVector2D linkDirX;
    QVector2D linkDirY;
    QVector2D linkLinear;

    bool isLinked;
    QVector2D curPtt;

    bool mEnableHit;
};

class LoginTreeItemThread : public QThread
{
    Q_OBJECT
public:
    explicit LoginTreeItemThread(QTreeWidgetItem *it, bool open, QObject *parent = Q_NULLPTR);
    ~LoginTreeItemThread();
public:
    virtual void run();
public:
    QTreeWidgetItem *item;
    bool doOpen;
};

class OpenNodeDataTimer : public QTimer
{
    Q_OBJECT
public:
    explicit OpenNodeDataTimer(QObject *parent = 0);
    ~OpenNodeDataTimer();
    void doFinish(int no);
signals:
    void sigFinish(int no);
};

class OpenLinkDataTimer : public QTimer
{
    Q_OBJECT
public:
    explicit OpenLinkDataTimer(QObject *parent = 0);
    ~OpenLinkDataTimer();
    void doFinish(int no);
signals:
    void sigFinish(int no);
};

///\brief 主页
class PageMain : public QWidget
{
    Q_OBJECT
    
public:
    explicit PageMain(QWidget *parent = 0);
    ~PageMain();

public:
    void OpenTreeNode(ComTool::NODE_TREE* nodeTree);
    void CloseTreeNode(ComTool::NODE_TREE* nodeTree);
    int  TurnCloseCameraAll_Panel(int nStart);
    static void TurnNodeDataPlay(QYVideoWidget* wd, ComTool::NODE_DATA* willData, bool showDlg=false);
    void TurnCloseCamera(QYVideoWidget* wd=0);
    void TurnFullScreen(bool full);

    int PTZControlAll(void* lRealHandle, unsigned int dwPTZCommand, unsigned int dwStop, int Speed);

    static int OpenCameraPanel(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd);
    static int CloseCameraPanel(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd, bool refreshUI=true);

    static int OPenCamera(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd, int flag);
    static int CloseCamera(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd, int flag, bool refreshUI=true, bool power=false);

    int OpenCameraLink(ComTool::LINK_DATA* link, QYVideoWidget* curSelA, QYVideoWidget* curSelB);
    int CloseCameraLink(ComTool::LINK_DATA* link);
    int TurnCloseLinkAll_Panel();

    static int OpenHHCamera(ComTool::NODE_DATA* nodeData, int PlayerNo);
    static int OpenHCCamera(ComTool::NODE_DATA* nodeData, HWND hwnd);
    int OpenHCCameraStream(ComTool::NODE_DATA* nodeData, HCStreamCB* streamTool);
    static int CloseHCCameraStream(ComTool::NODE_DATA* nodeData, HCStreamCB* streamPort);

    static int CloseHHCamera(ComTool::NODE_DATA* nodeData);
    static int CloseHCCamera(ComTool::NODE_DATA* nodeData);

    void LoginNodeTree(ComTool::NODE_TREE* tree, bool open);
    static bool LoginNodeData(ComTool::NODE_DATA* nodeData);
    static QVariant LoginCamera(const QString& szName,
                            const QString& szRegisterIP, unsigned short registerDataPort,
                            const QString& szUserName,const QString& szUserPsw);
    static void refreshTreeNode(QTreeWidgetItem* nodeItem, bool deep=true);
    static bool treeAddNodeData(QTreeWidgetItem* nodeItem, ComTool::NODE_DATA* nodeData);
    static bool treeAddNodeTree(QTreeWidgetItem* nodeItem, ComTool::NODE_TREE* nodeTree);

    static void LogoutCamera(ComTool::NODE_DATA* nodeData);
    void DelNodeTree(ComTool::NODE_TREE* nodeTree);
    void DelNodeData(ComTool::NODE_DATA* nodeData, ComTool::NODE_TREE* nodeTree);
    void DelLinkData(ComTool::LINK_DATA* link);

    void TurnResumeDatas(int flag, bool isOpen);

    ComTool::NODE_DATA* _GotSelFromTree(void);

    static void TurnOffOther(ComTool::NODE_DATA* nodeData);

    bool canTurnPanoShow(QYVideoWidget* wdVideo);
    bool turnPanoShow(QYVideoWidget* wdVideo, int butNo);
    static bool turnPanoClose(QYVideoWidget* wdVideo);

    static bool turnSpeekCamera(QYVideoWidget* wd, bool on);
    static bool turnCaptureCamera(QYVideoWidget* wd);
    static bool isRecordCamera(const ComTool::NODE_DATA* nodeData);
    static bool turnRecordCamera(QYVideoWidget* wd, bool on);
    static bool isSoundCamera(const ComTool::NODE_DATA* nodeData);
    static bool turnSoundCamera(QYVideoWidget* wd, bool on);
    bool turnStreamCamera(QYVideoWidget* wd, bool on);
    bool turnAspectCamera(QYVideoWidget* wd, int nAspect);
    bool isFullScreenCamera(const QYVideoWidget* wd);
    bool turnFullScreenCamera(QYVideoWidget* wd, bool on, bool refreshUI=true);

    int _GotCurSelQQ_TopItem();
    bool _TurnShow_TopItem(int itemNO);
    bool _isCurSelQQ_TopItem();
    bool _isCurSelQQ_TopLink(const ComTool::LINK_DATA* link);
    QYVideoWidget* _isCurSelQQ_TopLinkEx(const ComTool::LINK_DATA* link);

protected:
    virtual void paintEvent(QPaintEvent* event);

private slots:

    void oChanagedSize(bool bMax);
    void oChanagedPage(int curPage);
    void oChanagedShow(int curShow, int flag);
    void oChanagedShowUserLeft(int modeUserLeft);
    void oChanagedShowBKSubPage(int subPage);
    void oChanagedTreeNode(QTreeWidgetItem* item, void* pData, int type);
    void oAddLink(ComTool::LINK_DATA* link);
    void oSigTrackClicked(QWidget* pano, QVector2D uv);
    void oSigTrackRect(QWidget*, QVector2D uvStart, QVector2D uvEnd);
    void oSigTrackWheel(QWidget* pano, qreal fTurn);
    void oSigDoubleClicked_RPageA_Bot();

    void on_butOpenImage_clicked();
    void on_butOpenVideo_clicked();
    void on_butSaveCfg_clicked();

    void on_butAA_clicked();

    void on_butAB_clicked();

    void on_butAC_clicked();

    void on_butAA_A_clicked();

    void on_butAA_B_clicked();

    void on_butAB_A_clicked();

    void on_butAB_B_clicked();

    void on_butAA_Add_A_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void refresh_PanelVideos();
    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);

    void triggeredMenuItem(bool);

    void oSelPanelVideo(int sel);
    void on_tableWidget_qq_itemDoubleClicked(QTableWidgetItem *item);
    void on_tableWidget_qq_itemPressed(QTableWidgetItem *item);

    void resume_PanelVideos();
    void close_Loading();

    void oButABPressed();
    void oButABReleased();
    void on_comboBox_Speed_currentTextChanged(const QString &arg1);

    void on_butRQQ_Calc_clicked();

    void on_cb_Linked_clicked();


    void on_dSpinBox_Ag_valueChanged(double arg1);

    void on_dSpinBox_AgR_L_valueChanged(double arg1);

    void on_dSpinBox_AgR_R_valueChanged(double arg1);

    void on_cboBox_Row_currentTextChanged(const QString &arg1);

    void on_cboBox_Col_currentTextChanged(const QString &arg1);

    void timerOpenLink();
    void timerOpenLinksFinished(int no);
    void timerFinishedLoading();
    //顺序打开
    //void timerOpenTreeVideos();
    void timerOpenDataVideos();
    void timerOpenDataVideosFinished(int no);


    void on_cb_shadow_clicked();

    void oPixPtEx_Hit(int cur);

    void oFinishedLoginTreeItemThread();
    void oMovieframeChanged(int);
    void on_butAA_Add_B_clicked();

    void on_butAA_B_A_clicked();

    void on_butAA_B_B_clicked();

private:
    virtual bool eventFilter(QObject *, QEvent *);

private:
    void _TurnLeftTab(int modeLeft);
    void _TurnLeftYunPanel(int modeYunLeft);

    void _GotResumeDatas(int flag);
    void _GotCurSelQQ(QYVideoWidget* &curSelA, QYVideoWidget* &curSelB);
    void _GotCurSel(QYVideoWidget* &wd);
    ComTool::LINK_DATA* _GotCurSelQQ_Data(ComTool::NODE_DATA* &dataA, ComTool::NODE_DATA* &dataB);
    void _GotCurSel_Data(ComTool::NODE_DATA* &data);
    void _GotCurSelPano(ComTool::NODE_DATA* &pano);
    void _GotCurSelSphere(ComTool::NODE_DATA* &sphere);
    ComTool::NODE_DATA* _GotCurSelPanoVideo(QYVideoWidget* &wdPano);
    ComTool::NODE_DATA* _GotCurSelSphereVideo(QYVideoWidget* &wdSphere);

    ComTool::LINK_DATA* _GotOpenedLink(ComTool::NODE_DATA* &pano, ComTool::NODE_DATA* &sphere, QYVideoWidget* &wdPano, QYVideoWidget* &wdSphere);

    void _VisibleVideo(QYVideoWidget* wd, bool show);
    static void _TurnSphere3DPTZ(ComTool::NODE_DATA* nodeData);
    static QString _CaptureCamera(QYVideoWidget *wd);

    QList<ComTool::LINK_DATA*> _GotAllLink_Panel();
    bool _HasLinkOpened_Panel();
    bool _HasLinkOpenedSame_Panel();//相同的打开
private:
    typedef QList<QWidget*> ListPanel;
    ListPanel mPageList;
    ListPanel mPageContent;

    QPropertyAnimation* m_pAniwd_TabA;
    QPropertyAnimation* m_pAniwd_TabB;
    QPropertyAnimation* m_pAniwd_TabC;
    int m_ShowModeLeft;

    int m_ShowYunLeft;

    QMenu*      m_menuTreeWd;
    QAction*    m_acLink;
    QAction*    m_acDel;
    QAction*    m_acAttr;

    QAction*    m_acOpen;
    QAction*    m_acClose;

    QAction*    m_acAddCamera;
    QAction*    m_acAddHome;

    //联动
    int mSelLink[3];

    //面板切换时数据结构
    typedef struct _NODE_DATA_RESUME{
        ComTool::NODE_DATA* data;
        QYVideoWidget* wd;
        int flag;
        _NODE_DATA_RESUME(){
            data    = 0;
            wd      = 0;
            flag    = 0;
        }
        _NODE_DATA_RESUME(ComTool::NODE_DATA* d, QYVideoWidget* w, int f){
            data = d;
            wd   = w;
            flag = f;
        }
    }NODE_DATA_RESUME;
    typedef QList<NODE_DATA_RESUME> DATA_RESUME_LIST;
    DATA_RESUME_LIST resumeDatas;

    typedef struct _LINK_DATA_RESUME{
        ComTool::LINK_DATA* link;
        QYVideoWidget* wdA;
        QYVideoWidget* wdB;
        _LINK_DATA_RESUME(){
            link = 0;
            wdA  = 0;
            wdB  = 0;
        }
        _LINK_DATA_RESUME(ComTool::LINK_DATA* l, QYVideoWidget* a, QYVideoWidget* b){
            link = l;
            wdA  = a;
            wdB  = b;
        }
    }LINK_DATA_RESUME;
    typedef QList<LINK_DATA_RESUME> LINK_RESUME_LIST;
    LINK_RESUME_LIST resumeLinks;

    //
    int m_speedYunTai;

    friend class QYPixPointEx;
    QYPixPointEx* pixPointEx;

    QMovie* mMovie;
    QList<QTreeWidgetItem*> mMovieList;
    QMutex mMovieLock;

    static QIcon* iconLogout;
    static QIcon* iconClosed;
    static QIcon* iconOpend;
    static QIcon* iconHome;
    static QIcon* iconHard;

    int sumOpenData;
    int sumOpenLink;
private:
    Ui::PageMain *ui;
};

#endif // PAGEMAIN_H
