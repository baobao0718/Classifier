#pragma once
#include <list>
using namespace std;
#include"BasePoint.h"
class MyStroke
{
public:
	MyStroke(void);
	~MyStroke(void);
	
	int &getColor() {
		return color;
	}
	void setColor(int color) {
		this->color = color;
	}
	list<BasePoint> &getPoints() {
		return points;
	}
	void addPoint(BasePoint point) {
		(this->points).push_back(point);
	}
	 float getStrokeWidth() {
		return strokeWidth;
	}
	 void setStrokeWidth(float strokeWidth) {
		this->strokeWidth = strokeWidth;
	}
	 void Clear(){
		this->points.clear();
	}
	 int getPointssize(){
		return this->points.size();
	}
private:
	int color;
	list<BasePoint> points;
	float strokeWidth;
};

