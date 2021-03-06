// Job_apply.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <dirent.h>
#include <sys\stat.h>
#include<iostream>
#include<fstream>
#include<string>
#include <windows.h>
#include<vector>
#include<thread>
#include "psapi.h"

using namespace std;
string substring;
//префикс функция
vector<int> prefixFunction(string s)
{
	vector<int> p(s.length());
	for (int i = 1; i < s.length(); i++)
	{
		int k = p[i - 1];
		while (k > 0 && s[i] != s[k])
			k = p[k - 1];
		if (s[i] == s[k])
			k++;
		p[i] = k;
	}
	return p;
}

//Алгоритм Кнута-Морриса-Пратта
//Асимптотика О(n)
bool kmp(string p, string t)
{
	int pl = p.length();
	int tl = t.length();
	vector<int> prefixf = prefixFunction(p + "`" + t);
	int count = 0;
	for (int i = 0; i < tl; i++)
	{
		if (prefixf[pl + i + 1] == pl)
			return true;
	}
	return false;
}
void read_file(const char *file_name, ofstream &fout)
{
	ifstream fin(file_name);
	if (fin)
	{
		std::string str((std::istreambuf_iterator<char>(fin)),
			std::istreambuf_iterator<char>());
		if (kmp(substring, str))
			fout << file_name << endl;
	}
	else
		cout << "Problem opening file" <<file_name << endl;
}

//проверяет совместимость маски со строкой
//Асимптотика и память O(m*n)
bool fits(const char* path, const char* mask)
{
	string p, s;
	s = path;
	p = mask;
	p = " " + p;
	s = " " + s;
	int n = p.size();
	int m = s.size();
	vector<vector<int>> d(n + 1, vector<int>(m + 1));
	d[0][0] = 1;
	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < m + 1; j++)
		{
			if (p[i - 1] == '*')
			{
				d[i][j] = d[i - 1][j] | d[i][j - 1];
			}
			else
				if (p[i - 1] == '?')
					d[i][j] = d[i - 1][j - 1];
				else
				{
					if (s[j - 1] == p[i - 1])
						d[i][j] = d[i - 1][j - 1];
				}
		}
	if (d[n][m] == 1)
		return true;
	else
		return false;
}

//спускается по дерикториям
void explore(const char *dir_name,const char* mask, ofstream &fout)
{
	DIR *dir;
	struct dirent *entry;
	struct stat info;
	dir = opendir(dir_name);
	if (!dir)
	{
		cout << "Directory was not found" << endl;
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			string path = string(dir_name) + "/" + string(entry->d_name);
			stat(path.c_str(), &info);
			if (S_ISDIR(info.st_mode))
				explore(path.c_str(),mask, fout);
			else
			{
				if (fits(entry->d_name, mask))
				{
					read_file(path.c_str(), fout);
				}
			}
		}
	}
}

//отдельный поток для проверки памяти
void memory_check(bool &flag)
{

	MEMORYSTATUSEX memInfo;
	SIZE_T virtualMemUsedByMe;
	SIZE_T physMemUsedByMe = 0;
	while (physMemUsedByMe < 10485760)
	{
		if (flag)
			return;
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		physMemUsedByMe = pmc.WorkingSetSize;
	}
	cout << "Ram limit exceeded" << endl;
	exit(0);
}

//supports arguments only on english
int main(int argc, const char* argv[])
{
	bool flag=false;
	thread thr(memory_check,std::ref(flag));
	if (argc < 5)
	{
		cout<<endl << "Wrong parameters" << endl <<
			"Please enter: " << endl <<
			"file path, mask of files to search, path to substring, path to output file" << endl;
		flag = true;
		system("pause");
		exit(0);
	}
	ifstream fin(argv[3]);
	if (fin.fail())
	{
		cout << "Fail while trying to open file with substring";
		flag = true;
		system("pause");
		exit(0);
	}
	std::string str((std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>());
	substring = str;
	ofstream fout(argv[4]);
	if (fout.fail())
	{
		cout << "Fail while trying to open output file";
		flag = true;
		system("pause");
		exit(0);
	}
	explore(argv[1], argv[2],fout);
	flag = true;
	system("pause");
	exit(0);
}
