#include "DDA.h"
#include<cstdlib>
using namespace std;
#include<math.h>

DDA::DDA(void)
{
}
list<BasePoint> DDA::DDAData(BasePoint &start,BasePoint &end)
{
	point.push_back(start);
	short dx = (short) (end.getX() - start.getX());
	short dy = (short) (end.getY() - start.getY());
	int steps;
	float xin, yin, x = start.getX(), y = start.getY();
	steps = max(abs(dx), abs(dy));
	xin = (float)dx / steps;//计算两个方向的增量
	yin = (float)dy / steps;
	for (int i = 0; i < steps; i++)
	{
		x += xin;
		y += yin;
		point.push_back(BasePoint((short)(x+0.5), (short)(y+0.5)));
		//point.push_back(new BasePoint((short)round(x), (short)round(y)))
	}
	point.push_back(end);
	return this->point;
}

DDA::~DDA(void)
{
}
