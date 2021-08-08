#include "game_hobby.h"
#include "ui_game_hobby.h"

game_hobby::game_hobby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_hobby)
{
    ui->setupUi(this);

    //退出大厅
    connect(ui->quit_Game,&QPushButton::clicked,
            this,game_hobby::back_Slot);
    //世界广播
    connect(ui->world_Broadcast,&QPushButton::clicked,
            this,&game_hobby::on_world_Broadcast_clicked);

}

//返回登录槽函数
void game_hobby::back_Slot()
{
    emit back_loginslot();
}

game_hobby::~game_hobby()
{
    delete ui;
}

void game_hobby::on_world_Broadcast_clicked()
{
    this->close();

}
