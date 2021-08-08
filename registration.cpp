#include "registration.h"
#include "ui_registration.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QRegExpValidator>
registration::registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    //输入用户账号密码设置规范
    ui->user_name->setValidator(new QRegExpValidator
                                (QRegExp("[\u4e00-\u9fa5a-zA-Z]{0,9}$")));
    ui->user_account->setValidator(new QRegExpValidator
                                   (QRegExp("[0-9]{3,6}$")));
    ui->user_password->setValidator(new QRegExpValidator
                                    (QRegExp("[0-9a-zA-Z]{6,16}$")));
    connect(ui->button_yes,&QPushButton::clicked,
            this,[=]()
    {
        QString username = ui->user_name->text();
        if(username.length()<3){
            QMessageBox::information(this,"注册提示","昵称长度应为3-9位");
            return;
        }
        QString account = ui->user_account->text();
        if(account.length()>65535){
            QMessageBox::information(this,"注册提示","账号数字不能超过65535");
            return;
        }
        QString password =ui->user_password->text();
        if(password.length()<6){
            QMessageBox::information(this,"注册提示","密码长度应为6-16位");
            return;
        }
        QString password_2 = ui->user_password2->text();
        if(password_2 != password){
            QMessageBox::information(this,"注册提示","密码不一致，请重新输入");
            return;
        }
    }
    );

    //载入数据库
    createDB();
    createTable();
    //queryTable();
    //退出大厅
    connect(ui->button_yes,&QPushButton::clicked,
            this,&registration::queryTable);
    connect(ui->button_yes,&QPushButton::clicked,
            this,registration::back_Slot);

}
registration::~registration()
{
    delete ui;

}
//返回登录槽函数
void registration::back_Slot()
{
    emit back_login_slot();

}

//创建数据库
void registration::createDB()
{
    //添加数据库驱动库
    db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名字
    db.setDatabaseName("user.db");
    //打开数据库
    if(db.open()==true)
    {
//        qDebug()<<"创建/打开数据库成功";
         qDebug()<<"db open success";
    }
    else{
//        qDebug()<<"创建/打开数据库失败";
         qDebug()<<"db opent fail";
    }
}

//创建数据表
void registration::createTable()
{
    QSqlQuery query;
    QString str = QString("CREATE TABLE user("
                          "name TEXT NOT NULL,"
                          "account INT PRIMARY KEY NOT NULL,"
                          "password VARCHAR NOT NULL)");

    if(query.exec(str) == true)
        qDebug()<<"创建数据表成功";
    else
        qDebug()<<query.lastError();

}

//查询判断
void registration::queryTable()
{
    QSqlQuery query;
    QString stri=QString("SELECT * FROM user");
    query.exec(stri);
    int id =ui->user_account->text().toInt();
    while(query.next())
    {
        int userId= query.value(1).toInt();

        if(id == userId)
        {
            qDebug()<<userId<<query.value(2);
            QMessageBox::information(
                        this,"注册提示","账号已被注册了");
            return;
        }
    }

    //ID不冲突插入数据
    QString name=ui->user_name->text();
    QString pass=ui->user_password->text();
    stri=QString(
                "INSERT INTO user(name,account,password) VALUES('%1',%2,'%3')"
                ).arg(name).arg(id).arg(pass);
    if(query.exec(stri)==true)
        qDebug()<<"数据库输入成功";
    else
        qDebug()<<"数据库输入失败";
}
