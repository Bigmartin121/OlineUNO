#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QDialog>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QDialog dlg;
};

#endif // MAINWINDOW_H
