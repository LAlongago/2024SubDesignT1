#pragma once

#ifndef SORTER_H
#define SORTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Sort
{
public:
	Sort(string filename);
	void readData();
	virtual long long sort() = 0;
	vector<int> getSortedData();
protected:
	vector<int> data;
	string filename;
};

class ShellSort : public Sort
{
public:
	ShellSort(string filename);
	long long sort();
};

class QuickSort : public Sort
{
public:
	QuickSort(string filename);
	long long sort();
private:
	void quickSort(int left, int right);
};

class HeapSort : public Sort
{
public:
	HeapSort(string filename);
	long long sort();
private:
	void adjustHeap(int i, int length);
};

class MergeSort : public Sort
{
public:
	MergeSort(string filename);
	long long sort();
private:
	void mergeSort(int left, int right);
	void merge(int left, int mid, int right);
};

#endif