#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "computerRoom.h"

class Student :public Identity
{
public:
	//默认构造
	Student();

	//有参构造
	Student(int id, string name, string pwd);

	//菜单界面
	virtual void subMenu();//必须重写父类中的纯虚函数，才能实例化对象

	//申请预约
	void ApplyReserv();

	//查看自身的预约
	void CheckMyReserv();

	//查看所有预约
	void CheckAllReserv();

	//取消预约
	void CancelReserv();

	//注销登录
	//void ExitStudent();

	//初始化机房信息
	void InitComputerRoom();

	int m_Id;
	vector<ComputerRoom> vCom;
};