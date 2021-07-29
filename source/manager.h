#pragma once
#include<iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include<string>
#include<fstream>

using namespace std;

class user {
public:
	string name;
	string password;
};

class Manager
{
public:
	Manager();
	void show_style();
	void show_welcome();
	void exitSystem();
	vector<user>v1;//±£¥Ê’À∫≈√‹¬Î
	void initUserdata();
	void login();
	void enroll();
	int usernum;
	void operaterpush_back(vector<user> &v);
	bool managerMain();
	~Manager();
};
