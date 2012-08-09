#pragma once
#include <string>
#include <list>
using namespace std;
class ListTable
{
public:
	ListTable(void);
	~ListTable(void);
public:
	static string Labels;
	static double C[316][160];
	static list< list<double> >Classingroup;
	static double eigvector[512][160];
	static double u[3755][160];
	static double d[3755][75];
	static float v[20*160][8];
	static double classsigma[3755];
	 static list<string>recognizeT;
	// static double C1[316*160];
	// static float *v;
	//static double a;
	
};

