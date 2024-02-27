// 编写一个类用来生成随机数据，并将其保存到文件中

#include "DataGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

DataGenerator::DataGenerator(int n, int range, string filename)
{
	this->n = n;
	this->range = range;
	this->filename = filename;
}

void DataGenerator::SetSize(int n)
{
	this->n = n;
}

void DataGenerator::generate()
{
	ofstream out(filename);
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		out << rand() % range << " ";
	}
	out.close();
}
