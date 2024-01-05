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
	//cout << "欢迎：" << this->m_Name << " 老师登录！" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "\t\t\t\t|         机房预约系统      |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t|         1.所有预约        |" << endl;
	//cout << "\t\t\t\t|         2.审核预约        |" << endl;
	//cout << "\t\t\t\t|         0.退出登录        |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "请输入您的操作：";

	cout << "Welcome Teacher：" << this->m_Name << " Login！" << endl;
	cout << "\t\t\t\t-----------------------------------" << endl;
	cout << "\t\t\t\t|         Reservation System      |" << endl;
	cout << "\t\t\t\t|---------------------------------|" << endl;
	cout << "\t\t\t\t|         1.Show All Reservations |" << endl;
	cout << "\t\t\t\t|         2.Review Reservations   |" << endl;
	cout << "\t\t\t\t|         0.Exit                  |" << endl;
	cout << "\t\t\t\t|---------------------------------|" << endl;
	cout << "\t\t\t\t-----------------------------------" << endl;
	cout << "Please enter：";
}

//查看所有预约
void Teacher::CheckAllReserv()
{
	ReservationFile of;
	if (of.m_Size == 0)
	{
		cout << "No reservation record!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << ". ";
		cout << "Name:" << of.m_ReservData[i]["stuName"];
		cout << " StuId:" << of.m_ReservData[i]["stuId"];
		string dDate = "Date:";// << of.m_ReservData[i]["date"];
		if (of.m_ReservData[i]["date"] == "1") dDate += "Monday";
		if (of.m_ReservData[i]["date"] == "2") dDate += "Tuesday";
		if (of.m_ReservData[i]["date"] == "3") dDate += "Wednesday";
		if (of.m_ReservData[i]["date"] == "4") dDate += "Thursday";
		if (of.m_ReservData[i]["date"] == "5") dDate += "Friday";
		cout << dDate;
		cout << " Interval:" << (of.m_ReservData[i]["interval"] == "1" ? "Morning" : "Afternoon");
		cout << " RoomNo.:" << of.m_ReservData[i]["roomId"];
		string status = " Status:"; // 0:取消的预约 1:审核中 2:已预约 -1:预约失败
		if (of.m_ReservData[i]["status"] == "1")
		{
			status += "under review";
		}
		else if (of.m_ReservData[i]["status"] == "2")
		{
			status += "successful";
		}
		else if (of.m_ReservData[i]["status"] == "-1")
		{
			status += "failed";
		}
		else
		{
			status += "is canceld";
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
		cout << "No Record" << endl;
		system("pause");
		system("cls");
		return;
	}

	int select;
	int choice;
	int count = 0;
	vector<int> v; // 用来记录临时的编号,储存所有待审核的申请
	cout << "The under Applyings are waiting for review:" << endl;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_ReservData[i]["status"] == "1")
		{
			v.push_back(i);
			count++;
			cout << count << ". "; // 这里不能直接count++, 因为它是先赋值再累加的
			string dDate = "Date:";// << of.m_ReservData[i]["date"];
			if (of.m_ReservData[i]["date"] == "1") dDate += "Monday";
			if (of.m_ReservData[i]["date"] == "2") dDate += "Tuesday";
			if (of.m_ReservData[i]["date"] == "3") dDate += "Wednesday";
			if (of.m_ReservData[i]["date"] == "4") dDate += "Thursday";
			if (of.m_ReservData[i]["date"] == "5") dDate += "Friday";
			cout << dDate;
			cout << " Interval:" << (of.m_ReservData[i]["interval"] == "1" ? "Morning" : "Afternoon");
			cout << " RoomID:" << of.m_ReservData[i]["roomId"];
			cout << " StuID:" << of.m_ReservData[i]["stuId"];
			cout << " Name:" << of.m_ReservData[i]["stuName"];
			cout << " Status: Under review" << endl; // 0:取消的预约 1:审核中 2:已预约 -1:预约失败
		}
	}

	if (v.size() == 0)
	{
		cout << "Empty" << endl;
		system("pause");
		system("cls");
		return;
	}

	while (true)
	{
		cout << "Please select the application you want to review, press 0 to return.：";
		cin >> select;
		if (select < 0 || select > v.size())
		{
			cout << "This record is not existed, please reenter!" << endl;
		}
		else if (select == 0)
		{
			break;
		}
		else
		{
			cout << "1.Pass" << endl;
			cout << "2.Reject" << endl;
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
				//cout << "该机房在该时段下已经没有空位，不可审核。" << endl;
				cout << "There is no more seats at this time interval, can not review." << endl;
				break;
			}

			while (true)
			{
				//cout << "请输入您的选择, 按0返回：";
				cout << "please enter your choice, press 0 to return:";
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
					cout << "Passed" << endl;
					cout << "No." << roomId << " in the time interval " << date << interval << " has:"
						<< re.mRestSeats[index][date + interval] << " seats left." << endl;
					break;
				}
				else if (choice == 2)
				{
					of.m_ReservData[v[select - 1]]["status"] = "-1"; // "-1":预约失败
					cout << "Rejected" << endl;
					break;
				}
				else if (choice == 0)
				{
					break;
				}
				else
				{
					//cout << "输入有误，请重新输入！" << endl;
					cout << "The input is wrong, please reenter." << endl;
				}
			}
			of.UpdateReserv();
			break;
		}
	}

	system("pause");
	system("cls");
}