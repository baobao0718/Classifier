#pragma once
class Distance
{
public:
	Distance(void);
	~Distance(void);
	 float x;
	float y;
	double Dis;
	Distance(float x, float y) {
			this->x = x;
			this->y = y;
		}
};

