#include<opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <math.h>
#include <random>
using namespace cv;
using namespace std;


int random_n(int n)
{
  std::random_device r;
  std::default_random_engine el(r());
  std::uniform_int_distribution<int> uniform(0, n);
  return uniform(el);
}

struct node
{
  node();
  string split;
  float a;
  float a_tar;
  node* l = NULL;
  node* r = NULL;
  node* parent;
  float height;
  float width;
  int id;
  float x, y;
  int N;
  Mat image;
  bool operator==(const node&) const;
};

node::node()
{
  this->id = random_n(100000000000);
}

bool node::operator==(const node& rhs) const
{
  if (this->id == rhs.id)
    return true;
  else
    return false;
}

void TopDown(node* v)
{
  if (v->parent->split == "V")
  {
    v->height = v->parent->height;
    v->width = v->parent->width * v->a;
  }
  else
  {
    v->width = v->parent->width;
    v->height = v->parent->height / v->a;
  }

  if (v->parent->l == v)
  {
    v->x = v->parent->x;
    v->y = v->parent->y;
  }
  else
  {
    if (v->parent->split == "H")
    {
      v->y = v->parent->y + v->parent->height - v->height;
      v->x = v->parent->x;
    }
    else
    {
      v->x = v->parent->x + v->parent->width - v->width;
      v->y = v->parent->y;
    }
  }
}

string define_split(int d)
{
  if (d % 2 == 0)
    return "H";
  if (d % 2 == 1)
    return "V";
}

int binary_search(vector<float> k, float x)
{
  int l = -1;
  int r = k.size()-1;
  while (l < r - 1)
  {
    int m = (l + r) / 2;
    if (k[m] < x)
      l = m;
    else
      r = m;
  }
  return r;
}

std::array<int, 2> FindPair(vector<float> k, float a)
{
  int p = 0;
  int q = k.size()-1;
  auto m= abs(k[p]+k[q]-a);
  int i=p, j=q;

  while (p < q)
  {
    if (k[p] + k[q] > a)
    {
      if (abs(k[p] + k[q] - a) < m)
      {
        m = abs(k[p] + k[q] - a);
        i = p, j = q;
      }
      q--;
    }
    else
    {
      if (k[p]+ k[q] < a)
      {
        if (abs(k[p] + k[q] - a) < m)
        {
          m = abs(k[p] + k[q] - a);
          i = p, j = q;
        }
        p++;
      }
      else
      {
        i = p, j = q;
        break;
      }
    }

  }

  return{i,j};
}

void FAST(vector<Mat> &L,vector<float> &k, float a_tar, int N, node* v)
{
  if (N == 1)
  {
    int index = binary_search(k, a_tar);
    auto a = k[index];
    v->a = a;
    v->image = L[index].clone();
    L.erase(L.begin() + index);
    k.erase(k.begin() + index);
    return;
  }
  if (N == 2)
  {
    auto copy = k;
    auto a = a_tar;

    //if (v->l == NULL || v->r == NULL)
    //{
      v->split = define_split(random_n(1));
      node* l = new node();
      node* r = new node();
      v->l = l;
      v->r = r;
      l->parent = v;
      r->parent = v;
    /*}*/

    array<int, 2> indexes;
    if (v->split == "H")
    {
      for (int i = 0; i < copy.size(); i++)
        copy[i] = 1 / copy[i];
      a = 1 / a;
      indexes = FindPair(copy, a);
      v->a = k[indexes[0]] * k[indexes[1]] / (k[indexes[0]] + k[indexes[1]]); 
    }
    else
    {
      indexes = FindPair(copy, a);
      v->a = k[indexes[0]] + k[indexes[1]];
    }
    if (indexes[0] > indexes[1])
      swap(indexes[0], indexes[1]);
    v->l->a = k[indexes[0]];
    v->r->a = k[indexes[1]];
    v->l->image = L[indexes[0]].clone();
    v->r->image = L[indexes[1]].clone();
    L.erase(L.begin() + indexes[1]);
    L.erase(L.begin() + indexes[0]);
    k.erase(k.begin() + indexes[1]);
    k.erase(k.begin() + indexes[0]);
    return;
  }

  //if (v->l == NULL || v->r == NULL)
  //{
    v->split = define_split(random_n(1));
    node* l = new node();
    node* r = new node();
    v->l = l;
    v->r = r;
    l->parent = v;
    r->parent = v;
    v->l->N = N / 2;
    v->r->N = N - N / 2;
    if (v->split == "V")
    {
      v->l->a_tar = a_tar / 2;
      v->r->a_tar = a_tar / 2;
    }
    else
    {
      v->l->a_tar = a_tar * 2;
      v->r->a_tar = a_tar * 2;
    }
  //}

  FAST(L,k, v->l->a_tar, v->l->N, v->l);
  FAST(L,k, v->r->a_tar, v->r->N, v->r);
}

// a = width / height

float CalcA(node *v)
{
  if (v->split != "")
  {
    auto al = CalcA(v->l);
    auto ar = CalcA(v->r);
    if (v->split == "V")
    {
      v->a = al + ar;
    }
    else
      v->a = al*ar / (al + ar);
  }
  return v->a;
}

void AdjustTree(node* v, float th)
{
  if (v->split == "")
    return;
  if (v->split != "")
  {
    if (v->a > v->a_tar*th)
      v->split = "H";
    if (v->a < v->a_tar / th)
      v->split = "V";
  }
  if (v->split == "V")
  {
    v->l->a_tar = v->a_tar / 2;
    v->r->a_tar = v->a_tar / 2;
  }
  else
  {
    v->l->a_tar = v->a_tar * 2;
    v->r->a_tar = v->a_tar * 2;
  }
  AdjustTree(v->l, th);
  AdjustTree(v->r, th);
}

template<class T>
T copy(const T& value)
{
  auto output = value;
  return output;
}

void PosCalc(node* v)
{
  if (v->split == "H")
  {
    v->l->width = v->width;
    v->l->height = v->l->width / v->l->a;
    v->l->x = v->x;
    v->l->y = v->y;
    v->r->width = v->width;
    v->r->height = v->height - v->l->height;
    v->r->x = v->x;
    v->r->y = v->y + v->l->height;
  }
  if (v->split == "V") 
  {
    v->l->height = v->height;
    v->l->width = v->height*v->l->a;
    v->l->x = v->x;
    v->l->y = v->y;
    v->r->width = v->width - v->l->width;
    v->r->height = v->height;
    v->r->x = v->x + v->l->width;
    v->r->y = v->y;
  }
  if (v->split == "")
  {
    return;
  }
  PosCalc(v->l);
  PosCalc(v->r);
}

void fill(Mat& output, node* v)
{
  if (v->split == "")
  {
    Size size(v->width, v->height);
    auto img = v->image;
    resize(img, img, size);
    for (int i = 0; i < img.rows; i++)
    {
      for (int j = 0; j < img.cols; j++)
      {
        output.at<cv::Vec3b>(i + v->y, j + v->x) = img.at<cv::Vec3b>(i, j);
      }
    }
    return;
  }
  fill(output, v->l);
  fill(output, v->r);
}

int main()
{
  float desirable_height = 500;
  vector<Mat> images;
  vector<float> k;
  float a_ideal = 1;
  for (int i = 0; i <20; i++)
    images.push_back(imread("image_" + to_string(i) + ".jpg"));

  std::sort(images.begin(), images.end(), [](Mat a, Mat b)
  {
    float k1 = (float) a.cols / a.rows;
    float k2 = (float) b.cols / b.rows;
    return k1 < k2;
  });

  for (int i = 0; i < images.size(); i++)
    k.push_back((float)images[i].cols / images[i].rows);

  node* v = new node();
  v->N = images.size();
  v->a_tar = a_ideal;
  FAST(copy(images), copy(k), a_ideal, images.size(), v);
  CalcA(v);
  for (int i = 0; i < 200; i++)
  {
    AdjustTree(v, 1.5);
    CalcA(v);
  }
  float width = desirable_height * v->a;
  v->height = desirable_height;
  v->width = width;
  v->x = 0;
  v->y = 0;
  PosCalc(v);
  Mat output(Size(v->width, v->height), images[0].type());
  cout << v->a << endl;
  fill(output, v);
  imshow("output", output);
  waitKey(0);
  system("pause");
  return 0;
}