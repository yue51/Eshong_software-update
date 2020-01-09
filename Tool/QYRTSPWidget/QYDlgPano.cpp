#include "QYDlgPano.h"
#include "ui_QYDlgPano.h"
#include <QtGui/QPainter.h>
#include "../../ComTool.h"

QYDlgPano::QYDlgPano(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QYDlgPano)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Widget | Qt::Popup);
    setVisible(false);
}

QYDlgPano::~QYDlgPano()
{
    delete ui;
}

void QYDlgPano::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}

void QYDlgPano::on_butPano_5_clicked()
{
    emit sigClicked(ComTool::BN_PANO_TB);
}

void QYDlgPano::on_butOff_clicked()
{
    emit sigClicked(ComTool::BN_PANO_CLOSE);
}

void QYDlgPano::on_butPano_1_clicked()
{
    emit sigClicked(ComTool::BN_PANO_ONE);
}

void QYDlgPano::on_butPano_2_clicked()
{
    emit sigClicked(ComTool::BN_PANO_TWO);
}

void QYDlgPano::on_butPano_3_clicked()
{
    emit sigClicked(ComTool::BN_PANO_THREE);
}

void QYDlgPano::on_butPano_4_clicked()
{
    emit sigClicked(ComTool::BN_PANO_FOUR);
}

void QYDlgPano::on_butPano_6_clicked()
{
    emit sigClicked(ComTool::BN_PANO_SIX);
}

void QYDlgPano::on_butPano_7_clicked()
{
    emit sigClicked(ComTool::BN_PANO_SEV);
}

void QYDlgPano::on_butPano_8_clicked()
{
    emit sigClicked(ComTool::BN_PANO_ENT);
}
