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
	void UpdateReserv();	//更新预约记录
	map<string, string> CutString(string type, map<string, string> m_SubData);
	int m_Size;	//记录预约条数
	//记录所有预约信息的容器， key记录条数， value具体记录键值对信息
	map<int, map<string, string>> m_ReservData;

	//这里不用multimap是因为每一条数据在这里不会出现重复的, 因为int记录的是条数
};