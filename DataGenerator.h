#pragma once

#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class DataGenerator
{
public:
	void SetSize(int n);
	DataGenerator(int n, int range, string filename);
	void generate();
private:
	int n;
	int range;
	string filename;
};

#endif