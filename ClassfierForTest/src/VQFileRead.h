#pragma once
#include <string>
using namespace std;
class VQFileRead
{
public:
	VQFileRead(void);
	VQFileRead(string codebook_address,string indices_address,int DQ,int DL,int L,int K,int M);
	void ReadCodeBook();
	void ReadIndices();
	~VQFileRead(void);
public:
	//unsigned char 
	int DQ;
	int DL;
	int L;
	int K;
	int M;
	string codebook_address;
	string indices_address;
	float CodeBook[255][2];
	char Indices[3755][8*80];//byte
};

