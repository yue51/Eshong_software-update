#include "QYDlgToolBar.h"
#include "ui_QYDlgToolBar.h"

QYDlgToolBar::QYDlgToolBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QYDlgToolBar)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, false);

    setStyleSheet("QDialog { background-color: rgba(16,16,16,0); border-width:0px;}");//transparent
}

QYDlgToolBar::~QYDlgToolBar()
{
    delete ui;
}
