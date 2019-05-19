#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;
int last = 0;
void renowate(vector<long long> &t, int n)
{
	for (int i = n - 2; i >= 0; i--)
	{
		t[i] = min(t[(i << 1) + 1], t[(i << 1) + 2]);
	}
}
long long propagatesum(int node, long long x, int a, int b, vector<long long> &t)
{
	if (node > t.size())
		return 0;
	if (a > b)
		return 0;
	t[node] += x;
	if (a == b)
		return 0;
	propagatesum((node << 1) + 1, x, a, (a + b) >> 1, t);
	propagatesum((node << 1) + 2, x, 1 + ((a + b) >> 1), b, t);
	return 0;
}
long long mininimum(int node, int l, int r, int a, int b, vector<long long> &t,int n,int counter)
{
	if (last != counter - 1)
	{
		renowate(t, n);
	}
	last = counter;
	if (a > b || a > r || b < l)
		return 1000000000000000001;
	if (a >= l&&b <= r)
	{
		return  t[node];
	}
	long long q1 = mininimum((node << 1) + 1, l, r, a, (a + b) >> 1, t,n,counter);
	long long q2 = mininimum((node << 1) + 2, l, r, 1 + ((a + b) >> 1), b, t,n,counter);
	long long res = min(q1, q2);
	return res;
}
int propagate(int node, long long x, int a, int b, vector<long long> &t)
{
	if (a > b)
		return 0;
	if (node > t.size())
		return 0;
	t[node] = x;
	if (a == b)
		return 0;
	propagate((node << 1) + 1, x, a, (a + b) >> 1, t);
	propagate((node << 1) + 2, x, 1 + ((a + b) >> 1), b, t);
	return 0;
}
int set(int node, int i, int j, long long x, int a, int b, vector<long long> &t)
{

	if (a > b || b<i || a>j)
		return 0;
	if (a >= i&&b <= j)
	{
		propagate(node, x, a, b, t);
		return 0;
	}
	set((node << 1) + 1, i, j, x, a, (a + b) >> 1, t);
	set((node << 1) + 2, i, j, x, 1 + ((a + b) >> 1), b, t);
	return 0;
}
int add(int node, int i, int j, long long x, int a, int b, vector<long long> &t)
{
	if (a > b || a > j || b < i)
		return 0;
	if (a >= i&&b <= j)
	{
		propagatesum(node,x,a,b,t);
		return 0;
	}
	add((node << 1) + 1, i, j, x, a, ((a + b) >> 1), t);
	add((node << 1) + 2, i, j, x, 1 + ((a + b) >> 1), b, t);
	return 0;
}
int main()
{
	ifstream fin("rmq2.in");
	ofstream fout("rmq2.out");
	int n;
	fin >> n;
	int w = 0;
	int q = n;
	int approve = 0;
	while (q > 1)
	{
		if (q % 2 == 0)
			;
		else
			approve++;
		q = q >> 1;
		w++;
	}
	if (approve>0)
		w++;
	q = n;
	n = 1<<w;
	vector<long long> a(n);
	vector<long long> t((n << 1) - 1);
	for (int i = 0; i < n; i++)
	{
		if (i < q)
		{
			fin >> a[i];
		}
		else
			a[i] = 1000000000000000001;
	}
	for (int i = 0; i < n; i++)
	{
		t[n - 1 + i] = a[i];
	}
	for (int i = n - 2; i >= 0; i--)
	{
		t[i] = min(t[(i << 1) + 1], t[(i << 1) + 2]);
	}
	string z;
	int c;
	long long b;
	int counter=0;
	while (getline(fin, z))
	{
		counter++;
		fin >> z;
		if (z == "min")
		{
			fin >> c >> q;
			c--;
			q--;
			cout << mininimum(0, c, q, 0, n - 1, t,n,counter) << endl;
		}
		if (z == "set")
		{
			fin >> c >> q >> b;
			set(0, c - 1, q - 1, b, 0, n - 1, t);
		}
		if (z == "add")
		{
			fin >> c >> q >> b;
			add(0, c - 1, q - 1, b, 0, n - 1, t);
		}
	}
  system("pause");
	return 0;
}
