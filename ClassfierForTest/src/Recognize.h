#pragma once
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <cfloat>
#include <math.h>
#include <fstream>
#include <vector>
using namespace std;
#include "VQFileRead.h"
#include"DataUnit.h"
#include"MyStroke.h"
#include"P2DMNClass.h"
#include"Feature.h"
#include"DDA.h"
class Recognize {
public:
	Recognize(void);
	~Recognize(void);
	void recognition(list<DataUnit> &lst);
private:
	int ClassNum;
	int GroupNum;
	VQFileRead *vqfileread;
	boost::unordered_map<int, int> classtoindex;
	void BiMatrix(double a[1][512], double b[512][160], float z[1][160]);
	void DDA_disp(list<MyStroke> &recognizeTable, short test[64][64]);
	void FindminTmp(double distance[], int k, int n, int Grouplabel[]);
	void Findmin(double distance[], int k, int n, int Grouplabel[]);
	int Min(double array[], int n);
	int Max(int array[], int n);
	double Cal_Euclid_Dis(float**input, int index);
	void readdataone(string file, double **matrix, int Row, int Col);
	void readData(string file, double matrix[], int Col);
	void readData(string file, list<list<double> > &Classingroup, int GroupNum);
	void readlable(string file);
	double MQDF(float**input, int k, int index, double classsigma);
	void getVector(DataUnit &charUnit, list<MyStroke> &recognizeTable);
	void get128CharUnit(DataUnit &charUnit);
	void extractChar(DataUnit &dataUnit);
	double CMF(int cmfclasslabel, int cmfsimilarclasslabel, float** input,
			int k, double mqdf, double classsigma);
public:
	string classifier(list<MyStroke> &recognizeTable_o);
	list<MyStroke> transtosmall(list<MyStroke> &recognizeTable);
};

