
#pragma once
#include<list>
#include <string>
using namespace std;
#include"BasePoint.h"
#include"DataType.h"
class DataUnit
{
public:
	DataUnit(void);
	~DataUnit(void);
	DataUnit(short width, short height,DataType dataType);
	DataUnit(DataType dType);
	short &getWidth();
	void setWidth(short width);
	short &getHeight() ;
	void setHeight(short height);
	void addPoint(BasePoint p) ;
	list<BasePoint> &getPoints() ;
	DataType &getDataType() ;
	string regResult;
	DataType dataType;
private:
	short width, height;
	list<BasePoint> points;
	
	
};

