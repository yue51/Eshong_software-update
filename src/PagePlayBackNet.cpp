#include "PagePlayBackNet.h"
#include "ui_PagePlayBackNet.h"
#include <QtGui/QPainter.h>
#include <QDebug>
#include <QTimer>
#include <QScrollBar>

#include "ComHeader.h"
#include "ComTool.h"
#include "AppZZB.h"
#include "PageMain.h"

PagePlayBackNet::PagePlayBackNet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagePlayBackNet)
{
    ui->setupUi(this);
    ui->wd_timeline2->setVisible(false);
    //ui->wdB_video->setProperty(ComTool::Def::PRO_HOTBARVISIBLE, QVariant(false));
    ui->wdB_video->setProperty(ComTool::Def::PRO_HOTBARVISIBLE, QVariant(1));

    m_RecType       = 0xff;
    m_FileProperty  = 0xff;
    m_FileFindThread= 0;
    findNodeData  = 0;

    _ResetValPlay();
    m_bResume       = false;

    _ResetValDown();

    mPlayData = new ComTool::NODE_DATA();

    qApp->setStyleSheet("QTableCornerButton::section{background:rgba(76,75,80,255);}");
    typedef QList<QTableWidget*> QYTabPanel;
    QYTabPanel tabPanel;
    tabPanel.push_back(ui->tableWidget);
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
    }

    {
        ui->dateEdit_Start->setDate(QDate::currentDate());
        ui->dateEdit_Stop->setDate(QDate::currentDate());
        ui->timeEdit_Start->setTime(QTime::currentTime());
        ui->timeEdit_Stop->setTime(QTime::currentTime());
    }
}

PagePlayBackNet::~PagePlayBackNet()
{
    _StopTimeDown();
    StopDown();

    _StopTimePlay();
    StopPlayback();

    ComTool::CCommon<ComTool::NODE_DATA>::DeleteA(&mPlayData);

    findNodeData  = 0;
    releaseFindThread();
    releaseFindList();

    delete ui;
}

void PagePlayBackNet::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}



void PagePlayBackNet::releaseFindList()
{
    for(int i=0, l=m_FindDataList.length(); i<l; ++i){
        FIND_DATA* findData = m_FindDataList.at(i);
        ComTool::CCommon<FIND_DATA>::DeleteA(&findData);
    }
    m_FindDataList.clear();
}
void PagePlayBackNet::releaseFindThread()
{
    if(0 == m_FileFindThread){return;}
    if(!m_FileFindThread->isFinished()){
        m_FileFindThread->Stop();
    }
    ComTool::CCommon<FileFindThread>::DeleteA(&m_FileFindThread);
}
PagePlayBackNet::FileFindThread::~FileFindThread(){
    if(0 != mHfindInfo){
        NET_DVR_FILECOND *pFileCond = (NET_DVR_FILECOND*)mHfindInfo;
        delete pFileCond;
        mHfindInfo = 0;
    }
}
int PagePlayBackNet::FileFindThread::_funFind()
{
    LONG lLoginID = (LONG)mHloginID;
    NET_DVR_FILECOND *pFileCond = (NET_DVR_FILECOND*)mHfindInfo;

    LONG hFindHandle = NET_DVR_FindFile_V30(lLoginID, pFileCond);
    if(-1 == hFindHandle){
        return -1;
    }

    NET_DVR_FINDDATA_V30 FindData;  //查找到的文件信息
    int ret = retCode;
    while(!mbStop && 0 < (ret = NET_DVR_FindNextFile_V30(hFindHandle,&FindData))){
        //qDebug()<<"ret: "<<ret;
        if(NET_DVR_ISFINDING == ret){  //正在查找
            msleep(1000);
        }else if(NET_DVR_FILE_SUCCESS == ret){  //获取文件信息成功
            //保存文件信息
            FIND_DATA* findData = 0;
            ComTool::CCommon<FIND_DATA>::NewA(&findData);
            findData->strFileName = QString().sprintf("%s", FindData.sFileName);
            findData->strFileSize = QString().sprintf("%0.2fM",(double)FindData.dwFileSize/1024/1024);
            findData->strStartTime= QString().sprintf("%04d/%02d/%02d %02d:%02d:%02d",FindData.struStartTime.dwYear,FindData.struStartTime.dwMonth,FindData.struStartTime.dwDay,\
                                                      FindData.struStartTime.dwHour,FindData.struStartTime.dwMinute,FindData.struStartTime.dwSecond);
            findData->strStopTime = QString().sprintf("%04d/%02d/%02d %02d:%02d:%02d",FindData.struStopTime.dwYear,FindData.struStopTime.dwMonth,FindData.struStopTime.dwDay,\
                            FindData.struStopTime.dwHour,FindData.struStopTime.dwMinute,FindData.struStopTime.dwSecond);
            findData->byLocked = FindData.byLocked;//FindData.byLocked == 1 ? "文件被锁定" : "正常文件"

            mFindDataList->push_back(findData);
        }else{
            return ret;
        }
    }
    //关闭查找，释放句柄
    NET_DVR_FindClose_V30(hFindHandle);
    ret = 0;
    return ret;
}
void PagePlayBackNet::FileFindThread::run(){
    retCode = _funFind();
    quit();
 }

void PagePlayBackNet::on_butFind_clicked()
{
    if(0 != m_playState){
        on_butBK_Stop_clicked();
    }

    PageMain* pageMain = AppZZB::getInstance()->pageMain;
    ComTool::NODE_DATA* nodeData = pageMain->_GotSelFromTree();
    if(0 == nodeData || -1== (LONG)nodeData->hLogon || 0 == nodeData->qytype){//HHSDK Out
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("远程回放"), QString::fromLocal8Bit("请在左边列表中选择一个硬盘录像机通道"), 0);
        return;
    }

    QDate dataStart  = ui->dateEdit_Start->date();
    QTime timeStart = ui->timeEdit_Start->time();
    QDate dataEnd  = ui->dateEdit_Stop->date();
    QTime timeEnd = ui->timeEdit_Stop->time();

    bool bData = (dataStart < dataEnd) || (dataStart <= dataEnd && timeStart < timeEnd);
    if(!bData){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("远程回放"), QString::fromLocal8Bit("请选择起始结束时间，确保起始时间早于结束时间！"), 0);
        return;
    }

    //获取查找的时间段
    NET_DVR_TIME StartSearchTime, StopSearchTime;

    StartSearchTime.dwYear      = dataStart.year();
    StartSearchTime.dwMonth     = dataStart.month();
    StartSearchTime.dwDay       = dataStart.day();
    StartSearchTime.dwHour      = timeStart.hour();
    StartSearchTime.dwMinute    = timeStart.minute();
    StartSearchTime.dwSecond    = timeStart.second();

    StopSearchTime.dwYear      = dataEnd.year();
    StopSearchTime.dwMonth     = dataEnd.month();
    StopSearchTime.dwDay       = dataEnd.day();
    StopSearchTime.dwHour      = timeEnd.hour();
    StopSearchTime.dwMinute    = timeEnd.minute();
    StopSearchTime.dwSecond    = timeEnd.second();

    NET_DVR_FILECOND *pFileCond = new NET_DVR_FILECOND();
    NET_DVR_FILECOND& FileCond  = *pFileCond;
    FileCond.dwFileType     = m_RecType;
    FileCond.dwIsLocked     = m_FileProperty;
    FileCond.dwUseCardNo    = 0;
    FileCond.lChannel       = nodeData->dwChannelNo;
    memcpy(&FileCond.struStartTime,&StartSearchTime,sizeof(NET_DVR_TIME));
    memcpy(&FileCond.struStopTime,&StopSearchTime,sizeof(NET_DVR_TIME));

    releaseFindList();
    releaseFindThread();
    findNodeData  = nodeData;
    AppZZB::getInstance()->TurnShowDlgLoading(true);
    if(0 == m_FileFindThread){
        m_FileFindThread = new FileFindThread(nodeData->hLogon, (void*)pFileCond, &m_FindDataList);
        connect(m_FileFindThread, SIGNAL(started()), this, SLOT(oFindThreadStarted()));
        connect(m_FileFindThread, SIGNAL(finished()), this, SLOT(oFindThreadFinished()));
    }
    m_FileFindThread->turnRunning(true);
    m_FileFindThread->start();
}

bool PagePlayBackNet::StartDown()
{
    if(-1 == (LONG)m_hDownHandle && 0 == m_downState){
        int cur = ui->tableWidget->currentRow();
        if(0>cur ||
                0 == findNodeData ||
                -1 == (LONG)findNodeData->hLogon){
            return false;
        }

        QTableWidgetItem *item = ui->tableWidget->item(cur, 0);
        QString strFileName = item->text();

        char fileName[MAX_SIZE];
        memset(fileName, 0, MAX_SIZE);
        ::sprintf_s(fileName, "%s", strFileName.toStdString().c_str());

        QString strSaveFilePath = AppZZB::getInstance()->GetSavePath(1);
        ComTool::Tool::isExistDir(strSaveFilePath, true);
        strSaveFilePath += "/";
        strSaveFilePath += strFileName;
        strSaveFilePath += AppZZB::getInstance()->GetSavePath(3);

        char saveFilePath[MAX_SIZE];
        memset(saveFilePath, 0, MAX_SIZE);
        ::sprintf_s(saveFilePath, "%s",strSaveFilePath.toStdString().c_str());
        //qWarning(fileName);
        //qWarning(saveFilePath);
        m_hDownHandle = (void*)NET_DVR_GetFileByName((LONG)findNodeData->hLogon, fileName, saveFilePath);

        if(-1 == (LONG)m_hDownHandle){
            int err = NET_DVR_GetLastError();
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("下载错误 ") + QString().sprintf(" %d", err), 0);
            return false;
        }
        NET_DVR_PlayBackControl((LONG)m_hDownHandle, NET_DVR_PLAYSTART, 0, NULL);
        m_downNodeData = findNodeData;
        m_downState = 1;
        if(0 == m_downTimer){
            m_downTimer = new QTimer(this);
            connect(m_downTimer, SIGNAL(timeout()), this, SLOT(refresh_downloading()));
        }
        m_downTimer->start(800);

    }
    _UpdateDownUI();
    return true;
}
bool PagePlayBackNet::StopDown()
{
    if(1 == m_downState){
        if(!NET_DVR_StopGetFile((LONG)m_hDownHandle)){
            int err = NET_DVR_GetLastError();
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("停止下载错误 ") + QString().sprintf(" %d", err), 0);
            return false;
        }
        _StopTimeDown();
        _ResetValDown();
    }
    _UpdateDownUI();
    return true;
}
void PagePlayBackNet::on_butDownload_clicked()
{
    if(-1 == (LONG)m_hDownHandle && 0 == m_downState){
        StartDown();
    }else if(1 == m_downState){
        StopDown();
    }
}

void PagePlayBackNet::on_comboBox_RecType_currentIndexChanged(int index)
{
    if(index<0 || 2<index){return;}
    //录像类型，0xff－全部；0－定时录像；1－移动侦测；2－报警触发；3-报警|移动侦测；4－报警&移动侦测；5－命令触发；6－手动录像
    static int S_VAL[3] = {0xff, 0, 6};
    m_RecType = S_VAL[index];
}

void PagePlayBackNet::oFindThreadStarted()
{

}
void PagePlayBackNet::oFindThreadFinished()
{
    AppZZB::getInstance()->TurnShowDlgLoading(false);
    if(0 == m_FileFindThread){return;}

    if(NET_DVR_FILE_EXCEPTION == m_FileFindThread->retCode){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("远程回放"), QString::fromLocal8Bit("查找文件时异常"), 0);
        return;
    }else if(NET_DVR_FILE_NOFIND == m_FileFindThread->retCode){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("远程回放"), QString::fromLocal8Bit("没有录像文件"), 0);
        return;
    }
    if(m_FindDataList.length() < 1){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("远程回放"), QString::fromLocal8Bit("没有录像文件"), 0);
        return;
    }

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();
    for(int i=0, l=m_FindDataList.length(); i<l; ++i){
        FIND_DATA* findData = m_FindDataList.at(i);
        int n = ui->tableWidget->rowCount();
        if(i>=n){
           ui->tableWidget->insertRow(n);
        }
        {
            QTableWidgetItem* item = new QTableWidgetItem(findData->strFileName);
            ui->tableWidget->setItem(i, 0, item);
        }
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(findData->strFileSize));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(findData->strStartTime));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(findData->strStopTime));
    }

    releaseFindThread();
}

void PagePlayBackNet::refresh_PanelVideos()
{
    QObject* sd = sender();
    if(!sd->inherits("QTimer")){
        return;
    }
    QTimer* timer = (QTimer*)sd;

    QVariant qv = timer->property(ComTool::Def::REFRESHID);
    if(!qv.isNull()){
        QYVideoWidget* wd = qv.value<QYVideoWidget*>();
        wd->showWidget()->setVisible(false);
        timer->setProperty(ComTool::Def::REFRESHID, QVariant());
    }
    timer->deleteLater();
}
void PagePlayBackNet::refresh_SliderBK()
{
    if(ui->Slider_BK->isSliderDown()){
        return;
    }
    if(-1 == (LONG)m_hPlayHandle || 1 != m_playState){
        return;
    }
    DWORD PlayPos;
    NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYGETPOS,0,&PlayPos);
    if(PlayPos>=0 && PlayPos<100){
        ui->Slider_BK->setValue(PlayPos);
    }else if(PlayPos == 100){   //播放完毕
       on_butBK_Stop_clicked();
    }
}

void PagePlayBackNet::_ResetValPlay()
{
    m_hPlayHandle   = (void*)-1;
    m_playState     = 0;
    m_curPlayIndex  = -1;
    m_bPlaySound    = false;
    m_bChangeSpeed  = false;
    m_bPlayStep     = false;
    m_playTimer     = 0;
}
void PagePlayBackNet::_StopTimePlay()
{
    if(0 == m_playTimer){
        return;
    }
    m_playTimer->stop();
    disconnect(m_playTimer, SIGNAL(timeout()), this, SLOT(refresh_SliderBK()));
    delete m_playTimer;
    m_playTimer = 0;
}
void PagePlayBackNet::_ResetValDown()
{
    m_downNodeData    = 0;
    m_hDownHandle = (void*)-1;
    m_downState       = 0;
    m_downTimer       = 0;
}
void PagePlayBackNet::_StopTimeDown()
{
    if(0 == m_downTimer){
        return;
    }
    m_downTimer->stop();
    disconnect(m_downTimer, SIGNAL(timeout()), this, SLOT(refresh_downloading()));
    delete m_downTimer;
    m_downTimer = 0;
}
void PagePlayBackNet::refresh_downloading()
{
    if(-1 == (LONG)m_hDownHandle || 1 != m_downState){
        return;
    }
    int DownloadPos = NET_DVR_GetDownloadPos((LONG)m_hDownHandle);
            if(DownloadPos>=0 && DownloadPos <100){
                ui->progressBar_Download->setTextVisible(true);
                ui->progressBar_Download->setValue(DownloadPos);
            }else if (DownloadPos == 100){
                ui->progressBar_Download->setTextVisible(false);
                ui->progressBar_Download->setValue(0);
                _StopTimeDown();
                _ResetValDown();
                _UpdateDownUI();

                AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("下载完毕"), 0);
            }
}

//开始回放
bool PagePlayBackNet::StartPlayback()
{
    int cur = ui->tableWidget->currentRow();
    if(0>cur ||
       0 == findNodeData ||
       -1 == (LONG)findNodeData->hLogon){
        return false;
    }
    m_curPlayIndex = cur;
    QTableWidgetItem *item = ui->tableWidget->item(cur, 0);
    QString strFileName = item->text();

    if(!StopPlayback())
        return false;

    QWidget* wdShow = ui->wdB_video->showWidget();
    HWND hPlayWnd = (HWND)wdShow->winId();


    char fileName[MAX_SIZE];
    memset(fileName, 0, MAX_SIZE);
    ::sprintf_s(fileName, "%s", strFileName.toStdString().c_str());

    //char fileName = const_cast<char*>(strFileName.toStdString().c_str());
    m_hPlayHandle = (void*)NET_DVR_PlayBackByName((LONG)(findNodeData->hLogon),fileName,hPlayWnd);
    if(-1 == (LONG)m_hPlayHandle){
        int err = NET_DVR_GetLastError();
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("播放错误") + QString().sprintf(" %d, %s", err, fileName), 0);
        return false;
    }
    //qDebug()<<"sfdsf: "<<m_hPlayHandle;

    //更新当前播放文件
    //m_csCurFile.Format("%s",pFileName);
    //获取总帧数和总时间
    //NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_GETTOTALFRAMES,0,&m_TotalFrames);
    //NET_DVR_PlayBackControl(m_hPlayHandle,NET_DVR_GETTOTALTIME,0,&m_TotalTime);
    //调用播放函数后需要调用这个函数启动播放
    NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSTART,0,NULL);

    mPlayData->hLogon = (void*)1000;
    mPlayData->hOpen  = m_hPlayHandle;
    ui->wdB_video->setProperty(ComTool::Def::NODEDATANO, QVariant::fromValue(mPlayData));
    ui->wdB_video->onShowVideo(mPlayData->vWidth,mPlayData->vHeight,mPlayData->nAspect);

    wdShow->setVisible(true);

    m_playState = 1;
    if(0 == m_playTimer){
        m_playTimer = new QTimer(this);
        connect(m_playTimer, SIGNAL(timeout()), this, SLOT(refresh_SliderBK()));
    }
    m_playTimer->start(800);

    //打开声音
    if(NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSTARTAUDIO,0,NULL)){
        m_bPlaySound = true;
    }

    _UpdatePlayUI();
    return true;
}

bool PagePlayBackNet::PausePlayBack(bool bPlayOrPause)
{
    if(-1 == (LONG)m_hPlayHandle){
        return true;
    }

    if(bPlayOrPause && 1 == m_playState){  //暂停
            NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYPAUSE,0,NULL);
            m_playState = 2;
    }else if(1 != m_playState){    //播放
        NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYRESTART,0,NULL);
        m_playState = 1;
    }

    _UpdatePlayUI();
    return true;
}

bool PagePlayBackNet::StopPlayback()
{
    if(-1 == (LONG)m_hPlayHandle){
        return true;
    }

    if(!NET_DVR_StopPlayBack((LONG)m_hPlayHandle)){
        int err = NET_DVR_GetLastError();
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("关闭错误") + QString().sprintf(" %d", err), 0);
        return false;
    }

    //关闭声音
    if(NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSTOPAUDIO,0,NULL)){
        m_bPlaySound = false;
   }

    _StopTimePlay();
    _ResetValPlay();

    mPlayData->hLogon = (void*)-1;
    mPlayData->hOpen  = m_hPlayHandle;
    ui->wdB_video->setProperty(ComTool::Def::NODEDATANO, QVariant());

    _UpdatePlayUI();

    return true;
}
void PagePlayBackNet::_UpdatePlayUI()
{
    {
        std::string ssCur = AppZZB::getInstance()->StyleCur().toStdString();
        QString playSS    = QString().sprintf("url(\":/%s/027_0\")", ssCur.c_str());
        QString pauseSS   = QString().sprintf("url(\":/%s/027_1\")", ssCur.c_str());
        ComTool::Tool::updateSS_brImage(ui->butBK_Play, (1 == m_playState) ? pauseSS : playSS);
    }

    {
        std::string ssCur      = AppZZB::getInstance()->StyleCur().toStdString();
        QString audio_CloseSS  = QString().sprintf("url(\":/%s/035_0\")", ssCur.c_str());
        QString audio_OpenSS   = QString().sprintf("url(\":/%s/035_1\")", ssCur.c_str());
        ComTool::Tool::updateSS_brImage(ui->butBK_Audio, m_bPlaySound ? audio_OpenSS : audio_CloseSS);
    }

    if(0 == m_playState){
        ui->progressBar_Download->setTextVisible(false);
        ui->Slider_BK->setValue(0);
    }
}
void PagePlayBackNet::_UpdateDownUI()
{
    if(1 == m_downState){
        ui->butDownload->setText(QString::fromLocal8Bit("停止"));
    }else{
        ui->butDownload->setText(QString::fromLocal8Bit("下载"));
        ui->progressBar_Download->setValue(0);
        ui->progressBar_Download->setTextVisible(false);
    }
}

void PagePlayBackNet::on_butBK_Play_clicked()
{
    //速度调整为正常状态
    if(m_bChangeSpeed || m_bPlayStep){
        NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYNORMAL,0,NULL);
        m_bChangeSpeed = false;
        m_bPlayStep = false;
    }

    if(2 == m_playState){   //暂停状态，继续播放
        PausePlayBack(false);\
    }else{//播放状态，暂停；或播放文件
        if(-1 != (LONG)m_hPlayHandle){
             PausePlayBack(TRUE);
        }else{
            StartPlayback();
        }
    }
}

void PagePlayBackNet::on_butBK_Stop_clicked()
{
    bool isStoped = (0 == m_playState);
    StopPlayback();
    if(!isStoped && 0 == m_playState){
        QTimer* timer = new QTimer(this);
        timer->setProperty(ComTool::Def::REFRESHID, QVariant::fromValue(ui->wdB_video));
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(refresh_PanelVideos()));
        timer->start(800);
    }
}

void PagePlayBackNet::on_butBK_Audio_clicked()
{
    if(-1 == (LONG)m_hPlayHandle){
        return;
    }

    if(!m_bPlaySound){
         if(NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSTARTAUDIO,0,NULL)){
             m_bPlaySound = true;
         }
    }else{
        if(NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSTOPAUDIO,0,NULL)){
            m_bPlaySound = false;
        }
    }
    _UpdatePlayUI();
}
void PagePlayBackNet::on_butBK_Full_clicked()
{
    if(-1 == (LONG)m_hPlayHandle){
        return;
    }
    AppZZB::getInstance()->SetFocusVideo(ui->wdB_video);
    AppZZB::getInstance()->TurnButDlgHotBar(ComTool::BN_FULL);
}
void PagePlayBackNet::on_butBK_Capture_clicked()
{
    if(-1 == (LONG)m_hPlayHandle){
        return;
    }

    QString saveImagePath = AppZZB::getInstance()->GetSavePath(0);
    QString saveImageExt  = AppZZB::getInstance()->GetSavePath(2);

    ComTool::Tool::isExistDir(saveImagePath, true);

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString fileName = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
    QString strFilePath = saveImagePath + "/" + fileName + saveImageExt;

    qDebug()<<strFilePath.toLocal8Bit().data();
    if(!NET_DVR_PlayBackCaptureFile((LONG)m_hPlayHandle, strFilePath.toLocal8Bit().data())){
        int err = NET_DVR_GetLastError();
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("抓图错误 ") + QString().sprintf(" %d", err), 0);
    }else{
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("抓图成功！"), 0);
    }
}

void PagePlayBackNet::on_butBK_Back_clicked()
{
    if(-1 == (LONG)m_hPlayHandle || 1 != m_playState){
        return;
    }
    NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSETPOS,0,NULL);
}

void PagePlayBackNet::on_butBK_Slow_clicked()
{
    if(-1 == (LONG)m_hPlayHandle || 1 != m_playState){
        return;
    }
    NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSLOW,0,NULL);
    m_bChangeSpeed = true;
}

void PagePlayBackNet::on_butBK_Fast_clicked()
{
    if(-1 == (LONG)m_hPlayHandle || 1 != m_playState){
        return;
    }
    NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYFAST,0,NULL);
    m_bChangeSpeed = true;
}

void PagePlayBackNet::on_butBK_Step_clicked()
{
    if(-1 == (LONG)m_hPlayHandle || 1 != m_playState){
        return;
    }
    NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYFRAME,0,NULL);
    m_bPlayStep = true;
}

void PagePlayBackNet::on_Slider_BK_sliderReleased()
{
    if(-1 == (LONG)m_hPlayHandle || 1 != m_playState){
        return;
    }
    int value = ui->Slider_BK->value();
    NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYSETPOS,value,NULL);
}

void PagePlayBackNet::on_slider_audio_sliderReleased()
{
    if(-1 == (LONG)m_hPlayHandle){
        return;
    }
    int value = ui->slider_audio->value();
    if(!NET_DVR_PlayBackControl((LONG)m_hPlayHandle,NET_DVR_PLAYAUDIOVOLUME,value,NULL)){
        int err = NET_DVR_GetLastError();
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("硬盘回放"), QString::fromLocal8Bit("音量设置错误 ") + QString().sprintf(" %d", err), 0);
        return;
    }
}

QYVideoWidget* PagePlayBackNet::player()
{
    return ui->wdB_video;
}
bool PagePlayBackNet::isPlaying()
{
    return (-1 != (LONG)m_hPlayHandle) && (1 == m_playState);
}

void PagePlayBackNet::Enter()
{
    if(-1 == (LONG)m_hPlayHandle || 2 != m_playState || !m_bResume){
        m_bResume = false;
        return;
    }
    on_butBK_Play_clicked();
    m_bResume = false;
    ui->wdB_video->_UpdatePosSize();
    ui->wdB_video->showWidget()->setVisible(true);
}
void PagePlayBackNet::Exit()
{
    if(-1 == (LONG)m_hPlayHandle || 1 != m_playState){
        return;
    }
    on_butBK_Play_clicked();
    if(2 == m_playState){
        m_bResume = true;
    }
    ui->wdB_video->showWidget()->setVisible(false);
}

void PagePlayBackNet::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    StopPlayback();
    StartPlayback();
}
