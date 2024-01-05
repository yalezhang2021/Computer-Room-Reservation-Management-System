#include "teacher.h"
#include "reservationFile.h"
#include <vector>
#include "computerRoom.h"
#include "restSeats.h"

//加上函数的作用域和空实现

//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//菜单界面
void Teacher::subMenu()
{
	cout << "欢迎：" << this->m_Name << " 老师登录！" << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "\t\t\t\t|         机房预约系统      |" << endl;
	cout << "\t\t\t\t|---------------------------|" << endl;
	cout << "\t\t\t\t|         1.所有预约        |" << endl;
	cout << "\t\t\t\t|         2.审核预约        |" << endl;
	cout << "\t\t\t\t|         0.退出登录        |" << endl;
	cout << "\t\t\t\t|---------------------------|" << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "请输入您的操作：";
}

//查看所有预约
void Teacher::CheckAllReserv()
{
	ReservationFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << ". ";
		cout << "姓名:" << of.m_ReservData[i]["stuName"];
		cout << " 学号:" << of.m_ReservData[i]["stuId"];
		cout << " 预约日期:周" << of.m_ReservData[i]["date"];
		cout << " 时段:" << (of.m_ReservData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 机房:" << of.m_ReservData[i]["roomId"];
		string status = " 状态:"; // 0:取消的预约 1:审核中 2:已预约 -1:预约失败
		if (of.m_ReservData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_ReservData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_ReservData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

//审核预约
void Teacher::ReviewReserv()
{
	ReservationFile of;
	RestSeats re;
	re.InitRestSeats();

	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	int select;
	int choice;
	int count = 0;
	vector<int> v; // 用来记录临时的编号,储存所有待审核的申请
	cout << "以下申请条目正在等待审核" << endl;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_ReservData[i]["status"] == "1")
		{
			v.push_back(i);
			count++;
			cout << count << ". "; // 这里不能直接count++, 因为它是先赋值再累加的
			cout << "预约日期:周" << of.m_ReservData[i]["date"];
			cout << " 时段:" << (of.m_ReservData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房:" << of.m_ReservData[i]["roomId"];
			cout << " 学号:" << of.m_ReservData[i]["stuId"];
			cout << " 姓名:" << of.m_ReservData[i]["stuName"];
			cout << " 状态: 审核中" << endl; // 0:取消的预约 1:审核中 2:已预约 -1:预约失败
		}
	}

	if (v.size() == 0)
	{
		cout << "空" << endl;
		system("pause");
		system("cls");
		return;
	}

	while (true)
	{
		cout << "请选择你要审核的申请条目, 按0返回：";
		cin >> select;
		if (select < 0 || select > v.size())
		{
			cout << "没有该记录，请重新输入!" << endl;
		}
		else if (select == 0)
		{
			break;
		}
		else
		{
			cout << "1.通过" << endl;
			cout << "2.拒绝" << endl;
			//给出提示消息
			cout << "--------------" << endl;
			string roomId = of.m_ReservData[v[select - 1]]["roomId"]; // "1" "2" "3"
			string date = of.m_ReservData[v[select - 1]]["date"]; // 周 "1" "2" "3" "4" "5"
			string interval = of.m_ReservData[v[select - 1]]["interval"] == "1" ? "Am" : "Pm"; // "1"：上午， "2":下午
			int index = stoi(roomId) - 1;

			if (date == "1") date = "monday";
			else if (date == "2") date = "tuesday";
			else if (date == "3") date = "wednesday";
			else if (date == "4") date = "thursday";
			else date = "friday";

			cout << "No." << roomId << " in the time interval " << date << interval << " has:"
				<< re.mRestSeats[index][date + interval] << " seats left." << endl;

			//判断是否还有剩余位置
			if (re.mRestSeats[index][date + interval] == "0")
			{
				cout << "该机房在该时段下已经没有空位，不可审核。" << endl;
				break;
			}

			while (true)
			{
				cout << "请输入您的选择, 按0返回：";
				cin >> choice;
				if (choice == 1)
				{


					of.m_ReservData[v[select - 1]]["status"] = "2"; // "2":预约成功
					//在这里更新机房剩余位置
					//string roomId = of.m_ReservData[v[select - 1]]["roomId"]; // "1" "2" "3"
					//string date = of.m_ReservData[v[select - 1]]["date"]; // 周 "1" "2" "3" "4" "5"
					//string interval = of.m_ReservData[v[select - 1]]["interval"] == "1" ? "Am" : "Pm"; // "1"：上午， "2":下午

					//if (date == "1") date = "monday";
					//else if (date == "2") date = "tuesday";
					//else if (date == "3") date = "wednesday";
					//else if (date == "4") date = "thursday";
					//else date = "friday";

					//int index = stoi(roomId) - 1;
					//RestSeats re;
					//re.InitRestSeats();
					
					re.mRestSeats[index][date + interval] = to_string(stoi(re.mRestSeats[index][date + interval]) - 1);
					re.UpdateRestSeats();
					cout << "已通过" << endl;
					cout << "No." << roomId << " in the time interval " << date << interval << " has:"
						<< re.mRestSeats[index][date + interval] << " seats left." << endl;
					break;
				}
				else if (choice == 2)
				{
					of.m_ReservData[v[select - 1]]["status"] = "-1"; // "-1":预约失败
					cout << "已拒绝" << endl;
					break;
				}
				else if (choice == 0)
				{
					break;
				}
				else
				{
					cout << "输入有误，请重新输入！" << endl;
				}
			}
			of.UpdateReserv();
			break;
		}
	}

	system("pause");
	system("cls");
}