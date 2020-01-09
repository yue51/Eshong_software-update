#include "PagePlayBackLocal.h"
#include "ui_PagePlayBackLocal.h"
#include <QtGui/QPainter.h>
#include <QDebug>
#include <QTimer>
#include <QScrollBar>
#include <QFileDialog>

#include "ComHeader.h"
#include "ComTool.h"
#include "AppZZB.h"
#include "PageMain.h"

#define USED_PORT 99		//card decode port

/*********************************************************
Function:	DisplayCBFun
Desc:		callback function of capture
Input:		nPort,port; pBuf, image buffer; nSize,image size; nWidth,image width; nHeight,image height; nType,type;
Output:
Return:
**********************************************************/
bool g_bLocalCapPic = false;
char g_filePathCapPic[MAX_PATH];
void CALLBACK DisplayCBFun(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved)
{
    if (!g_bLocalCapPic){
        return;
    }
    g_bLocalCapPic=false;
    if (!PlayM4_ConvertToBmpFile(pBuf, nSize, nWidth, nHeight, nType, g_filePathCapPic)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString::fromLocal8Bit("抓图失败！"), 0);
    }else{
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString::fromLocal8Bit("抓图成功！"), 0);
    }
}

PagePlayBackLocal::PagePlayBackLocal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PagePlayBackLocal)
{
    ui->setupUi(this);
    ui->wd_timeline->setVisible(false);
    ui->wd_timeline2->setVisible(false);
    ui->wdB_video->setProperty(ComTool::Def::PRO_HOTBARVISIBLE, QVariant(1));

    m_RecType       = 0xff;
    m_FileProperty  = 0xff;
    m_FileFindThread= 0;
    findNodeData  = 0;

    _ResetValPlay();

    mPlayData = new ComTool::NODE_DATA();

    m_bResume = false;

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

PagePlayBackLocal::~PagePlayBackLocal()
{
    _StopTimePlay();
    StopPlayback();

    ComTool::CCommon<ComTool::NODE_DATA>::DeleteA(&mPlayData);

    findNodeData  = 0;
    releaseFindThread();
    releaseFindList();

    delete ui;
}

void PagePlayBackLocal::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}



void PagePlayBackLocal::releaseFindList()
{
    for(int i=0, l=m_FindDataList.length(); i<l; ++i){
        FIND_DATA* findData = m_FindDataList.at(i);
        ComTool::CCommon<FIND_DATA>::DeleteA(&findData);
    }
    m_FindDataList.clear();
}
void PagePlayBackLocal::releaseFindThread()
{
    if(0 == m_FileFindThread){return;}
    if(!m_FileFindThread->isFinished()){
        m_FileFindThread->Stop();
    }
    ComTool::CCommon<FileFindThread>::DeleteA(&m_FileFindThread);
}
PagePlayBackLocal::FileFindThread::~FileFindThread(){
    if(0 != mHfindInfo){
        NET_DVR_FILECOND *pFileCond = (NET_DVR_FILECOND*)mHfindInfo;
        delete pFileCond;
        mHfindInfo = 0;
    }
}
int PagePlayBackLocal::FileFindThread::_funFind()
{
    FIND_INFO *pFileCond = (FIND_INFO*)mHfindInfo;
    QDir dir(pFileCond->path);
    if(!dir.exists()){
        return NET_DVR_FILE_EXCEPTION;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    if(file_count <= 0){
            return NET_DVR_FILE_NOFIND;
    }

    for(int i=0; i<file_count; ++i){
        QFileInfo file_info = list.at(i);
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("mp4"), Qt::CaseInsensitive) == 0)
        {
            QString absolute_file_path = file_info.absoluteFilePath();

            //保存文件信息
            QFileInfo fileInfo(absolute_file_path);
            qint64 size = fileInfo.size();  //---获取文件大小（字节）
            QDateTime lastVisitTime = fileInfo.lastRead(); //---获取文件最近访问时间
            QString strLastVisit = lastVisitTime.toString("yyyy/MM/dd hh:mm:ss ");

            FIND_DATA* findData = 0;
            ComTool::CCommon<FIND_DATA>::NewA(&findData);
            findData->strFileName = ComTool::Tool::GetFile_Name(absolute_file_path);
            findData->strFileSize = QString().sprintf("%0.2fM",(double)size/1024/1024);
            findData->strStartTime= strLastVisit;
            findData->strStopTime = absolute_file_path;

            mFindDataList->push_back(findData);
        }
    }
    return 0;
}
void PagePlayBackLocal::FileFindThread::run(){
    retCode = _funFind();
    quit();
 }

void PagePlayBackLocal::on_butFind_clicked()
{
    if(0 != m_playState){
        on_butBK_Stop_clicked();
    }

    PageMain* pageMain = AppZZB::getInstance()->pageMain;
    ComTool::NODE_DATA* nodeData = pageMain->_GotSelFromTree();
//    if(0 == nodeData || -1== (LONG)nodeData->hLogon || 0 == nodeData->qytype){//HHSDK Out
//        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("远程回放"), QString::fromLocal8Bit("请在左边列表中选择一个硬盘录像机通道"), 0);
//        return;
//    }

    QDate dataStart  = ui->dateEdit_Start->date();
    QTime timeStart = ui->timeEdit_Start->time();
    QDate dataEnd  = ui->dateEdit_Stop->date();
    QTime timeEnd = ui->timeEdit_Stop->time();

//    bool bData = (dataStart < dataEnd) || (dataStart <= dataEnd && timeStart < timeEnd);
//    if(!bData){
//        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("远程回放"), QString::fromLocal8Bit("请选择起始结束时间，确保起始时间早于结束时间！"), 0);
//        return;
//    }

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

    FIND_INFO*pFileCond = new FIND_INFO();
    pFileCond->path = AppZZB::getInstance()->GetSavePath(1);
    pFileCond->strStartTime = QString().sprintf("%04d/%02d/%02d %02d:%02d:%02d",StartSearchTime.dwYear,StartSearchTime.dwMonth,StartSearchTime.dwDay,
                                                StartSearchTime.dwHour,StartSearchTime.dwMinute,StartSearchTime.dwSecond);
    pFileCond->strStopTime = QString().sprintf("%04d/%02d/%02d %02d:%02d:%02d",StopSearchTime.dwYear,StopSearchTime.dwMonth,StopSearchTime.dwDay,
                                                StopSearchTime.dwHour,StopSearchTime.dwMinute,StopSearchTime.dwSecond);

    releaseFindList();
    releaseFindThread();
    findNodeData  = nodeData;
    AppZZB::getInstance()->TurnShowDlgLoading(true);
    if(0 == m_FileFindThread){
        m_FileFindThread = new FileFindThread(0, (void*)pFileCond, &m_FindDataList);//nodeData->hLogon
        connect(m_FileFindThread, SIGNAL(started()), this, SLOT(oFindThreadStarted()));
        connect(m_FileFindThread, SIGNAL(finished()), this, SLOT(oFindThreadFinished()));
    }
    m_FileFindThread->turnRunning(true);
    m_FileFindThread->start();
}

void PagePlayBackLocal::on_comboBox_RecType_currentIndexChanged(int index)
{
    if(index<0 || 2<index){return;}
    //录像类型，0xff－全部；0－定时录像；1－移动侦测；2－报警触发；3-报警|移动侦测；4－报警&移动侦测；5－命令触发；6－手动录像
    static int S_VAL[3] = {0xff, 0, 6};
    m_RecType = S_VAL[index];
}

void PagePlayBackLocal::oFindThreadStarted()
{

}
void PagePlayBackLocal::oFindThreadFinished()
{
    AppZZB::getInstance()->TurnShowDlgLoading(false);
    if(0 == m_FileFindThread){return;}

    if(NET_DVR_FILE_EXCEPTION == m_FileFindThread->retCode){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString::fromLocal8Bit("查找文件时异常"), 0);
        return;
    }else if(NET_DVR_FILE_NOFIND == m_FileFindThread->retCode){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString::fromLocal8Bit("没有录像文件"), 0);
        return;
    }
    if(m_FindDataList.length() < 1){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString::fromLocal8Bit("没有录像文件"), 0);
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
void PagePlayBackLocal::refresh_PanelVideos()
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
void PagePlayBackLocal::refresh_SliderBK()
{
    if(ui->Slider_BK->isSliderDown()){
        return;
    }
    if(1 != m_playState || 1 > m_iTotalSeconds){
        return;
    }

    DWORD nCurSecond=PlayM4_GetPlayedTime(USED_PORT);
    ui->Slider_BK->setValue(nCurSecond*100/m_iTotalSeconds);

    float fCurPos = PlayM4_GetPlayPos(USED_PORT);
    if (fCurPos <= 1.00+0.000001 && fCurPos >= 1.00-0.000001){//播放完毕
        on_butBK_Stop_clicked();
    }
}
//开始回放
bool PagePlayBackLocal::StartPlayback()
{
    if(0 != m_playState){
        return false;
    }

    int cur = ui->tableWidget->currentRow();
    if(0>cur){
        return false;
    }
    m_curPlayIndex = cur;
    QTableWidgetItem *item = ui->tableWidget->item(cur, 3);
    QString strFilePath = item->text();

    QWidget* wdShow = ui->wdB_video->showWidget();
    HWND hPlayWnd = (HWND)wdShow->winId();

    //set stream secret key
    static const char* s = "StreamNotEncrypt";
    if(!PlayM4_SetSecretKey(USED_PORT, 1, const_cast<char*>(s), 128)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_SetSecretKey %d", PlayM4_GetLastError(USED_PORT)), 0);
        return false;
    }

    char filePath[MAX_SIZE];
    memset(filePath, 0, MAX_SIZE);
    ::sprintf_s(filePath, "%s", strFilePath.toStdString().c_str());

    if (!PlayM4_OpenFile(USED_PORT, filePath)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_OpenFile %d", PlayM4_GetLastError(USED_PORT)), 0);
        return false;
    }

    m_iTotalSeconds = PlayM4_GetFileTime(USED_PORT);
    if (m_iTotalSeconds < 1){
        PlayM4_CloseFile(USED_PORT);
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("文件大小为 %d", 0), 0);
        return false;
    }

    if (!PlayM4_SetDisplayCallBack(USED_PORT,DisplayCBFun)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_SetDisplayCallBack err[%d]", PlayM4_GetLastError(USED_PORT)), 0);
    }

    if(!PlayM4_Play(USED_PORT,hPlayWnd)){
        PlayM4_CloseFile(USED_PORT);
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_Play err[%d]", PlayM4_GetLastError(USED_PORT)), 0);
        return false;
    }
    m_hPlayHandle = (void*)hPlayWnd;

    //ui->wdB_video->_UpdatePosSize();

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
    if(PlayM4_PlaySound(USED_PORT)){
        m_bPlaySound = true;
        PlayM4_SetVolume(USED_PORT,(WORD)ui->slider_audio->value());
    }

    _UpdatePlayUI();
    return true;
}

bool PagePlayBackLocal::PausePlayBack(bool bPlayOrPause)
{
    if(0 == m_playState){
        return false;
    }
    if(bPlayOrPause){  //暂停
        if(1 == m_playState && !PlayM4_Pause(USED_PORT, true)){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_Pause err[%d]", PlayM4_GetLastError(USED_PORT)), 0);
            return false;
        }
        m_playState = 2;
    }else if(2 == m_playState){    //播放
        if(!PlayM4_Play(USED_PORT,(HWND)m_hPlayHandle)){
            AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_Play err[%d]", PlayM4_GetLastError(USED_PORT)), 0);
            return false;
        }
         m_playState = 1;
    }

    _UpdatePlayUI();
    return true;
}

void PagePlayBackLocal::_ResetValPlay()
{
    m_hPlayHandle   = (void*)-1;
    m_playState     = 0;
    m_curPlayIndex  = -1;
    m_bPlaySound    = false;
    m_bPlayStep     = false;
    m_iTotalSeconds = 0;
}
void PagePlayBackLocal::_StopTimePlay()
{
    if(0 == m_playTimer){
        return;
    }
    disconnect(m_playTimer, SIGNAL(timeout()), this, SLOT(refresh_SliderBK()));
    m_playTimer->stop();
    delete m_playTimer;
    m_playTimer = 0;
}

bool PagePlayBackLocal::StopPlayback()
{
    if(0 == m_playState){
        return true;
    }

    if(!PlayM4_Stop(USED_PORT)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_Stop err[%d]", PlayM4_GetLastError(USED_PORT)), 0);
        return false;
    }
    PlayM4_CloseFile(USED_PORT);
    if(m_bPlaySound){
         PlayM4_StopSound();
    }

    //状态变量设置
    _StopTimePlay();
    _ResetValPlay();

    mPlayData->hLogon = (void*)-1;
    mPlayData->hOpen  = m_hPlayHandle;
    ui->wdB_video->setProperty(ComTool::Def::NODEDATANO, QVariant());

    _UpdatePlayUI();

    return true;
}
void PagePlayBackLocal::_UpdatePlayUI()
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
        ui->Slider_BK->setValue(0);
    }
}

void PagePlayBackLocal::on_butBK_Play_clicked()
{
//    //速度调整为正常状态
//    if(m_bPlayStep){
//        PlayM4_Play(USED_PORT,(HWND)m_hPlayHandle);
//        m_bPlayStep = false;
//    }
    if(2 == m_playState){   //继续播放
        PausePlayBack(false);
    }else if(1 == m_playState){//暂停
        PausePlayBack(true);
    }else{
        StartPlayback();
    }
}

void PagePlayBackLocal::on_butBK_Stop_clicked()
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

void PagePlayBackLocal::on_butBK_Audio_clicked()
{
    if(1 != m_playState){
        return;
    }

    if(!m_bPlaySound){
         if(PlayM4_PlaySound(USED_PORT)){
             m_bPlaySound = true;
         }
    }else{
        if(PlayM4_StopSound()){
            m_bPlaySound = false;
        }
    }
    _UpdatePlayUI();
}

void PagePlayBackLocal::on_butBK_Full_clicked()
{
    if(-1 == (LONG)m_hPlayHandle){
        return;
    }
    AppZZB::getInstance()->SetFocusVideo(ui->wdB_video);
    AppZZB::getInstance()->TurnButDlgHotBar(ComTool::BN_FULL);
}

void PagePlayBackLocal::on_butBK_Capture_clicked()
{
    if(0 == m_playState){
        return;
    }

    QString saveImagePath = AppZZB::getInstance()->GetSavePath(0);
    QString saveImageExt  = AppZZB::getInstance()->GetSavePath(2);

    ComTool::Tool::isExistDir(saveImagePath, true);

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString fileName = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
    QString strFilePath = saveImagePath + "/" + fileName + saveImageExt;

    memset(g_filePathCapPic, 0, MAX_SIZE);
    ::sprintf_s(g_filePathCapPic, "%s", strFilePath.toStdString().c_str());
    g_bLocalCapPic = true;
}

void PagePlayBackLocal::on_butBK_Back_clicked()
{
    if(0 == m_playState){
        return;
    }
    if (!PlayM4_SetPlayedTimeEx(USED_PORT, 0)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_SetPlayedTimeEx %d", 0), 0);
    }
    PausePlayBack(false);
}

void PagePlayBackLocal::on_butBK_Slow_clicked()
{
    if(1 != m_playState){
        return;
    }
    PlayM4_Slow(USED_PORT);
}

void PagePlayBackLocal::on_butBK_Fast_clicked()
{
    if(1 != m_playState){
        return;
    }
    PlayM4_Fast(USED_PORT);
}

void PagePlayBackLocal::on_butBK_Step_clicked()
{
    if(0 == m_playState){
        return;
    }
    PausePlayBack(true);
    PlayM4_OneByOne(USED_PORT);
    m_bPlayStep=true;
}

void PagePlayBackLocal::on_Slider_BK_sliderReleased()
{
    if(1 != m_playState){
        return;
    }
    int value = ui->Slider_BK->value();
    if (!PlayM4_SetPlayedTimeEx(USED_PORT, m_iTotalSeconds*value*0.01*1000)){
        AppZZB::getInstance()->MsgBox(QString::fromLocal8Bit("本地回放"), QString().sprintf("PlayM4_SetPlayedTimeEx %d", m_iTotalSeconds*value*10), 0);
    }
}

void PagePlayBackLocal::on_slider_audio_sliderReleased()
{
    if(1 != m_playState){
        return;
    }
    int value = ui->slider_audio->value();
    PlayM4_SetVolume(USED_PORT,(WORD)value);
}

void PagePlayBackLocal::on_butOpenFile_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,
                                                     QString::fromLocal8Bit("请选择视频文件:"),
                                                     AppZZB::getInstance()->GetSavePath(1),
                                                     QString("Video (*.mp4 *.MP4)"));
    if(file_path.isEmpty()){
        return;
    }

    QFileInfo fileInfo(file_path);
    qint64 size = fileInfo.size();  //---获取文件大小（字节）
    QDateTime lastVisitTime = fileInfo.lastRead(); //---获取文件最近访问时间
    QString strLastVisit = lastVisitTime.toString("yyyy/MM/dd hh:mm:ss ");

    //保存文件信息
    FIND_DATA* findData = 0;
    ComTool::CCommon<FIND_DATA>::NewA(&findData);
    findData->strFileName = ComTool::Tool::GetFile_Name(file_path);
    findData->strFileSize = QString().sprintf("%0.2fM",(double)size/1024/1024);
    findData->strStartTime= strLastVisit;
    findData->strStopTime = file_path;

    m_FindDataList.push_back(findData);

    //Insert
    {
        int n = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(n);
        {
            QTableWidgetItem* item = new QTableWidgetItem(findData->strFileName);
            ui->tableWidget->setItem(n, 0, item);
        }
        ui->tableWidget->setItem(n, 1, new QTableWidgetItem(findData->strFileSize));
        ui->tableWidget->setItem(n, 2, new QTableWidgetItem(findData->strStartTime));
        ui->tableWidget->setItem(n, 3, new QTableWidgetItem(findData->strStopTime));
    }
}

void PagePlayBackLocal::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    StopPlayback();
    StartPlayback();
}

void PagePlayBackLocal::Enter()
{
    if(2 != m_playState || !m_bResume){
        m_bResume = false;
        return;
    }
    on_butBK_Play_clicked();
    m_bResume = false;
    ui->wdB_video->_UpdatePosSize();
    ui->wdB_video->showWidget()->setVisible(true);
}
void PagePlayBackLocal::Exit()
{
    if(1 != m_playState){
        return;
    }
    on_butBK_Play_clicked();
    if(2 == m_playState){
        m_bResume = true;
    }
    ui->wdB_video->showWidget()->setVisible(false);
}
