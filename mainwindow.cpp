#include "mainwindow.h"

#include <string>
#include <stdlib.h>




extern "C"  {
#include "guiCore.h"
#include "guiMsg.h"
#include "guiLcdHAL.h"
#include "guiButtonHAL.h"
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
	pTimer->setInterval(1);
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
	Buttons_onKeyPressed(KEY_ENTER);
}

void MainWindow::slotOnEscBtn()
{
    lbl->setText("Esc Button");
	Buttons_onKeyPressed(KEY_ESC);
}

void MainWindow::slotOnLeftBtn()
{
    lbl->setText("Left Button");
	Buttons_onKeyPressed(KEY_LEFT);
}

void MainWindow::slotOnRightBtn()
{
    lbl->setText("Right Button");
	Buttons_onKeyPressed(KEY_RIGHT);
}

void MainWindow::slotTimerTimeout()
{
    px->updateDisplay(guiLcdBuffer);
	 guiMsg_ProcessMessageQueue();
}
