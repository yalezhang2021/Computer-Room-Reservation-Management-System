#include "student.h"
#include <fstream>
#include "globalFile.h"
#include "reservationFile.h"
#include <map>
#include "computerRoom.h"
#include "restSeats.h"

//���Ϻ�����������Ϳ�ʵ��

//Ĭ�Ϲ���
Student::Student()
{

}

//�вι���
Student::Student(int id, string name, string pwd)
{
	//��ʼ������
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	this->InitComputerRoom();
}

//�˵�����
void Student::subMenu()
{
	//cout << "��ӭѧ����" << this->m_Name << " ��¼��" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "\t\t\t\t|         ����ԤԼϵͳ      |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t|         1.����ԤԼ        |" << endl;
	//cout << "\t\t\t\t|         2.�ҵ�ԤԼ        |" << endl;
	//cout << "\t\t\t\t|         3.����ԤԼ        |" << endl;
	//cout << "\t\t\t\t|         4.ȡ��ԤԼ        |" << endl;
	//cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "���������Ĳ�����";

	cout << "Welcome student��" << this->m_Name << " login��" << endl;
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
	cout << "Please enter��";
}

//����ԤԼ
void Student::ApplyReserv()
{
	RestSeats re;
	re.InitRestSeats();

	int date, interval, roomId;
	//cout << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "\t\t\t\t1. ��һ\n";
	//cout << "\t\t\t\t2. �ܶ�\n";
	//cout << "\t\t\t\t3. ����\n";
	//cout << "\t\t\t\t4. ����\n";
	//cout << "\t\t\t\t5. ����\n";
	//cout << "��ѡ������:" << endl;
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
		cout << "The input is wrong��please reenter��";
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
		cout << "The input is wrong��please reenter��";
	}

	cout << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		//�жϻ���i�ڸ�ʱ����ʣ���λ������
		string sDate;
		string sInterval = interval == 1 ? "Am" : "Pm"; // 1�����磬 2:����

		if (date == 1) sDate = "monday";
		else if (date == 2) sDate = "tuesday";
		else if (date == 3) sDate = "wednesday";
		else if (date == 4) sDate = "thursday";
		else sDate = "friday";

		cout << "\t\t\t\tRoomNo.:" << vCom[i].m_Id << ", Max Seats��" << vCom[i].m_Num << ", Left Seats��" 
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
		cout << "The input is wrong��please reenter��";
	}

	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "Appointment successful��under review..." << endl;
	//cout << "ԤԼ��¼���£�" << endl;
	//cout << "ѧ��:" << this->m_Id << " "
	//	<< "����:" << this->m_Name << " "
	//	<< "����:" << date << " "
	//	<< "ʱ��:" << interval << " "
	//	<< "����:" << roomNum << " "
	//	<< "״̬:" << 1 << endl;	// 1�������

	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::app);
	ofs << "stuId:" << this->m_Id << " "
		<< "stuName:" << this->m_Name << " "
		<< "date:" << date << " "
		<< "interval:" << interval << " "
		<< "roomId:" << roomId << " "
		<< "status:" << 1 << endl;	// 1�������
	ofs.close();
	system("pause");
	system("cls");
}

//�鿴�ҵ�ԤԼ
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
			string status = " Status:"; // 0:ȡ����ԤԼ 1:����� 2:��ԤԼ -1:ԤԼʧ��
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

//�鿴����ԤԼ
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
		string status = " Status:"; // 0:ȡ����ԤԼ 1:����� 2:��ԤԼ -1:ԤԼʧ��
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

//ȡ��ԤԼ
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
			string status = " Status:"; // 0:ȡ����ԤԼ 1:����� 2:��ԤԼ -1:ԤԼʧ��
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
		cout << "Select the appointment you want to cancel, press 0 to return.��" << endl;
		cin >> select;
		if (select < 0 || select > myRecord.size())
		{
			cout << "This record is not exist��please reenter!" << endl;
		}			
		else if (select == 0)
		{
			system("cls");
			return;
		}
		else
		{
			if (of.m_ReservData[myRecord[select - 1]]["status"] == "2") //�����
			{
				//����һ�¸û���ʣ���λ��
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
				rest.InitRestSeats(); //ֱ�ӷ��ڹ��캯���ﲻ����
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

//��ʼ��������Ϣ
void Student::InitComputerRoom()
{
	vCom.clear();

	//��һ������ȡupdate�Ǹ��ļ�������Ǹ��ļ������Ҳ�Ϊ�գ���ֱ����update���ļ���ʼ��������Ϣ
	//��������ڻ���Ϊ�յ�ʱ�����������COMPUTER_FILE����ʼ��
	//���Ǽ�¼һ��COMPUTER_FILE���ȡ�Ļ����������
	//update�ļ����¼�ĸ�������ʣ�����λ��

	ifstream ifs;

	ifs.open(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "unable to open student file" << endl;
		return;
	}

	ComputerRoom c; //��������Ϣ��ֱ�Ӷ���ȥ�ģ������m_Id, m_Num��ͨ���ļ��������ֱ��д��ȥ��
	while (ifs >> c.m_Id && ifs >> c.m_Num)
	{
		vCom.push_back(c);
	}

	//cout << "��ǰ�Ļ�������Ϊ��" << vCom.size() << endl;
	ifs.close();
}