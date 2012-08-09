#pragma once
class BasePoint
{

public:
	BasePoint(void);
	BasePoint(short x, short y) ;
	 BasePoint(BasePoint *point);
	~BasePoint(void);
	short &getX();
	void setX(short x);
	short &getY();
	void setY(short y);
	 bool isEnd();
	 void setEnd(bool isEnd);
	 bool RecisEnd() {//zhuxiaoqing 11.30
		return this->recogisEnd;
	}
	 void RecsetEnd(bool isEnd) {

		this->recogisEnd = isEnd;
	
	}
private:
	short x,y;
	bool iEnd;
	bool recogisEnd;
};

