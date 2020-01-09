#ifndef PAGEPLAYBACKLOCAL_H
#define PAGEPLAYBACKLOCAL_H

#include <QWidget>
#include <QThread>

namespace Ui {
class PagePlayBackLocal;
}

class QTableWidgetItem;

namespace ComTool {
typedef struct _NODE_DATA NODE_DATA;
}

class PagePlayBackLocal : public QWidget
{
    Q_OBJECT

public:
    explicit PagePlayBackLocal(QWidget *parent = 0);
    ~PagePlayBackLocal();

public:
    ComTool::NODE_DATA* findNodeData;

    void Enter();
    void Exit();
protected:
    virtual void paintEvent(QPaintEvent* event);

private:
    void releaseFindList();
    void releaseFindThread();

    bool StartPlayback();
    bool StopPlayback();
    bool PausePlayBack(bool bPlayOrPause);
    void _UpdatePlayUI();

    void _ResetValPlay();
    void _StopTimePlay();
private slots:
    void oFindThreadStarted();
    void oFindThreadFinished();

    void refresh_PanelVideos();
    void refresh_SliderBK();


    void on_butFind_clicked();

    void on_comboBox_RecType_currentIndexChanged(int index);

    void on_butBK_Play_clicked();

    void on_butBK_Stop_clicked();

    void on_butBK_Audio_clicked();

    void on_butBK_Full_clicked();

    void on_butBK_Capture_clicked();

    void on_butBK_Back_clicked();

    void on_butBK_Slow_clicked();

    void on_butBK_Fast_clicked();

    void on_butBK_Step_clicked();

    void on_Slider_BK_sliderReleased();

    void on_slider_audio_sliderReleased();

    void on_butOpenFile_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
private://playback

    typedef struct _Find_Data{
        QString strFileName;
        QString strStartTime;//文件的开始时间
        QString strStopTime;//文件的结束时间
        QString strFileSize;//文件的大小
    }FIND_DATA;

    typedef struct _Find_Info{
        QString path;
        QString strStartTime;//文件的开始时间
        QString strStopTime;//文件的结束时间
    }FIND_INFO;

    class FileFindThread : public QThread
    {
    public:
        explicit FileFindThread(void* lLoginID, void* findInfo, QList<FIND_DATA*>* findList, QObject *parent = 0)
            :QThread(parent)
        {
            mbRunning    = false;
            mbStop       = false;
            mHloginID    = lLoginID;
            mHfindInfo   = findInfo;
            retCode      = -1;
            mFindDataList= findList;
        }
        virtual ~FileFindThread();
    public:
         void turnRunning(bool bRunning){mbRunning = bRunning; mbStop = !mbRunning;}
         void Stop(){
             mbStop = true;
             wait();
         }
         int retCode;
    protected:
        virtual void run();
    private:
         int _funFind();
    private:
        bool        mbRunning;
        bool        mbStop;

        void*       mHloginID;
        void*       mHfindInfo;
        QList<FIND_DATA*>* mFindDataList;
    };

    int m_RecType;        //录像类型，0xff－全部；0－定时录像；1－移动侦测；2－报警触发；3-报警|移动侦测；4－报警&移动侦测；5－命令触发；6－手动录像
    int m_FileProperty;   //文件属性，0－正常文件；1－锁定文件；0xff表示所有文件
    FileFindThread     *m_FileFindThread;
    QList<FIND_DATA*>   m_FindDataList;

    void*   m_hPlayHandle;
    int     m_curPlayIndex;
    int     m_playState; //0-stop 1-playing 2-pause
    bool    m_bPlaySound;
    bool    m_bPlayStep;
    int     m_iTotalSeconds;
    QTimer* m_playTimer;

    ComTool::NODE_DATA* mPlayData;

    bool   m_bResume;
private:
    Ui::PagePlayBackLocal *ui;
};

#endif // PAGEPLAYBACKLOCAL_H
