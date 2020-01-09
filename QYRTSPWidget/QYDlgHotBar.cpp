#include "QYDlgHotBar.h"
#include "ui_QYDlgHotBar.h"
#include <QtGui/QPainter.h>
#include <QDebug>
#include <QKeyEvent>
#include "../../ComTool.h"
#include "../../AppZZB.h"

QYDlgHotBar::QYDlgHotBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QYDlgHotBar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, false);

    setStyleSheet("QDialog { background-color: rgba(16,16,16,0); border-width:0px;}");//transparent
}

QYDlgHotBar::~QYDlgHotBar()
{
    delete ui;
}

void QYDlgHotBar::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}
void QYDlgHotBar::keyPressEvent(QKeyEvent *e)
{
    if(Qt::Key_Escape == e->key()){
        QWidget::keyPressEvent(e);
        AppZZB::getInstance()->revMsg(0, Qt::Key_Escape);
        return;
    }
   QDialog::keyPressEvent(e);
}

void QYDlgHotBar::turnStyle(int style){
    if(1 == style){
        QRect rt[9];
        rt[1] = ui->butClose->geometry();
        ui->butAspect->move(rt[1].left(), rt[1].top());

        ui->butFull->setVisible(true);
        ui->butAspect->setVisible(true);

        ui->butClose->setVisible(false);
        ui->butAudio->setVisible(false);
        ui->butSpeek->setVisible(false);
        ui->butCamera->setVisible(false);
        ui->butRecord->setVisible(false);
        ui->butPano->setVisible(false);
        ui->butStream->setVisible(false);
        return;
    }

    ui->butFull->setVisible(true);
    ui->butClose->setVisible(true);
    ui->butAudio->setVisible(true);
    ui->butSpeek->setVisible(true);
    ui->butCamera->setVisible(true);
    ui->butRecord->setVisible(true);
    ui->butPano->setVisible(true);
    ui->butStream->setVisible(true);
    ui->butAspect->setVisible(true);
}
void QYDlgHotBar::turnState(int butNo, int state){
    if(ComTool::BN_FULL == butNo){
        QString CloseSS  = QString("url(\":/QYRTSPWidget/5_0\")");
        QString OpenSS   = QString("url(\":/QYRTSPWidget/5_1\")");
        ComTool::Tool::updateSS_brImage(ui->butFull, (0==state) ? CloseSS : OpenSS);
    }else if(ComTool::BN_AUDIO == butNo){
        QString CloseSS  = QString("url(\":/QYRTSPWidget/7_0\")");
        QString OpenSS   = QString("url(\":/QYRTSPWidget/7_1\")");
        ComTool::Tool::updateSS_brImage(ui->butAudio, (0==state) ? CloseSS : OpenSS);
    }else if(ComTool::BN_SPEEK == butNo){
        QString CloseSS  = QString("url(\":/QYRTSPWidget/8_0\")");
        QString OpenSS   = QString("url(\":/QYRTSPWidget/8_1\")");
        ComTool::Tool::updateSS_brImage(ui->butSpeek, (0==state) ? CloseSS : OpenSS);
    }else if(ComTool::BN_RECORD == butNo){
        QString CloseSS  = QString("url(\":/QYRTSPWidget/10_0\")");
        QString OpenSS   = QString("url(\":/QYRTSPWidget/10_1\")");
        ComTool::Tool::updateSS_brImage(ui->butRecord, (0==state) ? CloseSS : OpenSS);
    }else if(ComTool::BN_STREAM == butNo){
        QString CloseSS  = QString("url(\":/QYRTSPWidget/12_0\")");
        QString OpenSS   = QString("url(\":/QYRTSPWidget/12_1\")");
        ComTool::Tool::updateSS_brImage(ui->butStream, (0==state) ? CloseSS : OpenSS);
    }else if(ComTool::BN_ASPECT == butNo){
        //QString as169SS  = QString("url(\":/QYRTSPWidget/4_0\")");
        //QString as43SS   = QString("url(\":/QYRTSPWidget/4_1\")");
        //QString asfullSS = QString("url(\":/QYRTSPWidget/4_2\")");
        //QString asfull2SS= QString("url(\":/QYRTSPWidget/4_3\")");
        QString asSS = QString("url(\":/QYRTSPWidget/4_0\")");
        if(1 == state){
            asSS = QString("url(\":/QYRTSPWidget/4_1\")");
        }else if(2 == state){
            asSS = QString("url(\":/QYRTSPWidget/4_2\")");
        }else if(3 == state){
            asSS = QString("url(\":/QYRTSPWidget/4_3\")");
        }
        ComTool::Tool::updateSS_brImage(ui->butAspect, asSS);
    }
}
void QYDlgHotBar::on_butPano_clicked()
{
    emit sigClicked(ComTool::BN_PANO, ui->butPano);
}

void QYDlgHotBar::on_butAspect_clicked()
{
    emit sigClicked(ComTool::BN_ASPECT, ui->butAspect);
}

void QYDlgHotBar::on_butClose_clicked()
{
    emit sigClicked(ComTool::BN_CLOSE, ui->butClose);
}

void QYDlgHotBar::on_butFull_clicked()
{
    emit sigClicked(ComTool::BN_FULL, ui->butFull);
}

void QYDlgHotBar::on_butAudio_clicked()
{
    emit sigClicked(ComTool::BN_AUDIO, ui->butAudio);
}

void QYDlgHotBar::on_butSpeek_clicked()
{
    emit sigClicked(ComTool::BN_SPEEK, ui->butSpeek);
}

void QYDlgHotBar::on_butCamera_clicked()
{
    emit sigClicked(ComTool::BN_CAMERA, ui->butCamera);
}

void QYDlgHotBar::on_butRecord_clicked()
{
    emit sigClicked(ComTool::BN_RECORD, ui->butRecord);
}

void QYDlgHotBar::on_butStream_clicked()
{
    emit sigClicked(ComTool::BN_STREAM, ui->butStream);
}
