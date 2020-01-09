#ifndef QYDLGTOOLBAR_H
#define QYDLGTOOLBAR_H

#include <QDialog>

namespace Ui {
class QYDlgToolBar;
}

class QYDlgToolBar : public QDialog
{
    Q_OBJECT

public:
    explicit QYDlgToolBar(QWidget *parent = 0);
    ~QYDlgToolBar();

private:
    Ui::QYDlgToolBar *ui;
};

#endif // QYDLGTOOLBAR_H
