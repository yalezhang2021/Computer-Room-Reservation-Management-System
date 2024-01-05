#include "student.h"
#include <fstream>
#include "globalFile.h"
#include "reservationFile.h"
#include <map>
#include "computerRoom.h"
#include "restSeats.h"

//加上函数的作用域和空实现

//默认构造
Student::Student()
{

}

//有参构造
Student::Student(int id, string name, string pwd)
{
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->InitComputerRoom();
}

//菜单界面
void Student::subMenu()
{
	//cout << "欢迎学生：" << this->m_Name << " 登录！" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "\t\t\t\t|         机房预约系统      |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t|         1.申请预约        |" << endl;
	//cout << "\t\t\t\t|         2.我的预约        |" << endl;
	//cout << "\t\t\t\t|         3.所有预约        |" << endl;
	//cout << "\t\t\t\t|         4.取消预约        |" << endl;
	//cout << "\t\t\t\t|         0.退出登录        |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "请输入您的操作：";

	cout << "Welcome student：" << this->m_Name << " login！" << endl;
	cout << "\t\t\t\t------------------------------------" << endl;
	cout << "\t\t\t\t|         Reservation System       |" << endl;
	cout << "\t\t\t\t|----------------------------------|" << endl;
	cout << "\t\t\t\t|         1.Apply Reservation      |" << endl;
	cout << "\t\t\t\t|         2.Show My Reservations   |" << endl;
	cout << "\t\t\t\t|         3.Show All Reservations  |" << endl;
	cout << "\t\t\t\t|         4.Cancel Reservation     |" << endl;
	cout << "\t\t\t\t|         0.Exit                   |" << endl;
	cout << "\t\t\t\t|----------------------------------|" << endl;
	cout << "\t\t\t\t------------------------------------" << endl;
	cout << "Please enter：";
}

//申请预约
void Student::ApplyReserv()
{
	RestSeats re;
	re.InitRestSeats();

	int date, interval, roomId;
	//cout << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "\t\t\t\t1. 周一\n";
	//cout << "\t\t\t\t2. 周二\n";
	//cout << "\t\t\t\t3. 周三\n";
	//cout << "\t\t\t\t4. 周四\n";
	//cout << "\t\t\t\t5. 周五\n";
	//cout << "请选择日期:" << endl;
	//cout << endl;

	cout << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "\t\t\t\t1. Monday\n";
	cout << "\t\t\t\t2. Tuesday\n";
	cout << "\t\t\t\t3. Wednesday\n";
	cout << "\t\t\t\t4. Thursday\n";
	cout << "\t\t\t\t5. Friday\n";
	cout << "Please choose date:" << endl;
	cout << endl;

	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "The input is wrong，please reenter：";
	}

	cout << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "\t\t\t\t1. Morning\n";
	cout << "\t\t\t\t2. Afternoon\n";
	cout << "Please choose interval:" << endl;
	cout << endl;

	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		cout << "The input is wrong，please reenter：";
	}

	cout << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		//判断机房i在该时段下剩余的位置数量
		string sDate;
		string sInterval = interval == 1 ? "Am" : "Pm"; // 1：上午， 2:下午

		if (date == 1) sDate = "monday";
		else if (date == 2) sDate = "tuesday";
		else if (date == 3) sDate = "wednesday";
		else if (date == 4) sDate = "thursday";
		else sDate = "friday";

		cout << "\t\t\t\tRoomNo.:" << vCom[i].m_Id << ", Max Seats：" << vCom[i].m_Num << ", Left Seats：" 
			<< re.mRestSeats[i][sDate + sInterval] << endl;
	}
	cout << "Please select Room NO.:";
	cout << endl;

	while (true)
	{
		cin >> roomId;
		if (roomId >= 1 && roomId <= 3)
		{
			break;
		}
		cout << "The input is wrong，please reenter：";
	}

	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "Appointment successful！under review..." << endl;
	//cout << "预约记录如下：" << endl;
	//cout << "学号:" << this->m_Id << " "
	//	<< "姓名:" << this->m_Name << " "
	//	<< "日期:" << date << " "
	//	<< "时段:" << interval << " "
	//	<< "机房:" << roomNum << " "
	//	<< "状态:" << 1 << endl;	// 1：审核中

	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::app);
	ofs << "stuId:" << this->m_Id << " "
		<< "stuName:" << this->m_Name << " "
		<< "date:" << date << " "
		<< "interval:" << interval << " "
		<< "roomId:" << roomId << " "
		<< "status:" << 1 << endl;	// 1：审核中
	ofs.close();
	system("pause");
	system("cls");
}

//查看我的预约
void Student::CheckMyReserv()
{
	ReservationFile of;
	if (of.m_Size == 0)
	{
		cout << "No Record" << endl;
		system("pause");
		system("cls");
		return;
	}

	int count = 0;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (stoi(of.m_ReservData[i]["stuId"]) == this->m_Id)
		{
			count++;
			cout << count << ". ";
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
	}

	if (count == 0)
	{
		cout << "You have no reservation right now" << endl;
		system("pause");
		system("cls");
		return;
	}

	system("pause");
	system("cls");
}

//查看所有预约
void Student::CheckAllReserv()
{
	ReservationFile of;
	if (of.m_Size == 0)
	{
		cout << "No Record" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << ". "; 
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

//取消预约
void Student::CancelReserv()
{
	ReservationFile of;

	if (of.m_Size == 0)
	{
		cout << "No Record" << endl;
		system("pause");
		system("cls");
		return;
	}

	int select;
	int count = 0;
	vector<int> myRecord;
	cout << "Records under review or successful appointments can be canceled" << endl;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (stoi(of.m_ReservData[i]["stuId"]) == this->m_Id
			&& (of.m_ReservData[i]["status"] == "1" || of.m_ReservData[i]["status"] == "2"))
		{
			myRecord.push_back(i);
			count++;
			cout << count << ". ";
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
	}

	if (myRecord.size() == 0)
	{
		cout << "You currently have no records of successful appointments or reviews~" << endl;
		system("pause");
		system("cls");
		return;
	}

	while (true)
	{
		cout << "Select the appointment you want to cancel, press 0 to return.：" << endl;
		cin >> select;
		if (select < 0 || select > myRecord.size())
		{
			cout << "This record is not exist，please reenter!" << endl;
		}			
		else if (select == 0)
		{
			system("cls");
			return;
		}
		else
		{
			if (of.m_ReservData[myRecord[select - 1]]["status"] == "2") //审核中
			{
				//更新一下该机房剩余的位置
				string date = of.m_ReservData[myRecord[select - 1]]["date"]; // "1" "2" "3" "4" "5"
				string interval = of.m_ReservData[myRecord[select - 1]]["interval"] == "1" ? "Am" : "Pm"; // "1" "2"
				string roomId = of.m_ReservData[myRecord[select - 1]]["roomId"]; // "1" "2" "3"
				int index = stoi(roomId) - 1;

				if (date == "1") date = "monday";
				else if (date == "2") date = "tuesday";
				else if (date == "3") date = "wednesday";
				else if (date == "4") date = "thursday";
				else date = "friday";

				RestSeats rest;
				rest.InitRestSeats(); //直接放在构造函数里不好吗
				rest.mRestSeats[index][date + interval] = to_string(stoi(rest.mRestSeats[index][date + interval]) + 1);
				rest.UpdateRestSeats();
			}

			of.m_ReservData[myRecord[select - 1]]["status"] = "0";
			of.UpdateReserv();
			cout << "The No." << select << " appointment is canceld" << endl;
			break;
		}
	}

	system("pause");
	system("cls");
}

//初始化机房信息
void Student::InitComputerRoom()
{
	vCom.clear();

	//加一个，读取update那个文件，如果那个文件存在且不为空，则直接用update的文件初始化机房信息
	//如果不存在或者为空的时候，再用下面的COMPUTER_FILE来初始化
	//但是记录一下COMPUTER_FILE里读取的机房最大容量
	//update文件里记录哪个机房和剩余多少位置

	ifstream ifs;

	ifs.open(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "unable to open student file" << endl;
		return;
	}

	ComputerRoom c; //机房的信息是直接都进去的，这里的m_Id, m_Num是通过文件里的数字直接写进去的
	while (ifs >> c.m_Id && ifs >> c.m_Num)
	{
		vCom.push_back(c);
	}

	//cout << "当前的机房数量为：" << vCom.size() << endl;
	ifs.close();
}