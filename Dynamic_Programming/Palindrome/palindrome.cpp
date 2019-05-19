#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<string>
#include<utility>
using namespace std;
int n;
string answer = "";
string answer1 = "";
void print(int i, int j, vector<vector<pair<int, int>>> &path, string a)
{
	if (i == j)
		answer += a[i];
	if (i == n - 1 || j == 0)
		return;
	if (path[i][j].first == i + 1 && path[i][j].second == j - 1)
	{
		print(i+1, j - 1, path, a);
		answer1 += a[i];
		string tmp = answer;
		answer = a[j] + tmp;
	}
	else
		if (path[i][j].first == i + 1 && path[i][j].second == j)
			print(i + 1, j, path, a);
		else
			print(i, j - 1, path, a);
}
int main()
{
	ifstream fin("palindrome.in");
	ofstream fout("palindrome.out"); 
	string a;
	cin >> a;
	n = a.size();
	vector<vector<int>> d(n,vector<int> (n));
	vector<vector<pair<int, int>>> path(n, vector<pair<int, int>>(n));
	for (int i = 0; i < n; i++)
	{
		d[i][i] = 1;
		path[i][i] = make_pair(i, i);
	}
	for (int i = 1; i < n; i++)
	{
		d[i][i - 1]=0;
	}
	for (int l = n - 1; l >= 0; l--)
		for (int r = l + 1; r < n; r++)
		{
			if (a[l] == a[r])
			{
				d[l][r] = d[l + 1][r - 1] + 2;
				path[l][r] = make_pair(l + 1, r - 1);
			}
			else
				if (d[l + 1][r]>d[l][r - 1])
				{
					d[l][r] = d[l + 1][r];
					path[l][r] = make_pair(l + 1, r);
				}
				else
				{
					d[l][r] = d[l][r - 1];
					path[l][r] = make_pair(l, r - 1);
				}
		}
	cout << d[0][n - 1]<<endl;
	print(0, n - 1, path, a);
	cout << answer << answer1;
	system("pause");
	return 0;
}