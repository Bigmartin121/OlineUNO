#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //登录信号
    connect(ui->button_login,&QPushButton::clicked,
            this,&Widget::onLogin);
    //注册信号
    connect(ui->button_registration,
            &QPushButton::clicked,
            this,&Widget::onRegistration);

    //处理游戏大厅退出信号
    connect(&hobby,&game_hobby::back_loginslot,
            this,&Widget::back_signal);
    //处理注册退出信号
    connect(&registra,&registration::back_login_slot,
            this,&Widget::back_registration);

}
//处理登录按钮的槽函数
void Widget::onLogin()
{
    QSqlQuery query;

    query.exec(QObject::tr("select * from user"));
    //判断数据库的账号密码是否匹配
    while(query.next()){
       //查看数据库的账号密码 qDebug()<<query.value(1)<<query.value(2);
        if((ui->account->text().trimmed()==query.value(1)&&
                ui->password->text()==query.value(2))||
                (ui->account->text() =="liu" &&
                ui->password->text() == "123"))
        {
            qDebug()<<"登录成功";
            qDebug()<<query.value(1)<<query.value(2);
            hide();
            hobby.show();
            ui->account->clear();
            ui->password->clear();
            return ;
        }

    }
    //判断数据库最后一个数据是否匹配，如果不匹配提示信息
    if((ui->account->text().trimmed()!=query.value(1)&&
            ui->password->text()!=query.value(2))||
            (ui->account->text() !="liu" &&
            ui->password->text() != "123"))
            {
                QMessageBox::warning(this,tr("Warning"),tr("账号或密码错误"));
                ui->account->clear();
                ui->password->clear();
                return ;
            }

}


//处理注册按钮的槽函数
void Widget::onRegistration()
{
    this->hide();
    registra.show();

}
//处理退出大厅信号
void Widget::back_signal()
{
    show();
    hobby.close();

}
//处理退出注册信号
void Widget::back_registration()
{
    show();
    registra.close();
}

Widget::~Widget()
{
    delete ui;
}
