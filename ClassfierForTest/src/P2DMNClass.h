#pragma once
#include<list>
using namespace std;
#include"MyStroke.h"
#include"ReturnValue.h"
#include "ReturnMoment.h"
class P2DMNClass
{
public:
	P2DMNClass(void);
	~P2DMNClass(void);
	 list<MyStroke> P2DMN(short matrix[64][64],list<MyStroke> recognizeTable);
	 ReturnValue centroid(short matrix[64][64]);
	 ReturnValue centroid_float(float matrix[64][64]);
	 float *BiMatrixPr2D(float *a,float*b,int numofarray);
	 float* BiMatrix(float a[64][1],float *b,int numofarray);
	 void Inner(float *a,short b[64][64],float z[64][64]);
	 float* transmatrix(float a[],int n,int numofarray);
	 float* transmatrix_short(short a[],int n);
	 returnMoment moment(float matrix[64][64],ReturnValue tmp);
	  float* Transpose(float* matr);
	 void weight(short matrix[64][64]);
	 void pr1D(short matrix[64][64]);
	 void pr2D(short matrix[64][64]);
private:
	int xc,yc;
	int Y[64];
	int X[64];

	float Y1[64][64];		/**  存储变化后的Y坐标  **/
	float X1[64][64];		/**  存储变化后的X坐标  **/
	float w1_Y[64],w2_Y[64],w3_Y[64],w1_X[64],w2_X[64],w3_X[64];
	short x1[64],x2[64],x3[64],y1[64],y2[64],y3[64];
};

