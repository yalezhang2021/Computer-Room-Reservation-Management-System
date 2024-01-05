#pragma once //防止头文件重复包含
#include <iostream>
using namespace std;

//身份抽象类
class Identity
{
public:

	//操作菜单 ,多态技术，写子菜单，声明这个接口，之后可以复用这个函数
	virtual void subMenu() = 0; //声明纯虚函数

	//学生，老师和管理员都有的共性就是用户名和密码,把它们提炼出来写到基类里
	string m_Name; //用户名
	string m_Pwd;  //密码
};