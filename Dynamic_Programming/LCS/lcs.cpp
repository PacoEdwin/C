#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include<algorithm>
using namespace std;
vector<int> answer;
void print(int i, int j, vector<vector<pair<int, int>>> &path,vector<int> &a)
{
	if (i == 0 || j == 0)
		return;
	if (path[i][j].first == i - 1 && path[i][j].second == j - 1)
	{
		print(i - 1, j - 1, path, a);
		answer.push_back(a[i-1]);
	}
	else
		if (path[i][j].first == i - 1 && path[i][j].second == j)
			print(i - 1, j, path, a);
		else
			print(i, j - 1, path, a);
}
int main()
{
	ifstream fin("lcs.in");
	ofstream fout("lcs.out");
	int n, m;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cin >> m;
	vector<int> b(m);
	for (int i = 0; i < m; i++)
		cin >> b[i];
	vector<vector<int>> d(n+1, vector<int>(m+1));
	for (int i = 0; i < n; i++)
		d[i][0] = 0;
	for (int i = 0; i < m; i++)
		d[0][i] = 0;
	vector<vector<pair<int, int>>> path(n+1, vector<pair<int, int>>(m+1));

	for (int i = 1; i < n+1; i++)
		for (int j = 1; j < m+1; j++)
			if (a[i-1] == b[j-1])
			{
				d[i][j] = d[i - 1][j - 1] + 1;
				path[i][j] = make_pair(i - 1, j - 1);
			}
			else
				if (d[i-1][j] >= d[i][j-1])
				{
					d[i][j] = d[i-1][j];
					path[i][j] = make_pair(i-1, j);
				}
				else
				{
					d[i][j] = d[i][j-1];
					path[i][j] = make_pair(i, j-1);
				}
	int ans = 0;
	for (int i = 1; i < n+1; i++)
		for (int j = 1; j < m+1; j++)
			ans = max(ans, d[i][j]);
	cout << ans << endl;
	print(n, m , path, a);
	for (int i = 0; i <n+1; i++)
		if (d[i][0] == 1)
			answer.push_back(a[i]);
	//reverse(answer.begin(), answer.end());
	for (int i = 0; i < answer.size(); i++)
		if (answer.size() == ans)
			cout << answer[i] << " ";
		else
			if (i > 0)
				cout << answer[i] << " ";
	return 0;
}