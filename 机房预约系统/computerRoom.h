#pragma once
#include <iostream>
using namespace std;
#include <map>
#include <vector>

class ComputerRoom
{
public:
	ComputerRoom();
	ComputerRoom(int id, int num);

	int m_Id;	//��¼������
	int m_Num;	//��¼ÿ������������λ��

	//int m_Size;	//��¼�ж��ٸ�����
	//int m_Rest; //��¼ÿ������ʣ�����λ��
	//vector<ComputerRoom> vComputerHC;	//��¼�����ź�ʣ��λ��
	//map<int, map<string, string>> m_ComputerHC;
};
