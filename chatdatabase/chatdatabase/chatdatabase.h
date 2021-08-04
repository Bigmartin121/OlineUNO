#ifndef CHATDATABASE_H
#define CHATDATABASE_H

#include <mysql/mysql.h>
#include <iostream>
#include <string.h>

using namespace std;

class ChatDataBase
{
private:
	MYSQL* mysql;
public:
	ChatDataBase();
	~ChatDataBase();

	void database_connect(const char* name);				//数据库连接  const char* name 为需要连接的数据库名称类型
	bool database_user_exist(string);						//判断用户是否存在，string为用户名类型
	void database_register_user_password(string, string);	//注册用户，两个string形参表示用户名与密码的类型
	bool database_password_correct(string, string);			//判断密码是否正确
	bool database_whether_friend(string, string);			//判断是否是好友关系，防止重复添加某个好友
	void database_add_new_friend(string, string);			//添加新好友
	void database_delete_friend(string, string);			//删除好友
	void database_disconnect();								//断开数据库
};


#endif // !CHATDATABASE_H
