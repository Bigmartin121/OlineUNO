#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QTcpSocket;    //第一步：初始化
    socket->connectToHost(QHostAddress("120.55.55.171"),PORT);  //第一步：连接IP和端口
    connect(socket, &QTcpSocket::connected, this, &Widget::connect_success);    //第一步：进行连接
    connect(socket, &QTcpSocket::readyRead, this, &Widget::server_reply);       //第二步

}

Widget::~Widget()
{
    delete ui;
}

/*第一步：*/
void Widget::connect_success()
{
    QMessageBox::information(this,"连接提示","连接服务器成功");    //信息对话框
}

//第二步：注册按钮槽函数
void Widget::on_registerButton_clicked()
{
    QString username = ui->userLineEdit->text();
    QString password = ui->passwdLineEdit->text();

    QJsonObject obj;
    obj.insert("cmd", "register");
    obj.insert("user", username);
    obj.insert("password", password);

    QByteArray ba = QJsonDocument(obj).toJson();
    socket->write(ba);
}

//第二步
void Widget::server_reply()
{
    QByteArray ba = socket->readAll();
    QJsonObject obj = QJsonDocument::fromJson(ba).object();
    QString cmd = obj.value("cmd").toString();
    if (cmd == "register_reply")
    {
        client_register_handler(obj.value("result").toString());
    }
}

//第二步
void Widget::client_register_handler(QString res)
{
    if (res == "success")
    {
        QMessageBox::information(this, "注册提示", "注册成功");
    }
    else if (res == "failure")
    {
        QMessageBox::warning(this, "注册提示", "注册失败");
    }
}

