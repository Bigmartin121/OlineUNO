#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class registration;
}

class registration : public QWidget
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = 0);
    void back_Slot();
    ~registration();
signals:
    void back_login_slot();
private slots:
   // void on_button_yes_clicked();//确认注册按钮槽函数


private:
    Ui::registration *ui;
    QSqlDatabase db;//建立Qt和数据库连接
    QSqlQueryModel model;//保存结果集
    //创建数据库
    void createDB();
    //创建数据表
    void createTable();
    //
    void queryTable();
};

#endif // REGISTRATION_H
