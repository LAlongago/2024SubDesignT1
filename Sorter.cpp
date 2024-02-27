// 一个基类Sort用于接受数据，四个派生类分别实现希尔、快速、堆排序、归并排序算法

#include "Sorter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;

Sort::Sort(string filename)
{
	this->filename = filename;
}

void Sort::readData()
{
	ifstream in(filename);
	int temp;
	while (in >> temp)
	{
		data.push_back(temp);
	}
	in.close();
}

vector<int> Sort::getSortedData()
{
	return data;
}

ShellSort::ShellSort(string filename) : Sort(filename)
{
}

long long ShellSort::sort()
{
	auto start = chrono::high_resolution_clock::now();
	int gap = data.size() / 2;
	while (gap > 0)
	{
		for (int i = gap; i < data.size(); i++)
		{
			int temp = data[i];
			int j = i - gap;
			while (j >= 0 && data[j] > temp)
			{
				data[j + gap] = data[j];
				j -= gap;
			}
			data[j + gap] = temp;
		}
		gap /= 2;
	}
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

QuickSort::QuickSort(string filename) : Sort(filename)
{
}

long long QuickSort::sort()
{
	auto start = chrono::high_resolution_clock::now();
	quickSort(0, data.size() - 1);
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

void QuickSort::quickSort(int left, int right)
{
	if (left < right)
	{
		int i = left;
		int j = right;
		int temp = data[i];
		while (i < j)
		{
			while (i < j && data[j] >= temp)
			{
				j--;
			}
			if (i < j)
			{
				data[i++] = data[j];
			}
			while (i < j && data[i] < temp)
			{
				i++;
			}
			if (i < j)
			{
				data[j--] = data[i];
			}
		}
		data[i] = temp;
		quickSort(left, i - 1);
		quickSort(i + 1, right);
	}
}

HeapSort::HeapSort(string filename) : Sort(filename)
{
}

long long HeapSort::sort()
{
	auto start = chrono::high_resolution_clock::now();
	for (int i = data.size() / 2 - 1; i >= 0; i--)
	{
		adjustHeap(i, data.size());
	}
	for (int i = data.size() - 1; i > 0; i--)
	{
		swap(data[0], data[i]);
		adjustHeap(0, i);
	}
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

void HeapSort::adjustHeap(int i, int length)
{
	int temp = data[i];
	for (int k = 2 * i + 1; k < length; k = 2 * k + 1)
	{
		if (k + 1 < length && data[k] < data[k + 1])
		{
			k++;
		}
		if (data[k] > temp)
		{
			data[i] = data[k];
			i = k;
		}
		else
		{
			break;
		}
	}
	data[i] = temp;
}

MergeSort::MergeSort(string filename) : Sort(filename)
{
}

long long MergeSort::sort()
{
	auto start = chrono::high_resolution_clock::now();
	mergeSort(0, data.size() - 1);
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

void MergeSort::mergeSort(int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(left, mid);
		mergeSort(mid + 1, right);
		merge(left, mid, right);
	}
}

void MergeSort::merge(int left, int mid, int right)
{
	vector<int> temp(right - left + 1);
	int i = left;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= right)
	{
		if (data[i] <= data[j])
		{
			temp[k++] = data[i++];
		}
		else
		{
			temp[k++] = data[j++];
		}
	}
	while (i <= mid)
	{
		temp[k++] = data[i++];
	}
	while (j <= right)
	{
		temp[k++] = data[j++];
	}
	for (int i = 0; i < temp.size(); i++)
	{
		data[left + i] = temp[i];
	}
}