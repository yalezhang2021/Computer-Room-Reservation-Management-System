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

//�������Ա�Ӳ˵�����
void AdminMenu(Identity*& admin) //ͨ������ָ�봫����, ����ָ�봴���������
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		admin->subMenu();//���麯��ʵ����
		

		//������ָ��תΪ����ָ�룬�����������������нӿ�
		Admin* adm = (Admin*)admin;//ǿ��ת������ΪAdmin*
		//adm->InitVector();

		int select = 0;
		//�����û�ѡ��
		cin >> select;

		if (select == 1) //����˺�
		{
			//cout << "����˺�" << endl;
			adm->AddAccount();
		}
		else if (select == 2) //�鿴�˺�
		{
			//cout << "�鿴�˺�" << endl;
			adm->ShowAccount();
		}
		else if (select == 3) //�鿴����
		{
			//cout << "�鿴����" << endl;
			adm->ShowRoomInfo();
		}
		else if (select == 4) //���ԤԼ
		{
			//cout << "���ԤԼ" << endl;
			adm->CleanReservRecord();
		}
		else
		{ 
			delete admin; //���ٵ���������
			cout << "Logout successful" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//����ѧ���Ӳ˵�����
void StudentMenu(Identity*& student) //ͨ������ָ�봫����, ����ָ�봴���������
{
	while (true)
	{
		//����ѧ���Ӳ˵�
		student->subMenu();//���麯��ʵ����
		//������ָ��תΪ����ָ�룬�����������������нӿ�
		Student* stu = (Student*)student;//ǿ��ת������ΪAdmin*

		int select;
		//�����û�ѡ��
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
			delete student; //���ٵ���������
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

//������ʦ�Ӳ˵�����
void TeacherMenu(Identity*& teacher) //ͨ������ָ�봫����, ����ָ�봴���������
{
	while (true)
	{
		//����laoshi �Ӳ˵�
		teacher->subMenu();//���麯��ʵ����
		//������ָ��תΪ����ָ�룬�����������������нӿ�
		Teacher* tea = (Teacher*)teacher;//ǿ��ת������ΪAdmin*

		int select;
		//�����û�ѡ��
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
			delete teacher; //���ٵ���������
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

//��¼����
void LoginIn(string fileName, int type)
{
	//fileName: �����ļ����� type: �����������
	//����ָ�룬 ����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "File is not existed" << endl;
		ifs.close();
		return;
	}

	//�ж��ļ��Ƿ�Ϊ��
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

	//׼�������û�����Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type == 1)
	{
		cout << "Enter your StuID��" << endl;
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
		//ѧ�������֤
		int fId; //���ļ��ж�ȡ��id��
		string fName; //���ļ��ж�ȡ������
		string fPwd; //���ļ��ж�ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPwd) //ÿ�������ո���оͻ������ȡ
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "Student Verification Login Successful��" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				//����ѧ����ݵ��Ӳ˵�
				StudentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId; //���ļ��ж�ȡ��id��
		string fName; //���ļ��ж�ȡ������
		string fPwd; //���ļ��ж�ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPwd) //ÿ�������ո���оͻ������ȡ
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "Teacher Verification Login Successful��" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//�����ʦ��ݵ��Ӳ˵�
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName; //���ļ��ж�ȡ������
		string fPwd; //���ļ��ж�ȡ������

		while (ifs >> fName && ifs >> fPwd) //ÿ�������ո���оͻ������ȡ
		{
			if (fName == name && fPwd == pwd)
			{
				cout << "Admin Verification Login successful��" << endl;
				//��¼�ɹ��󣬰�������������Ա����
				system("pause");
				system("cls");

				person = new Admin(name, pwd);
				//�������Ա��ݵ��Ӳ˵�
				AdminMenu(person);
				return;
			}
		}
	}

	cout << "Authentication Login Failed��" << endl;
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
		//cout << "\t\t\t\t|         ����ԤԼϵͳ      |" << endl;
		//cout << "\t\t\t\t|---------------------------|" << endl;
		//cout << "\t\t\t\t|         1.ѧ����¼        |" << endl;
		//cout << "\t\t\t\t|         2.��ʦ��¼        |" << endl;
		//cout << "\t\t\t\t|         3.����Ա��¼      |" << endl;
		//cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
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

		cout << "Please enter��" << endl;
		cin >> select;

		switch (select)
		{
		case 0://�˳�ϵͳ
			cout << "Thank you��bye��" << endl;
			system("pause");
			return 0;
			break;
		case 1://ѧ����¼
			LoginIn(STUDENT_FILE, 1);
			//Student stt;
			//����ԤԼ
			//stt.ApplyReserv();
			//�鿴�����ԤԼ
			//stt.CheckMyReserv();
			//�鿴����ԤԼ
			//stt.CheckAllReserv();
			//ȡ��ԤԼ
			//stt.CancelReserv();
			//ע����¼
			//stt.ExitStudent();
			break;
		case 2://��ʦ��¼
			LoginIn(TEACHER_FILE, 2);
			//sm.TeacherLogin();
			break;
		case 3://����Ա��¼
			LoginIn(ADMIN_FILE, 3);
			//sm.AdminLogin();
			break;
		default:
			cout << "The input is wrong, please reenter��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}