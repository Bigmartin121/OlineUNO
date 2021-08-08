#ifndef GAME_HOBBY_H
#define GAME_HOBBY_H

#include <QWidget>

#include <QPushButton>


namespace Ui {
class game_hobby;
}

class game_hobby : public QWidget
{
    Q_OBJECT

public:
    explicit game_hobby(QWidget *parent = 0);
    void back_Slot();
    ~game_hobby();
signals:
    //返回登录信号
    void back_loginslot();

private slots:
    void on_world_Broadcast_clicked();

private:
    Ui::game_hobby *ui;
    QPushButton back_login;//返回登录按钮

};

#endif // GAME_HOBBY_H
