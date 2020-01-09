#include "QYDlgPanoHalf.h"
#include "ui_QYDlgPanoHalf.h"
#include <QtGui/QPainter.h>
#include "../../ComTool.h"

QYDlgPanoHalf::QYDlgPanoHalf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QYDlgPanoHalf)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Widget | Qt::Popup);
    setVisible(false);
}

QYDlgPanoHalf::~QYDlgPanoHalf()
{
    delete ui;
}

void QYDlgPanoHalf::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter  drawPainter(this);
    QPainter* painter = &drawPainter;

    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    QWidget::paintEvent(event);
}

void QYDlgPanoHalf::on_butOff_clicked()
{
    emit sigClicked(ComTool::BN_PANO_CLOSE);
}

void QYDlgPanoHalf::on_butPano_0_clicked()
{
    emit sigClicked(ComTool::BN_PANOH_ONE);
}

void QYDlgPanoHalf::on_butPano_1_clicked()
{
    emit sigClicked(ComTool::BN_PANOH_TWO);
}
