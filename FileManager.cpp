//用于读取数据和存储数据

#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

void FileManager::StoreData(vector<int> dt)
{
	this->data = dt;
}

bool FileManager::SaveData()
{
	ofstream out(targetfd);
	if (!out)
	{
		cout << "open file error" << endl;
		return false;
	}
	for (int i = 0; i < data.size(); i++)
	{
		out << data[i] << " ";
	}
	out.close();
	return true;
}

void FileManager::ChangeTarget(string target)
{
	targetfd = target;
}