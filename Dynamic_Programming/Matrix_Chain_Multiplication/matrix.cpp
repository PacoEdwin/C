#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<fstream>
#include<string>
#define INF INT_MAX
using namespace std;
vector<int> p;
vector<vector<int>> m;
vector<vector<int>> s;
ifstream fin("matrix.in");
ofstream fout("matrix.out");
void matrix()
{
	int n = p.size()-1;
	m.resize(n+1);
	s.resize(n+1);
	for (int i = 0; i <= n; i++)
		s[i].resize(n+1), m[i].resize(n+1);
	for (int l = 2; l <= n; l++)
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			m[i][j] = INF;
			for (int k = i; k < j; k++)
			{
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
}
void print(int i,int j)
{
	if (i == j)
		cout << "A";
	else
	{
		cout << "(";
		print(i, s[i][j]);
		print(s[i][j] + 1, j);
		cout << ")";
	}
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		p.push_back(a);
		if (i == n - 1)
			p.push_back(b);
	}
	matrix();
	print(1,n);
	system("pause");
	return 0;
}