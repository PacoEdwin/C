#include<opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <math.h>
using namespace cv;
using namespace std;

// h/w
const float ideal_ratio = 0.7;

Size2f F2_up(int i, int j, vector<float> k, Size2f size)
{
  int w = size.width;
  float x = k[i] * w / (k[i] + k[j]);
  float y = k[j] * x;
  return Size2f(w, size.height + y);
}
Mat Mat2_up(int i, int j, vector<float> k, vector<Mat> image, Mat current)
{
  int w = current.cols;
  float x = k[i] * w / (k[i] + k[j]);
  float y = k[j] * x;

  auto image_i = image[i];
  auto image_j = image[j];
  resize(image_i, image_i, Size(x, y));
  resize(image_j, image_j, Size(w - x, y));
  Mat output(Size(w, current.rows + y), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + current.rows, l)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_j.rows; k++)
  {
    for (int l = 0; l < image_j.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + current.rows, image_i.cols + l)[z] = image_j.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

Size2f F2_side(int i, int j, vector<float> k, Size2f size)
{
  return Size2f(size.width + size.height / (k[i] + k[j]), size.height);
}

Mat Mat2_side(int i, int j, vector<float> k, vector<Mat> image, Mat current)
{
  int h = current.rows;
  float y = h / (k[i] * (1 / k[j] + 1 / k[i]));
  float x = h / (k[i] + k[j]);

  auto image_i = image[i];
  auto image_j = image[j];
  resize(image_j, image_j, Size(x, y));
  resize(image_i, image_i, Size(x, h - y));

  Mat output(Size(current.cols + x, h), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l+current.cols)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_j.rows; k++)
  {
    for (int l = 0; l < image_j.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + image_i.rows, current.cols + l)[z] = image_j.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

Size2f F1_up(int i, vector<float> k, Size size)
{
  return Size2f(size.width, k[i] * size.width + size.height);
}

Mat Mat1_up(int i, vector<float> k, vector<Mat> image, Mat current)
{
  int w = current.cols;
  int y = w*k[i];
  auto image_i = image[i];
  resize(image_i, image_i, Size(w, y));

  Mat output(Size(w, current.rows + y), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k + current.rows, l)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

Size2f F1_side(int i, vector<float> k, Size2f size)
{
  return Size2f(size.width + size.height / k[i], size.height);
}

Mat Mat1_side(int i, vector<float> k, vector<Mat> image, Mat current)
{
  int h= current.rows;
  int x = h/k[i];
  auto image_i = image[i];
  resize(image_i, image_i, Size(x, h));

  Mat output(Size(current.cols + x, h), current.type());

  for (int k = 0; k < current.rows; k++)
  {
    for (int l = 0; l < current.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k, l)[z] = current.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  for (int k = 0; k <image_i.rows; k++)
  {
    for (int l = 0; l < image_i.cols; l++)
    {
      for (int z = 0; z < current.channels(); z++)
      {
        output.at<cv::Vec3b>(k , l + current.cols)[z] = image_i.at<cv::Vec3b>(k, l)[z];
      }
    }
  }

  return output;
}

vector<Mat> er(vector<Mat> images, int i, int j = -1)
{
  images.erase(images.begin() + i);
  if (j != -1)
    images.erase(images.begin() + j - 1);
  return images;
}
vector<float> er_k(vector<float> k, int i, int j = -1)
{
  k.erase(k.begin() + i);
  if (j != -1)
    k.erase(k.begin() + j - 1);
  return k;
}

struct info
{
  vector<int> indexes;
  bool side;
};

pair<float, vector<info>> arrange(vector<Mat> images, vector<float> k, Size2f current)
{
  vector<float> ratios;
  vector<vector<info>> inf;
  vector<info> infos;
  if (images.size() == 0)
  {
    info s;
    infos.push_back(s);
    auto lol = make_pair(current.height / current.width, infos);
    return lol;
  }

  for (int i = 0; i < images.size(); i++)
  {
    for (int j = i; j < images.size(); j++)
    {
      if (j == i)
      {
        info a, b;

        auto c = arrange(er(images, i), er_k(k, i), F1_up(i, k, current));
        ratios.push_back(c.first);
        inf.push_back(c.second);
        a.side = 0;
        a.indexes.push_back(i);

        c = arrange(er(images, i), er_k(k, i), F1_side(i, k, current));
        ratios.push_back(c.first);
        inf.push_back(c.second);
        b.side = 1;
        b.indexes.push_back(i);

        infos.push_back(a);
        infos.push_back(b);
        continue;
      }
      info a, b;

      auto c = arrange(er(images, i, j), er_k(k, i, j), F2_up(i, j, k, current));
      ratios.push_back(c.first);
      inf.push_back(c.second);
      a.side = 0;
      a.indexes.push_back(i);
      a.indexes.push_back(j);
      infos.push_back(a);

      c = arrange(er(images, i, j), er_k(k, i, j), F2_side(i, j, k, current));
      ratios.push_back(c.first);
      inf.push_back(c.second);
      b.side = 1;
      b.indexes.push_back(i);
      b.indexes.push_back(j);
      infos.push_back(b);
    }
  }

  float min = 100000000000;
  int index = 0;
  for (int i = 0; i < ratios.size(); i++)
  {
    if (abs(ratios[i] - ideal_ratio) < min)
    {
      min = abs(ratios[i] - ideal_ratio), index = i;
    }
  }
  inf[index].push_back(infos[index]);
  return make_pair(ratios[index], inf[index]);
}

Mat decode(vector<info> v, vector<float> k, vector<Mat> images, Mat image)
{
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i].indexes.size() == 1)
    {
      if (v[i].side)
      {
        image = Mat1_side(v[i].indexes[0], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[0]);
      }
      if (!v[i].side)
      {
        image = Mat1_up(v[i].indexes[0], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[0]);
      }
    }
    if (v[i].indexes.size() == 2)
    {
      if (v[i].side)
      {
        image = Mat2_side(v[i].indexes[0], v[i].indexes[1], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        images.erase(images.begin() + v[i].indexes[1] - 1);
        k.erase(k.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[1] - 1);
      }
      if (!v[i].side)
      {
        image = Mat2_up(v[i].indexes[0], v[i].indexes[1], k, images, image);
        //imshow("img", image);
        //waitKey(0);
        images.erase(images.begin() + v[i].indexes[0]);
        images.erase(images.begin() + v[i].indexes[1] - 1);
        k.erase(k.begin() + v[i].indexes[0]);
        k.erase(k.begin() + v[i].indexes[1] - 1);
      }
    }
  }

  return image;
}

int main()
{
  vector<Mat> images;
  for (int i = 0; i < 7; i++)
  {
    string filename = "image_" + to_string(i) + ".jpg";
    Mat read = cv::imread(filename);
    images.push_back(read);
  }

  vector<float> k;
  for (int i = 0; i < images.size(); i++)
  {
    k.push_back((float)images[i].rows / images[i].cols);
    resize(images[i], images[i], Size(100, k[i] * 100));
  }

  auto current = images[0];
  images.erase(images.begin() + 0);
  k.erase(k.begin() + 0);
  auto as = arrange(images, k, current.size());
  cout << as.first << endl;
  auto v = as.second;
  v.erase(v.begin());
  std::reverse(v.begin(), v.end());
  auto output = decode(v,k, images, current);
  imwrite("collge_07f.jpg",output);
  imshow("output", output);
  waitKey(0);
  system("pause");
}
