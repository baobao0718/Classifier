#include "P2DMNClass.h"
#include <cmath>
#include<iostream>
using namespace std;

P2DMNClass::P2DMNClass(void)
{
}
list<MyStroke>P2DMNClass::P2DMN(short matrix[64][64],list<MyStroke> recognizeTable)
{
	list<MyStroke> RecognizeTable1;
	for(int i=0;i<64;i++)	//求反1->0,0->1
	{
		for(int j=0;j<64;j++)
		{
			matrix[i][j]=(short) (1-matrix[i][j]);
			//*((short*)matrix + 64*i + j)=(short)(1-*((short*)matrix + 64*i + j));
		}
	}
	weight(matrix);
	pr1D(matrix);
	pr2D(matrix);
	list<MyStroke>::iterator it=recognizeTable.begin();
	list<BasePoint>md;
	for(int i=0;i<recognizeTable.size();i++,it++)
	{
		MyStroke tmp;
		md.clear();
		md=(*it).getPoints();
		list<BasePoint>::iterator itb=md.begin();
		for(int j=0;j<(*it).getPointssize();j++,itb++)
		{
			short colt=(*itb).getX();
			short rowt=(*itb).getY();
			//cout<<rowt<<endl;
			// cout<<"p2dmn:"<<colt<<" "<<rowt<<endl;
			short col=(short) X1[rowt][colt];
			short row=(short) Y1[rowt][colt];

			col=(col<1)?1:col;
			col=(col>64)?64:col;
			row=(row<1)?1:row;
			row=(row>64)?64:row;
			col--;row--;
			//RecognizeTable.get(i).getPoints().set(j, new BasePoint(col,row));
			tmp.addPoint(BasePoint(col,row));

		}
		RecognizeTable1.push_back(tmp);
	}
	return RecognizeTable1;
}

/**
 * 计算权重(w0=0.75)
 *
 * */
void P2DMNClass::weight(short matrix[64][64])
{
	ReturnValue tmp;
	tmp=centroid(matrix);
	xc=tmp.xc_in;
	yc=tmp.yc_in;
	for(int i=0;i<64;i++)
	{
		Y[i]=i+1;
		X[i]=i+1;
		w1_Y[i]=0;
		w3_Y[i]=0;
		w2_Y[i]=0;
		w1_X[i]=0;
		w2_X[i]=0;
		w3_X[i]=0;
	}
	for(int i=0;i<xc;i++)
	{
		w1_X[i]=(float) (0.75*((1-(float)X[i]/xc)));
		w2_X[i]=1-w1_X[i];
	}
	for(int i=0;i<yc;i++)
	{
		w2_Y[i]=(float)Y[i]/yc;
		w1_Y[i]=1-(float)Y[i]/yc;

	}
	for(int i=xc;i<64;i++)
	{
		w3_X[i]=(float) (0.75*((X[i]-(float)xc))/(64-xc));
		w2_X[i]=1-w3_X[i];
	}
	for(int i=yc;i<64;i++)
	{
		w3_Y[i]=(Y[i]-(float)yc)/(64-yc);
		w2_Y[i]=1-w3_Y[i];
	}
}
/**
 * 计算质心以及行/列密度
 * */
ReturnValue P2DMNClass::centroid(short matrix[64][64])
{
	ReturnValue tmp;
	float whole=0;
	for(int i=0;i<64;i++)
		for(int j=0;j<64;j++)
			//whole+=*((short*)matrix + 64*i + j);
			whole+=matrix[i][j];
	float Xsum=0,Ysum=0;
	for(int col=0;col<64;col++)
	{
		int sum=0;
		for(int j=0;j<64;j++)
			//sum+=*((short*)matrix + 64*j + col);
			sum+=matrix[j][col];
		Xsum+=(col+1)*sum;
	}
	for(int row=0;row<64;row++)
	{
		int sum=0;
		for(int j=0;j<64;j++)
			//sum+=*((short*)matrix + 64*row + j);
			sum+=matrix[row][j];
		Ysum+=(row+1)*sum;
	}
	tmp.xc_in=(int)(Xsum/whole+0.5);
	tmp.yc_in=(int)(Ysum/whole+0.5);
	if(whole==0)
	{
		tmp.xc_in=(64/2);
		tmp.yc_in=(64/2);
		whole=1;
	}
	for(int i=0;i<64;i++)
	{
		int sum=0;
		for(int j=0;j<64;j++)
			//sum+=*((short*)matrix + 64*j + i);
			sum+=matrix[j][i];
		tmp.prox_in[i]=sum/whole;
		//System.out.println(tmp.prox_in[i]);
	}
	for(int i=0;i<64;i++)
	{
		int sum=0;
		for(int j=0;j<64;j++)
			//sum+=*((short*)matrix + 64*i + j);
			sum+=matrix[i][j];
		tmp.proy_in[i]=sum/whole;
		//System.out.println(tmp.proy_in[i]);
	}
	return tmp;
}
ReturnValue P2DMNClass::centroid_float(float matrix[64][64])
{
	ReturnValue tmp;
	float whole=0;
	for(int i=0;i<64;i++)
		for(int j=0;j<64;j++)
			whole+=matrix[i][j];

	//if(whole==0)

	float Xsum=0,Ysum=0;
	for(int col=0;col<64;col++)
	{
		float sum=0;
		for(int j=0;j<64;j++)
			sum+=matrix[j][col];
		Xsum+=(col+1)*sum;
	}

	for(int row=0;row<64;row++)
	{
		float sum=0;
		for(int j=0;j<64;j++)
			sum+=matrix[row][j];
		Ysum+=(row+1)*sum;
	}


	if(whole==0)
	{
//			System.out.println("whole==0");
		tmp.xc_in=(64/2);
		tmp.yc_in=(64/2);
		whole=1;
	}else
	{
		tmp.xc_in=(int)(Xsum/whole+0.5);
		tmp.yc_in=(int)(Ysum/whole+0.5);
	}
	for(int i=0;i<64;i++)
	{
		float sum=0;
		for(int j=0;j<64;j++)
			sum+=matrix[j][i];
		tmp.prox_in[i]=sum/whole;
	}
	for(int i=0;i<64;i++)
	{
		float sum=0;
		for(int j=0;j<64;j++)
			sum+=matrix[i][j];
		tmp.proy_in[i]=sum/whole;
	}
	return tmp;
}
void P2DMNClass::pr1D(short matrix[64][64])
{
	float dy1[64][64] ;
	float dy2[64][64] ;
	float dy3[64][64] ;
	float dx1[64][64] ;
	float dx2[64][64] ;
	float dx3[64][64] ;
	float tmp[64][1];
	ReturnValue tmpvalue;
	returnMoment tmpmoment;
	for(int i=0;i<64;i++)
		tmp[i][0]=1;

	Inner(BiMatrix(tmp,transmatrix(w1_X,64,64),64),matrix,dy1);
	Inner(BiMatrix(tmp,transmatrix(w2_X,64,64),64),matrix,dy2);
	Inner(BiMatrix(tmp,transmatrix(w3_X,64,64),64),matrix,dy3);
	Inner(Transpose(BiMatrix(tmp,transmatrix(w1_Y,64,64),64)),matrix,dx1);
	Inner(Transpose(BiMatrix(tmp,transmatrix(w2_Y,64,64),64)),matrix,dx2);
	Inner(Transpose(BiMatrix(tmp,transmatrix(w3_Y,64,64),64)),matrix,dx3);
	tmpvalue=centroid_float(dx1);
		 /*for(int i=0;i<64;i++)F
		 {
			 for(int j=0;j<64;j++)
				 System.out.print(dx1[i][j]);
			 System.out.println();
		 }*/
	tmpmoment=moment(dx1,tmpvalue);
	//x1=tmpmoment.X;
	for(int i=0;i<64;i++)
	{
		x1[i]=tmpmoment.X[i];
		//cout<<"x1:"<<x1[i]<<endl;
	}
	tmpvalue=centroid_float(dx2);
	tmpmoment=moment(dx2,tmpvalue);
	//x2=tmpmoment.X;
	for(int i=0;i<64;i++)
	{
		x2[i]=tmpmoment.X[i];
		//cout<<"x2:"<<x2[i]<<endl;
	}
	tmpvalue=centroid_float(dx3);
	tmpmoment=moment(dx3,tmpvalue);
	//x3=tmpmoment.X;
	for(int i=0;i<64;i++)
	{
		x3[i]=tmpmoment.X[i];
		//cout<<"x3:"<<x3[i]<<endl;
	}
	tmpvalue=centroid_float(dy1);
	tmpmoment=moment(dy1,tmpvalue);
	//y1=tmpmoment.Y;
	for(int i=0;i<64;i++)
	{
		y1[i]=tmpmoment.Y[i];
	}
	tmpvalue=centroid_float(dy2);
	tmpmoment=moment(dy2,tmpvalue);
	//y2=tmpmoment.Y;
	for(int i=0;i<64;i++)
		y2[i]=tmpmoment.Y[i];

	tmpvalue=centroid_float(dy3);
	tmpmoment=moment(dy3,tmpvalue);
	//y3=tmpmoment.Y;
	for(int i=0;i<64;i++)
		y3[i]=tmpmoment.Y[i];
}
void P2DMNClass::pr2D(short matrix[64][64])
{
	ReturnValue tmp;
	tmp=centroid(matrix);
	float Y1_tmp [64][64];
	float *w1_y=new float[tmp.yc_in];
	float* w2_y=new float[tmp.yc_in];
	float* w1_y_l=new float[64-tmp.yc_in];
	float* w2_y_l=new float[64-tmp.yc_in];
	float* w1_x=new float[tmp.xc_in];
	float* w2_x=new float[tmp.xc_in];
	float* w1_x_l=new float[64-tmp.xc_in];
	float* w2_x_l=new float[64-tmp.xc_in];
	for(int i=0;i<tmp.yc_in;i++)
	{
		w1_y[i]=w1_Y[i];
		w2_y[i]=w2_Y[i];
	}
	float *matr,*matr2,*matr_l,*matr2_l,*matr_x,*matr2_x,*matrx_l,*matr2x_l;
	matr=new float[tmp.yc_in*64];
	matr2=new float[tmp.yc_in*64];
	matr_l=new float[(64-tmp.yc_in)*64];
	matr2_l=new float[(64-tmp.yc_in)*64];
	matr_x=new float[tmp.xc_in*64];
	matr2_x=new float[tmp.xc_in*64];
	matrx_l=new float[(64-tmp.xc_in)*64];
	matr2x_l=new float[(64-tmp.xc_in)*64];
	matr=BiMatrixPr2D(transmatrix(w1_y,1,tmp.yc_in),transmatrix_short(x1,64),tmp.yc_in);
	matr2=BiMatrixPr2D(transmatrix(w2_y,1,tmp.yc_in),transmatrix_short(x2,64),tmp.yc_in);
	for(int i=0;i<tmp.yc_in;i++)
	for(int j=0;j<64;j++)
	{
		X1[i][j]=*((float*)matr + 64*i + j)+*((float*)matr2 + 64*i + j);
	}
	for(int i=tmp.yc_in;i<64;i++)
	{
		w1_y_l[i-tmp.yc_in]=w2_Y[i];
		w2_y_l[i-tmp.yc_in]=w3_Y[i];
	}

	matr_l=BiMatrixPr2D(transmatrix(w1_y_l,1,(64-tmp.yc_in)),transmatrix_short(x2,64),(64-tmp.yc_in));
	matr2_l=BiMatrixPr2D(transmatrix(w2_y_l,1,(64-tmp.yc_in)),transmatrix_short(x3,64),(64-tmp.yc_in));
	for(int i=tmp.yc_in;i<64;i++)
		for(int j=0;j<64;j++)
			X1[i][j]=*((float*)matr_l + 64*(i-tmp.yc_in) + j)+*((float*)matr2_l + 64*(i-tmp.yc_in) + j);


	for(int i=0;i<tmp.xc_in;i++)
	{
			w1_x[i]=w1_X[i];
			w2_x[i]=w2_X[i];
			//cout<<w1_x[i]<<"  "<<w2_x[i]<<endl;
	}
	matr_x=BiMatrixPr2D(transmatrix(w1_x,1,tmp.xc_in),transmatrix_short(y1,64),tmp.xc_in);
	matr2_x=BiMatrixPr2D(transmatrix(w2_x,1,tmp.xc_in),transmatrix_short(y2,64),tmp.xc_in);
	//for(int m=0;m<64;m++)
	//	cout<<y1[m]<<"  "<<y2[m]<<endl;
	for(int i=0;i<tmp.xc_in;i++)
		for(int j=0;j<64;j++)
		{
			Y1_tmp[i][j]=*((float*)matr_x + 64*i + j)+(*((float*)matr2_x + 64*i + j));
			//cout<<"y1:"<<Y1_tmp[i][j]<<" matr_x:"<<*((float*)matr_x + 64*i + j)<<"matr2_x:"<<(*((float*)matr2_x + 64*i + j))<<endl;
		}
	for(int i=tmp.xc_in;i<64;i++)
	{
		w1_x_l[i-tmp.xc_in]=w2_X[i];
		w2_x_l[i-tmp.xc_in]=w3_X[i];
	}
	matrx_l=BiMatrixPr2D(transmatrix(w1_x_l,1,64-tmp.xc_in),transmatrix_short(y2,64),64-tmp.xc_in);
	matr2x_l=BiMatrixPr2D(transmatrix(w2_x_l,1,64-tmp.xc_in),transmatrix_short(y3,64),64-tmp.xc_in);
	for(int i=tmp.xc_in;i<64;i++)
		for(int j=0;j<64;j++)
		{
			Y1_tmp[i][j]=*((float*)matrx_l + 64*(i-tmp.xc_in) + j)+(*((float*)matr2x_l + 64*(i-tmp.xc_in) + j));
			//cout<<"y1:"<<Y1_tmp[i][j]<<" matr_x:"<<*((float*)matrx_l + 64*(i-tmp.xc_in) + j)<<"matr2_x:"<<(*((float*)matr2x_l + 64*(i-tmp.xc_in) + j))<<endl;
		}
	for(int i=0;i<64;i++)
		for(int j=0;j<64;j++)
		{
			X1[i][j]=(int)(X1[i][j]+0.5);
			Y1_tmp[i][j]=(int)(Y1_tmp[i][j]+0.5);
			if(X1[i][j]<1)
				X1[i][j]=1;
			if(X1[i][j]>64)
				X1[i][j]=64;
			if(Y1_tmp[i][j]<1)
				Y1_tmp[i][j]=1;
			if(Y1_tmp[i][j]>64)
				Y1_tmp[i][j]=64;
		}
	for(int i=0;i<64;i++)
	{
		for(int j=0;j<64;j++)
		{
			Y1[i][j]=Y1_tmp[j][i];

		}

	}

}

/**
 * 返回向量a*b构成的矩阵
 * */
float *P2DMNClass::BiMatrixPr2D(float *a,float*b,int numofarray)
{
	float *z=new float[numofarray*64];
	for(int xx=0;xx<numofarray;xx++){
		for(int yy=0;yy<64;yy++){
			float result=0;
			for(int oo=0;oo<1;oo++){
				result=result+(*((float*)a + 1*xx + oo))*(*((float*)b + 1*oo + yy));
			}
			*((float*)z + 64*xx + yy)=result;
		}
	}
	return z;
}

/**
 * 返回向量a*b构成的矩阵
 * */
float* P2DMNClass::BiMatrix(float a[64][1],float *b,int numofarray)
{
	float *z=new float[64*numofarray];
	for(int xx=0;xx<numofarray;xx++){
		for(int yy=0;yy<64;yy++){
			float result=0;
			for(int oo=0;oo<1;oo++){
				result=result+a[xx][oo]*(*((float*)b + 1*oo + yy));
			}
			*((float*)z + 64*xx + yy)=result;
		}
	}
	return z;
}

/**
 * 矩阵a与b的内积(同位置相乘)，结果存于z
 * */
void P2DMNClass::Inner(float *a,short b[64][64],float z[64][64])
{

	for(int i=0;i<64;i++)
			for(int j=0;j<64;j++)
			{
				//cout<<*((float*)a + 64*i + j)<<endl;
				z[i][j]= (*((float*)a + 64*i + j)*((float)b[i][j]));
				//cout<<"P2DMNClass Inner"<<z[i][j]<<endl;
			}
}

float* P2DMNClass::transmatrix(float a[],int n,int numofarray)
{
	int m = numofarray/n;

	float *b=new float[m*n];
	int num = -1;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			num++;
			*((float*)b + n*i + j) = a[num];
		}
	}
    return b;
}
/**
 *
 * */
float* P2DMNClass::transmatrix_short(short a[],int n)
{
	int m = 64/n;
	float *b=new float[m*n];
	int num = -1;

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				num++;
				*((float*)b + n*i + j) = a[num];
			}
		}
    return b;
}

/**
 * 计算矩
 * */
returnMoment P2DMNClass::moment(float matrix[64][64],ReturnValue tmp)
{
	returnMoment T;
	short X[64];
	short Y[64];
	short xcn=64/2;
	short ycn=64/2;
	double u20=0,u02=0,cigmax=0,cigmay=0;
	for(int i=0;i<64;i++)
	    u20=u20+(i+1-tmp.xc_in)*(i+1-tmp.xc_in)*tmp.prox_in[i];

	for(int i=0;i<64;i++)
	    u02=u02+(i+1-tmp.yc_in)*(i+1-tmp.yc_in)*tmp.proy_in[i];

	if(u20==0)
	    u20=1;
	if(u02==0)
	    u02=1;
	cigmax=4*sqrt(u20);
	cigmay=4*sqrt(u02);

	for(int col=0;col<64;col++)
	{
	    short COL=(short) ((64*((float)col+1-(float)tmp.xc_in)/cigmax+xcn)+0.5);
	    if(COL<1)
	    	COL=1;
	    if(COL>64)
	    	COL=64;
	    X[col]=COL;
        short ROW=(short) ((64*((float)col+1-(float)tmp.yc_in)/cigmay+ycn)+0.5);
	    if(ROW<1)
	    	ROW=1;
	    if(ROW>64)
	    	ROW=64;
        Y[col]=ROW;
	}
	for(int i=0;i<64;i++)
	{
		T.X[i]=X[i];
		T.Y[i]=Y[i];
	}
	return T;
}
 float* P2DMNClass::Transpose(float* matr)
 {
	/* float **b;
	 b=new float*[64];
	 for(int i=0;i<64;i++)
	 {
		b[i]=new float[64];
	 }*/
	float *b=new float[64*64];
	for(int i=0;i<64;i++)
		for(int j=0;j<64;j++)
		{
			*((float*)b + 64*j + i)=*((float*)matr + 64*i + j);
			//b[j][i]=matr[i][j];
		}
	return b;
 }
P2DMNClass::~P2DMNClass(void)
{
}
