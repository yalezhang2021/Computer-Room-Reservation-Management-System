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

	int m_Id;	//记录机房号
	int m_Num;	//记录每个机房最多多少位置

	//int m_Size;	//记录有多少个机房
	//int m_Rest; //记录每个机房剩余多少位置
	//vector<ComputerRoom> vComputerHC;	//记录机房号和剩余位置
	//map<int, map<string, string>> m_ComputerHC;
};
