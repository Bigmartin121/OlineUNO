#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QDialog>
#include <QAction>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(400,400);
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    QMenu *menu = mBar->addMenu("对话框");
    QAction *p1=menu->addAction("模态对话框");
    connect(p1,&QAction::triggered,
           [=]()
    {
        QDialog dlg;
        dlg.exec();

    }



            );
    QAction *p2=menu->addAction("非模态对话框");
    connect(p2,&QAction::triggered,
           [=]()
    {

        dlg.show();

    }
            );


}

MainWindow::~MainWindow()
{

}
