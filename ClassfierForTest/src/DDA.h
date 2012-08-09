#pragma once
#include<list>
using namespace std;
#include"BasePoint.h"
class DDA
{
public:
	DDA(void);
	~DDA(void);

	list<BasePoint> DDAData(BasePoint &start,BasePoint &end);///gaibianle≤ª”√DDA¡À
private:
	list<BasePoint> point;
};

