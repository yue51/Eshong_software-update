#include "PageMain.h"
#include "ui_PageMain.h"
#include "ComTool.h"
#include "AppZZB.h"

#include <QtGui/QPainter.h>

#include <QScrollBar>
#include <qfiledialog.h>
#include <QKeyEvent>
#include <QHBoxLayout>

#include <fstream>
#include "QYDlgCameraAdd.h"
#include <QDebug>
#include <QTimer>
#include <QMenu>
#include <map>
#include <QDateTime>
#include <QMutexLocker>

#include "ComHeader.h"
#include "QYDlgLinkGroupAdd.h"
#include "QYDlgLoading.h"
#include "QYDlgCameraCfg.h"
#include "QYDlgFullCtrlLink.h"
#include "QYDlgCameraHomeCfg.h"
#include "QYDlgCameraHomeHardCfg.h"

#include "QYPixViewer.h"
#include <QtMath>

#include "GLPanoWidget.h"

Q_DECLARE_METATYPE(QYPanelVideo*)
Q_DECLARE_METATYPE(QYVideoWidget*)

ComTool::NODE_DATA* gSpeekNodeData  = 0;
ComTool::NODE_DATA* gRecordNodeData = 0;
ComTool::NODE_DATA* gSoundNodeData  = 0;
QWidget* gFullScreenWd = 0;
//////////////////////////////////////////////////////////////////////////
///实时流回调
///
class HCStreamCB{
  public:
    HCStreamCB(){mPort = (LONG)-1; pano = 0; nodeData = 0;}
    ~HCStreamCB(){}

    LONG mPort;
    GLPanoWidget* pano;
    ComTool::NODE_DATA* nodeData;
    QYVideoWidget* wd;

    ////解码回调 视频为YUV数据(YV12)，音频为PCM数据
    void DecCBFun(long nPort, char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2){
        long lFrameType = pFrameInfo->nType;
        if (lFrameType ==T_AUDIO16){

        }else if(lFrameType ==T_YV12 && 0 != pano){
            //qDebug()<<"T_YV12: "<<nSize<<" "<<pFrameInfo->nWidth<<" "<<pFrameInfo->nHeight;
            if(!pano->StreamIn(pBuf, nSize, pFrameInfo->nWidth, pFrameInfo->nHeight)){
                //qWarning()<<"Sleep 1 s";
               //Sleep(1000);
            }
        }
    }//End Func
};


//HCStreamCB* gStreamPort = 0;
typedef std::map<LONG, HCStreamCB*> StreamPortMap;
StreamPortMap gStreamPortMap;
void CALLBACK gDecCBFun(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2)
{
    std::map<LONG, HCStreamCB*>::iterator it = gStreamPortMap.find(nPort);
    if(gStreamPortMap.end() == it){
        return;
    }
    HCStreamCB* hc = it->second;
    hc->DecCBFun(nPort, pBuf, nSize, pFrameInfo, nReserved1, nReserved2);
}
void CALLBACK gRealDataCallBack(LONG lRealHandle,DWORD dwDataType,BYTE *pBuffer,DWORD dwBufSize,void *pUser)
{
    switch (dwDataType)
    {
    case NET_DVR_SYSHEAD:{
        LONG nPort = (LONG)-1;
        if (!PlayM4_GetPort(&nPort)){
            break;
        }
        std::map<LONG, HCStreamCB*>::iterator it = gStreamPortMap.find(nPort);
        if(gStreamPortMap.end() != it){
            break;
        }
        HCStreamCB* pStreamPort = (HCStreamCB*)pUser;
        pStreamPort->mPort = nPort;
        gStreamPortMap.insert(std::make_pair(nPort, pStreamPort));

        if (!PlayM4_OpenStream(nPort,pBuffer,dwBufSize,1024*1024)){
            //DWORD dRet=PlayM4_GetLastError(nPort);
            break;
        }
        //设置解码回调函数 解码且显示
        if (!PlayM4_SetDecCallBackEx(nPort,gDecCBFun,NULL,NULL)){
            //DWORD dRet=PlayM4_GetLastError(nPort);
            break;
        }
        HWND hPlayWnd = (HWND)(pStreamPort->wd->showWidget()->winId());
        if (!PlayM4_Play(nPort,hPlayWnd)){
            //DWORD dRet=PlayM4_GetLastError(nPort);
            break;
        }
        break;
    }
    case NET_DVR_STREAMDATA:
    default:{
        HCStreamCB* pStreamPort = (HCStreamCB*)pUser;
        LONG nPort = pStreamPort->mPort;
        BOOL inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
        //        int t = 0;
        //        while (!inData){
        //            //Sleep(10);
        //            t++;
        //            inData=PlayM4_InputData(nPort,pBuffer,dwBufSize);
        //        }
        //qDebug()<<"tt: "<<inData;
        break;
    }
    }//End Switch
}
//////////////////////////////////////////////////////////////////////////
bool hasStreamPortMap()
{
    return gStreamPortMap.size() > 0;
}
bool canTurnStreamPortMap()
{
    return gStreamPortMap.size() < 10;
}
bool hasStreamPort(QYVideoWidget* wd)
{
    bool ret = false;
    StreamPortMap::iterator it;
    StreamPortMap::iterator iend = gStreamPortMap.end();
    for(it=gStreamPortMap.begin(); it!=iend; ++it){
        HCStreamCB* hc = it->second;
        if(0 != hc && wd == hc->wd){ret=true; break;}
    }
    return ret;
}
bool closeStreamPort(QYVideoWidget* wd)
{
    bool ret = false;
    StreamPortMap::iterator it;
    StreamPortMap::iterator iend = gStreamPortMap.end();
    for(it=gStreamPortMap.begin(); it!=iend; ++it){
        HCStreamCB* hc = it->second;
        if(0 != hc && wd == hc->wd){
            ret=true;
            PageMain::CloseHCCameraStream(hc->nodeData, hc);
            delete hc;
            hc = 0;
            gStreamPortMap.erase(it);
            break;
        }
    }
    return ret;
}
void CloseStreamPortAll()
{
    StreamPortMap::iterator it;
    StreamPortMap::iterator iend = gStreamPortMap.end();
    for(it=gStreamPortMap.begin(); it!=iend; ++it){
        HCStreamCB* hc = it->second;
        if(0 != hc){
            PageMain::CloseHCCameraStream(hc->nodeData, hc);
            delete hc;
            hc = 0;
        }
    }
    gStreamPortMap.clear();
}

//void ClearHwnd( HWND hWnd )
//{
//    HDC         hdc;
//    HBRUSH      hBrush;
//    RECT        rect;

//    hBrush = CreateSolidBrush(RGB(255,0,0));
//    GetClientRect(hWnd, &rect);
//    hdc = GetDC( hWnd );
//    FillRect( hdc, &rect, hBrush ); // 直接覆盖在背景上
//    DeleteObject( hBrush ); // 完事儿后删除画刷
//    ReleaseDC( hWnd, hdc );
//}
//////////////////////////////////////////////////////////////////////////
QIcon* PageMain::iconLogout  = 0;
QIcon* PageMain::iconClosed  = 0;
QIcon* PageMain::iconOpend   = 0;
QIcon* PageMain::iconHome    = 0;
QIcon* PageMain::iconHard    = 0;

PageMain::PageMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageMain)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    m_pAniwd_TabA  = 0;
    m_pAniwd_TabB  = 0;
    m_pAniwd_TabC  = 0;
    m_ShowModeLeft = 0;
    m_menuTreeWd   = 0;
    mSelLink[0] = -1;
    mSelLink[1] = -1;
    mSelLink[2] = -1;
    pixPointEx  = 0;
    sumOpenData = 0;
    sumOpenLink = 0;

    mMovie = new QMovie(":/images/ap2000/loading_001");
    connect(mMovie,SIGNAL(frameChanged(int)),this,SLOT(oMovieframeChanged(int)));
    mMovie->start();

    if(0 == PageMain::iconLogout){
        PageMain::iconLogout  = new QIcon(":/images/ap2000/tree_logout");
        PageMain::iconClosed  = new QIcon(":/images/ap2000/tree_close");
        PageMain::iconOpend   = new QIcon(":/images/ap2000/tree_open");
        PageMain::iconHome    = new QIcon(":/images/ap2000/tree_home");
        PageMain::iconHard    = new QIcon(":/images/ap2000/tree_hard");
    }

    connect(AppZZB::getInstance(), SIGNAL(chanagedSize(bool)), this, SLOT(oChanagedSize(bool)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedPage(int)), this, SLOT(oChanagedPage(int)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedShow(int, int)), this, SLOT(oChanagedShow(int, int)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedShowUserLeft(int)), this, SLOT(oChanagedShowUserLeft(int)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedShowBKSubPage(int)), this, SLOT(oChanagedShowBKSubPage(int)));
    connect(AppZZB::getInstance(), SIGNAL(chanagedTreeNode(QTreeWidgetItem*, void*, int)), this, SLOT(oChanagedTreeNode(QTreeWidgetItem*, void*, int)));
    connect(AppZZB::getInstance(), SIGNAL(sigAddLink(ComTool::LINK_DATA*)), this, SLOT(oAddLink(ComTool::LINK_DATA*)));
    connect(ui->panelvideos, SIGNAL(sigSel(int)), this, SLOT(oSelPanelVideo(int)));
    connect(ui->wdRPageA_Top, SIGNAL(sigSel(int)), this, SLOT(oSelPanelVideo(int)));
    connect(ui->wdRPageA_Bot, SIGNAL(sigSel(int)), this, SLOT(oSelPanelVideo(int)));
    ui->wdRPageA_Top->setIndexStart(40);
    ui->wdRPageA_Bot->setIndexStart(50);

    mPageContent.push_back(ui->wdRPageA);
    mPageContent.push_back(ui->wdRPageB);
    mPageContent.push_back(ui->wdRPageC);

    qApp->setStyleSheet("QTableCornerButton::section{background:rgba(76,75,80,255);}");
    typedef QList<QTableWidget*> QYTabPanel;
    QYTabPanel tabPanel;
    //tabPanel.push_back(ui->tableWidget);
    tabPanel.push_back(ui->tableWidget_qq);
    tabPanel.push_back(ui->tableWidget_YunA);
    tabPanel.push_back(ui->tableWidget_YunB);
    for(int i=0, l=tabPanel.size(); i<l; ++i){
        QTableWidget* pTab = tabPanel.at(i);
        pTab->horizontalHeader()->setStyleSheet("QHeaderView::section{"
                                                           "background-color:rgb(76,75,80,255);}");

        pTab->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal {\n"
                                                              "background-color: rgba(76,75,80,255);\n"
                                                              "}\n"
                                                              "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\n"
                                                              "background: none;\n"
                                                              "}");
        pTab->verticalHeader()->setStyleSheet("QHeaderView::section{"
                                                           "background-color:rgb(76,75,80,255);}");
        pTab->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {\n"
                                                              "background-color:rgba(76,75,80,255);\n"
                                                              "}\n"
                                                              "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
                                                              "background: none;\n"
                                                              "}");
        //pTab->setStyleSheet("QTableCornerButton::section{background-color:rgba(76,75,80,255);}");
        pTab->setStyleSheet("selection-background-color:rgba(200,200,200,128);");
        pTab->setSelectionBehavior(QAbstractItemView::SelectRows);

        pTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pTab->setSelectionMode(QAbstractItemView::SingleSelection);

    }

    //mCurPage    = 0;

    {
        ui->treeWidget->setColumnCount(1); //设置列数
        ui->treeWidget->setHeaderLabel(tr("用户列表")); //设置头的标题

        {
            ComTool::NODE_TREE* rootTree = ComTool::NodeTreeHelper::CreatNode("Root", 0);
            AppZZB::getInstance()->rootTree = rootTree;
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget,QStringList(rootTree->name), ComTool::Def::ITEM_TREE_TYPE);
            item->setIcon(0,*iconHome);
            item->setData(0,Qt::UserRole,QVariant::fromValue(rootTree));
            rootTree->other = QVariant::fromValue(item);
        }

    }

    //m_ShowUserLeft = 0;
    m_ShowYunLeft  = 0;
    //_TurnLeftUserPanel(m_ShowUserLeft);
    _TurnLeftYunPanel(m_ShowYunLeft);

    {
        ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、  Ctrl+A都可以）
        ui->treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
        ui->treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

        if(0 == m_menuTreeWd){
            m_menuTreeWd = new QMenu(ui->treeWidget);

            m_acLink = new QAction(QString::fromLocal8Bit("关联"), ui->treeWidget);   //因为是在QTreeWidget内实现右键，所以以其作为父类
            m_acDel  = new QAction(QString::fromLocal8Bit("删除"), ui->treeWidget);
            m_acAttr  = new QAction(QString::fromLocal8Bit("属性"), ui->treeWidget);

            m_acOpen  = new QAction(QString::fromLocal8Bit("打开"), ui->treeWidget);
            m_acClose  = new QAction(QString::fromLocal8Bit("关闭"), ui->treeWidget);

            m_acAddCamera  = new QAction(QString::fromLocal8Bit("添加设备"), ui->treeWidget);
            m_acAddHome  = new QAction(QString::fromLocal8Bit("添加区域"), ui->treeWidget);

            connect(m_acLink, SIGNAL(triggered(bool)), this , SLOT(triggeredMenuItem(bool)));
            connect(m_acDel, SIGNAL(triggered(bool)), this , SLOT(triggeredMenuItem(bool)));
            connect(m_acAttr, SIGNAL(triggered(bool)), this , SLOT(triggeredMenuItem(bool)));
            connect(m_acOpen, SIGNAL(triggered(bool)), this , SLOT(triggeredMenuItem(bool)));
            connect(m_acClose, SIGNAL(triggered(bool)), this , SLOT(triggeredMenuItem(bool)));
            connect(m_acAddCamera, SIGNAL(triggered(bool)), this , SLOT(triggeredMenuItem(bool)));
            connect(m_acAddHome, SIGNAL(triggered(bool)), this , SLOT(triggeredMenuItem(bool)));

            m_menuTreeWd->setStyleSheet(
                           " QMenu {\n"
                           "border-width: 0px;}\n"
                           "QMenu::item:selected {\n"
                           "background-color:rgba(200,200,200,128);}\n");
        }
    }

    {
        ui->butAB_0->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)UP_LEFT));
        ui->butAB_1->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)TILT_UP));
        ui->butAB_2->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)UP_RIGHT));

        ui->butAB_3->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)PAN_LEFT));
        ui->butAB_4->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)PAN_RIGHT));

        ui->butAB_5->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)DOWN_LEFT));
        ui->butAB_6->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)TILT_DOWN));
        ui->butAB_7->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)DOWN_RIGHT));

        ui->butAB_8->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)ZOOM_IN));
        ui->butAB_9->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)ZOOM_OUT));

        ui->butAB_10->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)FOCUS_NEAR));
        ui->butAB_11->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)FOCUS_FAR));

        ui->butAB_12->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)IRIS_OPEN));
        ui->butAB_13->setProperty(ComTool::Def::PRO_BUTTONKEY, QVariant((int)IRIS_CLOSE));

        QList<QPushButton*> buts;
        buts.push_back(ui->butAB_0);
        buts.push_back(ui->butAB_1);
        buts.push_back(ui->butAB_2);
        buts.push_back(ui->butAB_3);
        buts.push_back(ui->butAB_4);
        buts.push_back(ui->butAB_5);
        buts.push_back(ui->butAB_6);
        buts.push_back(ui->butAB_7);
        buts.push_back(ui->butAB_8);
        buts.push_back(ui->butAB_9);
        buts.push_back(ui->butAB_10);
        buts.push_back(ui->butAB_11);
        buts.push_back(ui->butAB_12);
        buts.push_back(ui->butAB_13);
        for(int i=0,l=buts.length(); i<l; ++i){
            QPushButton*  but = buts.at(i);
            connect(but, SIGNAL(pressed()), this, SLOT(oButABPressed()));
            connect(but, SIGNAL(released()), this, SLOT(oButABReleased()));
        }
        m_speedYunTai = 1;
    }

    {//Link UI
        ui->dSpinBox_Ag->setEnabled(false);
        ui->dSpinBox_AgR_L->setEnabled(false);
        ui->dSpinBox_AgR_R->setEnabled(false);
        ui->cboBox_Row->setEnabled(false);
        ui->cboBox_Col->setEnabled(false);
        ui->cb_shadow->setVisible(false);
    }

    //初始化播放库 HH
    HH5PLAYER_InitSDK((HWND)0);//winId()
    HH5PLAYER_SetDecoderQulity(0);  // 高质量图象显示

    //HC
    NET_DVR_Init();          //Init SDK
    //设置连接时间与重连时间
    //NET_DVR_SetConnectTime(1000, 1);
    //NET_DVR_SetReconnect(10000, true);
}

void PageMain::TurnOffOther(ComTool::NODE_DATA* nodeData){
    if((0 == nodeData && 0 != gSpeekNodeData) ||
       (0 != nodeData && nodeData == gSpeekNodeData)){
        turnSpeekCamera(0, false);
    }
    if((0 == nodeData && 0 != gRecordNodeData) ||
       (0 != nodeData && nodeData == gRecordNodeData)){
        turnRecordCamera(0, false);
    }
    if((0 == nodeData && 0 != gSoundNodeData) ||
       (0 != nodeData && nodeData == gSoundNodeData)){
        turnSoundCamera(0, false);
    }
}
PageMain::~PageMain()
{
    TurnOffOther(0);

    CloseStreamPortAll();
//    if(0 != gStreamPort){
//        CloseHCCameraStream(gStreamPort->nodeData, gStreamPort);
//        delete gStreamPort;
//        gStreamPort = 0;
//    }
//    gStreamPortMap.clear();

    for(int i=0, l=ui->panelvideos->numVideo(); i<l; ++i){
        QYVideoWidget* wd = ui->panelvideos->at(i);
        QVariant qvData = wd->property(ComTool::Def::NODEDATANO);
        if(qvData.isNull()){
            continue;
        }
        ComTool::NODE_DATA* nodeData = qvData.value<ComTool::NODE_DATA*>();
        if(1 == nodeData->qytype){
            if(-1 != (LONG)nodeData->hOpen){
                NET_DVR_StopRealPlay((LONG)nodeData->hOpen);
                nodeData->hOpen = (void*)-1;
            }
            if(-1 != (LONG)nodeData->hLogon){
                NET_DVR_Logout_V30((LONG)nodeData->hLogon);
                nodeData->hLogon = (void*)-1;
            }
        }else{
            if(-1 != (LONG)nodeData->hOpen){
                HHNET_CloseChannel(nodeData->hOpen);
                nodeData->hOpen = (void*)-1;
            }
            if(-1 != (LONG)nodeData->hLogon){
                HHNET_LogoffServer(nodeData->hLogon);
                nodeData->hLogon = (void*)-1;
            }
        }
        QVariant qv = wd->property(ComTool::Def::PLAYERNO);
        if(qv.isNull()){
            continue;
        }
        HH5PLAYER_CloseStream(qv.value<int>());
        HH5PLAYER_ReleasePlayer(qv.value<int>());
    }
    HH5PLAYER_ReleaseSDK();

    //HC
    NET_DVR_Cleanup();

    ComTool::CCommon<QPropertyAnimation>::DeleteA(&m_pAniwd_TabA);
    ComTool::CCommon<QPropertyAnimation>::DeleteA(&m_pAniwd_TabB);
    ComTool::CCommon<QPropertyAnimation>::DeleteA(&m_pAniwd_TabC);

    if(0 != mMovie){mMovie->stop();}
    ComTool::CCommon<QMovie>::DeleteA(&mMovie);
    ComTool::CCommon<QIcon>::DeleteA(&iconLogout);
    ComTool::CCommon<QIcon>::DeleteA(&iconClosed);
    ComTool::CCommon<QIcon>::DeleteA(&iconOpend);
    ComTool::CCommon<QIcon>::DeleteA(&iconHome);
    ComTool::CCommon<QIcon>::DeleteA(&iconHard);

    delete ui;
}
void PageMain::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}

int PageMain::TurnCloseCameraAll_Panel(int nStart)
{
    int sum = 0;
    for(int i=nStart, l=ui->panelvideos->numVideo(); i<l; ++i){
        QYVideoWidget* wd = ui->panelvideos->at(i);
        QVariant qvData = wd->property(ComTool::Def::NODEDATANO);
        if(qvData.isNull()){
            continue;
        }
        ComTool::NODE_DATA* nodeData = qvData.value<ComTool::NODE_DATA*>();
        CloseCameraPanel(nodeData, wd, true);
    }
    return sum;
}
////////////////////////////////////////////////////////////////////////////////

OpenNodeDataTimer::OpenNodeDataTimer(QObject *parent):QTimer(parent){}
OpenNodeDataTimer::~OpenNodeDataTimer(){}
void OpenNodeDataTimer::doFinish(int no){emit sigFinish(no);}
////////////////////////////////////////////////////////////////////////////////

OpenLinkDataTimer::OpenLinkDataTimer(QObject *parent):QTimer(parent){}
OpenLinkDataTimer::~OpenLinkDataTimer(){}
void OpenLinkDataTimer::doFinish(int no){emit sigFinish(no);}
////////////////////////////////////////////////////////////////////////////////

void PageMain::TurnNodeDataPlay(QYVideoWidget* wd, ComTool::NODE_DATA* willData, bool showDlg)
{
    if(0 == wd || 0 == willData){
        return;
    }
    QVariant qvData = wd->property(ComTool::Def::NODEDATANO);
    if(!qvData.isNull()){
        ComTool::NODE_DATA* nodeData = qvData.value<ComTool::NODE_DATA*>();
        if(nodeData == willData){//has opend
            return;
        }else{//close
            if(showDlg){
                int nRes = AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("播放提醒"), QString::fromLocal8Bit("是否替换当前窗口播放 ？"), 2,
                                                         QString::fromLocal8Bit("替换"), QString::fromLocal8Bit("不替换"));
                if(QDialog::Accepted != nRes){
                    return;
                }
            }//end if
            CloseCameraPanel(nodeData, wd, false);
        }
    }

    if(-1 != (LONG)willData->hOpen && !(willData->otheA.isNull())){//close
        QYVideoWidget* wda = willData->otheA.value<QYVideoWidget*>();
        CloseCameraPanel(willData, wda, false);
    }

    OpenCameraPanel(willData, wd);
}
void PageMain::TurnCloseCamera(QYVideoWidget* wd)
{
    int modeUserLeft = AppZZB::getInstance()->showUserLeft();
    if(0 == wd && 0 == modeUserLeft){
        TurnCloseCameraAll_Panel(0);
        return;
    }

    bool ret = true;
    bool refreshUI = true;
    bool powerClose = false;

    //if(0 != gStreamPort && wd == gStreamPort->wd){
    if(hasStreamPort(wd)){
        ret = turnPanoClose(wd);
        if(ret){
            refreshUI   = false;
            powerClose  = true;
        }
    }
    if(!ret){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("关闭提醒"), QString::fromLocal8Bit("请先关闭分屏"), 0);
        return;
    }

    if(0 == modeUserLeft){
        int curSel = ui->panelvideos->curSel();
        if(-1 == curSel){
            return;
        }
        if(0 == wd){
             wd = ui->panelvideos->at(curSel);
        }
        QVariant qv = wd->property(ComTool::Def::NODEDATANO);
        if(qv.isNull()){
            return;
        }
        ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();

        int nRes = CloseCamera(nodeData, wd, 0, refreshUI, powerClose);
        if(2 == nRes && !nodeData->other.isNull()){
            QTreeWidgetItem *item = nodeData->other.value<QTreeWidgetItem*>();
            if(0 != item){
                item->setIcon(0,QIcon(":/images/ap2000/tree_close"));
            }
        }//Update Tree Widget
    }else if(1 == modeUserLeft){
        QYVideoWidget* curSelA = 0;
        QYVideoWidget* curSelB = 0;

        if(0 != wd){
            curSelA = wd;
        }else{
            _GotCurSelQQ(curSelA, curSelB);
        }
        ComTool::LINK_DATA* link = 0;
        if(0 != curSelA){
            QVariant qv = curSelA->property(ComTool::Def::NODELINKNO);
            if(!qv.isNull()){link = qv.value<ComTool::LINK_DATA*>();}
        }

        QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(link);
        int nRes = CloseCameraLink(link);
        if(2 == nRes){
            if(!link->other.isNull()){
                QTableWidgetItem* item = link->other.value<QTableWidgetItem*>();
                if(0 != item){
                    item->setIcon(*iconClosed);
                }
            }
            if(link->isLinked && 0 != wdPano){
                ui->cb_Linked->setChecked(false);
                wdPano->enableTrack(false);
                wdPano->enableClick(false);
                disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
            }
        }
        if(AppZZB::getInstance()->IsFullScreen()){
            QYDlgFullCtrlLink* dlgFullCtrlLink = AppZZB::getInstance()->GetFullCtrlLink();
            if(0 != dlgFullCtrlLink){dlgFullCtrlLink->TurnCurItem(-1);}
        }

    }//End If
}

void PageMain::TurnFullScreen(bool full)
{
    int modeUserLeft = AppZZB::getInstance()->showUserLeft();
    QYPanelVideo* panelVideo = ui->panelvideos;
    if(1 == modeUserLeft){
        panelVideo = ui->wdRPageA_Top;
        if(full){
            AppZZB::getInstance()->TurnShowDlgFullCtrlLink(full);
        }
    }

    //bool fullPanelVideos = panelVideo->isFullScreen();
    if(full){// && !fullPanelVideos
        QRect rt = panelVideo->geometry();
        panelVideo->setProperty(ComTool::Def::SAVERECT, rt);
        panelVideo->setWindowFlags(Qt::Window);
        panelVideo->showFullScreen();
        QRect rtFull = AppZZB::getInstance()->GetDesktopRt();
        panelVideo->setGeometry(rtFull);
        panelVideo->UpdateGeometry(panelVideo->row(),panelVideo->col());
        panelVideo->installEventFilter(this);

    }else{// if(fullPanelVideos)
        panelVideo->setWindowFlags(Qt::Widget);
        QRect rt = panelVideo->property(ComTool::Def::SAVERECT).value<QRect>();
        panelVideo->setGeometry(rt);
        panelVideo->showNormal();
        panelVideo->UpdateGeometry(panelVideo->row(),panelVideo->col());
        panelVideo->removeEventFilter(this);
    }
    for(int i=0, l= panelVideo->row()*panelVideo->col(); i<l; ++i){
        QYVideoWidget* wd = panelVideo->at(i);
        _VisibleVideo(wd, false);
    }
    QTimer* timer = new QTimer(this);
    timer->setProperty(ComTool::Def::REFRESHVIDEOS, QVariant::fromValue(panelVideo));
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh_PanelVideos()));
    timer->start(1000);

    if(1 == modeUserLeft){
        AppZZB::getInstance()->TurnShowDlgFullCtrlLink(full);
    }
}
bool PageMain::eventFilter(QObject *watched, QEvent *event)
{
    unsigned int nType = event->type();
    if (QEvent::KeyPress == nType){
        QKeyEvent* evKey = (QKeyEvent*)event;
        if(Qt::Key_Escape ==  evKey->key()){
            if(watched->inherits("QYPanelVideo")){
                QYPanelVideo* p = (QYPanelVideo*)watched;
                if(!isFullScreenCamera(0) && AppZZB::getInstance()->IsFullScreen()){
                    AppZZB::getInstance()->TurnFullScreen(false);
                }
//                if(p->isFullScreen()){
//                    AppZZB::getInstance()->TurnFullScreen(false);
//                }
            }
        }//Key Value

    }
    return QWidget::eventFilter(watched, event);
}
void PageMain::oChanagedSize(bool bMax)
{
    _TurnLeftTab(m_ShowModeLeft);
}
void PageMain::oChanagedPage(int curPage)
{
    int l=mPageContent.size();
    if(l < 1){return;}

    {
        QWidget* pWd = mPageContent.at(0);
        if(pWd->isVisible() && (0 != curPage)){//close
            int modeUserLeft = AppZZB::getInstance()->showUserLeft();
            _GotResumeDatas(modeUserLeft);
            if(resumeDatas.length() > 0 || resumeLinks.length() > 0){
                AppZZB::getInstance()->TurnShowDlgLoading(true);
                QTimer* timer = new QTimer(this);
                QList<QPoint> pts;
                pts.push_back(QPoint(modeUserLeft,0));
                timer->setProperty(ComTool::Def::REFRESHVIDEOPANEL, QVariant::fromValue(pts));
                timer->setSingleShot(true);
                connect(timer, SIGNAL(timeout()), this, SLOT(resume_PanelVideos()));
                timer->start(100);
            }
        }else if(!(pWd->isVisible()) && (0 == curPage)){//open
            int modeUserLeft = AppZZB::getInstance()->showUserLeft();
            if(resumeDatas.length() > 0 || resumeLinks.length() > 0){
                AppZZB::getInstance()->TurnShowDlgLoading(true);
                QTimer* timer = new QTimer(this);
                QList<QPoint> pts;
                pts.push_back(QPoint(modeUserLeft,1));
                timer->setProperty(ComTool::Def::REFRESHVIDEOPANEL, QVariant::fromValue(pts));
                timer->setSingleShot(true);
                connect(timer, SIGNAL(timeout()), this, SLOT(resume_PanelVideos()));
                timer->start(100);
            }
        }
    }

    {//PlayBack Page
        QWidget* pWd = mPageContent.at(1);
        if(pWd->isVisible() && (1 != curPage)){//close
            AppZZB::getInstance()->setState(AppZZB::ST_OK);
            int subPage = AppZZB::getInstance()->showPlayBackSubPage();
            if(0 == subPage){
                ui->wdPlayBack_Local->Exit();
            }else{
                ui->wdPlayBack_Net->Exit();
            }
        }else if(!pWd->isVisible() && (1 == curPage)){//Open
            AppZZB::getInstance()->setState(AppZZB::ST_PLAYBACK);
            int subPage = AppZZB::getInstance()->showPlayBackSubPage();
            if(0 == subPage){
                ui->wdPlayBack_Local->Enter();
            }else{
                ui->wdPlayBack_Net->Enter();
            }
            _TurnLeftTab(0);
        }
    }

    for(int i=0; i<l; ++i){
        QWidget* pWd = mPageContent.at(i);
        pWd->setVisible(i == curPage);
    }
}
void PageMain::oChanagedShow(int curShow, int flag)
{
    if(0 == ui->panelvideos){return;}
    int nSizeVideo = curShow*curShow;
    QSize rowCol = QSize(curShow,curShow);
    ui->panelvideos->setSizeLabVideo(nSizeVideo);
    ui->panelvideos->UpdateGeometry(rowCol.width(), rowCol.height());

    int curSel = ui->panelvideos->curSel();
    if(-1 == curSel){
        ui->panelvideos->select(0);
    }

    QYPanelVideo* panelVideo = ui->panelvideos;
    for(int i=0, l= panelVideo->row()*panelVideo->col(); i<l; ++i){
        QYVideoWidget* wd = panelVideo->at(i);
        _VisibleVideo(wd, false);
    }
    if(0 == flag){
        QTimer* timer = new QTimer(this);
        timer->setProperty(ComTool::Def::REFRESHVIDEOS, QVariant::fromValue(panelVideo));
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(refresh_PanelVideos()));
        timer->start(1000);
    }
}
void PageMain::_VisibleVideo(QYVideoWidget* wd, bool show)
{
    if(!show){
        wd->showWidget()->setProperty(ComTool::Def::PRO_VISIBLE, QVariant(wd->showWidget()->isVisible()));
        wd->showWidget()->setVisible(false);
        QWidget* pano = wd->rootWidget()->findChild<QWidget*>("pano");
        if( 0  !=pano){
            pano->setProperty(ComTool::Def::PRO_VISIBLE, QVariant(pano->isVisible()));
            pano->setVisible(false);
        }
    }else{
        wd->_UpdatePosSize();

        QVariant qvVisible = wd->showWidget()->property(ComTool::Def::PRO_VISIBLE);
        wd->showWidget()->setVisible(qvVisible.toBool());
        wd->showWidget()->setProperty(ComTool::Def::PRO_VISIBLE, QVariant());
        QWidget* wdRoot = wd->rootWidget();
        QWidget* pano   = wd->rootWidget()->findChild<QWidget*>("pano");
        if(0 != pano){
            qvVisible = pano->property(ComTool::Def::PRO_VISIBLE);
            pano->setProperty(ComTool::Def::PRO_VISIBLE, QVariant());
            pano->setGeometry(QRect(0, 0, wdRoot->width(), wdRoot->height()));
            pano->setVisible(qvVisible.toBool());
        }
    }
}
void PageMain::oChanagedShowUserLeft(int modeUserLeft)
{
    static const QString ssDown = QString().sprintf("rgba(56,82,72,255)");
    static const QString ssUp = QString().sprintf("rgba(102,102,102,255)");
    ComTool::Tool::updateSS_bkColor(ui->butAA_A, (0==modeUserLeft) ? ssDown : ssUp);
    ComTool::Tool::updateSS_bkColor(ui->butAA_B, (1==modeUserLeft) ? ssDown : ssUp);

    ui->wdLeft_UserPanel->setVisible(0==modeUserLeft);
    ui->wdLeft_QQPanel->setVisible(1==modeUserLeft);

    //
    ui->panelvideos->setVisible(0==modeUserLeft);
    ui->panelvideos_QQ->setVisible(1==modeUserLeft);

    if(1 == modeUserLeft){
        if(0 == ui->wdRPageA_Bot->numVideo()){
            ui->wdRPageA_Bot->setFlagUI(0);
            ui->wdRPageA_Bot->setSizeLabVideo(4);
            ui->wdRPageA_Bot->UpdateGeometry(1,4);
            for(int i=0, l=ui->wdRPageA_Bot->numVideo(); i<l; ++i){
                QYVideoWidget* wd = ui->wdRPageA_Bot->at(i);
                connect(wd, SIGNAL(sigDoubleClicked()), this, SLOT(oSigDoubleClicked_RPageA_Bot()));
            }
        }
        if(0 == ui->wdRPageA_Top->numVideo()){
            ui->wdRPageA_Top->setFlagUI(1);
            ui->wdRPageA_Top->setSizeLabVideo(2);
            ui->wdRPageA_Top->UpdateGeometry(1,2);
            ui->wdRPageA_Top->select(0);
        }
       _GotResumeDatas(0);
    }else{
       _GotResumeDatas(1);
    }
    if(resumeDatas.length() > 0 || resumeLinks.length() > 0){
        AppZZB::getInstance()->TurnShowDlgLoading(true);
        QTimer* timer = new QTimer(this);
        QList<QPoint> pts;
        if(1 == modeUserLeft){
            pts.push_back(QPoint(0,0));pts.push_back(QPoint(1,1));
        }else if(0 == modeUserLeft){
            pts.push_back(QPoint(1,0));pts.push_back(QPoint(0,1));
        }
        timer->setProperty(ComTool::Def::REFRESHVIDEOPANEL, QVariant::fromValue(pts));
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(resume_PanelVideos()));
        timer->start(100);
    }
}
void PageMain::oChanagedShowBKSubPage(int subPage)
{
    if(1 == subPage){
        if(!ui->wdPlayBack_Net->isVisible()){
            ui->wdPlayBack_Net->setVisible(true);
            ui->wdPlayBack_Net->Enter();
        }
        if(ui->wdPlayBack_Local->isVisible()){
            ui->wdPlayBack_Local->setVisible(false);
            ui->wdPlayBack_Local->Exit();
        }
    }else if(0 == subPage){
        if(ui->wdPlayBack_Net->isVisible()){
            ui->wdPlayBack_Net->Exit();
            ui->wdPlayBack_Net->setVisible(false);
        }
        if(!ui->wdPlayBack_Local->isVisible()){
            ui->wdPlayBack_Local->setVisible(true);
            ui->wdPlayBack_Local->Enter();
        }
    }
}
void PageMain::oChanagedTreeNode(QTreeWidgetItem* nodeItem, void* pData, int type)
{
    if(1 == type && 0 != pData){
        PageMain::treeAddNodeData(nodeItem, (ComTool::NODE_DATA*)pData);
    }else if(2 == type && 0 != pData){
        PageMain::treeAddNodeTree(nodeItem, (ComTool::NODE_TREE*)pData);
    }else{
        PageMain::refreshTreeNode(nodeItem, false);
    }

//    if(ComTool::Def::ITEM_DATA_TYPE == nodeItem->type()){
//        return;
//    }



//    ComTool::NODE_TREE* nodeTree = nodeItem->data(0, Qt::UserRole).value<ComTool::NODE_TREE*>();

//    bool bRes = false;
//    for(int i=0, n=nodeTree->children.size(); i<n; ++i){
//        ComTool::NODE_DATA* nodeData = nodeTree->children[i];
//        if(!nodeData->other.isNull()){
//            continue;
//        }
//        QTreeWidgetItem *child = new QTreeWidgetItem(nodeItem,QStringList(nodeData->name),ComTool::Def::ITEM_DATA_TYPE);
//        child->setIcon(0, *iconLogout);
//        child->setData(0, Qt::UserRole, QVariant::fromValue(nodeData));
//        nodeData->other = QVariant::fromValue(child);
//        bRes = true;
//    }

//    for(int i=0, l=nodeTree->nodes.size(); i<l; ++i){
//        ComTool::NODE_TREE* nodeChild = nodeTree->nodes.at(i);
//        if(nodeChild->other.isNull()){
//            QTreeWidgetItem *item = new QTreeWidgetItem(nodeItem,QStringList(nodeChild->name), ComTool::Def::ITEM_TREE_TYPE);
//            item->setIcon(0,*iconHome);
//            item->setData(0,Qt::UserRole,QVariant::fromValue(nodeChild));
//            nodeChild->other = QVariant::fromValue(item);
//        }
//        bRes = true;
//    }

//    if(bRes){
//       nodeItem->setExpanded(true);
//    }
}
bool PageMain::treeAddNodeData(QTreeWidgetItem* nodeItem, ComTool::NODE_DATA* nodeData)
{
    if(!nodeData->other.isNull()){
        return false;
    }
    QTreeWidgetItem *child = new QTreeWidgetItem(nodeItem,QStringList(nodeData->name),ComTool::Def::ITEM_DATA_TYPE);
    bool isLogin = ((void*)-1 != nodeData->hLogon);
    child->setIcon(0, isLogin ? *iconClosed : *iconLogout);
    child->setData(0, Qt::UserRole, QVariant::fromValue(nodeData));
    nodeData->other = QVariant::fromValue(child);

    nodeItem->setExpanded(true);
}
bool PageMain::treeAddNodeTree(QTreeWidgetItem* nodeItem, ComTool::NODE_TREE* nodeTree)
{
   if(!nodeTree->other.isNull()){
        return false;
    }
    QTreeWidgetItem *item = new QTreeWidgetItem(nodeItem,QStringList(nodeTree->name), ComTool::Def::ITEM_TREE_TYPE);
    bool isHard = ComTool::NodeTreeHelper::isHard(nodeTree);
    item->setIcon(0, isHard ? *iconHard : *iconHome);
    item->setData(0,Qt::UserRole,QVariant::fromValue(nodeTree));
    nodeTree->other = QVariant::fromValue(item);

    PageMain::refreshTreeNode(item, true);
    nodeItem->setExpanded(true);
    return true;
}
void PageMain::refreshTreeNode(QTreeWidgetItem* nodeItem, bool deep)
{
    if(ComTool::Def::ITEM_DATA_TYPE == nodeItem->type()){
        return;
    }

    ComTool::NODE_TREE* nodeTree = nodeItem->data(0, Qt::UserRole).value<ComTool::NODE_TREE*>();

    bool bRes = false;
    for(int i=0, n=nodeTree->children.size(); i<n; ++i){
        ComTool::NODE_DATA* nodeData = nodeTree->children[i];
        QTreeWidgetItem *child = 0;
        if(nodeData->other.isNull()){
            child = new QTreeWidgetItem(nodeItem,QStringList(nodeData->name),ComTool::Def::ITEM_DATA_TYPE);
        }else{
           child = nodeData->other.value<QTreeWidgetItem *>();
        }
        bool isLogin = ((void*)-1 != nodeData->hLogon);
        child->setIcon(0, isLogin ? *iconClosed : *iconLogout);
        child->setData(0, Qt::UserRole, QVariant::fromValue(nodeData));
        nodeData->other = QVariant::fromValue(child);
        bRes = true;
    }

    for(int i=0, l=nodeTree->nodes.size(); i<l; ++i){
        ComTool::NODE_TREE* nodeChild = nodeTree->nodes.at(i);
        QTreeWidgetItem *item = 0;
        if(nodeChild->other.isNull()){
            item = new QTreeWidgetItem(nodeItem,QStringList(nodeChild->name), ComTool::Def::ITEM_TREE_TYPE);
        }else{
            item = nodeChild->other.value<QTreeWidgetItem *>();
        }
        bool isHard = ComTool::NodeTreeHelper::isHard(nodeChild);
        item->setIcon(0, isHard ? *iconHard : *iconHome);
        item->setData(0,Qt::UserRole,QVariant::fromValue(nodeChild));
        nodeChild->other = QVariant::fromValue(item);
        bRes = true;
    }

    if(bRes){
       nodeItem->setExpanded(true);
    }

    if(!deep){return;}

     for(int i=0, l=nodeTree->nodes.size(); i<l; ++i){
        ComTool::NODE_TREE* nodeChild = nodeTree->nodes.at(i);
        QTreeWidgetItem *item = nodeChild->other.value<QTreeWidgetItem*>();
        PageMain::refreshTreeNode(item);
     }
}

void PageMain::oAddLink(ComTool::LINK_DATA* link)
{
    if(0 == link){return;}

    int n = ui->tableWidget_qq->rowCount();
    ui->tableWidget_qq->insertRow(n);
    {
        QTableWidgetItem* item = new QTableWidgetItem(link->name);
        item->setIcon(*iconClosed);
        item->setData(Qt::UserRole,QVariant::fromValue(link));
        link->other = QVariant::fromValue(item);
        ui->tableWidget_qq->setItem(n, 0, item);
    }
    ui->tableWidget_qq->setItem(n, 1, new QTableWidgetItem(link->pano->name));
    ui->tableWidget_qq->setItem(n, 2, new QTableWidgetItem(link->sphere->name));
}

void PageMain::on_butOpenImage_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("图片抓取文件保存路径:"),QString::fromLocal8Bit("./"));
    if(file_path.isEmpty()){
        return;
    }
    ui->label_PathImage->setText(file_path);
}

void PageMain::on_butOpenVideo_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("图片抓取文件保存路径:"),QString::fromLocal8Bit("./"));
    if(file_path.isEmpty()){
        return;
    }
    ui->label_PathVideo->setText(file_path);
}
//Page3
void PageMain::on_butSaveCfg_clicked()
{
    AppZZB::getInstance()->SetSavePath(ui->cbJPEG->isChecked() ? QString(".jpg") : QString(".bmp"), 2);
    AppZZB::getInstance()->SetSavePath(ui->label_PathImage->text(), 0);
    AppZZB::getInstance()->SetSavePath(ui->label_PathVideo->text(), 1);

    AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("配置文件"), QString::fromLocal8Bit("保存成功！"), 0);
}

void PageMain::on_butAA_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    if(0 == m_ShowModeLeft){return;}
    _TurnLeftTab(0);
}

void PageMain::on_butAB_clicked()
{
    if(AppZZB::ST_PLAYBACK == AppZZB::getInstance()->state()){return;}
    if(1 == m_ShowModeLeft){return;}
    _TurnLeftTab(1);
}

void PageMain::on_butAC_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PLAYBACK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    if(2 == m_ShowModeLeft){return;}
    _TurnLeftTab(2);
}

void PageMain::_TurnLeftTab(int modeLeft)
{
    m_ShowModeLeft = modeLeft;
    int hLeft = ui->wdLeft->height();
    int hBut  = ui->butAA->height();
    int hD    = (int)(hBut*4.0/28.0);

    {//TabA
        QRect rtCur = ui->tabA->geometry();
        QRect rtDst = QRect(rtCur.left(), 0, rtCur.width(), hLeft-(hBut+hD)*2);
        if(1 == m_ShowModeLeft){
            rtDst = QRect(rtCur.left(), 0, rtCur.width(), hBut);
        }else if(2 == m_ShowModeLeft){
            rtDst = QRect(rtCur.left(), 0, rtCur.width(), hBut);
        }

        QWidget* pWd  = ui->tabA;
        QPropertyAnimation* &pAniwd = m_pAniwd_TabA;
        if(0 == pAniwd){
            pAniwd = new QPropertyAnimation(pWd, "geometry");
        }
        pAniwd->setDuration(ComTool::Def::DURATION);
        pAniwd->setStartValue(rtCur);
        pAniwd->setEndValue(rtDst);
        pAniwd->start();
    }


    {//TabB
        QRect rtCur = ui->tabB->geometry();
        QRect rtDst = QRect(rtCur.left(), hLeft-hBut*2-hD, rtCur.width(), hBut);
        if(1 == m_ShowModeLeft){
            rtDst = QRect(rtCur.left(), hBut+hD, rtCur.width(), hLeft-(hBut+hD)*2);
        }else if(2 == m_ShowModeLeft){
            rtDst = QRect(rtCur.left(), hBut+hD, rtCur.width(), hBut);
        }

        QWidget* pWd  = ui->tabB;
        QPropertyAnimation* &pAniwd = m_pAniwd_TabB;
        if(0 == pAniwd){
            pAniwd = new QPropertyAnimation(pWd, "geometry");
        }
        pAniwd->setDuration(ComTool::Def::DURATION);
        pAniwd->setStartValue(rtCur);
        pAniwd->setEndValue(rtDst);
        pAniwd->start();
    }

    {//TabC
        QRect rtCur = ui->tabC->geometry();
        QRect rtDst = QRect(rtCur.left(), hLeft-hBut, rtCur.width(), hBut);
        if(1 == m_ShowModeLeft){
            rtDst = QRect(rtCur.left(), hLeft-hBut, rtCur.width(), hBut);
        }else if(2 == m_ShowModeLeft){
            rtDst = QRect(rtCur.left(), hBut*2+hD*2, rtCur.width(), hLeft-(hBut+hD)*2);
        }

        QWidget* pWd  = ui->tabC;
        QPropertyAnimation* &pAniwd = m_pAniwd_TabC;
        if(0 == pAniwd){
            pAniwd = new QPropertyAnimation(pWd, "geometry");
        }
        pAniwd->setDuration(ComTool::Def::DURATION);
        pAniwd->setStartValue(rtCur);
        pAniwd->setEndValue(rtDst);
        pAniwd->start();
    }

    std::string ssCur = AppZZB::getInstance()->StyleCur().toStdString();
    QString upSS    = QString().sprintf("url(\":/%s/036_0\")", ssCur.c_str());
    QString downSS  = QString().sprintf("url(\":/%s/036_1\")", ssCur.c_str());

    ComTool::Tool::updateSS_bkImage(ui->butAA, (0==m_ShowModeLeft) ? downSS : upSS);
    ComTool::Tool::updateSS_bkImage(ui->butAB, (1==m_ShowModeLeft) ? downSS : upSS);
    ComTool::Tool::updateSS_bkImage(ui->butAC, (2==m_ShowModeLeft) ? downSS : upSS);

}

void PageMain::on_butAA_A_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnLeftUserPanel(0);
}

void PageMain::on_butAA_B_clicked()
{
    if(AppZZB::ST_PLAYBACK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnLeftUserPanel(1);
}

void PageMain::on_butAB_A_clicked()
{
    if(0==m_ShowYunLeft){return;}
    _TurnLeftYunPanel(0);
}

void PageMain::on_butAB_B_clicked()
{
    if(1==m_ShowYunLeft){return;}
    _TurnLeftYunPanel(1);
}

void PageMain::_TurnLeftYunPanel(int modeYunLeft)
{
    m_ShowYunLeft = modeYunLeft;

    static const QString ssDown = QString().sprintf("rgba(56,82,72,255)");
    static const QString ssUp = QString().sprintf("rgba(102,102,102,255)");
    ComTool::Tool::updateSS_bkColor(ui->butAB_A, (0==m_ShowYunLeft) ? ssDown : ssUp);
    ComTool::Tool::updateSS_bkColor(ui->butAB_B, (1==m_ShowYunLeft) ? ssDown : ssUp);

    ui->wdLeft_YunA->setVisible(0==m_ShowYunLeft);
    ui->wdLeft_YunB->setVisible(1==m_ShowYunLeft);
}
void PageMain::on_butAA_Add_A_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnShowDlgCameraAdd(true);
}
//添加区域
void PageMain::on_butAA_Add_B_clicked()
{
    if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
    AppZZB::getInstance()->TurnShowDlgCameraAddHome(true);
}
static int WINAPI QYChannelStreamCallback(HANDLE hOpenChannel,void *pStreamData,DWORD dwClientID,void *pContext,ENCODE_VIDEO_TYPE encodeVideoType,HHAV_INFO *pAVInfo){
    WORD			wDisplayNo  = (WORD)pContext;   //播放器编号
    DWORD			dwFrameSize = 0;
    HV_FRAME_HEAD	*pFrameHead = (HV_FRAME_HEAD *)pStreamData;
    //EXT_FRAME_HEAD  *pExtFrameHead = (EXT_FRAME_HEAD  *)((char *)pStreamData + sizeof(HV_FRAME_HEAD));

    if(0 == pFrameHead){return -1;}


    int	ret = 0;
    //HHERR_CODE	errCode = HHERR_SUCCESS;
    dwFrameSize = sizeof(HV_FRAME_HEAD) + pFrameHead->nByteNum;


//    if (FRAME_FLAG_VI == pFrameHead->streamFlag || FRAME_FLAG_VP == pFrameHead->streamFlag)
//        {

//        static int dwWriteN = 0;
//        static FILE* pFileR= 0;
//        if(dwWriteN++ < 1)
//        {
//            if(NULL == pFileR)
//                pFileR = fopen("D://VI.h264","w+b");

//            DWORD ret = fwrite((BYTE*)pStreamData+sizeof(HV_FRAME_HEAD)+sizeof(EXT_FRAME_HEAD),1,
//            pFrameHead->nByteNum-sizeof(EXT_FRAME_HEAD),pFileR);
////
//  //          ASSERT(ret == pFrameHead->nByteNum-sizeof(EXT_FRAME_HEAD));
//        }
//        else
//        {
//            if(pFileR)
//                fclose(pFileR);
//        }

//        }

    //送播放库显示
    ret = HH5PLAYER_PutDecStreamDataEx(
                    wDisplayNo,      //播放器编号
                    (BYTE *) pStreamData,
                    dwFrameSize,
                    encodeVideoType,
                    (HH5KAV_INFO *)pAVInfo);
    return ret;
}
int PageMain::OpenHHCamera(ComTool::NODE_DATA* nodeData, int PlayerNo)
{
    if(-1 != (LONG)nodeData->hOpen){
        return -1;
    }
    HHOPEN_CHANNEL_INFO_EX openInfo_ex ;
    openInfo_ex.nSubChannel  = nodeData->nStream;//1; 0=主流 1=子流
    openInfo_ex.dwClientID   = nodeData->dwChannelNo;
    openInfo_ex.nOpenChannel = nodeData->dwChannelNo;
    openInfo_ex.res          = 100;
    openInfo_ex.protocolType = NET_PROTOCOL_TCP;
    openInfo_ex.funcStreamCallback = QYChannelStreamCallback;
    openInfo_ex.pCallbackContext   = (void*)PlayerNo; //播放器编号

    HHERR_CODE errCode = HHERR_SUCCESS;
    errCode = HHNET_OpenChannel(const_cast<char*>(nodeData->szIp.toStdString().c_str()),
                                nodeData->port,
                                const_cast<char*>(nodeData->szDeviceName.toStdString().c_str()),
                                const_cast<char*>(nodeData->szUserName.toStdString().c_str()),
                                const_cast<char*>(nodeData->szUserPsw.toStdString().c_str()),
                                (HHOPEN_CHANNEL_INFO*)&openInfo_ex,
                                nodeData->hOpen);
    if(HHERR_SUCCESS != errCode){
        nodeData->hOpen =(void*) -1;
        return errCode;
    }

    HH_CHANNEL_INFO channelInfo;
    memset(&channelInfo,0,sizeof(HH_CHANNEL_INFO));
    errCode = HHNET_ReadChannelInfo(nodeData->hOpen, channelInfo);
    if(HHERR_SUCCESS == errCode){
        nodeData->vWidth = channelInfo.avInformation.nVideoWidth;
        nodeData->vHeight = channelInfo.avInformation.nVideoHeight;
    }

    return 0;
}
int PageMain::CloseHHCamera(ComTool::NODE_DATA* nodeData)
{
    if(-1 == (LONG)nodeData->hOpen){
        return -1;
    }
    TurnOffOther(nodeData);

    HHERR_CODE errCode = HHERR_SUCCESS;
    errCode = HHNET_CloseChannel(nodeData->hOpen);
    if(HHERR_SUCCESS != errCode){
        return errCode;
    }
    nodeData->hOpen = (void*)-1;
    return 0;
}

int PageMain::OpenHCCamera(ComTool::NODE_DATA* nodeData, HWND hwnd)
{
    if(-1 != (LONG)nodeData->hOpen){
        return -1;
    }

    NET_DVR_CLIENTINFO ClientInfo;
    ClientInfo.hPlayWnd     = hwnd;
    ClientInfo.lChannel     = nodeData->dwChannelNo;//1
    ClientInfo.lLinkMode    = 0;
    if(1 == nodeData->nStream){
        ClientInfo.lLinkMode = 1<<31;
    }
    ClientInfo.sMultiCastIP = 0;
    nodeData->hOpen = (void*)NET_DVR_RealPlay_V30((LONG)nodeData->hLogon,&ClientInfo,NULL,NULL,TRUE);
    if(-1 == (LONG)nodeData->hOpen){
        DWORD err=NET_DVR_GetLastError();
        return err;
    }
    return 0;
}
int PageMain::OpenHCCameraStream(ComTool::NODE_DATA* nodeData, HCStreamCB* streamPort)
{
    if(-1 != (LONG)nodeData->hOpen){
        return -1;
    }
    NET_DVR_CLIENTINFO ClientInfo;
    ClientInfo.hPlayWnd = NULL;  //窗口为空，设备SDK不解码只取流
    ClientInfo.lChannel = nodeData->dwChannelNo; //Channel number 设备通道号
    ClientInfo.lLinkMode    = 0;    //Main Stream
    ClientInfo.sMultiCastIP = 0;

    //gStreamPort = streamPort;
    //预览取流
    //qWarning()<<"gStreamPort 0: "<<gStreamPort;
    nodeData->hOpen = (void*)NET_DVR_RealPlay_V30((LONG)nodeData->hLogon, &ClientInfo, gRealDataCallBack,streamPort,TRUE);
    if(-1 == (LONG)nodeData->hOpen){
        //gStreamPort = 0;
        DWORD err=NET_DVR_GetLastError();
        return err;
    }
    return 0;
}
int PageMain::CloseHCCameraStream(ComTool::NODE_DATA* nodeData, HCStreamCB* streamPort)
{
    if(-1 == (LONG)nodeData->hOpen || 0 == streamPort){
        return -1;
    }

    TurnOffOther(nodeData);
    //停止预览
    if(!NET_DVR_StopRealPlay((LONG)(nodeData->hOpen))){
        return -1;
    }

    nodeData->hOpen = (void*)-1;

    LONG& nPort = streamPort->mPort;

    if (!PlayM4_Stop(nPort)){
        DWORD err = PlayM4_GetLastError(nPort);
    }
    if (!PlayM4_CloseStream(nPort)){
        DWORD err = PlayM4_GetLastError(nPort);
    }
    PlayM4_FreePort(nPort);
    nPort = -1;

    return 0;
}
int PageMain::CloseHCCamera(ComTool::NODE_DATA* nodeData)
{
    if(-1 == (LONG)nodeData->hOpen){
        return -1;
    }
    TurnOffOther(nodeData);

    if(!NET_DVR_StopRealPlay((LONG)(nodeData->hOpen))){
        return -1;
    }
    nodeData->hOpen = (void*)-1;
    return 0;
}
int PageMain::OpenCameraPanel(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd)
{
    int nRes = OPenCamera(nodeData, wd, 0);
    if(1 == nRes && !nodeData->other.isNull()){
        QTreeWidgetItem *item = nodeData->other.value<QTreeWidgetItem*>();
        if(0 != item){
            item->setIcon(0,*iconOpend);
        }
    }//Update Tree Widget
    return nRes;
}
int PageMain::CloseCameraPanel(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd, bool refreshUI)
{
    bool powerClose = false;
    //if(0 != gStreamPort && wd == gStreamPort->wd){
    if(hasStreamPort(wd)){
        bool ret = turnPanoClose(wd);
        if(ret){
            refreshUI   = false;
            powerClose  = true;
        }
    }

    int sum = 0;
    int nRes = CloseCamera(nodeData, wd, 0, refreshUI, powerClose);
    if(2 == nRes && !nodeData->other.isNull()){
        QTreeWidgetItem *item = nodeData->other.value<QTreeWidgetItem*>();
        if(0 != item){
            item->setIcon(0,*iconClosed);
        }
        sum = 1;
    }//Update Tree Widget

    QVariant qv = wd->property(ComTool::Def::PLAYERNO);
    if(!qv.isNull()){
        HH5PLAYER_CloseStream(qv.value<int>());
        HH5PLAYER_ReleasePlayer(qv.value<int>());
        wd->setProperty(ComTool::Def::PLAYERNO, QVariant());
    }

    return sum;
}
int PageMain::CloseCamera(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd, int flag, bool refreshUI, bool power)
{
    if(0 == nodeData || 0 == wd){return -1;}
    int nRes = power ? 2 : -1;

    if(1 == nodeData->qytype){//HC Camera
        if(-1 != (LONG)nodeData->hOpen){//close Camera
            if(0 == CloseHCCamera(nodeData)){
                nRes = 2;
            }
        }
    }else{//HH Camera
        if(-1 != (LONG)nodeData->hOpen){//Open Camera
            if(0 == CloseHHCamera(nodeData)){
                nRes = 2;
            }
        }
    }//End HH Camera
    if(2 == nRes){
        //QWidget* wdShow = wd->showWidget();
        //ClearHwnd((HWND)(wdShow->winId()));//Clear
        if(1 == nodeData->qytype && 1 == nodeData->imgtype){//HC Sphere
            _TurnSphere3DPTZ(nodeData);
//            QYVideoWidget* wdSphere = wd;
//            wdSphere->enableClick(false);
//            wdSphere->enableWheel(false);
//            wdSphere->showWidget()->setCursor(Qt::ArrowCursor);
//            disconnect(wdSphere, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
//            disconnect(wdSphere, SIGNAL(sigTrackRect(QWidget*, QVector2D, QVector2D)), this, SLOT(oSigTrackRect(QWidget*, QVector2D, QVector2D)));
//            disconnect(wdSphere, SIGNAL(sigTrackWheel(QWidget*, qreal)), this, SLOT(oSigTrackWheel(QWidget*, qreal)));
//            wdSphere->setProperty(ComTool::Def::SPHERE_SIGTRACK, QVariant());
        }

        if(0 == flag){
            nodeData->otheA = QVariant();
        }else{
            nodeData->otheB = QVariant();
        }
        wd->setProperty(ComTool::Def::NODEDATANO, QVariant());

        //刷新
        //this->setProperty(ComTool::Def::REFRESHID, QVariant::fromValue(wd));
        //QTimer::singleShot(1000,this,SLOT(refresh_PanelVideos()));

        wd->showWidget()->setVisible(false);
//        if(refreshUI){
//            PageMain* pageMain = AppZZB::getInstance()->pageMain;
//            QTimer* timer = new QTimer(pageMain);
//            timer->setProperty(ComTool::Def::REFRESHID, QVariant::fromValue(wd));
//            timer->setSingleShot(true);
//            connect(timer, SIGNAL(timeout()), pageMain, SLOT(refresh_PanelVideos()));
//            timer->start(1000);
//        }//end if refreshUI
    }
    return nRes;
}
int PageMain::OPenCamera(ComTool::NODE_DATA* nodeData, QYVideoWidget* wd, int flag)
{
    int nRes = -1; // 1 - Opend; 2 - Closed;
    if(0 == nodeData || 0 == wd){return nRes;}

    if(1 == nodeData->qytype){//HC Camera
        if(-1 == (LONG)nodeData->hOpen){//Open Camera
            QWidget* wdShow = wd->showWidget();
            if(0 == OpenHCCamera(nodeData, (HWND)(wdShow->winId()))){
                nRes = 1;
            }
        }
    }else{//HH Camera
        if(-1 == (LONG)nodeData->hOpen){//Open Camera
            QWidget* wdShow = wd->showWidget();
            QVariant qv = wd->property(ComTool::Def::PLAYERNO);
            int playerNo = -1;
            if(qv.isNull()){
                playerNo = wd->property(ComTool::Def::PRO_QYINDEX).value<int>() +
                           wd->property(ComTool::Def::PRO_QYINDEXSTART).value<int>();

                wd->setProperty(ComTool::Def::PLAYERNO, QVariant(playerNo));
                HH5PLAYER_InitPlayer2(playerNo, (HWND)(wdShow->winId()), false);
                HH5PLAYER_OpenStream(playerNo);
            }else{
                playerNo = qv.value<int>();
            }
            if(0 == OpenHHCamera(nodeData, playerNo)){ //curSel 播放器编号
                nRes = 1;
            }
        }
    }//End HH Camera

    if(1 == nRes){
        if(0 == flag){
            nodeData->otheA = QVariant::fromValue(wd);
        }else{
            nodeData->otheB = QVariant::fromValue(wd);
        }
        wd->setProperty(ComTool::Def::NODEDATANO, QVariant::fromValue(nodeData));

        //don't auto aspect
//        qreal faspect = nodeData->vWidth*1.0 / nodeData->vHeight;
//        if(abs(faspect - 4.0/3)<1.0e-3){
//            nodeData->nAspect = 1;
//        }

        wd->showWidget()->setVisible(false);
        wd->onShowVideo(nodeData->vWidth, nodeData->vHeight, nodeData->nAspect);
        wd->showWidget()->setVisible(true);

        if(1 == nodeData->qytype && 1 == nodeData->imgtype){//HC Sphere
            _TurnSphere3DPTZ(nodeData);
        }
    }

    return nRes;
}

void PageMain::refresh_PanelVideos()
{
    QObject* sd = sender();
    if(!sd->inherits("QTimer")){
        return;
    }
    QTimer* timer = (QTimer*)sd;

    QVariant qv;
    if(!(qv = timer->property(ComTool::Def::REFRESHID)).isNull()){
        QYVideoWidget* wd = qv.value<QYVideoWidget*>();
        wd->showWidget()->setVisible(false);
        timer->setProperty(ComTool::Def::REFRESHID, QVariant());

    }else if(!(qv = timer->property(ComTool::Def::REFRESHVIDEOS)).isNull()){
        int nStream = AppZZB::getInstance()->CompatibleStream();
        QYPanelVideo* panelVideo = qv.value<QYPanelVideo*>();
        for(int i=0, l= panelVideo->row()*panelVideo->col(); i<l; ++i){
            QYVideoWidget* wd = panelVideo->at(i);
            _VisibleVideo(wd, true);
            //自动切换主副流
            if(!hasStreamPort(wd)){
                turnStreamCamera(wd, nStream>0 ? true : false);
            }
        }
        timer->setProperty(ComTool::Def::REFRESHVIDEOS, QVariant());
    }else if(!(qv = timer->property(ComTool::Def::REFRESHVIDEO)).isNull()){
        QYVideoWidget* wd = qv.value<QYVideoWidget*>();
        _VisibleVideo(wd, true);
        //自动切换主副流
        if(!hasStreamPort(wd)){
            turnStreamCamera(wd, false);
        }
        timer->setProperty(ComTool::Def::REFRESHVIDEO, QVariant());
    }
    timer->deleteLater();
}
void PageMain::_GotResumeDatas(int flag)
{
    if(0 == flag){
        resumeDatas.clear();
        for(int i=0, l=ui->panelvideos->numVideo(); i<l; ++i){
            QYVideoWidget* wd = ui->panelvideos->at(i);
            QVariant qv = wd->property(ComTool::Def::NODEDATANO);
            if(qv.isNull()){
                continue;
            }
            ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
            if(-1 == (LONG)nodeData->hOpen){
                continue;
            }
            resumeDatas.push_back(NODE_DATA_RESUME(nodeData, wd, flag));
        }
    }else if(1 == flag){
        resumeLinks.clear();
        QList<QYVideoWidget*> wds;
        for(int i=0, l=ui->wdRPageA_Top->numVideo()-1; i<l; ++i){
            wds.push_back(ui->wdRPageA_Top->at(i));
        }
        for(int i=0, l=ui->wdRPageA_Bot->numVideo(); i<l; ++i){
            wds.push_back(ui->wdRPageA_Bot->at(i));
        }
        for(int i=0, l=wds.length(); i<l; ++i){
            QYVideoWidget* wd = wds.at(i);
            QVariant qv = wd->property(ComTool::Def::NODELINKNO);
            if(qv.isNull()){
                continue;
            }
            ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();
            QYVideoWidget* wdA = 0;
            QYVideoWidget* wdB = 0;
            if(link->otherA.isNull()){
                continue;
            }
            wdA = link->otherA.value<QYVideoWidget*>();
            if(!link->otherB.isNull()){
                wdB = link->otherB.value<QYVideoWidget*>();
            }
            if(0 == link->pano || -1 == (LONG)link->pano->hOpen){
                continue;
            }
            resumeLinks.push_back(LINK_DATA_RESUME(link, wdA, wdB));
        }
    }
}
void PageMain::TurnResumeDatas(int flag, bool isOpen)
{
    if(0 == flag){
        if(isOpen){//恢复面板0视频
            for(int i=0, l=resumeDatas.length(); i<l; ++i){
                const NODE_DATA_RESUME &resume = resumeDatas.at(i);
                int nRes = OPenCamera(resume.data, resume.wd, resume.flag);
                if(1 == nRes && !resume.data->other.isNull()){
                    QTreeWidgetItem *item = resume.data->other.value<QTreeWidgetItem*>();
                    if(0 != item){
                        item->setIcon(0,*iconOpend);
                    }
                }//Update Tree Widget
            }
            resumeDatas.clear();
        }else{//关闭面板0视频
            for(int i=0, l=resumeDatas.length(); i<l; ++i){
                const NODE_DATA_RESUME &resume = resumeDatas.at(i);
                int nRes = CloseCamera(resume.data, resume.wd, resume.flag);
                if(2 == nRes && !resume.data->other.isNull()){
                    QTreeWidgetItem *item = resume.data->other.value<QTreeWidgetItem*>();
                    if(0 != item){
                        item->setIcon(0,*iconClosed);
                    }
                }//Update Tree Widget
            }
        }
    }else if(1 == flag){
        if(isOpen){//恢复面板1视频
            for(int i=0, l=resumeLinks.length(); i<l; ++i){
                const LINK_DATA_RESUME &resume = resumeLinks.at(i);
                int nRes = OpenCameraLink(resume.link, resume.wdA, resume.wdB);
                if(1 == nRes){
                    if(!resume.link->other.isNull()){
                        QTableWidgetItem* item = resume.link->other.value<QTableWidgetItem*>();
                        if(0 != item){
                            item->setIcon(*iconOpend);
                        }
                    }
                    if(resume.link->isLinked && _isCurSelQQ_TopLink(resume.link)){//open  then auto link
                        ui->cb_Linked->setChecked(true);
                        resume.wdA->enableTrack(true);
                        resume.wdA->enableClick(true);
                        connect(resume.wdA, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
                    }
                }//Update Tree Widget
            }
            resumeLinks.clear();
        }else{//关闭面板1视频
            for(int i=0, l=resumeLinks.length(); i<l; ++i){
                const LINK_DATA_RESUME &resume = resumeLinks.at(i);

                QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(resume.link);
                int nRes = CloseCameraLink(resume.link);
                if(2 == nRes){
                    if(!resume.link->other.isNull()){
                        QTableWidgetItem* item = resume.link->other.value<QTableWidgetItem*>();
                        if(0 != item){
                            item->setIcon(*iconClosed);
                        }
                    }
                    if(resume.link->isLinked && 0 != wdPano){
                        ui->cb_Linked->setChecked(false);
                        wdPano->enableTrack(false);
                        wdPano->enableClick(false);
                        disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
                    }
                }//Update Table Widget
//                int nRes = CloseCameraLink(resume.link);
//                if(2 == nRes && !resume.link->other.isNull()){
//                    QTableWidgetItem* item = resume.link->other.value<QTableWidgetItem*>();
//                    if(0 != item){
//                        item->setIcon(*iconClosed);
//                    }
//                }//Update Table Widget
            }//End For
        }//End If
    }//End If flag
}
void PageMain::resume_PanelVideos()
{
    QObject* sd = sender();
    if(!sd->inherits("QTimer")){
        return;
    }
    QTimer* timer = (QTimer*)sd;

    QVariant qv = timer->property(ComTool::Def::REFRESHVIDEOPANEL);
    if(!qv.isNull()){
        QList<QPoint> pts = qv.value<QList<QPoint>>();
        for(int i=0, l=pts.length(); i<l; ++i){
            const QPoint& pt = pts.at(i);
            TurnResumeDatas(pt.x(), pt.y()>0);
        }
    }
    QTimer::singleShot(2000,this,SLOT(close_Loading()));
}
void PageMain::close_Loading()
{
    AppZZB::getInstance()->TurnShowDlgLoading(false);
}
//顺序打开
//void PageMain::timerOpenTreeVideos()
//{
//    QObject* sd = sender();
//    if(!sd->inherits("QTimer")){
//        AppZZB::getInstance()->TurnShowDlgLoading(false);
//        return;
//    }
//    QTimer* timer = (QTimer*)sd;

//    ComTool::NODE_TREE* nodeTree = 0;
//    int nStream = 0;
//    int no = 0;

//    {
//        QVariant qv = timer->property(ComTool::Def::PANEL_OPEN_TREE);
//        if(!qv.isNull()){nodeTree = qv.value<ComTool::NODE_TREE*>();}
//    }
//    {
//        QVariant qv = timer->property(ComTool::Def::PANEL_OPEN_TREE_STREAM);
//        if(!qv.isNull()){nStream = qv.value<int>();}
//    }
//    {
//        QVariant qv = timer->property(ComTool::Def::PANEL_OPEN_TREE_STARTNO);
//        if(!qv.isNull()){no = qv.value<int>();}
//    }

//    if(0 == nodeTree){
//        timer->deleteLater();
//        AppZZB::getInstance()->TurnShowDlgLoading(false);
//        return;
//    }

//    int l = nodeTree->children.length();
//    qWarning()<<"no "<<no<<"  "<<l;

//    if(0 == no){
//        TurnCloseCameraAll_Panel(l);
//        timer->setInterval((16<=l)?800:200);
//    }

//    if( no < l){
//            int i  = no;
//            ComTool::NODE_DATA *nodeData = nodeTree->children.at(i);
//            QYVideoWidget* wd = ui->panelvideos->at(i);
//            nodeData->nStream = nStream;
//            TurnNodeDataPlay(wd, nodeData);
//            timer->setProperty(ComTool::Def::PANEL_OPEN_TREE_STARTNO, QVariant((int)(no+1)));
//     }

//    if(l <= no){
//        timer->setProperty(ComTool::Def::PANEL_OPEN_TREE, QVariant());
//        timer->setProperty(ComTool::Def::PANEL_OPEN_TREE_STREAM, QVariant());
//        timer->setProperty(ComTool::Def::PANEL_OPEN_TREE_STARTNO, QVariant());
//        timer->deleteLater();
//        AppZZB::getInstance()->TurnShowDlgLoading(false);
//    }
//}
void PageMain::timerOpenDataVideos()
{
    QObject* sd = sender();
    if(!sd->inherits("OpenNodeDataTimer")){
        return;
    }
    OpenNodeDataTimer* timer = (OpenNodeDataTimer*)sd;

    ComTool::NODE_DATA* nodeData = 0;
    int nStream = 0;
    int no = 0;

    {
        QVariant qv = timer->property(ComTool::Def::PANEL_OPEN_DATA);
        if(!qv.isNull()){nodeData = qv.value<ComTool::NODE_DATA*>();}
    }
    {
        QVariant qv = timer->property(ComTool::Def::PANEL_OPEN_DATA_STREAM);
        if(!qv.isNull()){nStream = qv.value<int>();}
    }
    {
        QVariant qv = timer->property(ComTool::Def::PANEL_OPEN_DATA_STARTNO);
        if(!qv.isNull()){no = qv.value<int>();}
    }

    if(0 == nodeData){
        timer->doFinish(no);
        timer->deleteLater();
        return;
    }

    {
        int i  = no;
        QYVideoWidget* wd = ui->panelvideos->at(i);
        nodeData->nStream = nStream;
        TurnNodeDataPlay(wd, nodeData);
    }

    {
        timer->setProperty(ComTool::Def::PANEL_OPEN_TREE, QVariant());
        timer->setProperty(ComTool::Def::PANEL_OPEN_TREE_STREAM, QVariant());
        timer->setProperty(ComTool::Def::PANEL_OPEN_TREE_STARTNO, QVariant());
        timer->doFinish(no);
        timer->deleteLater();
    }
}
void PageMain::timerOpenDataVideosFinished(int no)
{
    qWarning()<<"NO: "<<no<<" "<<sumOpenData;
    sumOpenData--;
    if(0 == sumOpenData){
        AppZZB::getInstance()->TurnShowDlgLoading(false);
    }
}
void PageMain::CloseTreeNode(ComTool::NODE_TREE* nodeTree)
{
    if(0 == nodeTree || nodeTree->children.length() < 1){return;}
    int l = nodeTree->children.length();
    for(int i=0; i<l; ++i){
        ComTool::NODE_DATA* nodeData = nodeTree->children.at(i);
        if(-1 != (LONG)nodeData->hOpen && !(nodeData->otheA.isNull())){//close
            QYVideoWidget* wd = nodeData->otheA.value<QYVideoWidget*>();
            CloseCameraPanel(nodeData, wd, true);
        }
    }
}

void PageMain::OpenTreeNode(ComTool::NODE_TREE* nodeTree)
{
    if(0 == nodeTree || nodeTree->children.length() < 1){return;}
    if(ComTool::NodeTreeHelper::isHard(nodeTree)){
        if(!ComTool::NodeTreeHelper::isHardLogined(nodeTree)){//登陆中
            PageMain::LoginNodeTree(nodeTree, false);
            return;
        }
    }

    AppZZB::getInstance()->TurnShowDlgLoading(true);
    int l = nodeTree->children.length();
    int nStream  = 0;
    bool cg = false;
    if(1 == l){
        cg = AppZZB::getInstance()->TurnShow(1, 1);
    }else if(1 < l && l <= 4){
        cg = AppZZB::getInstance()->TurnShow(2, 1);
    }else if(4 < l && l <= 9){
        cg = AppZZB::getInstance()->TurnShow(3, 1);
        nStream = 1;
    }else if(9 < l && l <= 16){
        cg = AppZZB::getInstance()->TurnShow(4, 1);
        nStream = 1;
    }else if(16 < l){
        cg = AppZZB::getInstance()->TurnShow(5, 1);
        nStream = 1;
    }

    //begin
    TurnCloseCameraAll_Panel(l);
    sumOpenData = l;

    for(int i=l-1; i>=0; --i){
        OpenNodeDataTimer* timer = new OpenNodeDataTimer(this);
        timer->setProperty(ComTool::Def::PANEL_OPEN_DATA, QVariant::fromValue(nodeTree->children.at(i)));
        timer->setProperty(ComTool::Def::PANEL_OPEN_DATA_STREAM, QVariant(nStream));
        timer->setProperty(ComTool::Def::PANEL_OPEN_DATA_STARTNO, QVariant(i));

        connect(timer, SIGNAL(timeout()), this, SLOT(timerOpenDataVideos()));
        connect(timer, SIGNAL(sigFinish(int)), this, SLOT(timerOpenDataVideosFinished(int)));
        timer->setSingleShot(true);

        int t = (int)((cg ? 1500.0 : 1000.0) + ComTool::Tool::generateRandom()*1000.0);
        timer->start(t);
    }
    //end

//    顺序打开
//    QTimer* timer = new QTimer(this);
//    timer->setProperty(ComTool::Def::PANEL_OPEN_TREE, QVariant::fromValue(nodeTree));
//    timer->setProperty(ComTool::Def::PANEL_OPEN_TREE_STREAM, QVariant(nStream));
//    timer->setProperty(ComTool::Def::PANEL_OPEN_TREE_STARTNO, QVariant((int)0));

//    connect(timer, SIGNAL(timeout()), this, SLOT(timerOpenTreeVideos()));
//    timer->start(cg ? 3000 : 1000);
}

LoginTreeItemThread::LoginTreeItemThread(QTreeWidgetItem *it, bool open, QObject *parent):QThread(parent){
    item    = it;
    doOpen  = open;
}
LoginTreeItemThread::~LoginTreeItemThread(){}

void LoginTreeItemThread::run(){
    ComTool::NODE_DATA* nodeData = item->data(0, Qt::UserRole).value<ComTool::NODE_DATA*>();
    PageMain::LoginNodeData(nodeData);
}
void PageMain::LoginNodeTree(ComTool::NODE_TREE* tree, bool open)
{
    int nChan = tree->ChanNum + tree->IPChanNum;
    if(0 < nChan){
        QMutexLocker locker(&mMovieLock);
        for(int i=0, n=tree->children.size(); i<n; ++i){
            ComTool::NODE_DATA* nodeData = tree->children[i];
            mMovieList.push_back(nodeData->other.value<QTreeWidgetItem*>());
        }

        ComTool::NODE_DATA* nodeData = tree->children[0];
        LoginTreeItemThread* loginTreeItemThread = new LoginTreeItemThread(nodeData->other.value<QTreeWidgetItem*>(), open, this);
        connect(loginTreeItemThread, SIGNAL(finished()), this, SLOT(oFinishedLoginTreeItemThread()));
        loginTreeItemThread->start();
        return;
    }

    for(int i=0, n=tree->children.size(); i<n; ++i){
        ComTool::NODE_DATA* nodeData = tree->children[i];

        QMutexLocker locker(&mMovieLock);
        mMovieList.push_back(nodeData->other.value<QTreeWidgetItem*>());
        LoginTreeItemThread* loginTreeItemThread = new LoginTreeItemThread(nodeData->other.value<QTreeWidgetItem*>(), open, this);
        connect(loginTreeItemThread, SIGNAL(finished()), this, SLOT(oFinishedLoginTreeItemThread()));
        loginTreeItemThread->start();
    }

    for(int i=0, l=tree->nodes.size(); i<l; ++i){
        ComTool::NODE_TREE* nodeChild = tree->nodes.at(i);
        PageMain::LoginNodeTree(nodeChild, open);
    }
}

bool PageMain::LoginNodeData(ComTool::NODE_DATA* nodeData)
{
    if(0 == nodeData || (void*)-1 != nodeData->hLogon){
        return false;
    }
    ComTool::NODE_TREE* tree = (ComTool::NODE_TREE*)nodeData->parent;
    int nChan = tree->ChanNum + tree->IPChanNum;
    if( 0 == nChan){
        ComTool::NODE_DATA* data = nodeData;
        QVariant qv = LoginCamera(data->name, data->szIp, data->port, data->szUserName, data->szUserPsw);
        if(qv.isNull()){
           return false;
        }
        ComTool::NODE_DATA* qvData = qv.value<ComTool::NODE_DATA*>();
        data->hLogon = qvData->hLogon;
        return true;
    }

    ComTool::NODE_DATA* data = tree->children.at(0);
    QVariant qv = LoginCamera(data->name, data->szIp, data->port, data->szUserName, data->szUserPsw);
    if(qv.isNull()){
       return false;
    }//End If
    ComTool::NODE_TREE* qvTree = qv.value<ComTool::NODE_TREE*>();
    ComTool::NODE_DATA* qvData = qvTree->children.at(0);
    for(int i=0, l=tree->children.size(); i<l; ++i){
        ComTool::NODE_DATA* data = tree->children.at(i);
        data->hLogon = qvData->hLogon;
    }
//    ComTool::NODE_TREE* qvTree = qv.value<ComTool::NODE_TREE*>();
//    for(int ii=0, ll=qvTree->children.size(); ii<ll; ++ii){
//        ComTool::NODE_DATA* qvData = qvTree->children.at(ii);
//        for(int i=0, l=tree->children.size(); i<l; ++i){
//            ComTool::NODE_DATA* data = tree->children.at(i);
//            if(data->dwChannelNo == qvData->dwChannelNo){
//                qvData->name = data->name;
//                if(1 == data->calced){
//                    qvData->ag    = data->ag;
//                    qvData->lr[0] = data->lr[0];
//                    qvData->lr[1] = data->lr[1];
//                    qvData->lr[2] = data->lr[2];
//                }
//                qvData->calced= data->calced;
//                qvData->imgtype = data->imgtype;
//                qvData->vWidth  = data->vWidth;
//                qvData->vHeight = data->vHeight;
//                qvData->subType = data->subType;
//                qvData->nStream = data->nStream;
//                qvData->nAspect = data->nAspect;
//                qvData->other   = data->other;
//            }
//        }//end for
//    }//end for
//    tree->children.clear();
//    tree->children = qvTree->children;
    return true;
}
void PageMain::oFinishedLoginTreeItemThread()
{
    LoginTreeItemThread* loginTreeItemThread = (LoginTreeItemThread*)sender();
    QTreeWidgetItem* item = loginTreeItemThread->item;
    bool doOpen = loginTreeItemThread->doOpen;

    int nRes = 0; // 1 - Opend; 2 - Closed;
    ComTool::NODE_DATA* nodeData = item->data(0, Qt::UserRole).value<ComTool::NODE_DATA*>();
    ComTool::NODE_TREE* tree = (ComTool::NODE_TREE*)nodeData->parent;
    int nChan = tree->ChanNum + tree->IPChanNum;

    if((void*)-1 == nodeData->hLogon){
         AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("错误"), (0<nChan ? tree->name : nodeData->name) + QString::fromLocal8Bit("\n") + QString::fromLocal8Bit(" 无法登陆，请检查！"), 0);
         nRes = -1;
    }else if(doOpen && nodeData->otheA.isNull()){
        int curSel = ui->panelvideos->curSel();
        QYVideoWidget* wd = ui->panelvideos->at(curSel);
        QVariant qv = wd->property(ComTool::Def::NODEDATANO);
        if(!qv.isNull()){
           AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("播放提醒"),QString::fromLocal8Bit("当前播放窗口已被暂用，重选一个！"),0);
           return;
        }
        nRes = OPenCamera(nodeData, wd, 0);
    }

    //UI Update
    if(0 < nChan){
        for(int i=0, l=tree->children.size(); i<l; ++i){
            ComTool::NODE_DATA* data = tree->children.at(i);
            QTreeWidgetItem* it = data->other.value<QTreeWidgetItem*>();
            QMutexLocker locker(&mMovieLock);
            mMovieList.removeOne(it);
            if(0 == nRes){it->setIcon(0, *iconClosed);}
            else if(-1 == nRes){it->setIcon(0,*iconLogout);}
        }
    }else{
        QMutexLocker locker(&mMovieLock);
        mMovieList.removeOne(item);
    }

    if(-1 == nRes){
        item->setIcon(0,*iconLogout);
    }else if(0 == nRes){
        item->setIcon(0,*iconClosed);
    }else if(1 == nRes){
        item->setIcon(0,*iconOpend);
    }

    loginTreeItemThread->deleteLater();
}
void PageMain::oMovieframeChanged(int)
{
    QMutexLocker locker(&mMovieLock);
    for(int i=0, l=mMovieList.size(); i<l; ++i){
        QTreeWidgetItem* item = mMovieList.at(i);
        item->setIcon(0,QIcon(mMovie->currentPixmap()));
    }
}
void PageMain::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(AppZZB::ST_PLAYBACK == AppZZB::getInstance()->state()){return;}

    if(ComTool::Def::ITEM_DATA_TYPE == item->type()){
        //int nRes = 0; // 1 - Opend; 2 - Closed;
        ComTool::NODE_DATA* nodeData = item->data(0, Qt::UserRole).value<ComTool::NODE_DATA*>();
        bool isLogin = ((void*)-1 != nodeData->hLogon);
        bool isOpend = !(nodeData->otheA.isNull());
        if(!isLogin){
            QMutexLocker locker(&mMovieLock);
            mMovieList.push_back(item);
            
            LoginTreeItemThread* loginTreeItemThread = new LoginTreeItemThread(item, !isOpend, this);
            connect(loginTreeItemThread, SIGNAL(finished()), this, SLOT(oFinishedLoginTreeItemThread()));
            loginTreeItemThread->start();
            return;
        }
        if(isOpend){//close
            QYVideoWidget* wd = nodeData->otheA.value<QYVideoWidget*>();
            TurnCloseCamera(wd);
            //nRes = CloseCamera(nodeData, wd, 0);
        }else{
            int curSel = ui->panelvideos->curSel();
            QYVideoWidget* wd = ui->panelvideos->at(curSel);
            nodeData->nStream = AppZZB::getInstance()->CompatibleStream();
            TurnNodeDataPlay(wd, nodeData, false);
            //OpenNodeDataThread* openNodeDataThread = new OpenNodeDataThread(wd, nodeData);
            //openNodeDataThread->start();
//            QVariant qv = wd->property(ComTool::Def::NODEDATANO);
//            if(!qv.isNull()){
//               AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("播放提醒"),QString::fromLocal8Bit("当前播放窗口已被暂用，重选一个！"),0);
//               return;
//            }
//            nRes = OPenCamera(nodeData, wd, 0);
        }
//        //UI Update
//        if(1 == nRes){
//            item->setIcon(0,*iconOpend);
//        }else if(2 == nRes){
//            item->setIcon(0,*iconClosed);
//        }

    }else if(ComTool::Def::ITEM_TREE_TYPE == item->type()){
        ComTool::NODE_TREE* nodeTree = item->data(0, Qt::UserRole).value<ComTool::NODE_TREE*>();
        OpenTreeNode(nodeTree);
        item->setExpanded(false);
    }
}

void PageMain::_TurnSphere3DPTZ(ComTool::NODE_DATA* nodeData)
{
    //qWarning()<<"_TurnSphere3DPTZ: "<<nodeData->qytype<<" "<<nodeData->imgtype;
    if(1 != nodeData->qytype || 1 != nodeData->imgtype){
        return;
    }
    QYVideoWidget* wdSphere = 0;
    if(!nodeData->otheA.isNull()){
        wdSphere = nodeData->otheA.value<QYVideoWidget*>();
    }else if(!nodeData->otheB.isNull()){
        wdSphere = nodeData->otheB.value<QYVideoWidget*>();
    }
    if(0 == wdSphere){
        return;
    }

    if(-1 != (LONG)nodeData->hOpen && wdSphere->property(ComTool::Def::SPHERE_SIGTRACK).isNull()){
            wdSphere->enableClick(true);
            wdSphere->enableWheel(true);
            wdSphere->showWidget()->setCursor(Qt::CrossCursor);

            PageMain* pageMain = AppZZB::getInstance()->pageMain;
            connect(wdSphere, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), pageMain, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
            connect(wdSphere, SIGNAL(sigTrackRect(QWidget*, QVector2D, QVector2D)), pageMain, SLOT(oSigTrackRect(QWidget*, QVector2D, QVector2D)));
            connect(wdSphere, SIGNAL(sigTrackWheel(QWidget*, qreal)), pageMain, SLOT(oSigTrackWheel(QWidget*, qreal)));
            wdSphere->setProperty(ComTool::Def::SPHERE_SIGTRACK, QVariant(1));
    }else if(!wdSphere->property(ComTool::Def::SPHERE_SIGTRACK).isNull()){
        wdSphere->enableClick(false);
        wdSphere->enableWheel(false);
        wdSphere->showWidget()->setCursor(Qt::ArrowCursor);

        PageMain* pageMain = AppZZB::getInstance()->pageMain;
        disconnect(wdSphere, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), pageMain, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
        disconnect(wdSphere, SIGNAL(sigTrackRect(QWidget*, QVector2D, QVector2D)), pageMain, SLOT(oSigTrackRect(QWidget*, QVector2D, QVector2D)));
        disconnect(wdSphere, SIGNAL(sigTrackWheel(QWidget*, qreal)), pageMain, SLOT(oSigTrackWheel(QWidget*, qreal)));
        wdSphere->setProperty(ComTool::Def::SPHERE_SIGTRACK, QVariant());
    }
}
void PageMain::triggeredMenuItem(bool)
{
   QObject* sd = sender();
   if(sd == m_acLink){
       QYDlgLinkGroupAdd dlgLinkGroupAdd(this);
       int nRes = dlgLinkGroupAdd.exec();
       if(QDialog::Accepted == nRes){
           QVariant qvPano   = m_acLink->property(ComTool::Def::LINKPANO);
           QVariant qvSphere = m_acLink->property(ComTool::Def::LINKSPHERE);
           ComTool::NODE_DATA* pano = qvPano.isNull() ? 0 : qvPano.value<ComTool::NODE_DATA*>();
           ComTool::NODE_DATA* sphere = qvSphere.isNull() ? 0 : qvSphere.value<ComTool::NODE_DATA*>();
           if(0 != pano && 0 != sphere){
               ComTool::LINK_DATA* link = 0;
               ComTool::CCommon<ComTool::LINK_DATA>::NewA(&link);
               link->name = dlgLinkGroupAdd.groupName();
               link->pano = pano;
               link->sphere = sphere;
               AppZZB::getInstance()->AddNodeLink(link);
           }
           m_acLink->setProperty(ComTool::Def::LINKPANO, QVariant());
           m_acLink->setProperty(ComTool::Def::LINKSPHERE, QVariant());
           AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("添加机组"), QString::fromLocal8Bit("机组添加成功，在联动列表中可以查看!"), 0);
       }
   }else if(sd == m_acAttr){
       while(1){
           QVariant qvTree = m_acAttr->property(ComTool::Def::NODETREEATTR);
           ComTool::NODE_TREE* nodeTree = qvTree.isNull() ? 0 : qvTree.value<ComTool::NODE_TREE*>();
           if(0 == nodeTree){break;}
           QVariant qv = m_acAttr->property(ComTool::Def::NODEDATAATTR);
           ComTool::NODE_DATA* nodeData = qv.isNull() ? 0 : qv.value<ComTool::NODE_DATA*>();
           if(0 == nodeData){
               QYDlgCameraHomeCfg dlgCameraHomeCfg(this);
               dlgCameraHomeCfg.InitFromNodeTree(nodeTree);
               int nRes = dlgCameraHomeCfg.exec();
               if(QDialog::Accepted == nRes){dlgCameraHomeCfg.ResultToNodeTree();}
               return;
           }
           QYDlgCameraHomeHardCfg dlgCameraHomeHardCfg;
           dlgCameraHomeHardCfg.InitFromNode(nodeTree, nodeData);
           int nRes = dlgCameraHomeHardCfg.exec();
           if(QDialog::Accepted == nRes){dlgCameraHomeHardCfg.ResultToNode();}
           return;
       }
       QVariant qv = m_acAttr->property(ComTool::Def::NODEDATAATTR);
       ComTool::NODE_DATA* nodeData = qv.isNull() ? 0 : qv.value<ComTool::NODE_DATA*>();
       if(0 == nodeData){
           return;
       }
       QYDlgCameraCfg dlgCameraCfg(this);
       dlgCameraCfg.InitFromNodeData(nodeData);
       int nRes = dlgCameraCfg.exec();
       if(QDialog::Accepted == nRes){
            if(dlgCameraCfg.ResultToNodeData()){
                _TurnSphere3DPTZ(nodeData);
            }//end dlgCameraCfg
       }//end QDialog::Accepted
       m_acAttr->setProperty(ComTool::Def::NODETREEATTR, QVariant());
       m_acAttr->setProperty(ComTool::Def::NODEDATAATTR, QVariant());

   }else if(sd == m_acOpen){
       QVariant qv = m_acOpen->property(ComTool::Def::NODETREEATTR);
       ComTool::NODE_TREE* nodeTree = qv.isNull() ? 0 : qv.value<ComTool::NODE_TREE*>();
       if(0 == nodeTree){
           return;
       }
       m_acOpen->setProperty(ComTool::Def::NODETREEATTR, QVariant());
       OpenTreeNode(nodeTree);

   }else if(sd == m_acClose){
       QVariant qv = m_acClose->property(ComTool::Def::NODETREEATTR);
       ComTool::NODE_TREE* nodeTree = qv.isNull() ? 0 : qv.value<ComTool::NODE_TREE*>();
       if(0 == nodeTree){
           return;
       }
       m_acClose->setProperty(ComTool::Def::NODETREEATTR, QVariant());
       CloseTreeNode(nodeTree);

   }else if(sd == m_acDel){
       QVariant qvData = m_acDel->property(ComTool::Def::NODEDATAATTR);
       ComTool::NODE_DATA* nodeData = qvData.isNull() ? 0 : qvData.value<ComTool::NODE_DATA*>();

       QVariant qv = m_acDel->property(ComTool::Def::NODETREEATTR);
       ComTool::NODE_TREE* nodeTree = qv.isNull() ? 0 : qv.value<ComTool::NODE_TREE*>();

       QVariant qvLink = m_acDel->property(ComTool::Def::NODELINKATTR);
       ComTool::LINK_DATA* link = qvLink.isNull() ? 0 : qvLink.value<ComTool::LINK_DATA*>();
       if(0 != nodeTree){
           DelNodeTree(nodeTree);
       }//end nodeTree
       if(0 != nodeData){
           DelNodeData(nodeData, 0);
       }//end nodeData
       if(0 != link){
           DelLinkData(link);
       }//end link
       m_acDel->setProperty(ComTool::Def::NODEDATAATTR, QVariant());
       m_acDel->setProperty(ComTool::Def::NODETREEATTR, QVariant());
       m_acDel->setProperty(ComTool::Def::NODELINKATTR, QVariant());

   }else if(sd == m_acAddCamera){//添加相机
       if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
       if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
       if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
       QVariant qvTree = m_acAddCamera->property(ComTool::Def::NODETREEATTR);
       ComTool::NODE_TREE* tree = qvTree.value<ComTool::NODE_TREE*>();
       AppZZB::getInstance()->TurnShowDlgCameraAdd(true, tree);
       m_acAddCamera->setProperty(ComTool::Def::NODETREEATTR, QVariant());

   }else if(sd == m_acAddHome){//添加区域
       if(AppZZB::ST_LINK == AppZZB::getInstance()->state()){return;}
       if(AppZZB::ST_LINK_PT == AppZZB::getInstance()->state()){return;}
       if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){return;}
       QVariant qvTree = m_acAddHome->property(ComTool::Def::NODETREEATTR);
       ComTool::NODE_TREE* tree = qvTree.value<ComTool::NODE_TREE*>();
       AppZZB::getInstance()->TurnShowDlgCameraAddHome(true, tree);
       m_acAddHome->setProperty(ComTool::Def::NODETREEATTR, QVariant());

   }//end If
}
void PageMain::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    if(qApp->mouseButtons() == Qt::RightButton)   //判断是否为右键
    {
        QList<QTreeWidgetItem*> sels = ui->treeWidget->selectedItems();
        if(-1 == sels.indexOf(item)){
            return;
        }
        if(1 == sels.length()){
            if(ComTool::Def::ITEM_TREE_TYPE == item->type()){
                QVariant qvData = item->data(0, Qt::UserRole);
                ComTool::NODE_TREE* nodeTree = qvData.value<ComTool::NODE_TREE*>();
                int nChildren = nodeTree->children.length();

                m_menuTreeWd->clear();
                m_acOpen->setProperty(ComTool::Def::NODETREEATTR, QVariant());
                m_acClose->setProperty(ComTool::Def::NODETREEATTR, QVariant());
                if(0 < nChildren){
                    m_acOpen->setProperty(ComTool::Def::NODETREEATTR, QVariant::fromValue(nodeTree));
                    m_acClose->setProperty(ComTool::Def::NODETREEATTR, QVariant::fromValue(nodeTree));
                }
                m_acDel->setProperty(ComTool::Def::NODETREEATTR, QVariant::fromValue(nodeTree));
                m_acDel->setProperty(ComTool::Def::NODEDATAATTR, QVariant());
                m_acAttr->setProperty(ComTool::Def::NODETREEATTR, QVariant::fromValue(nodeTree));
                m_acAttr->setProperty(ComTool::Def::NODEDATAATTR, QVariant());
                if(ComTool::NodeTreeHelper::isHard(nodeTree)){
                    ComTool::NODE_DATA* nodeData = nodeTree->children.at(0);
                    m_acAttr->setProperty(ComTool::Def::NODEDATAATTR, QVariant::fromValue(nodeData));
                }
                if(0 < nChildren){
                    m_menuTreeWd->addAction(m_acOpen);
                    m_menuTreeWd->addAction(m_acClose);
                }
                m_menuTreeWd->addAction(m_acDel);
                m_menuTreeWd->addAction(m_acAttr);
                if(!ComTool::NodeTreeHelper::isHard(nodeTree)){
                    m_acAddCamera->setProperty(ComTool::Def::NODETREEATTR, QVariant::fromValue(nodeTree));
                    m_acAddHome->setProperty(ComTool::Def::NODETREEATTR, QVariant::fromValue(nodeTree));
                    m_menuTreeWd->addAction(m_acAddCamera);
                    m_menuTreeWd->addAction(m_acAddHome);
                }
                m_menuTreeWd->exec(QCursor::pos());
                return;
            }else if(ComTool::Def::ITEM_DATA_TYPE == item->type()){
                QVariant qvData = item->data(0, Qt::UserRole);
                ComTool::NODE_DATA* nodeData = qvData.value<ComTool::NODE_DATA*>();

                m_menuTreeWd->clear();
                m_acAttr->setProperty(ComTool::Def::NODETREEATTR, QVariant());
                m_acAttr->setProperty(ComTool::Def::NODEDATAATTR, QVariant::fromValue(nodeData));
                if(1 == nodeData->dwChannelNum){
                    m_acDel->setProperty(ComTool::Def::NODEDATAATTR, QVariant::fromValue(nodeData));
                    m_acDel->setProperty(ComTool::Def::NODETREEATTR, QVariant());
                    m_menuTreeWd->addAction(m_acDel);
                }
                m_menuTreeWd->addAction(m_acAttr);
                m_menuTreeWd->exec(QCursor::pos());
                return;
            }//end
        }

        if(2 != sels.length()){
            return;
        }
        ComTool::NODE_DATA* pano   = 0;
        ComTool::NODE_DATA* sphere = 0;
        {
            foreach (QTreeWidgetItem* p, sels) {
                if(ComTool::Def::ITEM_DATA_TYPE != p->type()){
                    break;
                }
                QVariant qvData = p->data(0, Qt::UserRole);
                ComTool::NODE_DATA* nodeData = qvData.value<ComTool::NODE_DATA*>();
                if(0 == nodeData->imgtype){//qytype
                    pano = nodeData;
                }else if(1 == nodeData->imgtype){//qytype
                    sphere = nodeData;
                }
            }//End For
        }
        if(0 == pano || 0 == sphere){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("相机属性"), QString::fromLocal8Bit("请先右键相机设置相机的设备类型"), 0);
            return;
        }
        ComTool::LINK_DATA* link = ComTool::LinkGroupHelper::FindLink(pano, sphere, AppZZB::getInstance()->rootLinks);
        if(0 != link){
            return;
        }

         m_menuTreeWd->clear();
         m_acLink->setProperty(ComTool::Def::LINKPANO, QVariant::fromValue(pano));
         m_acLink->setProperty(ComTool::Def::LINKSPHERE, QVariant::fromValue(sphere));
         m_menuTreeWd->addAction(m_acLink);
         m_menuTreeWd->exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
    }
}
void PageMain::on_tableWidget_qq_itemPressed(QTableWidgetItem *item)
{
    if(qApp->mouseButtons() == Qt::RightButton){   //判断是否为右键

        int row = ui->tableWidget_qq->row(item);
        QTableWidgetItem *item0 = ui->tableWidget_qq->item(row, 0);
        QVariant qv = item0->data(Qt::UserRole);
        if(qv.isNull()){
            return;
        }
        ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();

        m_menuTreeWd->clear();
        m_acDel->setProperty(ComTool::Def::NODELINKATTR, QVariant::fromValue(link));
        m_menuTreeWd->addAction(m_acDel);
        m_menuTreeWd->exec(QCursor::pos());
        return;
    }
}

//联动
void PageMain::oSelPanelVideo(int sel)
{
    static const QString ssDown = QString().sprintf("rgba(0,255,0,255)");
    static const QString ssUp = QString().sprintf("rgba(220,220,220,100)");
    QObject* sd = sender();
    if(sd == ui->wdRPageA_Top){
        if(sel != mSelLink[0]){
            bool bRes = true;
            if(-1 < sel && -1 < mSelLink[0]){
                bRes = false;
            }
            mSelLink[0] = sel;
            if(bRes){
                ComTool::Tool::updateSS_brColor(ui->wdRPageA_Top, -1 < sel ? ssDown : ssUp);
            }
        }
        if(-1 < sel){
            ui->wdRPageA_Bot->select(-1);
        }
    }else if(sd == ui->wdRPageA_Bot){
        if(sel != mSelLink[1]){
            mSelLink[1] = sel;
        }
        if(-1 < sel){
            ui->wdRPageA_Top->select(-1);
        }
    }else if(sd == ui->panelvideos){
        if(sel != mSelLink[2]){
            mSelLink[2] = sel;
        }
    }
   qWarning()<<" 1: "<<mSelLink[0]<<" 2: "<<mSelLink[1]<<" 2: "<<mSelLink[2];
}

int PageMain::CloseCameraLink(ComTool::LINK_DATA* link)
{
    int nRes = -1;
    if(0 == link){return nRes;}
    if(!link->otherA.isNull()){//Close
        QYVideoWidget* wd = link->otherA.value<QYVideoWidget*>();    
        if(hasStreamPort(wd)){
            nRes = turnPanoClose(wd) ? 2 : nRes;
        }else{
           nRes = CloseCamera(link->pano, wd, 1);
        }
        if(nRes > -1){
            link->otherA = QVariant();
            link->pano->nAspect = link->pano->nAspectLast;
            wd->setProperty(ComTool::Def::NODELINKNO, QVariant());
        }else{
            return nRes;
        }
    }
    if(!link->otherB.isNull()){
        QYVideoWidget* wd = link->otherB.value<QYVideoWidget*>();
        nRes = CloseCamera(link->sphere, wd, 1);
        if(nRes > -1){
            link->otherB = QVariant();
            link->sphere->nAspect = link->sphere->nAspectLast;
            wd->setProperty(ComTool::Def::NODELINKNO, QVariant());
        }else{
            return nRes;
        }
    }
    return nRes;
}
int PageMain::OpenCameraLink(ComTool::LINK_DATA* link, QYVideoWidget* curSelA, QYVideoWidget* curSelB)
{
    int nRes = -1;
    if(0 == link){return nRes;}
    if(0 != curSelA && link->otherA.isNull()){
        link->pano->nAspectLast = link->pano->nAspect;
        link->pano->nAspect = 1;
        nRes = OPenCamera(link->pano, curSelA, 1);
        if(nRes > -1){
            link->otherA = QVariant::fromValue(curSelA);
            curSelA->setProperty(ComTool::Def::NODELINKNO, QVariant::fromValue(link));
            curSelA->lr[0] = link->pano->lr[0];
            curSelA->lr[1] = link->pano->lr[1];
            curSelA->lr[2] = link->pano->lr[2];
        }else{
           link->pano->nAspect = link->pano->nAspectLast;
        }
    }
    if(-1 < nRes && 0 != curSelB && link->otherB.isNull()){
        link->sphere->nAspectLast = link->sphere->nAspect;
        link->sphere->nAspect = 1;
        nRes = OPenCamera(link->sphere, curSelB, 1);
        if(nRes > -1){
            link->otherB = QVariant::fromValue(curSelB);
            curSelB->setProperty(ComTool::Def::NODELINKNO, QVariant::fromValue(link));
        }else{
          link->sphere->nAspect = link->sphere->nAspectLast;
        }
    }
    return nRes;
}
void PageMain::_GotCurSelQQ(QYVideoWidget* &curSelA, QYVideoWidget* &curSelB)
{
    if(-1 == mSelLink[1] && -1 < mSelLink[0]){
        curSelA = ui->wdRPageA_Top->at(0);
        curSelB = ui->wdRPageA_Top->at(1);
    }else if(-1 == mSelLink[0] && -1 < mSelLink[1]){
        curSelA = ui->wdRPageA_Bot->at(mSelLink[1]);
    }
}
int PageMain::_GotCurSelQQ_TopItem()
{
    QYVideoWidget* curSelA = ui->wdRPageA_Top->at(0);

    QVariant qvTop = curSelA->property(ComTool::Def::NODELINKNO);
    if(!qvTop.isNull()){
        ComTool::LINK_DATA* linkTop = qvTop.value<ComTool::LINK_DATA*>();
        if(!linkTop->other.isNull()){
            QTableWidgetItem* item = linkTop->other.value<QTableWidgetItem*>();
            if(0 != item){
                return ui->tableWidget_qq->row(item);
            }
        }
    }
    return -1;
}
bool PageMain::_TurnShow_TopItem(int itemNo)
{
    QTableWidgetItem* item0 = ui->tableWidget_qq->item(itemNo, 0);
    if(0 == item0){
        return false;
    }
    QVariant qvBot = item0->data(Qt::UserRole);
    if(qvBot.isNull()){
        return false;
    }
    QYVideoWidget* botPano   = 0;
    QYVideoWidget* botSphere = 0;
    ComTool::LINK_DATA* linkBot = qvBot.value<ComTool::LINK_DATA*>();

    if(!linkBot->otherA.isNull()){
        botPano     = linkBot->otherA.value<QYVideoWidget*>();
        botSphere   = linkBot->otherB.value<QYVideoWidget*>();
        QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(linkBot);
        int nRes = CloseCameraLink(linkBot);
        if(2 != nRes){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("关联提醒"), QString::fromLocal8Bit("切换失败，请重试！"), 0);
            return false;
        }
        if(!linkBot->other.isNull()){
            QTableWidgetItem* item = linkBot->other.value<QTableWidgetItem*>();
            if(0 != item){
                item->setIcon(*iconClosed);
            }
        }
        if(linkBot->isLinked && 0 != wdPano){
            ui->cb_Linked->setChecked(false);
            wdPano->enableTrack(false);
            wdPano->enableClick(false);
            disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
        }

    }//end if


    //Close Top
    QYVideoWidget* curSelA = ui->wdRPageA_Top->at(0);
    QYVideoWidget* curSelB = ui->wdRPageA_Top->at(1);
    ComTool::LINK_DATA* linkTop = 0;

    QVariant qvTop = curSelA->property(ComTool::Def::NODELINKNO);
    if(!qvTop.isNull()){
        linkTop = qvTop.value<ComTool::LINK_DATA*>();
        QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(linkTop);
        int nRes = CloseCameraLink(linkTop);
        if(2 != nRes){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("关联提醒"), QString::fromLocal8Bit("切换失败，无法关闭，请重试！"), 0);
            return false;
        }
        if(!linkTop->other.isNull()){
            QTableWidgetItem* item = linkTop->other.value<QTableWidgetItem*>();
            if(0 != item){
                item->setIcon(*iconClosed);
            }
        }
        if(linkTop->isLinked && 0 != wdPano){
            ui->cb_Linked->setChecked(false);
            wdPano->enableTrack(false);
            wdPano->enableClick(false);
            disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
        }
    }

    //Open to Top
    AppZZB::getInstance()->TurnShowDlgLoading(true);
    sumOpenLink = 1;
    {
        linkBot->pano->nStream = 0;
        linkBot->sphere->nStream = 0;
        OpenLinkDataTimer* timer = new OpenLinkDataTimer(this);
        timer->setProperty(ComTool::Def::LINK_OPEN_LINK, QVariant::fromValue(linkBot));
        timer->setProperty(ComTool::Def::LINK_OPEN_SELA, QVariant::fromValue(curSelA));
        timer->setProperty(ComTool::Def::LINK_OPEN_SELB, QVariant::fromValue(curSelB));
        timer->setProperty(ComTool::Def::LINK_OPEN_LINK_NO, QVariant(0));
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(timerOpenLink()));
        connect(timer, SIGNAL(sigFinish(int)), this, SLOT(timerOpenLinksFinished(int)));
        timer->setSingleShot(true);
        timer->start(1500);
    }
    if(0 != linkTop  && 0 != botPano){
        sumOpenLink++;
        linkTop->pano->nStream = 1;
        linkTop->sphere->nStream = 1;
        OpenLinkDataTimer* timer = new OpenLinkDataTimer(this);
        timer->setProperty(ComTool::Def::LINK_OPEN_LINK, QVariant::fromValue(linkTop));
        timer->setProperty(ComTool::Def::LINK_OPEN_SELA, QVariant::fromValue(botPano));
        timer->setProperty(ComTool::Def::LINK_OPEN_SELB, QVariant::fromValue(botSphere));
        timer->setProperty(ComTool::Def::LINK_OPEN_LINK_NO, QVariant(1));
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(timerOpenLink()));
        connect(timer, SIGNAL(sigFinish(int)), this, SLOT(timerOpenLinksFinished(int)));
        timer->setSingleShot(true);
        timer->start(2000);
    }
}
bool PageMain::_isCurSelQQ_TopItem(){
    if(-1 == mSelLink[1] && -1 < mSelLink[0]){
        return true;
    }
    return false;
}
bool PageMain::_isCurSelQQ_TopLink(const ComTool::LINK_DATA* link)
{
    ComTool::LINK_DATA* linkTop = 0;
    QYVideoWidget* curSelA = ui->wdRPageA_Top->at(0);
    QVariant qvTop = curSelA->property(ComTool::Def::NODELINKNO);
    if(!qvTop.isNull()){linkTop = qvTop.value<ComTool::LINK_DATA*>();}
    return (0 != link) && (link == linkTop);
}
QYVideoWidget* PageMain::_isCurSelQQ_TopLinkEx(const ComTool::LINK_DATA* link)
{
    if(_isCurSelQQ_TopLink(link)){
        return ui->wdRPageA_Top->at(0);
    }
    return 0;
}
void PageMain::_GotCurSel(QYVideoWidget* &wd)
{
    if(-1 < mSelLink[2]){
        wd = ui->panelvideos->at(mSelLink[2]);
    }
}
ComTool::LINK_DATA* PageMain::_GotCurSelQQ_Data(ComTool::NODE_DATA* &dataA, ComTool::NODE_DATA* &dataB)
{
    QYVideoWidget* curSelA = 0;
    QYVideoWidget* curSelB = 0;
    _GotCurSelQQ(curSelA, curSelB);
    if(0 == curSelA){
        return 0;
    }
    QVariant qv = curSelA->property(ComTool::Def::NODELINKNO);
    if(qv.isNull()){
        return 0;
    }
    ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();
    dataA = link->pano;
    dataB = link->sphere;
    return link;
}
void PageMain::_GotCurSel_Data(ComTool::NODE_DATA* &nodedata)
{
    QYVideoWidget* wd = 0;
    _GotCurSel(wd);
    if(0 == wd){
        return;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
       return;
    }
    nodedata = qv.value<ComTool::NODE_DATA*>();
}
ComTool::NODE_DATA* PageMain::_GotCurSelPanoVideo(QYVideoWidget* &wdPano)
{
    ComTool::NODE_DATA* pano = 0;
    _GotCurSelPano(pano);
    if(0 == pano){return pano;}

    QVariant qv;
    int modeUserLeft = AppZZB::getInstance()->showUserLeft();
    if(0 == modeUserLeft){
        qv = pano->otheA;
    }else if(1 == modeUserLeft){
        qv = pano->otheB;
    }
    if(qv.isNull()){return pano;}
    wdPano = qv.value<QYVideoWidget*>();
    return pano;
}
void PageMain::_GotCurSelPano(ComTool::NODE_DATA* &pano)
{
    ComTool::NODE_DATA* dataA = 0;
    ComTool::NODE_DATA* dataB = 0;
    int modeUserLeft = AppZZB::getInstance()->showUserLeft();
    if(0 == modeUserLeft){
        _GotCurSel_Data(dataA);
    }else if(1 == modeUserLeft){
        _GotCurSelQQ_Data(dataA, dataB);
    }
    if(0 != dataA && 0 == dataA->qytype){
        pano = dataA;
    }
}
void PageMain::_GotCurSelSphere(ComTool::NODE_DATA* &sphere)
{
    ComTool::NODE_DATA* dataA = 0;
    ComTool::NODE_DATA* dataB = 0;
    int modeUserLeft = AppZZB::getInstance()->showUserLeft();
    if(0 == modeUserLeft){
        _GotCurSel_Data(dataB);
    }else if(1 == modeUserLeft){
        _GotCurSelQQ_Data(dataA, dataB);
    }
    if(0 != dataB && 1 == dataB->qytype){
        sphere = dataB;
    }
}
ComTool::NODE_DATA* PageMain::_GotCurSelSphereVideo(QYVideoWidget* &wdSphere)
{
    ComTool::NODE_DATA* sphere = 0;
    _GotCurSelSphere(sphere);
    if(0 == sphere){return sphere;}

    QVariant qv;
    int modeUserLeft = AppZZB::getInstance()->showUserLeft();
    if(0 == modeUserLeft){
        qv = sphere->otheA;
    }else if(1 == modeUserLeft){
        qv = sphere->otheB;
    }
    if(qv.isNull()){return sphere;}
    wdSphere = qv.value<QYVideoWidget*>();
    return sphere;
}
ComTool::LINK_DATA* PageMain::_GotOpenedLink(ComTool::NODE_DATA* &pano, ComTool::NODE_DATA* &sphere, QYVideoWidget* &wdPano, QYVideoWidget* &wdSphere)
{
    if(mSelLink[0] == -1){
        return 0;
    }
    ComTool::LINK_DATA* link = 0;
    link = _GotCurSelQQ_Data(pano, sphere);
    if(0 == link){return 0;}

    {
        QVariant qv = link->otherA;
        if(!qv.isNull()){
            wdPano = qv.value<QYVideoWidget*>();
        }
    }
    {
        QVariant qv = link->otherB;
        if(!qv.isNull()){
            wdSphere = qv.value<QYVideoWidget*>();
        }
    }
    if(0 == pano || -1 == (LONG)pano->hOpen || 0 == wdPano){return 0;}

    if(0 == sphere || -1 == (LONG)sphere->hOpen || 0 == wdSphere){return 0;}

    return link;
}
void PageMain::on_tableWidget_qq_itemDoubleClicked(QTableWidgetItem *item)
{
    int row = ui->tableWidget_qq->row(item);
    QTableWidgetItem *item0 = ui->tableWidget_qq->item(row, 0);
    QVariant qv = item0->data(Qt::UserRole);
    if(qv.isNull()){
        return;
    }
    ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();

    int nRes = -1;
    //Close
    QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(link);
    nRes = CloseCameraLink(link);
    if(2 == nRes){
        item0->setIcon(*iconClosed);
        if(link->isLinked && 0 != wdPano){
            ui->cb_Linked->setChecked(false);
            wdPano->enableTrack(false);
            wdPano->enableClick(false);
            disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
        }
    }
    if(nRes > -1){return;}

    //OPen
    QYVideoWidget* curSelA = 0;
    QYVideoWidget* curSelB = 0;
    _GotCurSelQQ(curSelA, curSelB);

    if(!curSelA->property(ComTool::Def::NODELINKNO).isNull()){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("播放提醒"),QString::fromLocal8Bit("当前播放窗口已被暂用，重选一个！"),0);
        return;
    }

    bool isTop = _isCurSelQQ_TopItem();
    int nStream = isTop ? 0 : 1;
    {link->pano->nStream = nStream; link->sphere->nStream = nStream;}

    nRes = OpenCameraLink(link, curSelA, curSelB);
    if(1 == nRes){
        item0->setIcon(*iconOpend);
        if(link->isLinked && _isCurSelQQ_TopLink(link)){//open  then auto link
            ui->cb_Linked->setChecked(true);
            curSelA->enableTrack(true);
            curSelA->enableClick(true);
            connect(curSelA, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
        }
    }
}

//云台控制
int PageMain::PTZControlAll(void* lRealHandle, unsigned int dwPTZCommand, unsigned int dwStop, int Speed)
{
    if(-1 == (LONG)lRealHandle){return -1;}

    BOOL ret;
    if(Speed>=1){
        ret = NET_DVR_PTZControlWithSpeed((LONG)lRealHandle,dwPTZCommand,dwStop,Speed);
    }else{
        ret = NET_DVR_PTZControl((LONG)lRealHandle,dwPTZCommand,dwStop);
    }

    if(!ret){
        return -1;
    }
    return 0;
}

void PageMain::oButABPressed()
{
    QObject* obj = sender();
    if(!obj->inherits("QPushButton")){return;}
    QPushButton* sd = (QPushButton*)obj;
    int key = -1;{
        QVariant qv = sd->property(ComTool::Def::PRO_BUTTONKEY);
        if(!qv.isNull()){key = qv.value<int>();}
    }
    if(-1 == key){return;}

    ComTool::NODE_DATA* sphere = 0;
    _GotCurSelSphere(sphere);
    if(0 == sphere || -1 == (LONG)sphere->hOpen){return;}

    PTZControlAll(sphere->hOpen, key, 0, m_speedYunTai);

//    {
//        NET_DVR_PTZPOS ptzPos;
//        memset(&ptzPos,0,sizeof(NET_DVR_PTZPOS));
//        DWORD  nRes = 0;

//        NET_DVR_GetDVRConfig((LONG)sphere->hLogon,NET_DVR_GET_PTZPOS,0,&ptzPos,sizeof(NET_DVR_PTZPOS),&nRes);
//        int t = QString().sprintf("%x", ptzPos.wPanPos).toInt();
//        int tt = QString().sprintf("%d", t).toInt(0,16);
//        qWarning()<<"Jim is: "<<ptzPos.wPanPos<<" "<<ptzPos.wTiltPos<<" "<<ptzPos.wZoomPos<<" "<<nRes<<" t: "<<t<< " "<<tt;


//    }
}
void PageMain::oButABReleased()
{
    QObject* obj = sender();
    if(!obj->inherits("QPushButton")){return;}
    QPushButton* sd = (QPushButton*)obj;
    int key = -1;{
        QVariant qv = sd->property(ComTool::Def::PRO_BUTTONKEY);
        if(!qv.isNull()){key = qv.value<int>();}
    }
    if(-1 == key){return;}

    ComTool::NODE_DATA* sphere = 0;
    _GotCurSelSphere(sphere);
    if(0 == sphere || -1 == (LONG)sphere->hOpen){return;}

    PTZControlAll(sphere->hOpen, key, 1, m_speedYunTai);
}
void PageMain::on_comboBox_Speed_currentTextChanged(const QString &arg1)
{
    int val = arg1.toInt();
    if(val < 1 || val >  7){return;}
    if(val != m_speedYunTai){
        m_speedYunTai = val;
    }

    ComTool::NODE_DATA* sphere = 0;
    _GotCurSelSphere(sphere);
    if(0 == sphere || -1 == (LONG)sphere->hOpen){return;}


//    {
//        NET_DVR_PTZPOS ptzPos;
//        memset(&ptzPos,0,sizeof(NET_DVR_PTZPOS));
//        ptzPos.wAction = 1;
//        ptzPos.wPanPos = QString().sprintf("%d", 2740).toInt(0,16);
//        ptzPos.wTiltPos = QString().sprintf("%d", 000).toInt(0,16);
//        ptzPos.wZoomPos = QString().sprintf("%d", 40).toInt(0,16);

//        NET_DVR_SetDVRConfig((LONG)sphere->hLogon,NET_DVR_SET_PTZPOS,0,&ptzPos,sizeof(NET_DVR_PTZPOS));
//        qWarning()<<"tOM is: "<<ptzPos.wPanPos<<" "<<ptzPos.wTiltPos<<" "<<ptzPos.wZoomPos;

//    }
}

void _GotoPTZ(ComTool::NODE_DATA* sphere, qreal p, qreal t, qreal z)
{
    NET_DVR_PTZPOS ptzPos;
    memset(&ptzPos,0,sizeof(NET_DVR_PTZPOS));
    ptzPos.wAction = 1;
    ptzPos.wPanPos = QString().sprintf("%d", (int)p*10).toInt(0,16);
    ptzPos.wTiltPos = QString().sprintf("%d",(int)t*10).toInt(0,16);
    ptzPos.wZoomPos = QString().sprintf("%d", (int)z*10).toInt(0,16);

    NET_DVR_SetDVRConfig((LONG)sphere->hLogon,NET_DVR_SET_PTZPOS,0,&ptzPos,sizeof(NET_DVR_PTZPOS));
}
void _GotPTZ(ComTool::NODE_DATA* sphere, qreal *p, qreal *t, qreal *z)
{
    NET_DVR_PTZPOS ptzPos;
    memset(&ptzPos,0,sizeof(NET_DVR_PTZPOS));
    DWORD  nRes = 0;

    NET_DVR_GetDVRConfig((LONG)sphere->hLogon,NET_DVR_GET_PTZPOS,0,&ptzPos,sizeof(NET_DVR_PTZPOS),&nRes);
    int ip = QString().sprintf("%x", ptzPos.wPanPos).toInt();
    int it = QString().sprintf("%x", ptzPos.wTiltPos).toInt();
    int iz = QString().sprintf("%x", ptzPos.wZoomPos).toInt();
    qWarning()<<"NET_DVR_GetDVRConfig : "<<ip<<" "<<it<<" "<<iz;
    if(0 !=p){*p = ip*0.1;}
    if(0 !=t){*t = it*0.1;}
    if(0 !=z){*z = iz*0.1;}
}

void PageMain::on_butRQQ_Calc_clicked()
{
    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link){return;}

    bool cb = ui->cb_Linked->isChecked();
    if(cb){
        ui->cb_Linked->setChecked(false);
        wdPano->enableTrack(false);
        wdPano->enableClick(false);
        disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
    }

    if(0 == pixPointEx){
        //抓图
        QString strPath = _CaptureCamera(wdPano);
        if(strPath.length()<1){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("关联提醒"), QString::fromLocal8Bit("圈圆抓图失败，请重试！"), 0);
            return;
        }
        QImage img;
        if(!img.load(strPath)){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("关联提醒"), QString::fromLocal8Bit("圈圆抓图失败，无法加载文件, 请重试！")+strPath, 0);
            return;
        }
        //截图之后赋值视频尺寸
        pano->vWidth = img.width();
        pano->vHeight = img.height();

        qreal *lr = wdPano->lr;
        lr[0] = pano->lr[0];
        lr[1] = pano->lr[1];
        lr[2] = pano->lr[2];

        QYPixViewer* pixViewer = wdPano->showPixTool(img);
        if(0 != pixViewer){
            if(0 == pixPointEx){
                pixPointEx = new QYPixPointEx(link);
                connect(pixPointEx, SIGNAL(hitPt(int)), this, SLOT(oPixPtEx_Hit(int)));
            }
            pixViewer->addHelper(pixPointEx);
        }
        wdPano->showWidget()->setVisible(false);
        AppZZB::getInstance()->setState(AppZZB::ST_LINK);
        _TurnLeftTab(1);
        if(link->isLinked){
            int nRes = AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("关联提醒"), QString::fromLocal8Bit("已经有关联数据，是否重置？"), 2);
            if(QDialog::Accepted != nRes){
              ComTool::LinkGroupHelper::CopyPixPointVec(&(link->linkPts), &(pixPointEx->pts));
              link->isLinked = false;
              ui->butRQQ_Calc->setText(QString::fromLocal8Bit("关联点值"));
              ui->butRQQ_Calc->setProperty(ComTool::Def::PRO_LINKSTEP, QVariant((int)3));
              ui->dSpinBox_Ag->setEnabled(false);
              ui->dSpinBox_AgR_L->setEnabled(false);
              ui->dSpinBox_AgR_R->setEnabled(false);
              ui->cboBox_Row->setEnabled(false);
              ui->cboBox_Col->setEnabled(false);
              ui->cb_shadow->setVisible(true);
              pixPointEx->enableHit(true);

              ui->dSpinBox_Ag->setValue(pano->ag);
              ui->dSpinBox_AgR_L->setValue(link->agBeg);
              ui->dSpinBox_AgR_R->setValue(link->agEnd);
              ui->cboBox_Row->setCurrentText(QString().sprintf("%d",link->jn));
              ui->cboBox_Col->setCurrentText(QString().sprintf("%d",link->in));

              wdSphere->showCross(true);
//              wdSphere->enableClick(true);
//              wdSphere->enableWheel(true);
//              wdSphere->showWidget()->setCursor(Qt::CrossCursor);
//              connect(wdSphere, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
//              connect(wdSphere, SIGNAL(sigTrackWheel(QWidget*, qreal)), this, SLOT(oSigTrackWheel(QWidget*, qreal)));
              AppZZB::getInstance()->setState(AppZZB::ST_LINK_PT);
              return;
            }
        }

        ComTool::LinkGroupHelper::ReleasePixPointVec(&(link->linkPts));
        link->isLinked = false;

        ui->butRQQ_Calc->setText(QString::fromLocal8Bit("圈圆"));
        ui->butRQQ_Calc->setProperty(ComTool::Def::PRO_LINKSTEP, QVariant((int)1));
        ui->dSpinBox_Ag->setEnabled(true);
        ui->dSpinBox_AgR_L->setEnabled(false);
        ui->dSpinBox_AgR_R->setEnabled(false);
        ui->cboBox_Row->setEnabled(false);
        ui->cboBox_Col->setEnabled(false);

        ui->dSpinBox_Ag->setValue(pano->ag);
        ui->dSpinBox_AgR_L->setValue(link->agBeg);
        ui->dSpinBox_AgR_R->setValue(link->agEnd);
        ui->cboBox_Row->setCurrentText(QString().sprintf("%d",link->jn));
        ui->cboBox_Col->setCurrentText(QString().sprintf("%d",link->in));
        return;
    }

    QVariant qv = ui->butRQQ_Calc->property(ComTool::Def::PRO_LINKSTEP);
    if(qv.isNull()){
        return;
    }

    int step = qv.toInt();
    if(1 == step)//开始计算网格
    {
        qreal *lr = pano->lr;
        lr[0] = wdPano->lr[0];
        lr[1] = wdPano->lr[1];
        lr[2] = wdPano->lr[2];
        pano->calced = 1;

        ui->butRQQ_Calc->setText(QString::fromLocal8Bit("网格"));
        ui->butRQQ_Calc->setProperty(ComTool::Def::PRO_LINKSTEP, QVariant((int)2));
        ui->dSpinBox_Ag->setEnabled(false);
        ui->dSpinBox_AgR_L->setEnabled(true);
        ui->dSpinBox_AgR_R->setEnabled(true);
        ui->cboBox_Row->setEnabled(true);
        ui->cboBox_Col->setEnabled(true);

        pixPointEx->ReCreatePts();

    }else if(2 == step){
        ui->butRQQ_Calc->setText(QString::fromLocal8Bit("关联点值"));
        ui->butRQQ_Calc->setProperty(ComTool::Def::PRO_LINKSTEP, QVariant((int)3));
        ui->dSpinBox_Ag->setEnabled(false);
        ui->dSpinBox_AgR_L->setEnabled(false);
        ui->dSpinBox_AgR_R->setEnabled(false);
        ui->cboBox_Row->setEnabled(false);
        ui->cboBox_Col->setEnabled(false);
        pixPointEx->enableHit(true);

        ui->cb_shadow->setVisible(true);
        wdSphere->showCross(true);
//        wdSphere->enableClick(true);
//        wdSphere->enableWheel(true);
//        wdSphere->showWidget()->setCursor(Qt::CrossCursor);
//        connect(wdSphere, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
//        connect(wdSphere, SIGNAL(sigTrackWheel(QWidget*, qreal)), this, SLOT(oSigTrackWheel(QWidget*, qreal)));
        AppZZB::getInstance()->setState(AppZZB::ST_LINK_PT);
    }else if(3 == step){
        pixPointEx->SetCurDownPos();
        pixPointEx->curHitted =  -1;
        ui->cb_shadow->setChecked(false);
        pixPointEx->ShowShadow(false);
        //pixPointEx->pixItem->UpdateView();
    }

//    { //开始做计算

//        if(-1 < pixCalcNo && pixCalcNo < 10){
//            pixPointEx->AddCurDownPos();
//        }
//        int n = pixPointEx->pts.size();
//        if(n<10){

//            static qreal TT[20] = {12.5,26.375,40.25,54.125,68.0,68.0,54.125,40.25,26.375,12.5,
//                                   12.5,26.375,40.25,54.125,68.0,68.0,54.125,40.25,26.375,12.5};
//            static qreal PP[20] = {0,0,0,0,0,180,180,180,180,180,
//                                   90,90,90,90,90,270,270,270,270,270};
//            static qreal TT[10] = {12.5,26.375,40.25,54.125,68.0,
//                                   12.5,26.375,40.25,54.125,68.0};
//            static qreal PP[10] = {0,0,0,0,0,90,90,90,90,90};
//            _GotoPTZ(sphere, PP[n], TT[n], 2);
//            pixCalcNo = n;
//            ui->butRQQ_Calc->setText(QString::fromLocal8Bit("标记点")+QString().sprintf("%d", n+1));
//            return;
//        }
//        pixPointEx->Calc(wdPano->lr);
//        QYPixViewer* pixViewer = wdPano->hidePixTool();
//        if(0 != pixViewer){
//            pixViewer->removeHelper(pixPointEx);
//            ComTool::CCommon<QYPixPointEx>::DeleteA(&pixPointEx);
//        }
//        pixCalcNo = -1;
//        wdSphere->showCross(false);
//        ui->butRQQ_Calc->setText(QString::fromLocal8Bit("校准"));

//        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("联动校准"), QString::fromLocal8Bit("成功完成校准！"),0);
//    }
}

QYPixPointEx::QYPixPointEx(ComTool::LINK_DATA* l, QObject *parent):QYPixHelper(parent){
    link = l;
    imgCross.load(":/QYRTSPWidget/3_0");
    imgCrossA.load(":/QYRTSPWidget/3_1");
    imgCrossB.load(":/QYRTSPWidget/3_2");
    isLinked = false;
    curHitted =  -1;
    mEnableHit = false;
}
QYPixPointEx::~QYPixPointEx(){
    ComTool::LinkGroupHelper::ReleasePixPointVec(&pts);
}
//int QYPixPointEx::AddCurDownPos()
//{
//    QPointF pt = pixItem->downPos;
//    qreal p = 0.0;
//    qreal t = 0.0;
//    qreal z = 0.0;
//    _GotPTZ(link->sphere, &p, &t, &z);
//    pts.push_back(new ComTool::PixPoint(pt, p,t,z));
//    return 0;
//}
int QYPixPointEx::SetCurDownPos()
{
    if(-1 == curHitted){return -1;}
    ComTool::PixPoint* pixPt = pts[curHitted];

    qreal p = 0.0;
    qreal t = 0.0;
    qreal z = 0.0;
    _GotPTZ(link->sphere, &p, &t, &z);

    pixPt->p = p;
    pixPt->t = t;
    pixPt->z = z;
    pixPt->flag = 1;

    //add Ref Point
    pixPt->isRef = pixItem->showDownPos;
    if(pixPt->isRef){
        pixPt->posRef = pixItem->downPos;
    }

    return 0;
}
int QYPixPointEx::HitObj(QPointF pt, qreal s, int flag)
{
    if(mEnableHit && 1 == flag && pts.size() > 0){
        curHitted = -1;

        //qreal ratio = 4.0/3.0;
        qreal *lr = link->pano->lr;
        qreal fbeg = link->agBeg;//12.5;
        qreal fend = link->agEnd;//68.0;
        qreal fAg  = link->pano->ag*0.5;
        qreal ratio= link->pano->vWidth*1.0/link->pano->vHeight;
        int jn = link->jn;
        int in = link->in;

        bool bo = false;
        int i1,i2, j1,j2=0;
        ComTool::LinkGroupHelper::CalcMeshIndex(pt, lr, fAg, ratio, fbeg, fend, in, jn, &bo, &i1, &i2, &j1, &j2, 0,0,0);

        std::vector<int> iv;
        if(bo){iv.push_back(0);}
        iv.push_back(1+in*j1+i1);
        iv.push_back(1+in*j1+i2);
        iv.push_back(1+in*j2+i1);
        iv.push_back(1+in*j2+i2);

        for(int i=0,l=iv.size(); i<l; ++i){
            int id = iv[i];
            if(id >= pts.size()){continue;}
            QPointF pos = pts[id]->pos;
            QPointF d = pt - pos;
            if(qAbs(d.x()*ratio) < s*0.5 && qAbs(d.y())<s*0.5){//Hit
                curHitted = id;
                break;
            }
        }//End for

         emit hitPt(curHitted);

    }//End If
    return 0;
}

void QYPixPointEx::Calc(const qreal* wdlr)
{
//    qreal *lr = link->pano->lr;
//    lr[0] = wdlr[0];
//    lr[1] = wdlr[1];
//    lr[2] = wdlr[2];

    ComTool::LinkGroupHelper::ReleasePixPointVec(&(link->linkPts));
    ComTool::LinkGroupHelper::CopyPixPointVec(&pts, &(link->linkPts));
    link->isLinked = true;

//    QVector2D& linkCross = link->linkCross;
//    QVector2D& linkDirX  = link->linkDirX;
//    QVector2D& linkDirY  = link->linkDirY;
//    QVector2D& linkLinear= link->linkLinear;
//    bool& isLinked       = link->isLinked;

//    for(int i=0, ll=pts.size(); i<ll; ++i){
//        qreal u = pts[i]->pos.x() - lr[1];
//        qreal v = pts[i]->pos.y() - lr[2];
//        pts[i]->_x = u;
//        pts[i]->_y = v;
////        qreal l = sqrt(u*u+v*v);
////        qreal ct = u/l;
////        qreal st = v/l;
////        qreal r = 1.0;
////        qreal phiAll = 180.0*0.5*(M_PI/180.0);
////        qreal phi = l/lr[0]*phiAll;
////        pts[i]->_x = r*sin(phi)*ct;
////        pts[i]->_y = r*cos(phi);
////        pts[i]->_z = r*sin(phi)*st;
////        qWarning()<<"erre: "<<pts[i]->_x<<" "<<pts[i]->_y<<" "<<pts[i]->_z;
//    }
//    {
//        czy::Fit fit;
//        std::vector<qreal> xs;
//        std::vector<qreal> ys;
//        for(int i=0; i<5; ++i){
//            xs.push_back(pts[i]->_x);
//            ys.push_back(pts[i]->_y);
//        }
//        fit.linearFit(xs,ys);

//        czy::Fit fit2;
//        std::vector<qreal> xs2;
//        std::vector<qreal> ys2;
//        for(int i=5; i<10; ++i){
//            xs2.push_back(pts[i]->_x);
//            ys2.push_back(pts[i]->_y);
//        }
//        fit2.linearFit(xs2,ys2);

//        //CrossPoint
//        qreal cx = -(fit.getIntercept() - fit2.getIntercept())/(fit.getSlope()-fit2.getSlope());
//        qreal cy = fit.getSlope()*cx+fit.getIntercept();
//        QVector2D cross = QVector2D(cx, cy);
//        QVector2D xx = QVector2D(xs[2], fit.getY(xs[2]));
//        QVector2D yy = QVector2D(xs2[2], fit2.getY(xs2[2]));
//        QVector2D dirX = xx - cross;
//        QVector2D dirY = yy - cross;
//        dirX.normalize();
//        dirY.normalize();

//        pts.push_back(new PixPoint(QPointF(cx+lr[1], cy+lr[2]), 0,0,0));
//        pixItem->update();

//        czy::Fit fit3;
//        std::vector<qreal> xs3;
//        std::vector<qreal> ys3;
//        for(int i=0; i<5; ++i){
//            QVector2D xx = QVector2D(xs[i], fit.getY(xs[i]));
//            qreal l = QVector2D::dotProduct(xx, dirX);
//            xs3.push_back(l);
//            ys3.push_back(pts[i]->t);

//            QVector2D yy = QVector2D(xs2[i], fit2.getY(xs2[i]));
//            qreal l2 = QVector2D::dotProduct(yy, dirY);
//            xs3.push_back(l2);
//            ys3.push_back(pts[5+i]->t);
//        }
//        fit3.linearFit(xs3,ys3);

//        linkCross = cross;
//        linkDirX = dirX;
//        linkDirY = dirY;
//        linkLinear.setX(fit3.getSlope());
//        linkLinear.setY(fit3.getIntercept());

//        isLinked = true;
//    }
}
void QYPixPointEx::ReCreatePts()
{
    if(0 == link || 0 == link->pano){return;}

    ComTool::LinkGroupHelper::ReleasePixPointVec(&pts);

    const qreal *lr = link->pano->lr;
    pts.push_back(new ComTool::PixPoint(QPointF(lr[1],lr[2]), 0,0,2));
    qreal fbeg = link->agBeg;//12.5;
    qreal fend = link->agEnd;//68.0;
    qreal fAg  = link->pano->ag*0.5;
    qWarning()<<"sdf: "<<link->pano->vWidth<<"  "<<link->pano->vHeight;
    qreal ratio= link->pano->vWidth*1.0/link->pano->vHeight;
    int jn = link->jn;
    int in = link->in;
    for(int j=0; j<jn; ++j){
        qreal rag = fbeg + j*(fend-fbeg)/(jn-1);
        qreal rr = rag / fAg * lr[0];
        for(int i=0; i<in; ++i){
            qreal ta = 2.0*M_PI*i/in;
            QPointF pt = QPointF(cos(ta)*rr/ratio+lr[1], sin(ta)*rr + lr[2]);
            pts.push_back(new ComTool::PixPoint(pt, 0,0,2));
        }
    }
    pixItem->UpdateView();
}
void QYPixPointEx::enableHit(bool enable)
{
    mEnableHit = enable;
}
bool QYPixPointEx::ShowShadow(bool show)
{
    if(show){
        if(-1 == curHitted){return false;}
        pixItem->showDownPos = true;
        enableHit(false);
    }else{
        pixItem->showDownPos = false;
        enableHit(true);
    }
    pixItem->UpdateView();

    return true;
}
void QYPixPointEx::paint(QPainter *painter)
{
    if(0 == pixItem || pts.size()<1){return;}
    QRectF rt = pixItem->boundingRect();
    qreal w = rt.width();
    qreal h = rt.height();

    qreal s  = pixItem->getScale();
    qreal wi = 4.0 * (4.0/s);
    qreal hi = 4.0 * (4.0/s);

    for(int i=0, l=pts.size(); i<l; ++i){
        ComTool::PixPoint* pixPt = pts[i];

        painter->drawImage(QRectF(pixPt->pos.x()*w-wi*0.5,
                                  pixPt->pos.y()*h-hi*0.5,
                                  wi,hi),  (curHitted==i)?imgCrossB:((0==pixPt->flag)?imgCross:imgCrossA));
    }
}

void PageMain::on_cb_shadow_clicked()
{
    if(0 == pixPointEx){
        ui->cb_shadow->setChecked(false);
        return;
    }
    bool cb = ui->cb_shadow->isChecked();
    if(!pixPointEx->ShowShadow(cb)){
        ui->cb_shadow->setChecked(false);
    }
}
void PageMain::oPixPtEx_Hit(int cur)
{
    qWarning()<<"oPixPtEx_Hit "<<cur;
    if(0 == pixPointEx || -1 == cur){return;}

    const ComTool::PixPoint* pt = pixPointEx->pts[cur];
    if(pt->isRef){
        pixPointEx->pixItem->downPos = pt->posRef;
        ui->cb_shadow->setChecked(true);
        on_cb_shadow_clicked();
    }
}
void PageMain::on_cb_Linked_clicked()
{
    bool cb = ui->cb_Linked->isChecked();

    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link){return;}

    if(!link->isLinked){
        if(!cb){return;}

        if(0 == pixPointEx || 1 > pixPointEx->pts.size() || AppZZB::ST_LINK_PT != AppZZB::getInstance()->state()){
            ui->cb_Linked->setChecked(false);
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("联动提醒"), QString::fromLocal8Bit("无法开启联动，请先完成校准！"), 0);
            return;
        }

        //Calc
        pixPointEx->Calc(wdPano->lr);
        pixPointEx->enableHit(false);
        QYPixViewer* pixViewer = wdPano->hidePixTool();
        if(0 != pixViewer){
            pixViewer->removeHelper(pixPointEx);
            ComTool::CCommon<QYPixPointEx>::DeleteA(&pixPointEx);
        }
        wdPano->_UpdatePosSize();
        wdPano->showWidget()->setVisible(true);

        //pixCalcNo = -1;
        wdSphere->showCross(false);
        ui->butRQQ_Calc->setText(QString::fromLocal8Bit("校准"));
        ui->butRQQ_Calc->setProperty(ComTool::Def::PRO_LINKSTEP, QVariant());
        ui->dSpinBox_Ag->setEnabled(false);
        ui->dSpinBox_AgR_L->setEnabled(false);
        ui->dSpinBox_AgR_R->setEnabled(false);
        ui->cboBox_Row->setEnabled(false);
        ui->cboBox_Col->setEnabled(false);
        ui->cb_shadow->setVisible(false);

//        wdSphere->enableClick(false);
//        wdSphere->enableWheel(false);
//        wdSphere->showWidget()->setCursor(Qt::ArrowCursor);
//        disconnect(wdSphere, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
//        disconnect(wdSphere, SIGNAL(sigTrackWheel(QWidget*, qreal)), this, SLOT(oSigTrackWheel(QWidget*, qreal)));

        AppZZB::getInstance()->setState(AppZZB::ST_OK);
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("联动校准"), QString::fromLocal8Bit("成功完成校准！"),0);
    }

    if(cb){
        wdPano->enableTrack(true);
        wdPano->enableClick(true);
        connect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
    }else{
        wdPano->enableTrack(false);
        wdPano->enableClick(false);
        disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
    }
}
void PageMain::oSigTrackClicked(QWidget* _wd, QVector2D uv)
{
    QYVideoWidget* wd = (QYVideoWidget*)_wd;
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
       return;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hOpen){
        return;
    }
    if(1 == nodeData->qytype && 1 == nodeData->imgtype){
        NET_DVR_POINT_FRAME rt;
        qreal dx = 0.0;//min(uv.x(), 1.0-uv.x());
        qreal dy = 0.0;//min(uv.y(), 1.0-uv.y());
        rt.xTop = (uv.x()-dx) * 255;
        rt.yTop = (uv.y()-dy) * 255;
        rt.xBottom = (uv.x()+dx) * 255;
        rt.yBottom = (uv.y()+dy) * 255;
        //NET_DVR_PTZSelZoomIn((LONG)sphere->hLogon, &rt);
        NET_DVR_PTZSelZoomIn_EX((LONG)nodeData->hLogon, nodeData->dwChannelNo, &rt);
        return;
    }

    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link || wdPano != wd){return;}

    qreal p = 0;
    qreal t = 0;
    qreal z = 0;
    if(0 == ComTool::LinkGroupHelper::CalcPTZ(link, uv, &p, &t, &z)){
        _GotoPTZ(sphere, p, t, z);
    }
}
void PageMain::oSigTrackRect(QWidget* _wd, QVector2D uvStart, QVector2D uvEnd)
{
    QYVideoWidget* wd = (QYVideoWidget*)_wd;
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
       return;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hOpen){
        return;
    }
    if(1 != nodeData->qytype || 1 != nodeData->imgtype){
        return;
    }
    NET_DVR_POINT_FRAME rt;
    rt.xTop = uvStart.x() * 255;
    rt.yTop = uvStart.y() * 255;
    rt.xBottom = uvEnd.x() * 255;
    rt.yBottom = uvEnd.y() * 255;
    //NET_DVR_PTZSelZoomIn((LONG)sphere->hLogon, &rt);
    NET_DVR_PTZSelZoomIn_EX((LONG)nodeData->hLogon, nodeData->dwChannelNo, &rt);
}
void PageMain::oSigTrackWheel(QWidget* _wd, qreal fTurn)
{
    QYVideoWidget* wd = (QYVideoWidget*)_wd;
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
       return;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hOpen){
        return;
    }
    if(1 != nodeData->qytype || 1 != nodeData->imgtype){
        return;
    }

    ComTool::NODE_DATA* sphere = nodeData;
    qreal p = 0.0;
    qreal t = 0.0;
    qreal z = 0.0;
//        unsigned int key = ZOOM_IN;
//        if(nTurn < 0){
//            key = ZOOM_OUT;
//        }
//        nTurn = qAbs(nTurn);
//        nTurn = (nTurn < 2) ? 2 : nTurn;
//        nTurn = (nTurn > 7) ? 7 : nTurn;
//        PTZControlAll(sphere->hOpen, key, 0, nTurn);
//        PTZControlAll(sphere->hOpen, key, 1, nTurn);

    _GotPTZ(sphere, &p, &t, &z);
    qreal fScale = 1.5;
    int flag = 1;
    if(fTurn < 0){
        //fScale = 0.9;
        flag   = -1;
    }
    z += flag*qPow(fScale, qAbs(fTurn));
    z = z < 1.0 ? 1.0 : z;
    z = z > 20.0 ? 20.0 : z;
    qWarning()<<"Sphere Zoom: "<<z;
    _GotoPTZ(sphere, p, t, z);
}

void PageMain::oSigDoubleClicked_RPageA_Bot()
{
    QYVideoWidget* wd = (QYVideoWidget*)sender();
    QVariant qvBot = wd->property(ComTool::Def::NODELINKNO);
    if(qvBot.isNull()){
        return;
    }
    ComTool::LINK_DATA* linkBot = qvBot.value<ComTool::LINK_DATA*>();
    if(linkBot->other.isNull()){
        return;
    }
    QTableWidgetItem* item = linkBot->other.value<QTableWidgetItem*>();
    if(0 == item){
        return;
    }
    int sel = ui->tableWidget_qq->row(item);
    int cur = _GotCurSelQQ_TopItem();
    if(cur != sel &&  -1 <sel){
        _TurnShow_TopItem(sel);
    }
}
void PageMain::timerOpenLink()
{
    QObject* sd = sender();
    if(!sd->inherits("OpenLinkDataTimer")){
        AppZZB::getInstance()->TurnShowDlgLoading(false);
        return;
    }
    OpenLinkDataTimer* timer = (OpenLinkDataTimer*)sd;

    ComTool::LINK_DATA* link = 0;
    QYVideoWidget* curSelA   = 0;
    QYVideoWidget* curSelB   = 0;
    int no = 0;
    {
        QVariant qv = timer->property(ComTool::Def::LINK_OPEN_LINK);
        if(!qv.isNull()){link = qv.value<ComTool::LINK_DATA*>();}
    }
    {
        QVariant qv = timer->property(ComTool::Def::LINK_OPEN_SELA);
        if(!qv.isNull()){curSelA = qv.value<QYVideoWidget*>();}
    }
    {
        QVariant qv = timer->property(ComTool::Def::LINK_OPEN_SELB);
        if(!qv.isNull()){curSelB = qv.value<QYVideoWidget*>();}
    }
    {
        QVariant qv = timer->property(ComTool::Def::LINK_OPEN_LINK_NO);
        if(!qv.isNull()){no = qv.value<int>();}
    }

    timer->setProperty(ComTool::Def::LINK_OPEN_LINK, QVariant());
    timer->setProperty(ComTool::Def::LINK_OPEN_SELA, QVariant());
    timer->setProperty(ComTool::Def::LINK_OPEN_SELB, QVariant());

    if(0 == link || 0 == curSelA){//|| 0 == curSelB
        timer->doFinish(no);
        timer->deleteLater();
        return;
    }

    //OPen
    int nRes = OpenCameraLink(link, curSelA, curSelB);
    if(1 == nRes){
        if(!link->other.isNull()){
            QTableWidgetItem* item = link->other.value<QTableWidgetItem*>();
            if(0 != item){
                item->setIcon(*iconOpend);
            }
        }
        if(link->isLinked && _isCurSelQQ_TopLink(link)){//open  then auto link
            ui->cb_Linked->setChecked(true);
            curSelA->enableTrack(true);
            curSelA->enableClick(true);
            connect(curSelA, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
        }
    }

    timer->doFinish(no);
    timer->deleteLater();
}
void PageMain::timerOpenLinksFinished(int no)
{
    qWarning()<<"timerOpenLinksFinished NO: "<<no;
    sumOpenLink--;
    if(0 == sumOpenLink){
        QTimer::singleShot(5000,this,SLOT(timerFinishedLoading()));
    }
}
void PageMain::timerFinishedLoading()
{
    //QTimer* timer = (QTimer*)sender();
    //timer->deleteLater();
    AppZZB::getInstance()->TurnShowDlgLoading(false);
    //ui->butAA_B_A->setEnabled(true);
    //ui->butAA_B_B->setEnabled(true);
}
void PageMain::on_dSpinBox_Ag_valueChanged(double arg1)
{
    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link){return;}

    if(fabs(pano->ag - arg1) < 1.0e-6){
        return;
    }
    pano->ag = arg1;
}

void PageMain::on_dSpinBox_AgR_L_valueChanged(double arg1)
{
    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link){return;}

    if(fabs(link->agBeg - arg1) < 1.0e-6){
        return;
    }
    link->agBeg = arg1;
    if(0 != pixPointEx){
        pixPointEx->ReCreatePts();
    }
}

void PageMain::on_dSpinBox_AgR_R_valueChanged(double arg1)
{
    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link){return;}

    if(fabs(link->agEnd - arg1) < 1.0e-6){
        return;
    }
    link->agEnd = arg1;
    if(0 != pixPointEx){
        pixPointEx->ReCreatePts();
    }
}

void PageMain::on_cboBox_Row_currentTextChanged(const QString &arg1)
{
    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link){return;}

    int nrow = arg1.toInt();
    if(nrow == link->jn){
        return;
    }
    link->jn = nrow;
    if(0 != pixPointEx){
        pixPointEx->ReCreatePts();
    }
}

void PageMain::on_cboBox_Col_currentTextChanged(const QString &arg1)
{
    ComTool::LINK_DATA* link = 0;
    ComTool::NODE_DATA* pano = 0;
    ComTool::NODE_DATA* sphere = 0;
    QYVideoWidget* wdPano = 0;
    QYVideoWidget* wdSphere = 0;
    link = _GotOpenedLink(pano,sphere,wdPano,wdSphere);
    if(0 == link){return;}

    int ncol = arg1.toInt();
    if(ncol == link->in){
        return;
    }
    link->in = ncol;
    if(0 != pixPointEx){
        pixPointEx->ReCreatePts();
    }
}

ComTool::NODE_DATA* PageMain::_GotSelFromTree(void)
{
    QTreeWidgetItem *nodeItem = ui->treeWidget->currentItem();
    if(0 == nodeItem || ComTool::Def::ITEM_TREE_TYPE == nodeItem->type()){
        return 0;
    }
    return nodeItem->data(0, Qt::UserRole).value<ComTool::NODE_DATA*>();
}

bool PageMain::canTurnPanoShow(QYVideoWidget* wd)
{
    //return true;
    if(0 == wd){
        return false;
    }
//    int modeUserLeft = AppZZB::getInstance()->showUserLeft();
//    if(0 != modeUserLeft){
//        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("分屏提醒"), QString::fromLocal8Bit("该页面窗口无法分屏"), 0);
//        return false;
//    }

//    if(0 != gStreamPort && wd != gStreamPort->wd){
//        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("分屏提醒"), QString::fromLocal8Bit("请先关闭已分屏窗口"), 0);
//        return false;
//    }

    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();

    if(1 != nodeData->qytype){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("相机属性"), QString::fromLocal8Bit("该硬件设备不被支持！"), 0);
        return false;
    }
    if(-1 == nodeData->imgtype){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("相机属性"), QString::fromLocal8Bit("请先右键相机设置相机的设备类型"), 0);
        return false;
    }else if(0 != nodeData->imgtype){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("相机属性"), QString::fromLocal8Bit("该硬件设备不被支持！"), 0);
        return false;
    }

    if(!canTurnStreamPortMap()){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("分屏提醒"), QString::fromLocal8Bit("分屏数量已达到上限！"), 0);
        return false;
    }

    {//关闭联动
        QVariant qvLink = wd->property(ComTool::Def::NODELINKNO);
        if(!qvLink.isNull()){
            ComTool::LINK_DATA* link = qvLink.value<ComTool::LINK_DATA*>();
            QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(link);
            if((0!=link) && link->isLinked && (0 != wdPano)){
                ui->cb_Linked->setChecked(false);
                wdPano->enableTrack(false);
                wdPano->enableClick(false);
                disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
            }//end if
        }//end if
    }//end


    if(AppZZB::ST_PANO == AppZZB::getInstance()->state()){
        wd->hidePixTool();
        nodeData->lr[0] = wd->lr[0];
        nodeData->lr[1] = wd->lr[1];
        nodeData->lr[2] = wd->lr[2];
        nodeData->ag    = wd->ag;
        nodeData->calced = 1;
        wd->_UpdatePosSize();
        wd->showWidget()->setVisible(true);
        AppZZB::getInstance()->setState(AppZZB::ST_OK);
        return true;
    }

    //是否重置
    QWidget* wdRoot = wd->rootWidget();
    GLPanoWidget* pano = wdRoot->findChild<GLPanoWidget*>("pano");
    if(1 == nodeData->calced && 0 == pano){
        int nRes = AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("实时显示"), QString::fromLocal8Bit("是否重新获取圆心参数?"), 2);
        if(QDialog::Accepted == nRes){
            nodeData->calced = 0;
        }
    }

    if(0 == nodeData->calced){
        QImage img;
        {
            QString strPath = _CaptureCamera(wd);
            if(strPath.length()<1){
                AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("实时显示"), QString::fromLocal8Bit("圈圆抓图失败，请重试！"), 0);
                return false;
            }
            if(!img.load(strPath)){
                AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("关联提醒"), QString::fromLocal8Bit("圈圆抓图失败，无法加载文件, 请重试！")+strPath, 0);
                return false;
            }
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("实时显示"), QString::fromLocal8Bit("获取圆心参数，请先圈圆！"), 0);
            //截图之后赋值视频尺寸
            nodeData->vWidth = img.width();
            nodeData->vHeight = img.height();
        }
        wd->showPixTool(img);
        wd->showWidget()->setVisible(false);
        AppZZB::getInstance()->setState(AppZZB::ST_PANO);
        return false;
    }

    return true;
}
GLPanoWidget* panopano = 0;
bool PageMain::turnPanoShow(QYVideoWidget* wd, int butNo)
{
    if(0 == wd){
        return false;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();

    QWidget* wdRoot = wd->rootWidget();
    GLPanoWidget* pano = wdRoot->findChild<GLPanoWidget*>("pano");
    if(ComTool::BN_PANO_CLOSE == butNo && turnPanoClose(wd)){
        QWidget* wdShow = wd->showWidget();
        OpenHCCamera(nodeData,(HWND)(wdShow->winId()));
        wdShow->setVisible(false);
        wd->_UpdatePosSize();
        wdShow->setVisible(true);

//        if(0 != pano && 0 != gStreamPort){
//            CloseHCCameraStream(nodeData, gStreamPort);
//            if(0 != gStreamPort){
//                delete gStreamPort;
//                gStreamPort = 0;
//            }
//            gStreamPortMap.clear();
//            qDebug()<<"dx: ";

//            pano->setVisible(false);
//            pano->deleteLater();
//            //delete pano;
//            //pano = 0;

//            qDebug()<<"dx2: ";

//            QWidget* wdShow = wd->showWidget();
//            OpenHCCamera(nodeData,(HWND)(wdShow->winId()));
//            wdShow->setVisible(false);
//            wd->_UpdatePosSize();
//            wdShow->setVisible(true);
//        }
        return true;

    }

    if(0 == pano){
        CloseHCCamera(nodeData);
        nodeData->nStream = 0; //强制为主码流
        AppZZB::getInstance()->updateUIDlgHotBar();

        HCStreamCB* hc = new HCStreamCB();
        hc->nodeData = nodeData;
        hc->wd = wd;
        if(0 != OpenHCCameraStream(nodeData, hc)){
            delete hc;
            hc = 0;
            return false;
        }
        wd->showWidget()->setVisible(false);
        QWidget* wdRoot = wd->rootWidget();
        pano = new GLPanoWidget(wdRoot);//wdRoot
        pano->setObjectName("pano");
        pano->setFocusPolicy(Qt::NoFocus);
        pano->setVisible(false);
        pano->setGeometry(QRect(0, 0, wdRoot->width(), wdRoot->height()));
        pano->SetParams(nodeData->lr, nodeData->ag);
        hc->pano = pano;
        pano->setVisible(true);
    }

    if(0 != pano){//CHNAGE
        QVariant qv = pano->property("ButID");
        int cNo = ComTool::BN_PANO_NONE;
        cNo = qv.isNull() ? cNo : qv.toInt();
        if((ComTool::BN_PANO_ONE <= butNo && butNo <=ComTool::BN_PANOH_TWO) && cNo != butNo){
            pano->setProperty("ButID", QVariant((int)butNo));
            pano->TurnViewType(butNo);
            return true;
        }
    }

    return false;
}
bool PageMain::turnPanoClose(QYVideoWidget* wd)
{
    if(0 == wd){
        return false;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();

    QWidget* wdRoot     = wd->rootWidget();
    GLPanoWidget* pano  = wdRoot->findChild<GLPanoWidget*>("pano");
    if(0 != pano && hasStreamPort(wd)){
        closeStreamPort(wd);
        pano->setVisible(false);
        pano->deleteLater();
        return true;
    }
//    if(0 != pano && 0 != gStreamPort && wd == gStreamPort->wd){
//        CloseHCCameraStream(nodeData, gStreamPort);
//        if(0 != gStreamPort){
//            delete gStreamPort;
//            gStreamPort = 0;
//        }
//        gStreamPortMap.clear();
//        qDebug()<<"dx: ";
//        pano->setVisible(false);
//        pano->deleteLater();
//        //delete pano;
//        //pano = 0;
//        qDebug()<<"dx2: ";
//        return true;
//    }

    return false;
}
bool PageMain::turnSpeekCamera(QYVideoWidget* wd, bool on)
{
    if(!on){
        if(0 != gSpeekNodeData && -1 != (LONG)gSpeekNodeData->hSpeek){
            NET_DVR_StopVoiceCom((LONG)(gSpeekNodeData->hSpeek));
            gSpeekNodeData->hSpeek = (void*)-1;
            gSpeekNodeData = 0;
            return true;
        }
        return false;
    }

    if(0 == wd){
        return false;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hLogon){
        return false;
    }
    if(0 != gSpeekNodeData && -1 != (LONG)gSpeekNodeData->hSpeek){
        NET_DVR_StopVoiceCom((LONG)(gSpeekNodeData->hSpeek));
        gSpeekNodeData->hSpeek = (void*)-1;
        gSpeekNodeData = 0;
    }

    int iCurChan = 1;
    int iCurChanIndex = 1;
    nodeData->hSpeek = (void*)NET_DVR_StartVoiceCom_V30((LONG)nodeData->hLogon,iCurChanIndex,iCurChan,0,0);
    if(-1 == (LONG)(nodeData->hSpeek)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("对讲提示"), QString::fromLocal8Bit("设备对讲连接失败！"), 0);
    }
    gSpeekNodeData = nodeData;
    return true;
}
bool PageMain::turnCaptureCamera(QYVideoWidget *wd)
{
    QString strPath = _CaptureCamera(wd);
    return strPath.length() > 0;
}
QString PageMain::_CaptureCamera(QYVideoWidget *wd)
{
    if(0 == wd){
        return QString();
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return QString();
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hLogon){
        return QString();
    }

    QString strSaveFilePath = AppZZB::getInstance()->GetSavePath(0);
    ComTool::Tool::isExistDir(strSaveFilePath, true);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString fileName = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
    strSaveFilePath += "/[" + fileName + "]";
    strSaveFilePath += nodeData->name;
    strSaveFilePath += AppZZB::getInstance()->GetSavePath(2);

    char saveFilePath[MAX_SIZE];
    memset(saveFilePath, 0, MAX_SIZE);
    ::sprintf_s(saveFilePath, "%s",strSaveFilePath.toStdString().c_str());

    if( 0 == nodeData->qytype){
        unsigned char* pCapBuf = new unsigned char[3840*2160*4];
        int picSize = 0;
        QVariant qv = wd->property(ComTool::Def::PLAYERNO);
        int playerNo = qv.value<int>();
        int	errCode = HHERR_SUCCESS;
        errCode = HH5PLAYER_CaptureOnePicture((USHORT)playerNo, (void**)&pCapBuf, picSize);
        if(HHERR_SUCCESS != errCode){
            delete[] pCapBuf;
            picSize = 0;
            return QString();
        }
        QImage img;
        if(img.loadFromData(pCapBuf, picSize)){
            img.save(strSaveFilePath);
            return strSaveFilePath;
        }
        delete[] pCapBuf;
        picSize = 0;
    }else{
//            unsigned int nSize = 3840*2160*4;
//            char *pCapBuf= new char[nSize];
//            DWORD  picSize=0;
//            if(!NET_DVR_CapturePictureBlock_New((LONG)nodeData->hOpen, pCapBuf, nSize, &picSize)){
//                delete[] pCapBuf;
//                picSize = 0;
//                return QString();
//            }

//            NET_DVR_JPEGPARA JpegPara;
//            JpegPara.wPicQuality=0;
//            JpegPara.wPicSize=0xff;

//            unsigned int nSize = 3840*2160*4;
//            char *pCapBuf= new char[nSize];

//            DWORD  picSize=0;
//            BOOL bRet= NET_DVR_CaptureJPEGPicture_NEW((LONG)nodeData->hLogon, nodeData->dwChannelNo,&JpegPara,pCapBuf,nSize,&picSize);
//            if (!bRet){
//                delete[] pCapBuf;
//                picSize = 0;
//                return QString();
//                //int err = NET_DVR_GetLastError();
//                //AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("截图提醒"), QString::fromLocal8Bit("截图失败，请重试！") + QString().sprintf(" %d", err), 0);
//            }
//            QImage img;
//            if(img.loadFromData((unsigned char*)pCapBuf, picSize)){
//                img.save(saveFilePath);
//                return saveFilePath;
//            }
//            delete[] pCapBuf;
//            picSize = 0;
        if(!NET_DVR_CapturePicture((LONG)nodeData->hOpen, saveFilePath)){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("截图提醒"), QString::fromLocal8Bit("截图失败，请重试！"), 0);
            return QString();
        }
        int timer = 20;
        QImage img;
        while(0 < timer && !img.load(strSaveFilePath)){
            Sleep(1000);
            timer--;
            qWarning()<<"capture laoding timer"<<timer;
        }
        return strSaveFilePath;
    }
    return QString();
}

bool PageMain::isRecordCamera(const ComTool::NODE_DATA* nodeData){
    if(0 == nodeData){
        return 0 != gRecordNodeData;
    }
    return nodeData == gRecordNodeData;
}
bool PageMain::turnRecordCamera(QYVideoWidget* wd, bool on)
{
    if(!on){
        if(0 != gRecordNodeData && -1 != (LONG)gRecordNodeData->hOpen){
            NET_DVR_StopSaveRealData((LONG)(gRecordNodeData->hOpen));
            gRecordNodeData = 0;
            return true;
        }
        return false;
    }

    if(0 == wd){
        return false;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hOpen){
        return false;
    }
    if(0 != gRecordNodeData && -1 != (LONG)gRecordNodeData->hOpen){
        NET_DVR_StopVoiceCom((LONG)(gRecordNodeData->hOpen));
        gRecordNodeData = 0;
    }

    char saveFilePath[MAX_SIZE];
    {
        QString strSaveFilePath = AppZZB::getInstance()->GetSavePath(1);
        ComTool::Tool::isExistDir(strSaveFilePath, true);
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        QString fileName = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
        strSaveFilePath += "/[" + fileName + "]";
        strSaveFilePath += nodeData->name;
        strSaveFilePath += AppZZB::getInstance()->GetSavePath(3);

        memset(saveFilePath, 0, MAX_SIZE);
        ::sprintf_s(saveFilePath, "%s",strSaveFilePath.toStdString().c_str());
    }

    if(!NET_DVR_SaveRealData((LONG)nodeData->hOpen, saveFilePath)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("录制提示"), QString::fromLocal8Bit("设备录制视频失败！"), 0);
        return false;
    }
    gRecordNodeData = nodeData;
    return true;
}
bool PageMain::isSoundCamera(const ComTool::NODE_DATA* nodeData){
    if(0 == nodeData){
        return 0 != gSoundNodeData;
    }
    return nodeData == gSoundNodeData;
}
bool PageMain::turnSoundCamera(QYVideoWidget* wd, bool on)
{
    if(!on){
        if(0 != gSoundNodeData && -1 != (LONG)gSoundNodeData->hOpen){
            NET_DVR_CloseSound();
            gRecordNodeData = 0;
            return true;
        }
        return false;
    }

    if(0 == wd){
        return false;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hOpen){
        return false;
    }
    if(0 != gRecordNodeData && -1 != (LONG)gRecordNodeData->hOpen){
        NET_DVR_CloseSound();
        gRecordNodeData = 0;
    }

    if(!NET_DVR_OpenSound((LONG)nodeData->hOpen)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("播音提示"), QString::fromLocal8Bit("设备播音失败！"), 0);
        return false;
    }
    gRecordNodeData = nodeData;
    return true;
}
bool PageMain::turnStreamCamera(QYVideoWidget* wd, bool on)
{
    if(0 == wd){
        return false;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hLogon){
        return false;
    }
    int nStream = on ? 1 : 0;
    if(nodeData->nStream == nStream){
        return false;
    }

    //if(0 != gStreamPort && wd == gStreamPort->wd){
    if(hasStreamPort(wd)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("切换码流"), QString::fromLocal8Bit("请先关闭分屏"), 0);
        return false;
    }

    nodeData->nStream = nStream;
    if(1 == nodeData->qytype){
        CloseHCCamera(nodeData);
        AppZZB::getInstance()->updateUIDlgHotBar();

        QWidget* wdShow = wd->showWidget();
        if(0 == OpenHCCamera(nodeData, (HWND)(wdShow->winId()))){
            return true;
        }
    }else if(0 == nodeData->qytype){
        CloseHHCamera(nodeData);
        AppZZB::getInstance()->updateUIDlgHotBar();

        QVariant qv = wd->property(ComTool::Def::PLAYERNO);
        if(qv.isNull()){
            return false;
        }
        int playerNo = qv.value<int>();
        if(0 == OpenHHCamera(nodeData, playerNo)){ //curSel 播放器编号
            return true;
        }
    }
    return false;
}
bool PageMain::turnAspectCamera(QYVideoWidget* wd, int nAspect)
{
    if(0 == wd){
        return false;
    }
    QVariant qv = wd->property(ComTool::Def::NODEDATANO);
    if(qv.isNull()){
        return false;
    }
    ComTool::NODE_DATA* nodeData = qv.value<ComTool::NODE_DATA*>();
    if(-1 == (LONG)nodeData->hOpen){
        return false;
    }
    nodeData->nAspect = nAspect;

    bool isVisible = wd->showWidget()->isVisible();
    wd->showWidget()->setVisible(false);
    wd->onShowVideo(nodeData->vWidth, nodeData->vHeight, nAspect);
    wd->showWidget()->setVisible(isVisible);

    QWidget* wdRoot = wd->rootWidget();
    QWidget* pano   = wd->rootWidget()->findChild<QWidget*>("pano");
    if(0 != pano){
        bool visible = pano->isVisible();
        pano->setGeometry(QRect(0, 0, wdRoot->width(), wdRoot->height()));
        pano->setVisible(visible);
    }

    return true;
}
bool PageMain::isFullScreenCamera(const QYVideoWidget* wd)
{
    if(0 == wd){
        return 0 != gFullScreenWd;
    }
    return wd == gFullScreenWd;
}
bool PageMain::turnFullScreenCamera(QYVideoWidget* wd, bool on, bool refreshUI)
{
    QYVideoWidget* wdRes = 0;
    bool bRes = false;
    if(!on && 0 != gFullScreenWd){

        //切换回原值
        QVariant qvData = wd->property(ComTool::Def::NODEDATANO);
        if(!qvData.isNull()){
            ComTool::NODE_DATA* nodeData = qvData.value<ComTool::NODE_DATA*>();
            nodeData->nAspect = nodeData->nAspectFull;
            nodeData->nAspectFull = 2;
            wd->onShowVideo(nodeData->vWidth, nodeData->vHeight, nodeData->nAspect);
        }

        gFullScreenWd->setWindowFlags(Qt::Widget);
        QRect rt = gFullScreenWd->property(ComTool::Def::SAVERECT).value<QRect>();
        gFullScreenWd->setGeometry(rt);
        gFullScreenWd->showNormal();

        gFullScreenWd = 0;
        bRes = true;
    }else if(on && 0 != wd){
        QRect rt = wd->geometry();
        wd->setProperty(ComTool::Def::SAVERECT, rt);
        wd->setWindowFlags(Qt::Window);
        wd->showFullScreen();

        //切换到全屏
        QVariant qvData = wd->property(ComTool::Def::NODEDATANO);
        if(!qvData.isNull()){
            ComTool::NODE_DATA* nodeData = qvData.value<ComTool::NODE_DATA*>();
            nodeData->nAspectFull = nodeData->nAspect;
            nodeData->nAspect = 2;
            wd->onShowVideo(nodeData->vWidth, nodeData->vHeight, nodeData->nAspect);
        }

        QRect rtFull = AppZZB::getInstance()->GetDesktopRt();
        wd->setGeometry(rtFull);



        gFullScreenWd = wd;
        bRes = true;
    }

    if(bRes && refreshUI){
        _VisibleVideo(wd, false);

        QTimer* timer = new QTimer(this);
        timer->setProperty(ComTool::Def::REFRESHVIDEO, QVariant::fromValue(wd));
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(refresh_PanelVideos()));
        timer->start(1000);
    }

    return bRes;
}

QVariant PageMain::LoginCamera(const QString& szName,
                           const QString& szRegisterIP, unsigned short registerDataPort,
                           const QString& szUserName,const QString& szUserPsw)
{

    //pano Top 114.242.18.230 32073 admin admin
    //pano Top 114.242.18.230 30641 admin a1111111

    //pano Left 114.242.18.230 61621 admin admin
    //pano Left 114.242.18.230 61627 admin a1111111

    //pano Left 114.242.18.230 61625 admin admin
    //pano Left 114.242.18.230 61627 admin a1111111

    //Hard 114.242.18.230 31451 admin a1111111

    //pano 222.222.0.156 8248 admin lAaQ2h7000

//    static int si = 0;

//    if(0 == si){
//        szName           = "Hard Drive";
//        szRegisterIP     = "114.242.18.230";
//        registerDataPort =  31411;
//        szUserName       = "admin";
//        szUserPsw        = "a1111111";
//    }
//    si++;

//    if(0 == si){
//        szName = "Pano Camera";
//        szRegisterIP = "114.242.18.230";
//        registerDataPort =  61625;
//        szUserName = "admin";
//        szUserPsw = "admin";
//    }

//    if(1 == si){
//        szName = "Sphere Camera";
//        szRegisterIP = "114.242.18.230";
//        registerDataPort =  30641;//30641;//61627;
//        szUserName = "admin";
//        szUserPsw = "a1111111";
//    }
//    si++;


    {
        ComTool::NODE_DATA* data = 0;
        data = ComTool::NodeTreeHelper::FindNode(szRegisterIP, registerDataPort, AppZZB::getInstance()->rootTree);
        if(0 != data && (void*)-1 != data->hLogon){
            return QVariant();
        }
    }

    //HCSDK Login
    while(1){
        NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;
        memset(&DeviceInfoTmp,0,sizeof(NET_DVR_DEVICEINFO_V30));
        LONG lLoginID = NET_DVR_Login_V30(const_cast<char*>(szRegisterIP.toStdString().c_str()),
                          registerDataPort,
                          const_cast<char*>(szUserName.toStdString().c_str()),
                          const_cast<char*>(szUserPsw.toStdString().c_str()),
                                          &DeviceInfoTmp);
        if(lLoginID == -1){
            break;
        }

        int nChan = DeviceInfoTmp.byChanNum + DeviceInfoTmp.byIPChanNum;
        if(nChan == 1){
            ComTool::NODE_DATA* data = 0;
            ComTool::CCommon<ComTool::NODE_DATA>::NewA(&data);
            data->qytype        = 1;
            data->hLogon        = (void*)lLoginID;
            data->szDeviceName  = reinterpret_cast<char*>(DeviceInfoTmp.sSerialNumber);
            data->szIp          = szRegisterIP;
            data->port          = registerDataPort;
            data->dwChannelNum  = 1;
            data->szUserName    = szUserName;
            data->szUserPsw     = szUserPsw;
            data->dwChannelNo   = ( 1 == DeviceInfoTmp.byChanNum) ? DeviceInfoTmp.byStartChan : DeviceInfoTmp.byStartDChan;
            data->name          = szName;

            return QVariant::fromValue(data);
        }else if(nChan > 1){// for hard device more channels
            ComTool::NODE_TREE* nodeTree = 0;

            NET_DVR_IPPARACFG_V40 IpAccessCfg;
            memset(&IpAccessCfg,0,sizeof(IpAccessCfg));
            DWORD  dwReturned;
            BOOL bIPRet = NET_DVR_GetDVRConfig(lLoginID,NET_DVR_GET_IPPARACFG_V40,0,&IpAccessCfg,sizeof(NET_DVR_IPPARACFG_V40),&dwReturned);
            if(!bIPRet){
                int  l = DeviceInfoTmp.byChanNum;
                if(0 < l && 0 == nodeTree){
                    ComTool::CCommon<ComTool::NODE_TREE>::NewA(&nodeTree);
                    nodeTree->name    = szName;
                    nodeTree->ChanNum = l;
                    nodeTree->StartChan = DeviceInfoTmp.byStartChan;
                }
                for(int i=0; i<l; ++i){
                    ComTool::NODE_DATA* data = 0;
                    ComTool::CCommon<ComTool::NODE_DATA>::NewA(&data);
                    data->qytype        = 1;
                    data->hLogon        = (void*)lLoginID;
                    data->szDeviceName  = reinterpret_cast<char*>(DeviceInfoTmp.sSerialNumber);
                    data->szIp          = szRegisterIP;
                    data->port          = registerDataPort;
                    data->dwChannelNum  = l;
                    data->szUserName    = szUserName;
                    data->szUserPsw     = szUserPsw;
                    data->dwChannelNo   = i + DeviceInfoTmp.byStartChan;
                    data->name          = QString().sprintf("camera_%d", data->dwChannelNo);
                    nodeTree->children.append(data);
                    data->parent        = nodeTree;
                }
            }else{
                //camera
                for(int i=0, l=DeviceInfoTmp.byChanNum; i<l; ++i){
                    if(!IpAccessCfg.byAnalogChanEnable[i]){
                        continue;
                    }
                    if(0 == nodeTree){
                        ComTool::CCommon<ComTool::NODE_TREE>::NewA(&nodeTree);
                        nodeTree->name      = szName;
                        nodeTree->ChanNum   = l;
                        nodeTree->StartChan = DeviceInfoTmp.byStartChan;
                    }
                    ComTool::NODE_DATA* data = 0;
                    ComTool::CCommon<ComTool::NODE_DATA>::NewA(&data);
                    data->qytype        = 1;
                    data->hLogon        = (void*)lLoginID;
                    data->szDeviceName  = reinterpret_cast<char*>(DeviceInfoTmp.sSerialNumber);
                    data->szIp          = szRegisterIP;
                    data->port          = registerDataPort;
                    data->dwChannelNum  = l;
                    data->szUserName    = szUserName;
                    data->szUserPsw     = szUserPsw;
                    data->dwChannelNo   = i + DeviceInfoTmp.byStartChan;
                    data->name          = QString().sprintf("camera_%d", data->dwChannelNo);
                    nodeTree->children.append(data);
                    data->parent        = nodeTree;
                }
                //ip camera
                for(int i=0, l=DeviceInfoTmp.byIPChanNum; i<l; ++i){
                    if(!IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable){
                        continue;
                    }
                    if(0 == nodeTree){
                        ComTool::CCommon<ComTool::NODE_TREE>::NewA(&nodeTree);
                    }
                    nodeTree->name           = szName;
                    nodeTree->IPChanNum      = l;
                    nodeTree->IPStartChan    = IpAccessCfg.dwStartDChan;
                    ComTool::NODE_DATA* data = 0;
                    ComTool::CCommon<ComTool::NODE_DATA>::NewA(&data);
                    data->qytype        = 1;
                    data->hLogon        = (void*)lLoginID;
                    data->szDeviceName  = reinterpret_cast<char*>(DeviceInfoTmp.sSerialNumber);
                    data->szIp          = szRegisterIP;
                    data->port          = registerDataPort;
                    data->dwChannelNum  = l;
                    data->szUserName    = szUserName;
                    data->szUserPsw     = szUserPsw;
                    data->dwChannelNo   = i + IpAccessCfg.dwStartDChan;
                    data->name          = QString().sprintf("ip_camera_%d", data->dwChannelNo);
                    nodeTree->children.append(data);
                    data->parent        = nodeTree;
                }
            }

            if(0 != nodeTree){
               return QVariant::fromValue(nodeTree);
            }
        }//End IF
        //return QVariant();
        break;
    }//End HCSDK Login

    //HHSDK Login
    HHERR_CODE errCode = HHERR_FAILURE;
    HANDLE     hLogon  = (HANDLE)-1;
    QString szDeviceName("NVS");
    errCode = HHNET_LogonServer(const_cast<char*>(szRegisterIP.toStdString().c_str()),
                        registerDataPort,
                        const_cast<char*>(szDeviceName.toStdString().c_str()),
                        const_cast<char*>(szUserName.toStdString().c_str()),
                        const_cast<char*>(szUserPsw.toStdString().c_str()),
                        0,
                        hLogon);

    qDebug()<<QString().sprintf("HHLogin:%d,handle:%x\n", errCode, hLogon);

    HH_SERVER_INFO	info;
    ZeroMemory(&info, sizeof(info));
    errCode = HHNET_ReadServerInfo(hLogon, info);
    if(HHERR_SUCCESS != errCode){
        return QVariant();
    }

    ComTool::NODE_DATA* data = 0;
    ComTool::CCommon<ComTool::NODE_DATA>::NewA(&data);

    data->qytype = 0;
    data->hLogon = hLogon;
    DVS_MACHINE_TYPE  nDeviceType = info.nMachineType;
    if(nDeviceType == HH5201 ||
       nDeviceType == HH5001C ||
       nDeviceType == HH5002H ||
       nDeviceType==HH5001D || nDeviceType==HH5004C ||
       (nDeviceType > HH5200 && nDeviceType < HH5301) ||
       nDeviceType  > HH5700)
    {   // 编码器
        //encoder  according to the devicetype
        data->bDecodeDevice = false;     //not a decoder

    }else if(nDeviceType == HH5104 ||
             nDeviceType == HH5108 ||
             nDeviceType == HH6104 ||
             nDeviceType == HH5301 ||
             nDeviceType == HH5700)
    {	//解码器
        data->bDecodeDevice = true;      //is a decoder
    }
    data->szDeviceName  = info.szDeviceName;
    data->szIp          = info.szServerIP;
    data->port          = info.nServerPort;
    data->dwChannelNum  = info.nServerChannelNum;
    data->szUserName    = szUserName;
    data->szUserPsw     = szUserPsw;
    data->dwChannelNo   = 0;

    //data->name = data->szIp+QString().sprintf("_%d_",data->port)+data->szDeviceName;
    data->name = szName;//data->szDeviceName;

    return QVariant::fromValue(data);
}

void PageMain::LogoutCamera(ComTool::NODE_DATA* nodeData)
{
    if(0 == nodeData){return;}

    if(1 == nodeData->qytype){
        if(-1 != (LONG)nodeData->hLogon){
            NET_DVR_Logout_V30((LONG)nodeData->hLogon);
            nodeData->hLogon = (void*)-1;
        }
    }else{
        if(-1 != (LONG)nodeData->hLogon){
            HHNET_LogoffServer(nodeData->hLogon);
            nodeData->hLogon = (void*)-1;
        }
    }
}
void PageMain::DelNodeData(ComTool::NODE_DATA* nodeData, ComTool::NODE_TREE* nodeTree)
{
    if(0 == nodeData){
        return;
    }
    if(0 != ComTool::LinkGroupHelper::FindLinkIn(nodeData, AppZZB::getInstance()->rootLinks)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("删除提醒"), QString::fromLocal8Bit("有关联机组，无法删除 ")+nodeData->name, 0);
        return;
    }
    if(-1 != (LONG)nodeData->hOpen && !(nodeData->otheA.isNull())){//close
        QYVideoWidget* wd = nodeData->otheA.value<QYVideoWidget*>();
        CloseCameraPanel(nodeData, wd, true);
    }
    LogoutCamera(nodeData);

    if(0 == nodeTree){
        nodeTree = ComTool::NodeTreeHelper::FindTree(nodeData, AppZZB::getInstance()->rootTree);
    }
    if(0 == nodeTree){
        return;
    }
    QTreeWidgetItem* itemParent = nodeTree->other.value<QTreeWidgetItem*>();
    QTreeWidgetItem* item = nodeData->other.value<QTreeWidgetItem*>();
    itemParent->removeChild(item);

    nodeTree->children.removeOne(nodeData);
    ComTool::CCommon<ComTool::NODE_DATA>::DeleteA(&nodeData);
}
void PageMain::DelNodeTree(ComTool::NODE_TREE* nodeTree)
{
    if(0 == nodeTree){
        return;
    }
    int nChan = nodeTree->ChanNum + nodeTree->IPChanNum;
    if(0<nChan){//for hard
        bool hasLink = false;
        for(int i=0, l=nodeTree->children.length(); i<l; ++i){
            ComTool::NODE_DATA* nodeData = nodeTree->children.at(i);
            if(0 != ComTool::LinkGroupHelper::FindLinkIn(nodeData, AppZZB::getInstance()->rootLinks)){
                hasLink = true;
                break;
            }
        }
        if(!hasLink){
            CloseTreeNode(nodeTree);
            LogoutCamera(nodeTree->children.at(0));

            ComTool::NodeTreeHelper::ReleaseNode(nodeTree, false);
        }
    }else{
        for(int i=0, l=nodeTree->children.length(); i<l; ){
            ComTool::NODE_DATA* nodeData = nodeTree->children.at(i);
            if(0 != ComTool::LinkGroupHelper::FindLinkIn(nodeData, AppZZB::getInstance()->rootLinks)){
                ++i;
                continue;
            }
            if(-1 != (LONG)nodeData->hOpen && !(nodeData->otheA.isNull())){//close
                QYVideoWidget* wd = nodeData->otheA.value<QYVideoWidget*>();
                CloseCameraPanel(nodeData, wd, true);
            }
            LogoutCamera(nodeData);

            QTreeWidgetItem* itemParent = nodeTree->other.value<QTreeWidgetItem*>();
            QTreeWidgetItem* item = nodeData->other.value<QTreeWidgetItem*>();
            itemParent->removeChild(item);

            nodeTree->children.removeAt(i);
            ComTool::CCommon<ComTool::NODE_DATA>::DeleteA(&nodeData);
            i = 0;
            l = nodeTree->children.length();
        }

        for(int i=0, l =nodeTree->nodes.length(); i<l; ++i){
            ComTool::NODE_TREE* tree = nodeTree->nodes.at(i);
            DelNodeTree(tree);
        }
    }

    bool allRemove = 0 == nodeTree->children.length() && 0 == nodeTree->nodes.length();

    ComTool::NODE_TREE* treeParent = nodeTree->parent;
    if(allRemove && 0 != treeParent){
        treeParent->nodes.removeOne(nodeTree);
        QTreeWidgetItem* itemParent = treeParent->other.value<QTreeWidgetItem*>();
        QTreeWidgetItem* item = nodeTree->other.value<QTreeWidgetItem*>();
        itemParent->removeChild(item);
        ComTool::CCommon<ComTool::NODE_TREE>::DeleteA(&nodeTree);
    }else if(!allRemove){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("删除提醒"), QString::fromLocal8Bit("有关联机组，无法删除 ")+nodeTree->name, 0);
    }
}
void PageMain::DelLinkData(ComTool::LINK_DATA* link)
{
    if(0 == link){
        return;
    }

    //Close
    //int nRes = CloseCameraLink(link);

    QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(link);
    int nRes = CloseCameraLink(link);
    if(2 == nRes){
        if(link->isLinked && 0 != wdPano){
            ui->cb_Linked->setChecked(false);
            wdPano->enableTrack(false);
            wdPano->enableClick(false);
            disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
        }
    }

    //UI
    QTableWidgetItem* item = link->other.value<QTableWidgetItem*>();
    if(0 != item){
        int row = ui->tableWidget_qq->row(item);
        if(-1 != row){
            ui->tableWidget_qq->removeRow(row);
        }
    }

    //Remove
    ComTool::LinkGroupHelper::ReleaseLink(link, AppZZB::getInstance()->rootLinks);
}

QList<ComTool::LINK_DATA*> PageMain::_GotAllLink_Panel()
{
    QList<ComTool::LINK_DATA*> listLink;
    {
        QYVideoWidget* curSelA = ui->wdRPageA_Top->at(0);
        QVariant qv = curSelA->property(ComTool::Def::NODELINKNO);
        if(!qv.isNull()){
            ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();
            listLink.push_back(link);
        }
    }
    {
        for(int i=0, l = ui->wdRPageA_Bot->row()*ui->wdRPageA_Bot->col(); i<l; ++i){
            QYVideoWidget* cur = ui->wdRPageA_Bot->at(i);
            QVariant qv = cur->property(ComTool::Def::NODELINKNO);
            if(!qv.isNull()){
                ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();
                listLink.push_back(link);
            }
        }//end for
    }
    return listLink;
}

bool PageMain::_HasLinkOpened_Panel(){
    QList<ComTool::LINK_DATA*> listLink = _GotAllLink_Panel();
    int nRes = 0;
    for(int i=0, l=listLink.size(); i<l; ++i){
        ComTool::LINK_DATA* link = listLink.at(i);
        if(0 == link){continue;}
        nRes++;
    }
    return nRes > 0;
}

bool PageMain::_HasLinkOpenedSame_Panel(){
    QList<ComTool::LINK_DATA*> listLink = _GotAllLink_Panel();
    int nRes = 0;
    for(int i=0, l=listLink.size(); i<l; ++i){
        ComTool::LINK_DATA* link = listLink.at(i);
        if(0 == link){continue;}
        nRes++;
    }
    int l = ui->tableWidget_qq->rowCount();
    int n = l > 5 ? 5 : l;
    //qWarning()<<"nRess: "<<nRes<<" == "<<n;
    if(nRes != n){return false;}

    int sum = 0;
    for(int i=0; i<n; ++i){
        QTableWidgetItem* item0 = ui->tableWidget_qq->item(i, 0);
        QVariant qv = item0->data(Qt::UserRole);
        if(qv.isNull()){continue;}
        ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();
        if(0 == link || link->otherA.isNull()){//no not opend
            continue;
        }
        if(link == listLink.at(i)){
            sum++;
        }
    }
    //qWarning()<<"nRess: "<<nRes<<" == "<<n <<" sum "<<sum;
    return sum == nRes;
}

int PageMain::TurnCloseLinkAll_Panel()
{
    QList<ComTool::LINK_DATA*> listLink = _GotAllLink_Panel();

    int nRes = 0;
    for(int i=0, l=listLink.size(); i<l; ++i){
        ComTool::LINK_DATA* link = listLink.at(i);
        if(0 == link){continue;}
        nRes++;
        //close
        QYVideoWidget* wdPano = _isCurSelQQ_TopLinkEx(link);
        int nRes = CloseCameraLink(link);
        if(2 == nRes){
            if(!link->other.isNull()){
                QTableWidgetItem* item = link->other.value<QTableWidgetItem*>();
                if(0 != item){
                    item->setIcon(*iconClosed);
                }
            }
            if(link->isLinked && 0 != wdPano){
                ui->cb_Linked->setChecked(false);
                wdPano->enableTrack(false);
                wdPano->enableClick(false);
                disconnect(wdPano, SIGNAL(sigTrackClicked(QWidget*, QVector2D)), this, SLOT(oSigTrackClicked(QWidget*, QVector2D)));
            }
        }//end if
    }//end for
    return nRes;
}
//一鍵开启Link
typedef struct _LinkVieoPanel{
    QYVideoWidget* wdPano;
    QYVideoWidget* wdSphere;
    _LinkVieoPanel(){wdPano = 0; wdSphere = 0;}
    _LinkVieoPanel(QYVideoWidget* wdP, QYVideoWidget* wdS){wdPano = wdP; wdSphere = wdS;}
    _LinkVieoPanel(const _LinkVieoPanel& rhs){wdPano = rhs.wdPano; wdSphere = rhs.wdSphere;}
    const _LinkVieoPanel& operator=(const _LinkVieoPanel& rhs){wdPano = rhs.wdPano; wdSphere = rhs.wdSphere; return *this;}
}LinkVieoPanel;
void PageMain::on_butAA_B_A_clicked()
{
    if(_HasLinkOpenedSame_Panel()){return;}
    //ui->butAA_B_A->setEnabled(false);

    //close all panel
    AppZZB::getInstance()->TurnShowDlgLoading(true);
    int cg = TurnCloseLinkAll_Panel();

    QList<LinkVieoPanel> listVideos;
    {
        {
            listVideos.push_back(LinkVieoPanel(ui->wdRPageA_Top->at(0), ui->wdRPageA_Top->at(1)));
        }
        {
            for(int i=0, l = ui->wdRPageA_Bot->row()*ui->wdRPageA_Bot->col(); i<l; ++i){
                listVideos.push_back(LinkVieoPanel(ui->wdRPageA_Bot->at(i), 0));
            }//end for
        }
    }
    sumOpenLink = 0;

    int l = ui->tableWidget_qq->rowCount();
    int n = l > 5 ? 5 : l;
    for(int i=0; i<n; ++i){
        QTableWidgetItem* item0 = ui->tableWidget_qq->item(i, 0);
        QVariant qv = item0->data(Qt::UserRole);
        if(qv.isNull()){continue;}
        ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();
        if(0 == link || !link->otherA.isNull()){//opend
            continue;
        }
        sumOpenLink++;
    }
    for(int i=0; i<n; ++i){
        QTableWidgetItem* item0 = ui->tableWidget_qq->item(i, 0);
        QVariant qv = item0->data(Qt::UserRole);
        if(qv.isNull()){continue;}
        ComTool::LINK_DATA* link = qv.value<ComTool::LINK_DATA*>();
        if(0 == link || !link->otherA.isNull()){//opend
            continue;
        }
        LinkVieoPanel linkVidePanel = listVideos.at(i);
        link->pano->nStream = (0 == i) ? 0 : 1;
        link->sphere->nStream = (0 == i) ? 0 : 1;
        OpenLinkDataTimer* timer = new OpenLinkDataTimer(this);
        timer->setProperty(ComTool::Def::LINK_OPEN_LINK, QVariant::fromValue(link));
        timer->setProperty(ComTool::Def::LINK_OPEN_SELA, QVariant::fromValue(linkVidePanel.wdPano));
        timer->setProperty(ComTool::Def::LINK_OPEN_SELB, QVariant::fromValue(linkVidePanel.wdSphere));
        timer->setProperty(ComTool::Def::LINK_OPEN_LINK_NO, QVariant(i));

        connect(timer, SIGNAL(timeout()), this, SLOT(timerOpenLink()));
        connect(timer, SIGNAL(sigFinish(int)), this, SLOT(timerOpenLinksFinished(int)));
        timer->setSingleShot(true);

        int t = (int)((cg>0 ? 1500.0 : 1000.0) + ComTool::Tool::generateRandom()*1000.0);
        timer->start(t);
    }
}
//一键关闭Link
void PageMain::on_butAA_B_B_clicked()
{
    if(!_HasLinkOpened_Panel()){return;}
    //ui->butAA_B_B->setEnabled(false);

    AppZZB::getInstance()->TurnShowDlgLoading(true);
    TurnCloseLinkAll_Panel();
    QTimer::singleShot(2000,this,SLOT(timerFinishedLoading()));
}
