#include <iostream>
using namespace std;
#include "globalFile.h"
#include "identity.h"
#include <fstream>
#include <string>
#include "student.h"
#include "teacher.h"
#include "admin.h"
#include "restSeats.h"

//进入管理员子菜单界面
void AdminMenu(Identity*& admin) //通过父类指针传进来, 父类指针创建子类对象
{
	while (true)
	{
		//调用管理员子菜单
		admin->subMenu();//纯虚函数实例化
		

		//将父类指针转为子类指针，调用子类里其他特有接口
		Admin* adm = (Admin*)admin;//强制转换类型为Admin*
		//adm->InitVector();

		int select = 0;
		//接收用户选项
		cin >> select;

		if (select == 1) //添加账号
		{
			//cout << "添加账号" << endl;
			adm->AddAccount();
		}
		else if (select == 2) //查看账号
		{
			//cout << "查看账号" << endl;
			adm->ShowAccount();
		}
		else if (select == 3) //查看机房
		{
			//cout << "查看机房" << endl;
			adm->ShowRoomInfo();
		}
		else if (select == 4) //清空预约
		{
			//cout << "清空预约" << endl;
			adm->CleanReservRecord();
		}
		else
		{ 
			delete admin; //销毁掉堆区对象
			cout << "Logout successful" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入学生子菜单界面
void StudentMenu(Identity*& student) //通过父类指针传进来, 父类指针创建子类对象
{
	while (true)
	{
		//调用学生子菜单
		student->subMenu();//纯虚函数实例化
		//将父类指针转为子类指针，调用子类里其他特有接口
		Student* stu = (Student*)student;//强制转换类型为Admin*

		int select;
		//接收用户选项
		cin >> select;
		switch (select)
		{
		case 1:
			stu->ApplyReserv();
			break;
		case 2:
			stu->CheckMyReserv();
			break;
		case 3:
			stu->CheckAllReserv();
			break;
		case 4:
			stu->CancelReserv();
			break;
		case 0:
			delete student; //销毁掉堆区对象
			cout << "Logout successful" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "The input is wrong, please reenter!" << endl;
			break;
		}		
	}
}

//进入老师子菜单界面
void TeacherMenu(Identity*& teacher) //通过父类指针传进来, 父类指针创建子类对象
{
	while (true)
	{
		//调用laoshi 子菜单
		teacher->subMenu();//纯虚函数实例化
		//将父类指针转为子类指针，调用子类里其他特有接口
		Teacher* tea = (Teacher*)teacher;//强制转换类型为Admin*

		int select;
		//接收用户选项
		cin >> select;
		switch (select)
		{
		case 1:
			tea->CheckAllReserv();
			break;
		case 2:
			tea->ReviewReserv();
			break;
		case 0:
			delete teacher; //销毁掉堆区对象
			cout << "Logout successful" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "The input is wrong, please reenter!" << endl;
			break;
		}
	}
}

//登录功能
void LoginIn(string fileName, int type)
{
	//fileName: 操作文件名， type: 操作身份类型
	//父类指针， 用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "File is not existed" << endl;
		ifs.close();
		return;
	}

	//判断文件是否为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "File is empty" << endl;
		ifs.close();
		return;
	}
	else
	{
		ifs.putback(ch);
	}

	//准备接收用户的信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type == 1)
	{
		cout << "Enter your StuID：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "Enter your staffID:" << endl;
		cin >> id;
	}

	cout << "Enter your username:" << endl;
	cin >> name;

	cout << "Enter your password:" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份验证
		int fId; //从文件中读取的id号
		string fName; //从文件中读取的姓名
		string fPwd; //从文件中读取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd) //每次碰到空格或换行就会结束读取
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "Student Verification Login Successful！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//进入学生身份的子菜单
				StudentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//教师身份验证
		int fId; //从文件中读取的id号
		string fName; //从文件中读取的姓名
		string fPwd; //从文件中读取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd) //每次碰到空格或换行就会结束读取
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "Teacher Verification Login Successful！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师身份的子菜单
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName; //从文件中读取的姓名
		string fPwd; //从文件中读取的密码

		while (ifs >> fName && ifs >> fPwd) //每次碰到空格或换行就会结束读取
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "Admin Verification Login successful！" << endl;
				//登录成功后，按任意键进入管理员界面
				system("pause");
				system("cls");

				person = new Admin(name, pwd);
				//进入管理员身份的子菜单
				AdminMenu(person);
				return;
			}
		}
	}

	cout << "Authentication Login Failed！" << endl;
	system("pause");
	system("cls");
}

int main()
{
	//RestSeats rest;
	//rest.InitRestSeats();
	//string a = rest.mRestSeats[0]["mondayAm"];
	//cout << a << endl;

	int select = 0;

	while (true)
	{	
		//cout << "\t\t\t\t-----------------------------" << endl;
		//cout << "\t\t\t\t|         机房预约系统      |" << endl;
		//cout << "\t\t\t\t|---------------------------|" << endl;
		//cout << "\t\t\t\t|         1.学生登录        |" << endl;
		//cout << "\t\t\t\t|         2.教师登录        |" << endl;
		//cout << "\t\t\t\t|         3.管理员登录      |" << endl;
		//cout << "\t\t\t\t|         0.退出登录        |" << endl;
		//cout << "\t\t\t\t|---------------------------|" << endl;
		//cout << "\t\t\t\t-----------------------------" << endl;

		cout << "\t\t\t\t-----------------------------------" << endl;
		cout << "\t\t\t\t|         Reservation System      |" << endl;
		cout << "\t\t\t\t|---------------------------------|" << endl;
		cout << "\t\t\t\t|         1.Student Login         |" << endl;
		cout << "\t\t\t\t|         2.Teacher Login         |" << endl;
		cout << "\t\t\t\t|         3.Admin   Login         |" << endl;
		cout << "\t\t\t\t|         0.Exit                  |" << endl;
		cout << "\t\t\t\t|---------------------------------|" << endl;
		cout << "\t\t\t\t-----------------------------------" << endl;

		cout << "Please enter：" << endl;
		cin >> select;

		switch (select)
		{
		case 0://退出系统
			cout << "Thank you，bye！" << endl;
			system("pause");
			return 0;
			break;
		case 1://学生登录
			LoginIn(STUDENT_FILE, 1);
			//Student stt;
			//申请预约
			//stt.ApplyReserv();
			//查看自身的预约
			//stt.CheckMyReserv();
			//查看所有预约
			//stt.CheckAllReserv();
			//取消预约
			//stt.CancelReserv();
			//注销登录
			//stt.ExitStudent();
			break;
		case 2://教师登录
			LoginIn(TEACHER_FILE, 2);
			//sm.TeacherLogin();
			break;
		case 3://管理员登录
			LoginIn(ADMIN_FILE, 3);
			//sm.AdminLogin();
			break;
		default:
			cout << "The input is wrong, please reenter！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}