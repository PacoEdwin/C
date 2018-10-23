#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
int main()
{
	ifstream fin("lis.in");
	ofstream fout("lis.out");
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> d(n);
	vector<int> indexes(n);
	for (int i = 0; i < n; i++)
	{
		d[i] = 1;
		indexes[i] = -1;
		for (int j = 0; j < i; j++)
		{
			if (a[j] < a[i])
				if (d[i] < d[j] + 1)
				{
					d[i] = 1 + d[j];
					indexes[i] = j;
				}

		}
	}
	int ans = d[0], ind = 0;
	for (int i = 0; i< n; i++)
		if (d[i]>ans)
		{
			ans = d[i];
			ind = i;
		}
	cout << ans << endl;
	vector<int> path;
	while (ind != -1)
	{
		path.push_back(ind);
		ind = indexes[ind];
	}
	reverse(path.begin(), path.end());
	for (int i = 0; i < path.size(); i++)
		cout << a[path[i]] << " ";
  system("pause");
	return 0;
}