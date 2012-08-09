#include "BasePoint.h"


BasePoint::BasePoint(void)
{
	recogisEnd=false;
}
BasePoint::BasePoint(short x, short y)
{
	this->x=x;
	this->y=y;
}
BasePoint::BasePoint(BasePoint *point)
{
	this->x=point->x;
	this->y=point->y;
}
 short &BasePoint::getX()
 {
	 return this->x;
 }
 void BasePoint::setX(short x)
 {
	 this->x=x;
 }
 short& BasePoint::getY()
 {
	 return this->y;
 }
 void BasePoint::setY(short y)
 {
	 this->y=y;
 }
 bool BasePoint::isEnd()
 {
	return iEnd;
 }
 void BasePoint::setEnd(bool isEnd)
 {
	 this->iEnd=isEnd;
 }
BasePoint::~BasePoint(void)
{
}
