#include "Feature.h"
#include<math.h>
#include <stdlib.h>
#include<iostream>
//#include<algorithm>
using namespace std;
Feature::Feature(void)
{
	for(int m=0;m<64;m++)
		for(int n=0;n<64;n++)
		{
			D0[m][n]=0.0;
			D1[m][n]=0.0;
			D2[m][n]=0.0;
			D3[m][n]=0.0;
			D4[m][n]=0.0;
			D5[m][n]=0.0;
			D6[m][n]=0.0;
			D7[m][n]=0.0;

		}
}

void Feature::FeatureData(list<MyStroke> vet, list<MyStroke> vet_o,double B[1][512])
{
	list<BasePoint>::iterator basepit,basepit2,basepit_o,basepit_o2;
	list<MyStroke>::iterator vet1=vet.begin();
	list<MyStroke>::iterator vet1_o=vet_o.begin();
	list<Distance*>::iterator ip;
	list<BasePoint> bpp1,bpp2;
	//cout<<vet.size()<<" "<<vet_o.size();
	for (int i = 0; i < vet.size(); i++,vet1++,vet1_o++) {
		bpp1.clear();
		bpp2.clear();
		bpp1=(*vet1_o).getPoints();
		bpp2=(*vet1).getPoints();
		//basepit_o=(*vet1_o).getPoints().begin();
		//basepit=(*vet1).getPoints().begin();
		basepit_o=bpp1.begin();
		basepit_o2=bpp1.begin();
		basepit_o2++;
		basepit=bpp2.begin();
		basepit2=bpp2.begin();
		basepit2++;
		//basepit--;//gaizheng
		//cout<<(*basepit).getY()<<endl;
			for (int j = 1; j < (*vet1).getPointssize(); j++,basepit_o++,basepit_o2++,basepit++,basepit2++) {

				short x = (short) ((*(basepit_o2)).getX() - (*(basepit_o)).getX());
				short y = (short) ((*(basepit_o2)).getY() - (*(basepit_o)).getY());
				// System.out.println(x);System.out.println(y);
				cout<<x<<endl;
				cout<<y<<endl;
				double len = sqrt((double)(x * x + y * y));
				//cout<<len<<endl;
				if ((x == 0) && (y != 0)) {
					if (y > 0) {
						double w1 = 1;
						//cout<<(*basepit).getY()<<endl;//9
						list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
						
						//basepit--;
						int l = point.size();
						ip=point.begin();
						
						for (int k = 0; k < l; k++,ip++)
							{
								D2[(int) ((*ip)->x)][(int) ((*ip)->y)] = (float) (w1 * ((*ip)->Dis));
								//cout<<"here1:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
						}
						// System.out.println("D2");
						// System.out.println(l);
					} else {
						double w1 = 1;
						list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
						ip=point.begin();
						//basepit--;
						int l = point.size();
						for (int k = 0; k < l; k++,ip++)
						{
							D6[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
							//cout<<"here2:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
						}
						// System.out.println("D6");
						// System.out.println(l);
					}
				}// if((x==0)&&(y!=0))

				if ((y == 0) && (x != 0)) {
					if (x > 0) {
						double w1 = 1;
						list<Distance*> point = DDA_w((*basepit)/*vet.get(i).getPoints().get(j - 1)*/,(*(basepit2))/*vet.get(i).getPoints().get(j)*/);
						//basepit--;
						ip=point.begin();
						int l = point.size();
						for (int k = 0; k < l; k++,ip++) {
							
							D0[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
							//cout<<"here 3:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
						}
						// System.out.println("D0");
						// System.out.println(l);
					} else {
						double w1 = 1;
						list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
						//basepit--;
						int l = point.size();
						ip=point.begin();
						for (int k = 0; k < l; k++,ip++)
						{
							D4[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
							//cout<<"here4:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
						}
						// System.out.println("D4");
						// System.out.println(l);
					}
				}// if((y==0)&&(x!=0))

				if ((x != 0) && (y != 0)) {
					if ((float) y / (float) x > 0) {
						if (((float) y / (float) x) == 1) {
							if (x > 0) {
								double w1 = 1;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D1[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here5:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							} else {
								double w1 = 1;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++)
								{
									D5[(int)(*ip)->x][(int)(*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here6:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							}
						} else if (x > 0) {
							if (x > y) {
								double w1 = (sqrt((double)2) * (y)) / len;
								double w2 = (x - y) / len;
								// System.out.println("D0、D1");
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D0[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 * (*ip)->Dis);
									D1[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here7:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							} else {
								double w1 = ((y) - (x)) / len;
								double w2 = sqrt((double)2) * (x) / len;

								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D1[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 *(*ip)->Dis);
									D2[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 *(*ip)->Dis);
									//cout<<"here8:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							}
						} else {
							if (abs(x) > abs(y)) {
								double w1 = -sqrt((double)2) * (y) / len;
								double w2 = (((y) - (x))) / len;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D4[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 * (*ip)->Dis);
									D5[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here9:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							} else {
								double w1 = ((x) - (y)) / len;
								double w2 = -sqrt((double)2) * (x) / len;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D5[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 * (*ip)->Dis);
									D6[(int)(*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here10:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}

							}
						}
					}// if(y/x>0)
					else {
						if (((float) y / (float) x) == -1) {
							if (x > 0) {
								double w1 = 1;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++)
								{
									D7[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here11:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							} else {
								double w1 = 1;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++)
								{
									D3[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here12:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							}
						} else if (x > 0) {
							if (abs(x) > abs(y)) {
								double w1 = ((y) + (x)) / len;
								double w2 = -sqrt((double)2) * (y) / len;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D7[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 * (*ip)->Dis);
									D0[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here13:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}

							} else {
								double w1 = sqrt((double)2) * (x) / len;
								double w2 = (-(x) - (y)) / len;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D6[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 * (*ip)->Dis);
									D7[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here14:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}
							}
						} else {
							if (abs(x) > abs(y)) {
								double w1 = sqrt(2.0) * (y) / len;
								double w2 = (-(x) - (y)) / len;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D4[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 * (*ip)->Dis);
									D3[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here15:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;
								}

							} else {
								double w1 = -sqrt(2.0) * (x) / len;
								double w2 = ((y) + (x)) / len;
								//cout<<(*basepit).getX()<<" "<<(*(basepit)).getY()<<" "<<(*basepit2).getX()<<" "<<(*basepit2).getY()<<endl;
								list<Distance*> point = DDA_w((*basepit), (*(basepit2)));
								//basepit--;
								ip=point.begin();
								int l = point.size();
								for (int k = 0; k < l; k++,ip++) {
									D2[(int) (*ip)->x][(int) (*ip)->y] = (float) (w2 * (*ip)->Dis);
									D3[(int) (*ip)->x][(int) (*ip)->y] = (float) (w1 * (*ip)->Dis);
									//cout<<"here16:"<<(*ip)->x<<" "<<(*ip)->y<<" "<<(*ip)->Dis<<endl;

								}
							}
						}
					}
				}// if((x!=0)&&(y!=0))
			}// for
		}// for
		//cout<<D2[32][43]<<endl;
		//cout<<D3[32][43]<<endl;
		//cout<<D2[33][42]<<endl;
		//cout<<D3[33][42]<<endl;
	/*	for(int m=0;m<64;m++)
			for(int k=0;k<64;k++)
				cout<<"M k"<<m<<" "<<k<<" "<<D0[m][k]<<" "<<D1[m][k]<<" "<<D2[m][k]<<" "<<D3[m][k]<<" "<<D4[m][k]<<" "<<D5[m][k]<<" "<<D6[m][k]<<" "<<D7[m][k]<<endl;
		*////////////D中内容正确

		Transpose(D0);
		Transpose(D1);
		Transpose(D2);
		Transpose(D3);
		Transpose(D4);
		Transpose(D5);
		Transpose(D6);
		Transpose(D7);
	/*	for(int m=0;m<64;m++)
			for(int k=0;k<64;k++)
				cout<<"M k"<<m<<" "<<k<<" "<<D0[m][k]<<" "<<D1[m][k]<<" "<<D2[m][k]<<" "<<D3[m][k]<<" "<<D4[m][k]<<" "<<D5[m][k]<<" "<<D6[m][k]<<" "<<D7[m][k]<<endl;
		*/
		gaussBlur(D0, 8, 3.6);
		gaussBlur(D1, 8, 3.6);
		gaussBlur(D2, 8, 3.6);
		gaussBlur(D3, 8, 3.6);
		gaussBlur(D4, 8, 3.6);
		gaussBlur(D5, 8, 3.6);
		gaussBlur(D6, 8, 3.6);
		gaussBlur(D7, 8, 3.6);
	/*	for(int m=0;m<64;m++)
			for(int k=0;k<64;k++)
				cout<<"M k"<<m<<" "<<k<<" "<<D0[m][k]<<" "<<D1[m][k]<<" "<<D2[m][k]<<" "<<D3[m][k]<<" "<<D4[m][k]<<" "<<D5[m][k]<<" "<<D6[m][k]<<" "<<D7[m][k]<<endl;
		*/
		double d0[64];
		double d1[64];
		double d2[64];
		double d3[64];
		double d4[64];
		double d5[64];
		double d6[64];
		double d7[64];
		Sampled(D0, 8,d0);
		Sampled(D1, 8,d1);
		Sampled(D2, 8,d2);
		Sampled(D3, 8,d3);
		Sampled(D4, 8,d4);
		Sampled(D5, 8,d5);
		Sampled(D6, 8,d6);
		Sampled(D7, 8,d7);
		double A[512];
		for (int i = 0; i < 64; i++)
			A[i] = d0[i];
		for (int i = 64; i < 128; i++)
			A[i] = d1[i - 64];
		for (int i = 128; i < 192; i++)
			A[i] = d2[i - 128];
		for (int i = 192; i < 256; i++)
			A[i] = d3[i - 192];
		for (int i = 256; i < 320; i++)
			A[i] = d4[i - 256];
		for (int i = 320; i < 384; i++)
			A[i] = d5[i - 320];
		for (int i = 384; i < 448; i++)
			A[i] = d6[i - 384];
		for (int i = 448; i < 512; i++)
			A[i] = d7[i - 448];
		double min = A[0], max = A[0];
		for (int i = 1; i < 512; i++) {
			if (A[i] > max)
				max = A[i];
			if (A[i] < min)
				min = A[i];
		}
		for (int i = 0; i < 512; i++) {

			A[i] = (0.01 + (A[i] - min) / (max - min) * (0.99 - 0.01));
			A[i] = (pow(A[i], 0.5));
		}
		min = A[0];
		max = A[0];
		for (int i = 1; i < 512; i++) {
			if (A[i] > max)
				max = A[i];
			if (A[i] < min)
				min = A[i];
		}
		for (int i = 0; i < 512; i++) {

			A[i] = (0.01 + (A[i] - min) / (max - min) * (0.99 - 0.01));
			// System.out.println(A[i]);
		}
		//double B[1][512];
		for (int i = 0; i < 512; i++) {
			B[0][i] = A[i];
			// System.out.println(B[0][i]+"  ");
			//cout<<A[i]<<endl;

		}
		
		//return B;
}
void Feature::Transpose(float matr[64][64])
{
	float b[64][64];
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++) {

			b[i][j] = matr[j][i];

		}
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++) {

			matr[i][j] = b[i][j];

		}
		
}
bool comp(const double &lhs, const double &rhs)
{
 return lhs < rhs;
}
list<Distance*> Feature::DDA_w(BasePoint p1, BasePoint p2)
{
	//cout<<"p1:"<<p1.getX()<<" "<<p1.getY()<<endl;
	//cout<<"p2:"<<p2.getX()<<" "<<p2.getY()<<endl;
	float Startx = (float) ((float) p1.getX() - 0.5);
	float Starty = (float) ((float) p1.getY() - 0.5);

	float Endx = (float) ((float) p2.getX() - 0.5);
	float Endy = (float) ((float) p2.getY() - 0.5);

	list<Distance*> Point ;
	list<Distance*> point ;
	list<float> Tmp ;
	list<float> Unique ;
	list<float>tmp;
	list<float>::iterator tmpit,uniit;
	Distance *p = new Distance(Startx, Starty);
	//Distance p;
	//p.x=Startx;
	//p.y=Starty;
	point.push_back(p);
	if ((Startx != Endx) && (Starty != Endy)) {

			float k = (Endy - Starty) / (Endx - Startx);
			float b = Starty - k * Startx;
			// System.out.println(Startx);
			// System.out.println(Starty);
			// System.out.println(k);
			// System.out.println(b);

			if (Startx < Endx) {

				for (float i = (float) ceil((float)((int)(Startx*1000+0.5))/1000); i <= ceil((float)((int)(Endx*1000+0.5))/1000) - 1; i++) {
					Tmp.push_back(i);
				}
				if (Starty < Endy) {
					for (float i = (float) ceil((float)((int)(Starty*1000+0.5))/1000); i <= ceil((float)((int)(Endy*1000+0.5))/1000) - 1; i++) {
						Tmp.push_back((i - b) / k);
						// System.out.println((i-b)/k);
					}
				} else {
					for (float i = (float) ceil((float)((int)(Endy*1000+0.5))/1000); i <= ceil((float)((int)(Starty*1000+0.5))/1000) - 1; i++) {
						Tmp.push_back((i - b) / k);
						// System.out.println((i-b)/k);
					}
				}

			} else {
				for (float i = (float) ceil((float)((int)(Endx*1000+0.5))/1000); i <= ceil((float)((int)(Startx*1000+0.5))/1000) - 1; i++) {
					Tmp.push_back(i);

				}
				if (Starty < Endy) {
					for (float i = (float) ceil((float)((int)(Starty*1000+0.5))/1000); i <= ceil((float)((int)(Endy*1000+0.5))/1000) - 1; i++) {
						Tmp.push_back((i - b) / k);
					}
				} else {
					for (float i = (float) ceil((float)((int)(Endy*1000+0.5))/1000); i <= ceil((float)((int)(Starty*1000+0.5))/1000) - 1; i++) {
						Tmp.push_back((i - b) / k);
					}
				}

			}
			tmpit=Tmp.begin();
			tmp.clear();
			for (int i = 0; i < Tmp.size()&&tmpit!=Tmp.end(); i++,tmpit++) {
				int flag = 0;
				uniit=Unique.begin();
				for (int j = 0; j < Unique.size()&&uniit!=Unique.end(); j++,uniit++) {
					if (abs((*uniit) - (*tmpit)) < 0.00001) {
						flag = 1;
						break;
					}
				}
				if (flag == 0)
					{
						Unique.push_back((*tmpit));
						tmp.push_back(*tmpit);
				}

			}
			Unique.sort(comp);
			tmp.sort(comp);
			list<float>::iterator tm=tmp.begin();
			for(int t=0;(t<(tmp.size()-1))&&(tm!=tmp.end());t++)
			{
				tm++;
			}
			if ((Endx - Startx) < 0) {
				//list<float> tmp = new ArrayList<Float>(Unique);
				Unique.clear();
				for (int i = tmp.size() - 1; i >=0; i--,tm--)
				{
					Unique.push_back((*tm));
					if(tm==tmp.begin())
						break;
				}
				list<float> ::iterator tttt=Unique.begin();
				//for(int m=0;m<Unique.size();m++,tttt++)
				//	cout<<Unique.size()<<" "<<(*tttt)<<endl;
			}
			uniit=Unique.begin();
			for (int i = 0; i < Unique.size(); i++,uniit++){
				point.push_back(new Distance((*uniit), (k * (*uniit) + b)));
			}
		} else if (Startx == Endx) {
			// System.out.println("x相等");

			if (Starty < Endy) {
				for (int i = (int) ceil((float)((int)(Starty*1000+0.5))/1000); i <= ceil((float)((int)(Endy*1000+0.5))/1000) - 1; i++)
					point.push_back(new Distance(Startx, i));
			} else {
				for (int i = (int) ceil((float)((int)(Endy*1000+0.5))/1000); i <= ceil((float)((int)(Starty*1000+0.5))/1000) - 1; i++)
					point.push_back(new Distance(Startx, i));
			}

		} else {
			// System.out.println("y相等");

			if (Startx < Endx) {
				for (int i = (int) ceil((float)((int)(Startx*1000+0.5))/1000); i <= ceil((float)((int)(Endx*1000+0.5))/1000) - 1; i++)
					point.push_back(new Distance(i, Starty));
			} else {
				for (int i = (int) ceil((float)((int)(Endx*1000+0.5))/1000); i <= ceil((float)((int)(Startx*1000+0.5))/1000) - 1; i++)
					point.push_back(new Distance(i, Starty));
			}
		}

		point.push_back(new Distance(Endx, Endy));
		/*
		 * for(int i=0;i<point.size();i++) {
		 * System.out.println(point.get(i).x+"   "+point.get(i).y); }
		 */
	/*	list<Distance*>::iterator ipp=point.begin();
		for(int mm=0;mm<point.size();mm++,ipp++)
		{
			cout<<"point zhi:"<<(*ipp)->x<<"  "<<(*ipp)->y<<endl;
		}*/
		list<Distance*>::iterator pii=point.begin();
		list<Distance*>::iterator pii2=point.begin();
		pii2++;
		//float(int(num*1000+0.5))/1000
		//(float)((int)(((*pii)->x)*1000+0.5))/1000
		for (int i = 0; i < point.size() - 1; i++,pii++,pii2++) {
			short x = (short) ceil(max((float)((int)(((*pii)->x)*1000+0.5))/1000, (float)((int)(((*pii2)->x)*1000+0.5))/1000));
			//pii--;
			short y = (short) ceil(max((float)((int)(((*pii)->y)*1000+0.5))/1000, (float)((int)(((*pii2)->y)*1000+0.5))/1000));
			//pii--;
			double dis = sqrt(pow((*(pii2))->x - (*(pii))->x, 2)+ pow((*(pii2))->y - (*(pii))->y, 2));
			Distance *tmp1 = new Distance(x, y);
			tmp1->Dis = dis;
			Point.push_back(tmp1);
		}
		return Point;
}
void Feature::gaussBlur(float data[64][64], double sigma, double radius)
{
	float b[64][64];
	int x, y, xx, xk, yk;
	int window;
	double dev_inv = 0.5 / (sigma * sigma);
	window = (int) (radius * 2 + 1);
	double lpMediate[64 * 64];
	double* mask = new double[window];// {-0.0940,-0.1185,-0.1382,-0.1493,-0.1493,-0.1382,-0.1185,-0.0940};
	double sum = 0;
	double temp;
	double weight;
	for (x = 0; x < radius; x++) {
		xx = (int) ((x - radius) * (x - radius));
		mask[x] = exp(-xx * dev_inv);
		mask[window - 1 - x] = mask[x];
		sum += 2 * mask[x];
	}
	mask[(int) radius] = 1;
	sum += 1;
	for (x = 0; x < window; x++) {
		mask[x] /= sum;
		// System.out.println(mask[x]);
	}
	for (y = 0; y < 64; y++) {
		for (x = (int) radius; x < 64 - radius; x++) {
			temp = 0;
			for (xk = (int)( -radius); xk < radius; xk++) {
				// System.out.println(xk);
				temp += data[(x + xk)][y] * mask[(int) (xk + radius)];
				// if(y==14)
				// System.out.println(data[(x+xk)][y]);
			}
			lpMediate[(x) + (y) * 64] = temp;

		}

		for (x = 0; x < radius; x++) {
			temp = 0;
			weight = 0;
			for (xk = -x; xk < radius + 1; xk++) {

				temp += data[(x + xk)][y] * mask[(int) (xk + radius)];
				weight += mask[(int) (xk + radius)];
			}
			lpMediate[(x) + (y) * 64] = temp / weight;
		}
		for (x = (int) (64 - radius); x < 64; x++) {
			temp = 0;
			weight = 0;
			for (xk = (int) -radius; xk < 64 - x; xk++) {
				temp += data[(x + xk)][y] * mask[(int) (xk + radius)];
				weight += mask[(int) (xk + radius)];
			}
			lpMediate[(x) + (y) * 64] = temp / weight;
		}
	}
	double Column[64];
	for (x = 0; x < 64; x++) {
		for (y = (int) radius; y < 64 - radius; y++) {
			temp = 0;
			for (yk = (int) -radius; yk < radius; yk++) {
				temp += lpMediate[(x) + (y + yk) * 64]
						* mask[(int) (yk + radius)];
				// if(x==47)
				// System.out.println(lpMediate[(x)+(y+yk)*64]);
			}
			Column[y] = temp;
		}
		for (y = 0; y < radius; y++) {
			temp = 0;
			weight = 0;
			for (yk = -y; yk < radius + 1; yk++) {
				temp += lpMediate[(x) + (y + yk) * 64]
						* mask[(int) (yk + radius)];
				weight += mask[(int) (yk + radius)];
			}
			Column[y] = temp / weight;
		}
		for (y = (int) (64 - radius); y < 64; y++) {
			temp = 0;
			weight = 0;
			for (yk = (int) (-radius); yk < 64 - y; yk++) {
				// System.out.println(yk);
				temp += lpMediate[(x) + (y + yk) * 64]
						* mask[(int) (yk + radius)];
				weight += mask[(int) (yk + radius)];
			}
			Column[y] = temp / weight;
		}
		// if(x==47)
		// for(int o=0;o<63;o++)
		// System.out.println(Column[o]);
		for (y = 0; y < 64; y++) {
			b[x][y] = (float) Column[y];
		}
	}
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++)
			data[i][j] = b[i][j];
}
void Feature::Sampled(float Char[64][64], int N,double feature[64])
{
	int len = 0;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++) {
				int xt = (int)((1 + (i - 1) * N + 8 + (i - 1) * N) / 2+0.5) + 1;
				int yt = (int)((1 + (j - 1) * N + 8 + (j - 1) * N) / 2+0.5) + 1;
				// System.out.println(xt);System.out.println(yt);
				double eigFeature = 0;
				for (int k = -9; k < 9; k++)
					for (int g = -9; g < 9; g++)
						if (((xt + k) > 0) && ((xt + k) < 65) && ((yt + g) > 0)
								&& ((yt + g) < 65)) {
							float gau = Gaussian(3.141592653589793, 8, k, g);
							// System.out.println(gau);
							eigFeature = eigFeature + 255
									* (Char[xt + k - 1][yt + g - 1]) * gau;
							// System.out.println(Char[xt+k-1][yt+g-1]);
						}
				feature[len] = eigFeature;
				len += 1;
			}
}
float Feature::Gaussian(double deta, int lanbuta, int x, int y)
{
	double k = (double)2 * 3.141592653589793 / lanbuta;
	float Gxy = (float) (pow(k, 2)* exp(-pow(k, 2) * (pow((double)x, 2) + pow((double)y, 2))/ (2 * pow(deta, 2))) / pow(deta, 2));
	return Gxy;
}
Feature::~Feature(void)
{
}
