#ifndef QYDLGHOTBAR_H
#define QYDLGHOTBAR_H

#include <QDialog>

namespace Ui {
class QYDlgHotBar;
}

class QPushButton;
class QYDlgHotBar : public QDialog
{
    Q_OBJECT

public:
    explicit QYDlgHotBar(QWidget *parent = 0);
    ~QYDlgHotBar();

signals:
    void sigClicked(int butNo, QPushButton*);

public:
    void turnState(int butNo, int state);
    void turnStyle(int style);
protected:
    virtual void paintEvent(QPaintEvent* event);

    virtual void keyPressEvent(QKeyEvent *e);


private slots:
    void on_butPano_clicked();

    void on_butAspect_clicked();

    void on_butClose_clicked();

    void on_butFull_clicked();

    void on_butAudio_clicked();

    void on_butSpeek_clicked();

    void on_butCamera_clicked();

    void on_butRecord_clicked();

    void on_butStream_clicked();

private:
    Ui::QYDlgHotBar *ui;
};

#endif // QYDLGHOTBAR_H
