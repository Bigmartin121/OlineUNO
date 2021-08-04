#include "chatdatabase.h"

ChatDataBase::ChatDataBase() {}

ChatDataBase::~ChatDataBase() {
	mysql_close(mysql);		//关闭数据库
}

// 数据库连接
void ChatDataBase::database_connect(const char* name)
{
	mysql = mysql_init(NULL);	//初始化
	mysql = mysql_real_connect(mysql, "localhost", "root", "root", name, 0, NULL, 0);	//连接数据库引擎，与运行在主机上的数据库建立连接。
	if (NULL == mysql) {
		cout << "connect database failure" << endl;
	}

	/* 
		mysql_query(): 查询数据库中的某一表内容。
		查询成功：返回0
		    错误：返回!0
		查询结果需要mysql_store_result来获取。
	*/
	if (mysql_query(mysql, "set names utf8;") != 0) {	//设置中文编码，此语句一般放在操作数据库之前
		cout << "set names utf8 mysql_query error" << endl;
	}
}

// 判断用户是否存在
bool ChatDataBase::database_user_exist(string name)
{
	char sql[128] = { 0 };	//初始化sql语句
	sprintf(sql, "show tables like '%s';", name.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "show tables like mysql_query error" << endl;
	}

	MYSQL_RES* res = mysql_store_result(mysql);	//获取查询结果
	MYSQL_ROW row = mysql_fetch_row(res);		//获取多行结果的一行内容
	if (NULL == row) {	//用户不存在
		return false;
	}
	else { return true; }
	
}

//注册用户
void ChatDataBase::database_register_user_password(string name, string password)
{
	char sql[128] = { 0 };

	//在数据库里面建一张表（用户名），表里头包含password和friend的列
	sprintf(sql, "create table %s (password varchar(16), friend varchar(4096)) character set utf8;", name.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "create table mysql_query error" << endl;
	}

	memset(sql, 0, sizeof(sql));	//对sql语句清空初始化
	//对该用户插入其密码
	sprintf(sql, "insert into %s (password) values ('%s');", name.c_str(), password.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "insert into password mysql_query error" << endl;
	}
}

// 判断密码是否正确
bool ChatDataBase::database_password_correct(string name, string password)
{
	char sql[128] = { 0 };
	sprintf(sql, "select password from %s;", name.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "select password mysql_query error" << endl;
	}

	MYSQL_RES* res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (password == row[0]) {	//密码正确
		return true;
	}
	else { return false; }

}

/*

//判断是否是好友关系
bool ChatDataBase::database_whether_friend(string name1, string name2)
{
	char sql[128] = { 0 };
	sprintf(sql, "select friend from %s;", name1.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "select friend mysql_query error" << endl;
	}

	MYSQL_RES *res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (NULL == row[0]) {
		return false;
	}
	else {
		memset(sql, 0, sizeof(sql));
		sprintf(sql, "select friend from %s where friend = '%s';", name1.c_str(), name2.c_str());
		if (mysql_query(mysql, sql) == 0) {		//查询成功则存在该好友
			cout << "select friend mysql_query error" << endl;
		}
		MYSQL_RES* res = mysql_store_result(mysql);
		MYSQL_ROW row = mysql_fetch_row(res);
		if (NULL != row[0]) {
			return true;
		}
	}
	return false;

}

//添加新好友
void ChatDataBase::database_add_new_friend(string name1, string name2)
{
	char sql[128] = { 0 };
	sprintf(sql, "select friend from %s;", name1.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "select friend mysql_query error" << endl;
	}

	memset(sql, 0, sizeof(sql));
	sprintf(sql, "insert into %s(friend) values('%s');", name1.c_str(), name2.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "insert into friend mysql_query error" << endl;
	}
}

//删除好友
void ChatDataBase::database_delete_friend(string name1, string name2)
{
	char sql[128] = { 0 };
	sprintf(sql, "select friend from %s;", name1.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "select friend mysql_query error" << endl;
	}

	memset(sql, 0, sizeof(sql));
	sprintf(sql, "delete from %s where friend = '%s';", name1.c_str(), name2.c_str());
	if (mysql_query(mysql, sql) != 0) {
		cout << "insert into friend mysql_query error" << endl;
	}
}

*/

//判断是否是好友
bool ChatDataBase::database_whether_friend(string name1, string name2)
{
	char sql[128] = { 0 };
	sprintf(sql, "select friend from %s;", name1.c_str());
	if (mysql_query(mysql, sql) != 0)
	{
		cout << "mysql_query error" << endl;
	}

	MYSQL_RES* res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (NULL == row[0])
	{
		return false;
	}
	else
	{
		string all_friend(row[0]);
		int start = 0, end = 0;
		while (1)
		{
			end = all_friend.find('|', start);
			if (-1 == end)
			{
				break;
			}
			if (name2 == all_friend.substr(start, end - start))
			{
				return true;
			}

			start = end + 1;
		}

		if (name2 == all_friend.substr(start, all_friend.size() - start))
		{
			return true;
		}
	}

	return false;
}

//添加好友
void ChatDataBase::database_add_new_friend(string name1, string name2)
{
	char sql[1024] = { 0 };
	sprintf(sql, "select friend from %s;", name1.c_str());
	if (mysql_query(mysql, sql) != 0)
	{
		cout << "mysql_query" << endl;
	}
	string friend_list;
	MYSQL_RES* res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (NULL == row[0])    //原来没有好友
	{
		friend_list.append(name2);
	}
	else
	{
		friend_list.append(row[0]);
		friend_list += "|";
		friend_list += name2;
	}

	memset(sql, 0, sizeof(sql));
	sprintf(sql, "update %s set friend = '%s';", name1.c_str(), friend_list.c_str());
	if (mysql_query(mysql, sql) != 0)
	{
		cout << "mysql_query error" << endl;
	}
}

//删除好友
void ChatDataBase::database_delete_friend(string name1, string name2)
{
	char sql[1024] = { 0 };
	sprintf(sql, "select friend from %s;", name1.c_str());
	if (mysql_query(mysql, sql) != 0)
	{
		cout << "mysql_query" << endl;
	}
	string friend_list;
	MYSQL_RES* res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (NULL == row[0])    //原来没有好友
	{
		
	}
	else
	{
		friend_list.append(row[0]);
		int pos = friend_list.find(name2);
		int n = name2.size();
		friend_list = friend_list.erase(pos, n + 1);
	}

	memset(sql, 0, sizeof(sql));
	sprintf(sql, "update %s set friend = '%s';", name1.c_str(), friend_list.c_str());
	if (mysql_query(mysql, sql) != 0)
	{
		cout << "mysql_query error" << endl;
	}
}


void ChatDataBase::database_disconnect()
{
	mysql_close(mysql);
}



int main()
{
}
