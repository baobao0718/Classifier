#include "VQFileRead.h"
#include"Transform.h"
#include<fstream>
#include<cmath>
#include<iostream>
using namespace std;
#include<math.h>
VQFileRead::VQFileRead(void)
{
}

VQFileRead::VQFileRead(string codebook_address,string indices_address,int DQ,int DL,int L,int K,int M)
{
	this->codebook_address = codebook_address;
		this->indices_address = indices_address;
		this->DQ =DQ;
		this->DL =DL;
		this->L =L;
		this->K = K;
		this->M = M;
		
}
void VQFileRead::ReadCodeBook()
{
	int index=0;
	char tembyteback[8];
	char *ByteCodeBook=new char[L*DQ*8+1];
	unsigned char tembyte[8];
	float *FCodeBook=new float[L*DQ];
	FILE *fp=fopen(codebook_address.c_str(),"rb");
	//FILE *fp=fopen("D:\\蒲俊奇转交\\helloworld_zou_new\\JAVA\\classsigma.txt","rb");
	fseek(fp,0,SEEK_END); 
	int n=ftell(fp);
	ByteCodeBook[L*DQ*8]=0;
	//char *buffer=new char[n];
	//char tembyte[4];
	fseek(fp,0,SEEK_SET);
	//fgets(buffer,n,fp);
	size_t sRet=fread(ByteCodeBook,sizeof(char),n,fp);
	// ifstream winf; 
	// winf.open(codebook_address,ios::binary); // 改为你要打开的文件名
	//winf.seekg(0, ios::end);
	//int length = winf.tellg();
	//winf.seekg (0, ios::beg);
	//char  *buffer= new char [length+1];
	//buffer[length]=0;
	//ByteCodeBook[L*DQ*8]=0;
	//winf.read (ByteCodeBook,length);
	//winf.close();
	for(int i=0;i!=L*2;i++)
	{	
		
		double   f=*(double*)(ByteCodeBook+index); 
		FCodeBook[i]=f;
		//cout<<FCodeBook[i]<<endl;
		//cout<<f<<endl;
		index+=8;
	}
		
	for(int j=0;j!=DQ;j++)
		for(int i=0;i!=L;i++)
		{
				CodeBook[i][j]=FCodeBook[j*L+i];
				//System.out.println((i+1)+"codebook "+(j+1)+" "+CodeBook[i][j]);
				//cout<<i+1<<"codebook"<<j+1<<" "<<CodeBook[i][j]<<endl;
		}
	fclose(fp);
}
void VQFileRead::ReadIndices()
{
	int bitnum = (int)ceil(log((double)L)/log((double)2));
	 char *ByteIndices = new  char[M*K*(DL/DQ)+1];
	 FILE *fp=fopen(indices_address.c_str(),"rb");
	//FILE *fp=fopen("D:\\蒲俊奇转交\\helloworld_zou_new\\JAVA\\classsigma.txt","rb");
	fseek(fp,0,SEEK_END); 
	int n=ftell(fp);
	ByteIndices[M*K*(DL/DQ)]=0;
	//char *buffer=new char[n];
	//char tembyte[4];
	fseek(fp,0,SEEK_SET);
	//fgets(buffer,n,fp);
	size_t sRet=fread(ByteIndices,sizeof(char),n,fp);
	//  ifstream winf; 
	// winf.open(codebook_address,ios::binary); // 改为你要打开的文件名
	//winf.seekg(0, ios::end);
	//int length = winf.tellg();
	//winf.seekg (0, ios::beg);
	//char  *buffer= new char [length+1];
	//buffer[length]=0;
	//ByteIndices[M*K*(DL/DQ)]=0;
	//winf.read (ByteIndices,length);
	//winf.close();
	for (int j=0;j!=K*(DL/DQ);j++)
		for (int i=0;i!=M;i++)
		{
				//Indices[i][j]=ByteIndices[j*M+i];
			Indices[i][j]=*(ByteIndices+j*M+i);
				//  System.out.println((i+1)+" indices "+(j+1)+" "+(Indices[i][j]&0xFF)+"   "+CodeBook[(Indices[i][j]&0xFF)-1][0]);
			//cout<<i+1<<"indices"<<j+1<<" "<<(int)Indices[i][j]<<endl;
		}
	fclose(fp);
}
VQFileRead::~VQFileRead(void)
{
}
