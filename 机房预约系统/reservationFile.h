#pragma once
#include <iostream>
using namespace std;
#include "globalFile.h"
#include <fstream>
#include <map>
#include <string>

class ReservationFile
{
public:
	ReservationFile();
	void UpdateReserv();	//����ԤԼ��¼
	map<string, string> CutString(string type, map<string, string> m_SubData);
	int m_Size;	//��¼ԤԼ����
	//��¼����ԤԼ��Ϣ�������� key��¼������ value�����¼��ֵ����Ϣ
	map<int, map<string, string>> m_ReservData;

	//���ﲻ��multimap����Ϊÿһ�����������ﲻ������ظ���, ��Ϊint��¼��������
};