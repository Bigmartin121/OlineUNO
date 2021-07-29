#include "manager.h"

Manager::Manager()
{
	this->initUserdata();
	v1.resize(10000);
}

void Manager::show_style()
{
	system("color f0");
	system("UNO游戏");
	system("mode con cols=100 lines=35"); //con为控制台
}

void Manager::show_welcome()
{
	cout << "**********欢迎来到UNO游戏**********\t" << endl;
	cout << endl << "**************1.注册**************\t" << endl;
	cout << "**************2.登录**************\t" << endl;
	cout << "**************3.退出**************\t" << endl;
	cout << endl;
}
void Manager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void Manager::login()
{
	string name, password;
	char tempusernum[10];
	user u1;
	ifstream iofs1;
	ifstream iofs2;
flag:
	iofs1.open("resource/userdata.txt", ios::in);
	iofs2.open("resource/usernum.txt", ios::in);
	cout << "请输入账号" << endl;
	cout << "账号应当为4-10位的英文字母" << endl;
	if (!iofs1.is_open() || !iofs2.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	else
	{
		iofs2.getline(tempusernum, sizeof(tempusernum));
		usernum = atoi(tempusernum);
		if (usernum != 0)
		{
			int p = usernum, point1 = 0;
			while (p > 0)
			{
				getline(iofs1, v1[point1].name);
				getline(iofs1, v1[point1].password);
				point1++;
				p--;
			}
			iofs1.close();
			iofs2.close();
		}
	}
	cin >> name;
	if (name >= "AAAA" && name <= "zzzzzzzzzz" && name.length() >= 4 && name.length() <= 10)
	{
		if (usernum > 0)
		{
			for (int i = 0; i < usernum; i++)
			{
				if (v1[i].name == name)
				{
					cout << "账号已存在!" << endl;
					system("pause");
					system("cls");
					return;
				}
			}
			cout << "请输入密码" << endl;
			cout << "密码长度应大于等于六位" << endl;
			cin >> password;
			if (password.length() < 6)
			{
				cout << "密码长度非法" << endl;
				system("pause");
				system("cls");
				goto flag;
			}
		}
		else
		{
			cout << "请输入密码" << endl;
			cout << "密码长度应大于等于六位" << endl;
			cin >> password;
			if (password.length() < 6)
			{
				cout << "密码长度非法" << endl;
				system("pause");
				system("cls");
				goto flag;
			}
		}
	}
	else
	{
		cout << "请重新输入合法账号" << endl;
		goto flag;
	}
	fstream iofs3;
	fstream iofs4;
	iofs3.open("resource/userdata.txt", ios::out | ios::app);
	iofs4.open("resource/usernum.txt", ios::out);
	iofs4 << ++usernum << endl;
	iofs3 << name << endl;
	iofs3 << password << endl;
	iofs3.close();
	iofs4.close();
	cout << "恭喜注册成功" << endl;
	system("pause");
	system("cls");
}

void Manager::enroll()				//登录
{
	string name, password, tempPassword;
	user u1;
	char tempusernum[10];
	cout << "请输入账号" << endl;
	ifstream iofs1;
	ifstream iofs2;
	iofs1.open("resource/userdata.txt", ios::in);
	iofs2.open("resource/usernum.txt", ios::in);
	if (!iofs1.is_open() || !iofs2.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}
	else
	{
		iofs2.getline(tempusernum, sizeof(tempusernum));
		usernum = atoi(tempusernum);
		if (usernum != 0)
		{
			int p = usernum, point1 = 0;
			while (p > 0)
			{
				getline(iofs1, v1[point1].name);
				getline(iofs1, v1[point1].password);
				point1++;
				p--;
			}
		}
	}
	iofs1.close();
	iofs2.close();
	cin >> name;
	if (name >= "AAAA" && name <= "zzzzzzzzzz" && name.length() >= 4 && name.length() <= 10)
	{
		if (usernum > 0)
		{
			bool flag = 0;
			for (int i = 0; i < usernum; i++)
			{
				if (v1[i].name == name)
				{
					tempPassword = v1[i].password;
					cout << "请输入密码" << endl;
					cin >> password;
					flag = 1;
				}
			}
			if (flag == 0)
			{
				cout << "账号不存在" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		else
		{
			cout << "账号不存在" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else
	{
		cout << "账号不存在" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (password == tempPassword)
	{
		cout << "登陆成功" << endl;
		cout << "游戏即将开始" << endl;
		system("pause");
		system("color fa");
		system("mode con cols=120 lines=40");
	}
	else
	{
		cout << "密码错误" << endl;
		system("pause");
		system("cls");
		return;
	}
}
void Manager::initUserdata()
{
	this->v1.clear();
}


bool Manager::managerMain() {
	system("resource/voice.vbs");
	this->show_style();
	string choice;
	while (true)
	{
		this->show_welcome();
		cout << "************请您选择功能************\t" << endl;
		cin >> choice;
		if (choice.length() != 1)
		{
			cout << "无效输入，请重新输入" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			switch (choice[0])
			{
			case '1':
				this->login();
				break;
			case '2':
				this->enroll();
				return true;
				break;

			case '3':
				this->exitSystem();
			default:
				cout << "无效输入，请重新输入" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
	}
	return false;
}

void Manager::operaterpush_back(vector<user>& v) {

}

Manager::~Manager()
{

}