#pragma once //��ֹͷ�ļ��ظ�����
#include <iostream>
using namespace std;

//��ݳ�����
class Identity
{
public:

	//�����˵� ,��̬������д�Ӳ˵�����������ӿڣ�֮����Ը����������
	virtual void subMenu() = 0; //�������麯��

	//ѧ������ʦ�͹���Ա���еĹ��Ծ����û���������,��������������д��������
	string m_Name; //�û���
	string m_Pwd;  //����
};