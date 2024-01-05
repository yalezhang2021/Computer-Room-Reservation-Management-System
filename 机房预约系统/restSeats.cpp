#include "restSeats.h"

RestSeats::RestSeats()
{

}

map<string, string> RestSeats::CutString(string type, map<string, string> m_SubData)
{
	string key;
	string value;
	int pos = type.find(":");
	if (pos != -1)	//��������ڵĻ����᷵��-1
	{
		key = type.substr(0, pos);
		value = type.substr(pos + 1, type.size() - pos - 1);
		m_SubData.insert(make_pair(key, value));
		return m_SubData;
	}
}

void RestSeats::InitVector()
{
	//��ȡcomputerroom.txt�е�����
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

//���Ӧ��ֻ����һ�Σ�ֻ��������ϵͳ��ʱ�򣬻��޸Ļ�����Ϣ������һ�ξͿ���
void RestSeats::InitRestSeats()
{
	//���ļ���һ������������棬��Ϊ��Ҳ���Դ�����������������ļ���ʱ��
	//ofstream of;
	//of.open(UPDATEHEADCOUNT_FILE, ios::out | ios::trunc); //���ʱ���Ѿ����ļ�����ˣ������������ʱ�����ǿ�

	ifstream ifs(UPDATEHEADCOUNT_FILE, ios::in);
	//����ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ����ڴ���" << endl;
		//�����ļ�
		ofstream of;
		of.open(UPDATEHEADCOUNT_FILE, ios::out | ios::trunc);
		of.close();
		cout << "�����ɹ�" << endl;
		return;
	}

	char ch;
	ifs >> ch;
	bool ret = false;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		ret = true;
		ifs.close();
	}
	else
	{
		ifs.putback(ch);
		ifs.close();
	}

	//�ļ���Ϊ�յ����
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

	//�ļ��������ݵ����
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

	this->m_Size = 0;	//��¼����

	ifstream ifss(UPDATEHEADCOUNT_FILE, ios::in);
	while (ifss >> mondayAm && ifss >> mondayPm && ifss >> tuesdayAm && ifss >> tuesdayPm && ifss >> wednesdayAm
		&& ifss >> wednesdayPm && ifss >> thursdayAm && ifss >> thursdayPm && ifss >> fridayAm && ifss >> fridayPm)
	{
		//���յĽṹӦ����:
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
	//	cout << "������" << it->first << ", value: " << endl;
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