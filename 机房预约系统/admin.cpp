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
	//��ʼ������Ա��Ϣ
	this->m_Name = name;
	this->m_Pwd = name;

	//��ʼ������ ��ȡ�����ļ��� ��ʦ ѧ������Ϣ
	this->InitVector();
	this->InitComputerRoom();
}

void Admin::subMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << " ��¼��" << endl;
	cout << "\t\t\t\t-----------------------------\n";
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "\t\t\t\t|       ����Ա����ԤԼϵͳ   |" << endl;
	cout << "\t\t\t\t|---------------------------|" << endl;
	cout << "\t\t\t\t|         1.����˺�        |" << endl;
	cout << "\t\t\t\t|         2.�鿴�˺�        |" << endl;
	cout << "\t\t\t\t|         3.�鿴����        |" << endl;
	cout << "\t\t\t\t|         4.���ԤԼ        |" << endl;
	cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
	cout << "\t\t\t\t|---------------------------|" << endl;
	cout << "\t\t\t\t-----------------------------" << endl;
	cout << "���������Ĳ�����" << endl;
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
		cout << "����������˺ŵ�����" << endl;
		cout << "1.���ѧ���˺�" << endl;
		cout << "2.�����ʦ�˺�" << endl;
		cout << "0.����" << endl;
		cout << endl;
		cout << "���������Ĳ�����" << endl;

		int select = 0;
		cin >> select;
		type = select;

		if (select == 0)
		{
			cout << "����" << endl;
			system("pause");
			system("cls");
			return;
		}
		else if (select == 1)
		{
			//���ѧ���˺�
			fileName = STUDENT_FILE;
			tip = "������ѧ�ţ�";
			errorTip = "��ѧ���˺��Ѵ��ڣ�����������:";
			break;
		}
		else if (select == 2)
		{
			//�����ʦ�˺�
			fileName = TEACHER_FILE;
			tip = "������ְ����ţ�";
			errorTip = "�ý�ʦ����Ѵ��ڣ�����������:";
			break;
		}
		else
		{
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	ofs.open(fileName, ios::out | ios::app); //д���ļ���׷��д��

	int id;
	string name;
	string pwd;

	cout << tip << endl;

	//�ж��Ƿ��ظ�
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

	cout << "������������" << endl;
	cin >> name;

	cout << "����������: " << endl;
	cin >> pwd;

	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;

	cout << "��ӳɹ���" << endl;

	system("pause");
	system("cls");
	ofs.close();

	//���������ϳ�ʼ�������ӿڣ����»�ȡ�ļ��е�����
	this->InitVector();
}

void PrintStudent(Student& s)
{
	cout << "ѧ���˺ţ� " << s.m_Id << ", ������" << s.m_Name << ", ���룺" << s.m_Pwd << endl;
}

void PrintTeacher(Teacher& t)
{
	cout << "��ʦ�˺ţ� " << t.m_EmpId << ", ������" << t.m_Name << ", ����" << t.m_Pwd << endl;
}

void Admin::ShowAccount()
{
	cout << endl;
	cout << "1. �鿴����ѧ��" << endl;
	cout << "2. �鿴������ʦ" << endl;
	cout << "��ѡ��鿴���ݣ�";
	int select;
	cin >> select;
	cout << endl;
	
	if (select == 1)
	{
		//for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		//{
		//	cout << "ѧ���˺ţ� " << it->m_Id << ", ������" << it->m_Name << endl;
		//}

		//����Ŀ�����for_each��������������
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), PrintStudent);
		cout << endl;
	}
	else if (select == 2)
	{
		//vector<Teacher>v;
		//for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		//{
		//	cout << "��ʦ�˺ţ� " << it->m_EmpId << ", ������" << it->m_Name << endl;
		//}

		//����Ŀ�����for_each��������������
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), PrintTeacher);
		cout << endl;
	}
	else
	{
		cout << "�����������������룡" << endl;
	}

	system("pause");
	system("cls");
}

void Admin::ShowRoomInfo()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "�����ţ�" << it->m_Id << ", �������:" << it->m_Num << endl;
	}
	
	system("pause");
	system("cls");
}

void Admin::CleanReservRecord()
{
	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::trunc);
	ofs.close();

	cout << "����ԤԼ��¼����գ�" << endl;
	system("pause");
	system("cls");
}

void Admin::InitVector()
{
	vStu.clear();
	vTea.clear();

	//��ȡ��Ϣ
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

	//cout << "��ǰ��ѧ������Ϊ��" << vStu.size() << endl;
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

	//cout << "��ǰ����ʦ����Ϊ��" << vTea.size() << endl;
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

	//cout << "��ǰ�Ļ�������Ϊ��" << vCom.size() << endl;
	ifs.close();
}