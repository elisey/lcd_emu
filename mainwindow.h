#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pixeldisplay.h"

#include <QTimer>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotOnEnterBtn();
    void slotOnEscBtn();
    void slotOnLeftBtn();
    void slotOnRightBtn();

    void slotTimerTimeout();

private:
    QWidget *pCentralWidget;
    QLabel *lbl;
    PixelDisplay *px;
    QPushButton *pBtnEnter;
    QPushButton *pBtnEsc;
    QPushButton *pBtnLeft;
    QPushButton *pBtnRight;

    QTimer *pTimer;

};

#endif // MAINWINDOW_H
