#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "computerRoom.h"

class Teacher :public Identity
{
public:
	//默认构造
	Teacher();

	//有参构造
	Teacher(int empId, string name, string pwd);

	//菜单界面
	virtual void subMenu();

	//查看所有预约
	void CheckAllReserv();

	//审核预约
	void ReviewReserv();

	//初始化机房信息
	//void 

	int m_EmpId;//教师编号
};