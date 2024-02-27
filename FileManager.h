#pragma once

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FileManager
{
public:
	FileManager();
	~FileManager();
	void StoreData(vector<int> dt);
	bool SaveData();
	void ChangeTarget(string target);
private:
	string sourcefd;
	string targetfd;
	vector<int> data;
};

#endif // !FILEMANAGER_H
