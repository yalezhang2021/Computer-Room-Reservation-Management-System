//#include "systemManager.h"
//
//SystemManager::SystemManager()
//{
//	this->InitSystem();
//}
//
//void SystemManager::ShowMainMenu()
//{
//	cout << "\t\t\t\t-----------------------------" << endl;
//	cout << "\t\t\t\t|         ����ԤԼϵͳ      |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.ѧ����¼        |" << endl;
//	cout <<	"\t\t\t\t|         2.��ʦ��¼        |" << endl;
//	cout << "\t\t\t\t|         3.����Ա��¼      |" << endl;
//	cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t-----------------------------" << endl;
//}
//
//void SystemManager::ShowStudentMenu()
//{
//	cout << "\t\t\t\t-----------------------------" << endl;
//	cout << "\t\t\t\t|         ѧ������ԤԼϵͳ   |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.����ԤԼ        |" << endl;
//	cout << "\t\t\t\t|         2.�ҵ�ԤԼ        |" << endl;
//	cout << "\t\t\t\t|         3.�鿴����ԤԼ    |" << endl;
//	cout << "\t\t\t\t|         4.ȡ��ԤԼ        |" << endl;
//	cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t-----------------------------" << endl;
//}
//
//void SystemManager::ShowTeacherMenu()
//{
//	cout << "\t\t\t\t-----------------------------" << endl;
//	cout << "\t\t\t\t|         ��ʦ����ԤԼϵͳ   |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.�鿴����ԤԼ    |" << endl;
//	cout << "\t\t\t\t|         2.���ԤԼ        |" << endl;
//	cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t-----------------------------" << endl;
//}
//
//void SystemManager::ShowAdminMenu()
//{
//	cout << "\t\t\t\t-----------------------------" << endl;
//	cout << "\t\t\t\t|       ����Ա����ԤԼϵͳ   |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.����˺�        |" << endl;
//	cout << "\t\t\t\t|         2.�鿴�˺�        |" << endl;
//	cout << "\t\t\t\t|         3.�鿴����        |" << endl;
//	cout << "\t\t\t\t|         4.���ԤԼ        |" << endl;
//	cout << "\t\t\t\t|         0.�˳���¼        |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t-----------------------------" << endl;
//}
//
//void SystemManager::InitSystem()
//{
//	this->mStudent.clear();
//	this->mTeacher.clear();
//	this->mAdmin.clear();
//}
//
//void SystemManager::StudentLogin()
//{
//	int id;
//	string password;
//	
//	cout << "������ѧ��: " << endl;
//	cin >> id;
//	cout << "����������: " << endl;
//	cin >> password;
//
//	//test
//	Student st;
//	st.m_Name = "С��";
//	st.m_Password = "123";
//	this->mStudent.insert(make_pair(1, st));
//
//	for (map<int, Student>::iterator it = mStudent.begin(); it != mStudent.end(); it++)
//	{
//		if (it->first == id && it->second.m_Password == password)
//		{
//			cout << "��¼�ɹ��� ��ã�" << it->second.m_Name << "!" << endl;
//			//��ת��ѧ���˵�����
//			system("pause");
//			this->ShowStudentMenu();
//		}
//	}
//}
//
//void Student::ApplyReserv()
//{
//
//}
//
//void SystemManager::ExitSystem()
//{
//	cout << "��л����ʹ�ã�" << endl;
//	system("pause");
//	exit(0); // ����ֱ��return 0 Ҳ��һ���ġ�
//}
//
//SystemManager::~SystemManager()
//{
//
//}