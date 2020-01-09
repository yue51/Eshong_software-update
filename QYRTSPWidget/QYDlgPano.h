#ifndef QYDLGPANO_H
#define QYDLGPANO_H

#include <QWidget>

namespace Ui {
class QYDlgPano;
}

class QYDlgPano : public QWidget
{
    Q_OBJECT

public:
    explicit QYDlgPano(QWidget *parent = 0);
    ~QYDlgPano();

signals:
    void sigClicked(int butNo);

protected:
    virtual void paintEvent(QPaintEvent* event);


private slots:
    void on_butPano_5_clicked();

    void on_butOff_clicked();

    void on_butPano_1_clicked();

    void on_butPano_2_clicked();

    void on_butPano_3_clicked();

    void on_butPano_4_clicked();

    void on_butPano_6_clicked();

    void on_butPano_7_clicked();

    void on_butPano_8_clicked();

private:
    Ui::QYDlgPano *ui;
};

#endif // QYDLGPANO_H
