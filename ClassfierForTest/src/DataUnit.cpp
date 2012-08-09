#include "DataUnit.h"
DataUnit::DataUnit(void)
{
}
DataUnit::DataUnit(short width, short height,DataType dataType)
{
 
		this->width = width;
		this->height = height;
		
		this->dataType = dataType;
		
	
}
DataUnit::DataUnit(DataType dType)
{
	this->dataType = dType;
}
short& DataUnit::getWidth(){
	
		return width;
	
}
void DataUnit::setWidth(short width)
{
	this->width = width;
}
short &DataUnit::getHeight()
{
	return height;
}
void DataUnit::setHeight(short height)
{
	this->height = height;
}
void DataUnit::addPoint(BasePoint p)
{
	this->points.push_back(p);
}
list<BasePoint> &DataUnit::getPoints()
{
	return points;
}
DataType & DataUnit::getDataType()
{
	return this->dataType;
}
DataUnit::~DataUnit(void)
{
}
