#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "computerRoom.h"

class Student :public Identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id, string name, string pwd);

	//�˵�����
	virtual void subMenu();//������д�����еĴ��麯��������ʵ��������

	//����ԤԼ
	void ApplyReserv();

	//�鿴�����ԤԼ
	void CheckMyReserv();

	//�鿴����ԤԼ
	void CheckAllReserv();

	//ȡ��ԤԼ
	void CancelReserv();

	//ע����¼
	//void ExitStudent();

	//��ʼ��������Ϣ
	void InitComputerRoom();

	int m_Id;
	vector<ComputerRoom> vCom;
};