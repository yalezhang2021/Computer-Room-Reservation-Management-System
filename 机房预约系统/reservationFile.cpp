#include "reservationFile.h"
#include <vector>

map<string, string> ReservationFile::CutString(string type, map<string, string> m_SubData)
{
	string key;
	string value;
	int pos = type.find(":");
	if (pos != -1)	//如果不存在的话，会返回-1
	{
		key = type.substr(0, pos);
		value = type.substr(pos + 1, type.size() - pos - 1);
		m_SubData.insert(make_pair(key, value));
		return m_SubData;
	}
}

ReservationFile::ReservationFile()
{
	ifstream ifs;
	ifs.open(RESERVATION_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	string stuId;	//学生编号
	string stuName;	//学生姓名
	string date;	//日期
	string interval;	//时间段
	string roomId;	//机房编号
	string status;	//状态

	this->m_Size = 0;	//记录条数

	while (ifs >> stuId && ifs >> stuName && ifs >> date && ifs >> interval &&
		ifs >> roomId && ifs >> status)
	{
		map<string, string> m_SubData;

		m_SubData = this->CutString(stuId, m_SubData);
		m_SubData = this->CutString(stuName, m_SubData);
		m_SubData = this->CutString(date, m_SubData);
		m_SubData = this->CutString(interval, m_SubData);
		m_SubData = this->CutString(roomId, m_SubData);
		m_SubData = this->CutString(status, m_SubData);

		this->m_ReservData.insert(make_pair(this->m_Size, m_SubData));
		this->m_Size++;
	}	
	ifs.close();

	//test m_ReservData
	//注意，这里的输出顺序和插入顺序不一样，是因为map容器，所有元素都会根据元素的key值自动排序。
	//for (map<int, map<string, string>>::iterator it = m_ReservData.begin();
	//	it != m_ReservData.end(); it++)
	//{
	//	cout << "条数：" << it->first << ", value: " << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << "key: " << mit->first << ", value: " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

//更新预约记录
void ReservationFile::UpdateReserv()
{
	if (this->m_Size == 0)
	{
		return;
	}

	ofstream ofs(RESERVATION_FILE, ios::out | ios::trunc);
	for (int i = 0; i < m_Size; i++)
	{
		ofs << "date:" << this->m_ReservData[i]["date"] << " ";
		ofs << "interval:" << this->m_ReservData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_ReservData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_ReservData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_ReservData[i]["roomId"] << " ";
		ofs << "status:" << this->m_ReservData[i]["status"] << endl;
	}
	ofs.close();
}

//map<string, string> ReservationFile::InterceptSubstr(string type)
//{
//	string key;
//	string value;
//	map<string, string> m_SubData;
//	int pos = type.find(":");
//	if (pos != -1)	//如果不存在的话，会返回-1
//	{
//		key = type.substr(0, pos);
//		value = type.substr(pos + 1, type.size() - pos - 1);
//		m_SubData.insert(make_pair(key, value));
//		//this->m_ReservData.insert(make_pair(this->m_Size, m_SubData));
//	}
//	return m_SubData;
//}
