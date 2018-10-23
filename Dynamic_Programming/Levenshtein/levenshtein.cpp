#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;
int main()
{
	ifstream fin("levenshtein.in");
	ofstream fout("levenshtein.out");
	string a, b;
	cin>> a >> b;
	int n = a.size();
	int m = b.size();
	vector<vector<int>> d(n+1, vector<int>(m+1));
	for (int i = 0; i <= n; i++)
		d[i][0] = i;
	for (int j = 0; j <= m; j++)
		d[0][j] = j;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			d[i][j] = min(d[i - 1][j] + 1, min(d[i][j - 1] + 1, d[i - 1][j - 1] + (a[i-1] == b[j-1] ?0:1)));
		}
  cout << d[n][m]<<endl;
	system("pause");
	return 0;
}