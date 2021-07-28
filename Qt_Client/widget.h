/** 第一步：连接服务器成功
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>   //第一步：Socket连接头文件
#include <QHostAddress> //第一步：地址
#include <QMessageBox>  //第一步，提示信息
#include <QJsonObject>  //第二步 Json
#include <QJsonDocument>//第二步 Json

#define IP 120.55.55.171
#define PORT 8000

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void connect_success(); //第一步：定义一个槽函数，提示连接成功
    void server_reply();    //第二步：服务器返回
    void on_registerButton_clicked();

private:
    void client_register_handler(QString);  //第二步
    Ui::Widget *ui;
    QTcpSocket *socket;     //第一步：创建一个对象

};

#endif // WIDGET_H
