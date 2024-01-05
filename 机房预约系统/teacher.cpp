#include "teacher.h"
#include "reservationFile.h"
#include <vector>
#include "computerRoom.h"
#include "restSeats.h"

//���Ϻ�����������Ϳ�ʵ��

//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι���
Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

//�˵�����
void Teacher::subMenu()
{
	//cout << "��ӭ��" << this->m_Name << " ��ʦ��¼��" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "\t\t\t\t|         ����ԤԼϵͳ      |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t|         1.����ԤԼ        |" << endl;
	//cout << "\t\t\t\t|         2.���ԤԼ        |" << endl;
	//cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
	//cout << "\t\t\t\t|---------------------------|" << endl;
	//cout << "\t\t\t\t-----------------------------" << endl;
	//cout << "���������Ĳ�����";

	cout << "Welcome Teacher��" << this->m_Name << " Login��" << endl;
	cout << "\t\t\t\t-----------------------------------" << endl;
	cout << "\t\t\t\t|         Reservation System      |" << endl;
	cout << "\t\t\t\t|---------------------------------|" << endl;
	cout << "\t\t\t\t|         1.Show All Reservations |" << endl;
	cout << "\t\t\t\t|         2.Review Reservations   |" << endl;
	cout << "\t\t\t\t|         0.Exit                  |" << endl;
	cout << "\t\t\t\t|---------------------------------|" << endl;
	cout << "\t\t\t\t-----------------------------------" << endl;
	cout << "Please enter��";
}

//�鿴����ԤԼ
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

//���ԤԼ
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
	vector<int> v; // ������¼��ʱ�ı��,�������д���˵�����
	cout << "The under Applyings are waiting for review:" << endl;
	for (int i = 0; i < of.m_Size; i++)
	{
		if (of.m_ReservData[i]["status"] == "1")
		{
			v.push_back(i);
			count++;
			cout << count << ". "; // ���ﲻ��ֱ��count++, ��Ϊ�����ȸ�ֵ���ۼӵ�
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
			cout << " Status: Under review" << endl; // 0:ȡ����ԤԼ 1:����� 2:��ԤԼ -1:ԤԼʧ��
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
		cout << "Please select the application you want to review, press 0 to return.��";
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
			//������ʾ��Ϣ
			cout << "--------------" << endl;
			string roomId = of.m_ReservData[v[select - 1]]["roomId"]; // "1" "2" "3"
			string date = of.m_ReservData[v[select - 1]]["date"]; // �� "1" "2" "3" "4" "5"
			string interval = of.m_ReservData[v[select - 1]]["interval"] == "1" ? "Am" : "Pm"; // "1"�����磬 "2":����
			int index = stoi(roomId) - 1;

			if (date == "1") date = "monday";
			else if (date == "2") date = "tuesday";
			else if (date == "3") date = "wednesday";
			else if (date == "4") date = "thursday";
			else date = "friday";

			cout << "No." << roomId << " in the time interval " << date << interval << " has:"
				<< re.mRestSeats[index][date + interval] << " seats left." << endl;

			//�ж��Ƿ���ʣ��λ��
			if (re.mRestSeats[index][date + interval] == "0")
			{
				//cout << "�û����ڸ�ʱ�����Ѿ�û�п�λ��������ˡ�" << endl;
				cout << "There is no more seats at this time interval, can not review." << endl;
				break;
			}

			while (true)
			{
				//cout << "����������ѡ��, ��0���أ�";
				cout << "please enter your choice, press 0 to return:";
				cin >> choice;
				if (choice == 1)
				{


					of.m_ReservData[v[select - 1]]["status"] = "2"; // "2":ԤԼ�ɹ�
					//��������»���ʣ��λ��
					//string roomId = of.m_ReservData[v[select - 1]]["roomId"]; // "1" "2" "3"
					//string date = of.m_ReservData[v[select - 1]]["date"]; // �� "1" "2" "3" "4" "5"
					//string interval = of.m_ReservData[v[select - 1]]["interval"] == "1" ? "Am" : "Pm"; // "1"�����磬 "2":����

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
					of.m_ReservData[v[select - 1]]["status"] = "-1"; // "-1":ԤԼʧ��
					cout << "Rejected" << endl;
					break;
				}
				else if (choice == 0)
				{
					break;
				}
				else
				{
					//cout << "�����������������룡" << endl;
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