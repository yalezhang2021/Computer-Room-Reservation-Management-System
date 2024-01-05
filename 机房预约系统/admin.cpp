#include "admin.h"
#include "globalFile.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
//#include <iostream>

Admin::Admin()
{

}

Admin::Admin(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = name;

	//初始化容器 获取所有文件中 老师 学生的信息
	this->InitVector();
	this->InitComputerRoom();
}

void Admin::subMenu()
{
	cout << "欢迎管理员：" << this->m_Name << " 登录！" << endl;
	cout << "\t\t\t\t-----------------------------\n";
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "\t\t\t\t|       管理员机房预约系统   |" << endl;
	cout << "\t\t\t\t|---------------------------|" << endl;
	cout << "\t\t\t\t|         1.添加账号        |" << endl;
	cout << "\t\t\t\t|         2.查看账号        |" << endl;
	cout << "\t\t\t\t|         3.查看机房        |" << endl;
	cout << "\t\t\t\t|         4.清空预约        |" << endl;
	cout << "\t\t\t\t|         0.退出登录        |" << endl;
	cout << "\t\t\t\t|---------------------------|" << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "请输入您的操作：" << endl;
}

void Admin::AddAccount()
{
	string fileName;
	string tip;
	ofstream ofs;
	int type;
	string errorTip;

	while (true)
	{
		cout << endl;
		cout << "请输入添加账号的类型" << endl;
		cout << "1.添加学生账号" << endl;
		cout << "2.添加老师账号" << endl;
		cout << "0.返回" << endl;
		cout << endl;
		cout << "请输入您的操作：" << endl;

		int select = 0;
		cin >> select;
		type = select;

		if (select == 0)
		{
			cout << "返回" << endl;
			system("pause");
			system("cls");
			return;
		}
		else if (select == 1)
		{
			//添加学生账号
			fileName = STUDENT_FILE;
			tip = "请输入学号：";
			errorTip = "该学生账号已存在，请重新输入:";
			break;
		}
		else if (select == 2)
		{
			//添加老师账号
			fileName = TEACHER_FILE;
			tip = "请输入职工编号：";
			errorTip = "该教师编号已存在，请重新输入:";
			break;
		}
		else
		{
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	ofs.open(fileName, ios::out | ios::app); //写入文件，追加写入

	int id;
	string name;
	string pwd;

	cout << tip << endl;

	//判断是否重复
	while (true)
	{
		cin >> id;
		bool isRepeat = this->CheckRepeat(id, type);

		if (isRepeat)
		{
			cout << errorTip;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码: " << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;

	cout << "添加成功！" << endl;

	system("pause");
	system("cls");
	ofs.close();

	//添加完后马上初始化容器接口，重新获取文件中的数据
	this->InitVector();
}

void PrintStudent(Student& s)
{
	cout << "学生账号： " << s.m_Id << ", 姓名：" << s.m_Name << ", 密码：" << s.m_Pwd << endl;
}

void PrintTeacher(Teacher& t)
{
	cout << "教师账号： " << t.m_EmpId << ", 姓名：" << t.m_Name << ", 密码" << t.m_Pwd << endl;
}

void Admin::ShowAccount()
{
	cout << endl;
	cout << "1. 查看所有学生" << endl;
	cout << "2. 查看所有老师" << endl;
	cout << "请选择查看内容：";
	int select;
	cin >> select;
	cout << endl;
	
	if (select == 1)
	{
		//for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		//{
		//	cout << "学生账号： " << it->m_Id << ", 姓名：" << it->m_Name << endl;
		//}

		//上面的可以用for_each遍历容器，更简单
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), PrintStudent);
		cout << endl;
	}
	else if (select == 2)
	{
		//vector<Teacher>v;
		//for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		//{
		//	cout << "老师账号： " << it->m_EmpId << ", 姓名：" << it->m_Name << endl;
		//}

		//上面的可以用for_each遍历容器，更简单
		cout << "所有老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), PrintTeacher);
		cout << endl;
	}
	else
	{
		cout << "输入有误，请重新输入！" << endl;
	}

	system("pause");
	system("cls");
}

void Admin::ShowRoomInfo()
{
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房号：" << it->m_Id << ", 最大容量:" << it->m_Num << endl;
	}
	
	system("pause");
	system("cls");
}

void Admin::CleanReservRecord()
{
	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::trunc);
	ofs.close();

	cout << "所有预约记录已清空！" << endl;
	system("pause");
	system("cls");
}

void Admin::InitVector()
{
	vStu.clear();
	vTea.clear();

	//读取信息
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "unable to open student file" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	//cout << "当前的学生数量为：" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "unable to open teacher file" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	//cout << "当前的老师数量为：" << vTea.size() << endl;
	ifs.close();
}

bool Admin::CheckRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (it->m_Id == id)
			{
				return true;
			}
		}
	}
	else if (type == 2)
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (it->m_EmpId == id)
			{
				return true;
			}
		}
	}
	return false;
}

void Admin::InitComputerRoom()
{
	vCom.clear();

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "unable to open student file" << endl;
		return;
	}

	ComputerRoom c;
	while (ifs >> c.m_Id && ifs >> c.m_Num)
	{
		vCom.push_back(c);
	}

	//cout << "当前的机房数量为：" << vCom.size() << endl;
	ifs.close();
}