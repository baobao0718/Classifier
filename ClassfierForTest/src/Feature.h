#pragma once
#include<list>
using namespace std;
#include"distance.h"
#include"MyStroke.h"
class Feature
{

public:
	Feature(void);
	~Feature(void);
	void FeatureData(list<MyStroke> vet, list<MyStroke> vet_o,double B[1][512]);
	list<Distance*> DDA_w(BasePoint p1, BasePoint p2);
	void Transpose(float matr[64][64]);
	void Sampled(float Char[64][64], int N,double feature[64]);
	float Gaussian(double deta, int lanbuta, int x, int y);
	void gaussBlur(float data[64][64], double sigma, double radius);
	//float** Transpose(float** matr);
	//list<Distance> DDA_w(BasePoint p1, BasePoint p2);//gaicheng daxiede le Distance
	//void gaussBlur(float** data, double sigma, double radius);
	//double* Sampled(float** Char, int N);
	//float Gaussian(double deta, int lanbuta, int x, int y);
	//double** Inner(double **a, double **b);
private:
	float D0 [64][64];
	float D1 [64][64];
	float D2 [64][64];
	float D3 [64][64];
	float D4 [64][64];
	float D5 [64][64];
	float D6 [64][64];
	float D7 [64][64];
};

