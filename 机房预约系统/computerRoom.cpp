#include "computerRoom.h"
#include "globalFile.h"
#include <fstream>
#include "student.h"
#include <fstream>

//map<string, string> CutString(string type, map<string, string> m_SubData)
//{
//	string key;
//	string value;
//	int pos = type.find(":");
//	if (pos != -1)	//如果不存在的话，会返回-1
//	{
//		key = type.substr(0, pos);
//		value = type.substr(pos + 1, type.size() - pos - 1);
//		m_SubData.insert(make_pair(key, value));
//		return m_SubData;
//	}
//}


ComputerRoom::ComputerRoom()
{
	//ifstream ifs;
	//ifs.open(UPDATEHEADCOUNT_FILE, ios::in);

	//if (!ifs.is_open())
	//{
	//	cout << "文件打开失败" << endl;
	//	return;
	//}

	//string mondayAm;
	//string mondayPm;
	//string tuesdayAm;
	//string tuesdayPm;
	//string wednesdayAm;
	//string wednesdayPm;
	//string thursdayAm;
	//string thursdayPm;
	//string fridayAm;
	//string fridayPm;

	//this->m_Size = 0;	//记录条数

	//while (ifs >> mondayAm && ifs >> mondayPm && ifs >> tuesdayAm && ifs >> tuesdayPm && ifs >> wednesdayAm
	//	&& ifs >> wednesdayPm && ifs >> thursdayAm && ifs >> thursdayPm && ifs >> fridayAm && ifs >> fridayPm)
	//{
	//	//最终的结构应该是:
	//	//map<int, map<string, string>>
	//	//mondayAm:20 mondayPm:30 tuesdayAm:30 tuesdayPm:40 wednesdayAm:10 wednesdayPm:0 thursdayAm:0 thursdayPm:50 fridayAm:50 fridayPm:50
	//	map<string, string> m_SubData;

	//	m_SubData = CutString(mondayAm, m_SubData);
	//	m_SubData = CutString(mondayPm, m_SubData);
	//	m_SubData = CutString(tuesdayAm, m_SubData);
	//	m_SubData = CutString(tuesdayPm, m_SubData);
	//	m_SubData = CutString(wednesdayAm, m_SubData);
	//	m_SubData = CutString(wednesdayPm, m_SubData);
	//	m_SubData = CutString(thursdayAm, m_SubData);
	//	m_SubData = CutString(thursdayPm, m_SubData);
	//	m_SubData = CutString(fridayAm, m_SubData);
	//	m_SubData = CutString(fridayPm, m_SubData);

	//	this->m_ComputerHC.insert(make_pair(this->m_Size, m_SubData));
	//	this->m_Size++;
	//}
	//ifs.close();

	////test m_ReservData
	////注意，这里的输出顺序和插入顺序不一样，是因为map容器，所有元素都会根据元素的key值自动排序。
	//for (map<int, map<string, string>>::iterator it = m_ComputerHC.begin();
	//	it != m_ComputerHC.end(); it++)
	//{
	//	cout << "条数：" << it->first << ", value: " << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << "key: " << mit->first << ", value: " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

ComputerRoom::ComputerRoom(int id, int num)
{
	this->m_Id = id;
	this->m_Num = num;
}

////更新预约记录
//void ComputerRoom::UpdateHCInfo()
//{
//	ofstream ofs;
//	ofs.open(UPDATEHEADCOUNT_FILE, ios::out | ios::trunc);
//
//	if (!ofs.is_open())
//	{
//		cout << "unable to open student file" << endl;
//		return;
//	}
//
//	if (this->m_Size == 0)
//	{
//		return;
//	}
//
//	for (int i = 0; i < m_Size; i++)
//	{
//		ofs << vComputerHC[i].m_Id << " " << vComputerHC[i].m_Num << endl;
//	}
//
//	//cout << "当前的机房数量为：" << vCom.size() << endl;
//	ofs.close();
//}