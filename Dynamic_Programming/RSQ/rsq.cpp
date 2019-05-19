#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
long long res = 0; 
int set(int node, int i, long long x, int a, int b, vector<long long> &t)
{
	long long dif;
	if (a > b || b<i || a>i)
		return 0;
	if (a == i&&b == i)
	{
		dif = x - t[node];
		t[node] = x;
		while (node > 0)
		{
			if (node % 2 == 0)
				node = node / 2 - 1;
			else
				node = node / 2;
			t[node] = t[2 * node + 1] + t[2 * node + 2];
		}
		return 0;
	}
	set(2 * node + 1, i, x, a, (a + b) / 2, t);
	set(2 * node + 2, i, x, 1 + (a + b) / 2, b, t);
	return 0;
}
long long sum(int node, int l, int r, int a, int b, vector<long long> &t)
{
	if (a > b || b < l||a>r)
		return 0;
	if (a >= l&&b <= r)
	{
		return t[node];
	}
	res = sum(2 * node + 1, l, r, a, min((a + b) / 2,b), t) + sum(2 * node + 2, l, r,max( 1 + (a + b) / 2,a), b, t);
	return res;
}
int main()
{
	ifstream fin("rsq.in");
	ofstream fout("rsq.out");
	int n;
	fin >> n;
	int w = 0;
	int q = n;
	while (q > 1)
	{
		q = q >> 1;
		w++;
	}
	w++;
	q = n;
	n = pow(2, w);
	vector<long long> a(n);
	vector<long long> t(4 * n);
	for (int i = 0; i < n; i++)
	{
		if (i < q)
		{
			fin >> a[i];
		}
		else
			a[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		t[n - 1 + i] = a[i];
	}
	for (int i = n - 2; i >= 0; i--)
	{
		t[i] = t[2 * i + 1]+t[2 * i + 2];
	}
	string z;
	int c, b;
	while (getline(fin, z))
	{
		fin >> z;
		if (z == "sum")
		{
			fin >> c >> b;
			c--;
			b--;
			cout << sum(0, c, b, 0, n - 1, t) << endl;
			res = 0;
		}
		if (z == "set")
		{
			fin >> c >> b;
			set(0, c - 1, b, 0, n - 1, t);
		}
	}
	system("pause");
	return 0;
}