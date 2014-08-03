#include "mainwindow.h"

#include <string>
#include <stdlib.h>




extern "C"  {
#include "guiCore.h"
#include "guiLcdHAL.h"
}

//extern color_t guiLcdBuffer[];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pCentralWidget = new QWidget;
    setCentralWidget(pCentralWidget);

    lbl = new QLabel;
    lbl->setText("Hello");

    px = new PixelDisplay;
    px->setSize(320, 240);
    //px->setScale(2);

    pBtnEnter = new QPushButton("Enter");
    pBtnEsc = new QPushButton("Esc");
    pBtnLeft = new QPushButton("<<-");
    pBtnRight = new QPushButton("->>");

    QObject::connect( pBtnEnter, SIGNAL(clicked()), this, SLOT(slotOnEnterBtn()) );
    QObject::connect( pBtnEsc, SIGNAL(clicked()), this, SLOT(slotOnEscBtn()) );
    QObject::connect( pBtnLeft, SIGNAL(clicked()), this, SLOT(slotOnLeftBtn()) );
    QObject::connect( pBtnRight, SIGNAL(clicked()), this, SLOT(slotOnRightBtn()) );

    QVBoxLayout *pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(lbl);
    pvbxLayout->addWidget(px);
    pvbxLayout->addWidget(pBtnEnter);
    pvbxLayout->addWidget(pBtnEsc);
    pvbxLayout->addWidget(pBtnLeft);
    pvbxLayout->addWidget(pBtnRight);

    pCentralWidget->setLayout(pvbxLayout);

    pTimer = new QTimer;
    pTimer->setInterval(100);
    pTimer->setSingleShot(false);
    emit pTimer->start();
    QObject::connect( pTimer, SIGNAL(timeout()), this, SLOT(slotTimerTimeout()) );
    guiCore_Init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::slotOnEnterBtn()
{
    lbl->setText("Enter Button");
}

void MainWindow::slotOnEscBtn()
{
    lbl->setText("Esc Button");
}

void MainWindow::slotOnLeftBtn()
{
    lbl->setText("Left Button");
}

void MainWindow::slotOnRightBtn()
{
    lbl->setText("Right Button");
}

void MainWindow::slotTimerTimeout()
{
    px->updateDisplay(guiLcdBuffer);
}
