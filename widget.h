#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>//消息提示框
#include <QDebug>//打印提示
#include <QString>
#include "game_hobby.h"
#include "registration.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:

    //处理登录按钮的槽函数
    void onLogin();
    //处理注册按钮的槽函数
    void onRegistration();
    //处理退出大厅信号
    void back_signal();
    //处理退出注册信号
    void back_registration();
private:
    Ui::Widget *ui;
    game_hobby hobby;//游戏大厅
    registration registra;

};

#endif // WIDGET_H
