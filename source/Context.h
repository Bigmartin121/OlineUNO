#pragma once
#include<iostream>
#include<string.h>
#include<windows.h>
using namespace std;

class Context {
public:
	void show() {
		cout << "游戏即将开始!" << endl;
		Sleep(2000);
	}
};