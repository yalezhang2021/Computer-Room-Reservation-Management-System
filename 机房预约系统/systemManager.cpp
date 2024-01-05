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
//	cout << "\t\t\t\t|         机房预约系统      |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.学生登录        |" << endl;
//	cout <<	"\t\t\t\t|         2.教师登录        |" << endl;
//	cout << "\t\t\t\t|         3.管理员登录      |" << endl;
//	cout << "\t\t\t\t|         0.退出登录        |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t-----------------------------" << endl;
//}
//
//void SystemManager::ShowStudentMenu()
//{
//	cout << "\t\t\t\t-----------------------------" << endl;
//	cout << "\t\t\t\t|         学生机房预约系统   |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.申请预约        |" << endl;
//	cout << "\t\t\t\t|         2.我的预约        |" << endl;
//	cout << "\t\t\t\t|         3.查看所有预约    |" << endl;
//	cout << "\t\t\t\t|         4.取消预约        |" << endl;
//	cout << "\t\t\t\t|         0.退出登录        |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t-----------------------------" << endl;
//}
//
//void SystemManager::ShowTeacherMenu()
//{
//	cout << "\t\t\t\t-----------------------------" << endl;
//	cout << "\t\t\t\t|         教师机房预约系统   |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.查看所有预约    |" << endl;
//	cout << "\t\t\t\t|         2.审核预约        |" << endl;
//	cout << "\t\t\t\t|         0.退出登录        |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t-----------------------------" << endl;
//}
//
//void SystemManager::ShowAdminMenu()
//{
//	cout << "\t\t\t\t-----------------------------" << endl;
//	cout << "\t\t\t\t|       管理员机房预约系统   |" << endl;
//	cout << "\t\t\t\t|---------------------------|" << endl;
//	cout << "\t\t\t\t|         1.添加账号        |" << endl;
//	cout << "\t\t\t\t|         2.查看账号        |" << endl;
//	cout << "\t\t\t\t|         3.查看机房        |" << endl;
//	cout << "\t\t\t\t|         4.清空预约        |" << endl;
//	cout << "\t\t\t\t|         0.退出登录        |" << endl;
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
//	cout << "请输入学号: " << endl;
//	cin >> id;
//	cout << "请输入密码: " << endl;
//	cin >> password;
//
//	//test
//	Student st;
//	st.m_Name = "小张";
//	st.m_Password = "123";
//	this->mStudent.insert(make_pair(1, st));
//
//	for (map<int, Student>::iterator it = mStudent.begin(); it != mStudent.end(); it++)
//	{
//		if (it->first == id && it->second.m_Password == password)
//		{
//			cout << "登录成功！ 你好，" << it->second.m_Name << "!" << endl;
//			//跳转到学生菜单界面
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
//	cout << "感谢您的使用！" << endl;
//	system("pause");
//	exit(0); // 或者直接return 0 也是一样的。
//}
//
//SystemManager::~SystemManager()
//{
//
//}