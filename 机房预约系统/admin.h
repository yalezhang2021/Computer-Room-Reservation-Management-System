#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"
#include <vector>

class Admin :public Identity
{
public:

	Admin();	//默认构造
	Admin(string name, string pwd);	//有参构造
	virtual void subMenu();	//重写纯虚函数
	void AddAccount();	//添加账户
	void ShowAccount();	//显示账户
	void ShowRoomInfo();	//显示机房信息
	void CleanReservRecord();	//清空预约记录
	void InitVector();	//初始化容器
	bool CheckRepeat(int id, int type);	//检测重复 true: 重复了
	void InitComputerRoom();	//初始化机房信息
	//void PrintInfo(int val);	//打印学生或老师容器的信息

	vector<Student> vStu;	//学生容器
	vector<Teacher> vTea;	//老师容器
	vector<ComputerRoom> vCom;	//机房信息
};