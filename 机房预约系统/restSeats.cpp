#include "restSeats.h"

RestSeats::RestSeats()
{

}

map<string, string> RestSeats::CutString(string type, map<string, string> m_SubData)
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

void RestSeats::InitVector()
{
	//读取computerroom.txt中的数据
	ifstream ifs(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "unable to open " << COMPUTER_FILE << endl;
		return;
	}

	ComputerRoom c;

	while (ifs >> c.m_Id && ifs >> c.m_Num)
	{
		vComp.push_back(c);
	}
	ifs.close();
}

//这个应该只运行一次，只有在重置系统的时候，或修改机房信息后，运行一次就可以
void RestSeats::InitRestSeats()
{
	//打开文件这一步必须放在外面，因为它也可以创建，当不存在这个文件的时候。
	//ofstream of;
	//of.open(UPDATEHEADCOUNT_FILE, ios::out | ios::trunc); //这个时候已经将文件清空了，所以下面读的时候总是空

	ifstream ifs(UPDATEHEADCOUNT_FILE, ios::in);
	//如果文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在，正在创建" << endl;
		//创建文件
		ofstream of;
		of.open(UPDATEHEADCOUNT_FILE, ios::out | ios::trunc);
		of.close();
		cout << "创建成功" << endl;
		return;
	}

	char ch;
	ifs >> ch;
	bool ret = false;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		ret = true;
		ifs.close();
	}
	else
	{
		ifs.putback(ch);
		ifs.close();
	}

	//文件里为空的情况
	if (ret)
	{
		cout << "file is empty, will initialize it..." << endl;
		ofstream of;
		of.open(UPDATEHEADCOUNT_FILE, ios::out | ios::trunc);
		this->InitVector();

		for (int i = 0; i < vComp.size(); i++)
		{
			of << "mondayAm:" << vComp[i].m_Num
				<< " mondayPm:" << vComp[i].m_Num
				<< " tuesdayAm:" << vComp[i].m_Num
				<< " tuesdayPm:" << vComp[i].m_Num
				<< " wednesdayAm:" << vComp[i].m_Num
				<< " wednesdayPm:" << vComp[i].m_Num
				<< " thursdayAm:" << vComp[i].m_Num
				<< " thursdayPm:" << vComp[i].m_Num
				<< " fridayAm:" << vComp[i].m_Num
				<< " fridayPm:" << vComp[i].m_Num << endl;
		}
		cout << "initialize is succeeful!" << endl;
		of.close();
		//return;
	}

	//文件里有数据的情况
	string mondayAm;
	string mondayPm;
	string tuesdayAm;
	string tuesdayPm;
	string wednesdayAm;
	string wednesdayPm;
	string thursdayAm;
	string thursdayPm;
	string fridayAm;
	string fridayPm;

	this->m_Size = 0;	//记录条数

	ifstream ifss(UPDATEHEADCOUNT_FILE, ios::in);
	while (ifss >> mondayAm && ifss >> mondayPm && ifss >> tuesdayAm && ifss >> tuesdayPm && ifss >> wednesdayAm
		&& ifss >> wednesdayPm && ifss >> thursdayAm && ifss >> thursdayPm && ifss >> fridayAm && ifss >> fridayPm)
	{
		//最终的结构应该是:
		//map<int, map<string, string>>
		//mondayAm:20 mondayPm:30 tuesdayAm:30 tuesdayPm:40 wednesdayAm:10 wednesdayPm:0 thursdayAm:0 thursdayPm:50 fridayAm:50 fridayPm:50
		map<string, string> m_SubData;

		m_SubData = this->CutString(mondayAm, m_SubData);
		m_SubData = this->CutString(mondayPm, m_SubData);
		m_SubData = this->CutString(tuesdayAm, m_SubData);
		m_SubData = this->CutString(tuesdayPm, m_SubData);
		m_SubData = this->CutString(wednesdayAm, m_SubData);
		m_SubData = this->CutString(wednesdayPm, m_SubData);
		m_SubData = this->CutString(thursdayAm, m_SubData);
		m_SubData = this->CutString(thursdayPm, m_SubData);
		m_SubData = this->CutString(fridayAm, m_SubData);
		m_SubData = this->CutString(fridayPm, m_SubData);

		this->mRestSeats.insert(make_pair(this->m_Size, m_SubData));
		this->m_Size++;
	}
	ifss.close();

	//test
	//for (map<int, map<string, string>>::iterator it = mRestSeats.begin();
	//	it != mRestSeats.end(); it++)
	//{
	//	cout << "条数：" << it->first << ", value: " << endl;
	//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
	//	{
	//		cout << "key: " << mit->first << ", value: " << mit->second << " ";
	//	}
	//	cout << endl;
	//}
}

void RestSeats::UpdateRestSeats()
{
	ofstream ofs(UPDATEHEADCOUNT_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << " mondayAm:" << mRestSeats[i]["mondayAm"] << " ";
		ofs << " mondayPm:" << mRestSeats[i]["mondayPm"] << " ";
		ofs << " tuesdayAm:" << mRestSeats[i]["tuesdayAm"] << " ";
		ofs << " tuesdayPm:" << mRestSeats[i]["tuesdayPm"] << " ";
		ofs << " wednesdayAm:" << mRestSeats[i]["wednesdayAm"] << " ";
		ofs << " wednesdayPm:" << mRestSeats[i]["wednesdayPm"] << " ";
		ofs << " thursdayAm:" << mRestSeats[i]["thursdayAm"] << " ";
		ofs << " thursdayPm:" << mRestSeats[i]["thursdayPm"] << " ";
		ofs << " fridayAm:" << mRestSeats[i]["fridayAm"] << " ";
		ofs << " fridayPm:" << mRestSeats[i]["fridayPm"] << endl;
	}
	ofs.close();
}