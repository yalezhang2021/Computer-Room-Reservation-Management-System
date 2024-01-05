#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"
#include <vector>

class Admin :public Identity
{
public:

	Admin();	//Ĭ�Ϲ���
	Admin(string name, string pwd);	//�вι���
	virtual void subMenu();	//��д���麯��
	void AddAccount();	//����˻�
	void ShowAccount();	//��ʾ�˻�
	void ShowRoomInfo();	//��ʾ������Ϣ
	void CleanReservRecord();	//���ԤԼ��¼
	void InitVector();	//��ʼ������
	bool CheckRepeat(int id, int type);	//����ظ� true: �ظ���
	void InitComputerRoom();	//��ʼ��������Ϣ
	//void PrintInfo(int val);	//��ӡѧ������ʦ��������Ϣ

	vector<Student> vStu;	//ѧ������
	vector<Teacher> vTea;	//��ʦ����
	vector<ComputerRoom> vCom;	//������Ϣ
};