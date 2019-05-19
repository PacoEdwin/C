#include<iostream>
#include<vector>
#include<string>
using namespace std;

float length;
float y;
vector<float> x;

float solve(vector<float> k, float l)
{
  if (k.size()==1)
  {
    float k0 = k[0];
    float res = k0*length / (l + k0);
    x.push_back(length - res);
    y = res*l;
    return res;
  }
  float k1 = k[k.size()-1];
  k.pop_back();
  float w = k1*l / (k1 + l);
  auto result = solve(k, w);
  auto sum = k[k.size() - 1] * result / (k[k.size() - 1] + l);
  x.push_back(result - sum);
  return sum;
}

int main()
{
  vector<float> k;
  length = 100.f;
  for (int i = 0; i < 10; i++)
  {
    k.push_back(0.5);
  }
  float l = k[k.size() - 1];
  k.pop_back();
  x.push_back(solve(k, l));
  system("pause");
  return 0;
}