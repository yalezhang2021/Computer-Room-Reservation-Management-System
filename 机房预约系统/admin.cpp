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
	//cout << "欢迎管理员：" << this->m_Name << " 登录！" << endl;
	//cout << "\t\t\t\t-----------------------------\n";
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "\t\t\t\t|       管理员机房预约系统   |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t|         1.添加账号        |" << endl;
	//cout << "\t\t\t\t|         2.查看账号        |" << endl;
	//cout << "\t\t\t\t|         3.查看机房        |" << endl;
	//cout << "\t\t\t\t|         4.清空预约        |" << endl;
	//cout << "\t\t\t\t|         0.退出登录        |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "请输入您的操作：" << endl;

	cout << "Welcome Admin：" << this->m_Name << " Login！" << endl;
	cout << "\t\t\t\t-----------------------------------\n";
	cout << "\t\t\t\t-----------------------------------" << endl;
	cout << "\t\t\t\t|       Reservation System        |" << endl;
	cout << "\t\t\t\t|---------------------------------|" << endl;
	cout << "\t\t\t\t|         1.Add Account           |" << endl;
	cout << "\t\t\t\t|         2.Show Accounts         |" << endl;
	cout << "\t\t\t\t|         3.Show Room Info        |" << endl;
	cout << "\t\t\t\t|         4.Clear All Appointments|" << endl;
	cout << "\t\t\t\t|         0.Exit                  |" << endl;
	cout << "\t\t\t\t|---------------------------------|" << endl;
	cout << "\t\t\t\t-----------------------------------" << endl;
	cout << "Enter your choice：" << endl;
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
		//cout << "请输入添加账号的类型" << endl;
		//cout << "1.添加学生账号" << endl;
		//cout << "2.添加老师账号" << endl;
		//cout << "0.返回" << endl;
		//cout << endl;
		//cout << "请输入您的操作：" << endl;
		cout << "Choose account type" << endl;
		cout << "1.Add Student Account" << endl;
		cout << "2.Add Teacher Account" << endl;
		cout << "0.Return" << endl;
		cout << endl;
		cout << "Please Enter：";

		int select = 0;
		cin >> select;
		type = select;

		if (select == 0)
		{
			cout << "Return" << endl;
			system("pause");
			system("cls");
			return;
		}
		else if (select == 1)
		{
			//添加学生账号
			fileName = STUDENT_FILE;
			//tip = "请输入学号：";
			//errorTip = "该学生账号已存在，请重新输入:";
			tip = "Please enter StuID：";
			errorTip = "This StuId is already exist，please reenter:";
			break;
		}
		else if (select == 2)
		{
			//添加老师账号
			fileName = TEACHER_FILE;
			//tip = "请输入职工编号：";
			//errorTip = "该教师编号已存在，请重新输入:";
			tip = "Please enter StaffID：";
			errorTip = "This StaffId is already exist，please reenter:";
			break;
		}
		else
		{
			cout << "The input is wrong, please reenter！" << endl;
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

	cout << "Please input Name：" << endl;
	cin >> name;

	cout << "Please input Password: " << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;

	cout << "Add successful！" << endl;

	system("pause");
	system("cls");
	ofs.close();

	//添加完后马上初始化容器接口，重新获取文件中的数据
	this->InitVector();
}

void PrintStudent(Student& s)
{
	cout << "StuID： " << s.m_Id << ", Name：" << s.m_Name << ", Password：" << s.m_Pwd << endl;
}

void PrintTeacher(Teacher& t)
{
	cout << "StaffID： " << t.m_EmpId << ", Name：" << t.m_Name << ", Password" << t.m_Pwd << endl;
}

void Admin::ShowAccount()
{
	cout << endl;
	//cout << "1. 查看所有学生" << endl;
	//cout << "2. 查看所有老师" << endl;
	//cout << "请选择查看内容：";
	cout << "1. Show All Student" << endl;
	cout << "2. Show All Teacher" << endl;
	cout << "Select：";
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
		cout << "All students' info：" << endl;
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
		cout << "All teachers' info：" << endl;
		for_each(vTea.begin(), vTea.end(), PrintTeacher);
		cout << endl;
	}
	else
	{
		cout << "Input wrong, please input again！" << endl;
	}

	system("pause");
	system("cls");
}

void Admin::ShowRoomInfo()
{
	cout << "Computer Room info：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "Room No.：" << it->m_Id << ", Max Seats:" << it->m_Num << endl;
	}
	
	system("pause");
	system("cls");
}

void Admin::CleanReservRecord()
{
	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::trunc);
	ofs.close();

	cout << "All reservation are cleared！" << endl;
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