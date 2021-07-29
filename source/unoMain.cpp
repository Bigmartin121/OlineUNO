#include<iostream>
#include<string.h>
#include"Process.h"
using namespace std;

int main() {
	Process unoProcess;
	bool flagEndUno = unoProcess.execute();
	if (!flagEndUno) {
		cout << "游戏遇到未知错误，马上退出游戏" << endl;
		exit(0);
	}	

}