#pragma once
#include <iostream>
#include <fstream>
#include "globalFile.h"
#include <map>
#include <string>
#include "computerRoom.h"
using namespace std;

class RestSeats
{
public:
	RestSeats();
	void InitRestSeats();
	void InitVector();
	map<string, string> CutString(string type, map<string, string> m_SubData);
	void UpdateRestSeats();
	int m_Size;
	
	vector<ComputerRoom> vComp;
	map<int, map<string, string>> mRestSeats;
};