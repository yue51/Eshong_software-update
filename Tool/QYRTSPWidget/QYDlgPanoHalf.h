#ifndef QYDLGPANOHALF_H
#define QYDLGPANOHALF_H

#include <QWidget>

namespace Ui {
class QYDlgPanoHalf;
}

class QYDlgPanoHalf : public QWidget
{
    Q_OBJECT

public:
    explicit QYDlgPanoHalf(QWidget *parent = 0);
    ~QYDlgPanoHalf();

signals:
    void sigClicked(int butNo);

protected:
    virtual void paintEvent(QPaintEvent* event);


private slots:

    void on_butOff_clicked();

    void on_butPano_0_clicked();

    void on_butPano_1_clicked();

private:
    Ui::QYDlgPanoHalf *ui;
};

#endif // QYDLGPANOHALF_H
