#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "computerRoom.h"

class Teacher :public Identity
{
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int empId, string name, string pwd);

	//�˵�����
	virtual void subMenu();

	//�鿴����ԤԼ
	void CheckAllReserv();

	//���ԤԼ
	void ReviewReserv();

	//��ʼ��������Ϣ
	//void 

	int m_EmpId;//��ʦ���
};