// HandWritingRecognize.cpp : 锟斤拷锟斤拷锟斤拷锟教ㄓ︼拷贸锟斤拷锟斤拷锟斤拷诘恪�
//

#include "stdafx.h"
#include "ListTable.h"
#include<iostream>
#include"Recognize.h"
#include"DataType.h"
#include"DataUnit.h"
//using namespace std;

//double ListTable::a=0;//锟斤拷锟斤拷要锟斤拷始锟斤拷
DataUnit *dataUnit;

	/** 图锟斤拷元锟斤拷锟斤拷 0x08 0000 1*** */
 char IMAGE_MASK = (char) 0x08;
/** 锟街凤拷元锟斤拷锟斤拷 0x40 01** **** */
 char CHAR_MASK = (char) 0x40;
/** 锟斤拷锟狡碉拷元锟斤拷锟斤拷锟斤拷锟斤拷 0xF0 1111 **** */
 char CTRL_TYPE_MASK = (char) 0xF0;
/** 锟斤拷锟狡碉拷元锟斤拷锟斤拷 0x80 1*** **** */
 char CTRL_MASK = (char) 0x80;
// /** 锟秸革拷元 0x90 1001 **** */
// private static final char SPACE = 0x90;
// /** 锟轿碉拷元 0xB0 1011 **** */
// private static final char PARA = 0xB0;
short charEnd = (short) 0x8080; // 锟街凤拷锟斤拷锟斤拷志 2锟街斤拷
 short strokeEnd = (short) 0x8000;// 锟绞伙拷锟斤拷锟斤拷锟街�
void startCharUnit() {
		dataUnit = new DataUnit((short) 0, (short) 0, TYPE_CHAR);
		//dataUnit((short) 0, (short) 0, DataType::TYPE_CHAR);
	}
void addPoint(short xTmp, short yTmp, bool endTmp) {
		
		BasePoint point = new BasePoint(xTmp, yTmp);
		point.setEnd(endTmp);
		dataUnit->addPoint(point);

	}
void endCharUnit(list<DataUnit> &array1) {
		// short ancher = 2;
		// int charWidth = (short)(maxX-minX+1);
		// this.dataUnit.setWidth((short)(charWidth + (ancher<<1)));
	array1.push_back(*dataUnit);
		// maxX = Integer.MIN_VALUE;
		// minX = Integer.MAX_VALUE;
	}
int charUnitDecoder(short byteData[], int index,list<DataUnit> &array1)
{
	int startIndex = index;
	// short charHeight = 0;
	bool startPoint = true;
	int x = 0;
	int y = 0;
	int mid = 0;
	bool end = false;
	int pointX = -1;
	int pointY = -1;
	int nextByte = 0;
	int nextNextByte = 0;
	short temp = 0;
	int tempX = 0;
	int tempY = 0;
	// short high = byteData[startIndex];
	// ++startIndex;
	// short low = byteData[startIndex];
	// ++startIndex;
	// charHeight = (short) ((high << 8) | low);
	// NSMutableArray *pointsPerStrokeArray = [[NSMutableArray alloc] init];
	// [self startCharUnit: charHeight andPointsPerStrokeArray:
	// pointsPerStrokeArray];
	startCharUnit();
	// int pointsNumPerStroke = 0;
	// 锟斤拷录每锟绞的碉拷锟斤拷
	while (true) {
		if (startPoint == true) {
			// 锟斤拷取锟绞伙拷锟斤拷一锟斤拷
			x = byteData[startIndex] & 0x00ff;
			++startIndex;
			mid = byteData[startIndex] & 0x00ff;
			++startIndex;
			temp = (short) ((x << 8) | mid);
			if (temp == charEnd) {
//					System.out.println("锟斤拷锟街斤拷锟斤拷" + temp);
				break;
			}

			y = byteData[startIndex] & 0x00ff;
			++startIndex;
			x = ((x << 4) | ((mid & 0xF0) >> 4)) & 0x00ff;
			y = (((mid & 0xF) << 8) | y) & 0x00ff;
			startPoint = false;
			pointX = x;
			pointY = y;
			end = false;
			// [self addPoint: (short)x andY: (short)y andIsEnd: end];
			addPoint((short) x, (short) y, end);
			// ++pointsNumPerStroke;
			tempX = byteData[startIndex] & 0x00ff;
			// System.out.println("tempX:"+tempX);
			++startIndex;
			tempY = byteData[startIndex] & 0x00ff;
			// System.out.println("tempY:"+tempY);
			++startIndex;
			temp = (short) ((tempX << 8) | tempY);
			// System.out.println("temp:"+temp);
		} else {
			while (temp != strokeEnd) {
				if (tempX > 128)
					tempX = 128 - tempX;
				if (tempY > 128)
					tempY = 128 - tempY;
				x = (pointX + tempX) & 0x00ff;
				y = (pointY + tempY) & 0x00ff;
				nextByte = byteData[startIndex] & 0x00ff;
				++startIndex;
				nextNextByte = byteData[startIndex] & 0x00ff;
				++startIndex;
				temp = (short) ((nextByte << 8) | nextNextByte);
				if (temp == strokeEnd) {
//						System.out.println("锟绞伙拷锟斤拷锟斤拷" + temp);

					end = true;
					startPoint = true;
					// [self addPoint: (short)x andY: (short)y andIsEnd:
					// end];
					addPoint((short) x, (short) y, end);
					// ++pointsNumPerStroke;
					// [pointsPerStrokeArray addObject:[NSNumber
					// numberWithInt:pointsNumPerStroke]];
					// pointsNumPerStroke = 0;
					break;
				} else {
					tempX = nextByte;
					tempY = nextNextByte;
					pointX = x;
					pointY = y;
					end = false;
					// [self addPoint: (short)x andY: (short)y andIsEnd:
					// end];
					addPoint((short) x, (short) y, end);
					// ++pointsNumPerStroke;
				}
			}
		}
	}
	// [self endCharUnit:grobalListTmp ];
	endCharUnit(array1);

	// 锟斤拷前锟街凤拷元锟斤拷锟斤拷
	return startIndex;
}
void base64_decode(const char *src, int src_len,short dst[])
{
	int i = 0, j = 0;
	short base64_decode_map[] =  {// 256锟斤拷元锟斤拷

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 62, 255, 255, 255, 255, 63, 52, 53, 54, 55, 56, 57,
		58, 59, 60, 61, 255, 255,

		255, 0, 255, 255, 255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		12, 13, 14,

		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255,
		255, 255, 26, 27, 28,

		29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
		45, 46, 47, 48,

		49, 50, 51, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255, 255, 255, 255, 255,

		255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
		255, 255, 255, 255 };
		for (; i < src_len; i += 4) {

			// dst[j++] = (byte)(base64_decode_map[src[i]] << 2 |
			// base64_decode_map[src[i + 1]] >> 4);
			//
			// dst[j++] = (byte)(base64_decode_map[src[i + 1]] << 4 |
			// base64_decode_map[src[i + 2]] >> 2);
			//
			// dst[j++] = (byte)(base64_decode_map[src[i + 2]] << 6 |
			// base64_decode_map[src[i + 3]]);

			dst[j++] = (short) (base64_decode_map[(src[i] & 0x00ff)] << 2 | base64_decode_map[(src[i + 1] & 0x00ff)] >> 4);

			dst[j++] = (short) (base64_decode_map[(src[i + 1] & 0x00ff)] << 4 | base64_decode_map[(src[i + 2] & 0x00ff)] >> 2);

			dst[j++] = (short) (base64_decode_map[(src[i + 2]) & 0x00ff] << 6 | base64_decode_map[(src[i + 3] & 0x00ff)]);

		}
}
void decodeDataUnitArray(list<DataUnit> &array1, const char *byteDataTemp,int size)
{
	DataUnit *dataUnit;
	
	short *byteData=new short[(size * 3) / 4];
	base64_decode(byteDataTemp, size,byteData);
	//System.out.println("锟斤拷锟斤拷锟�len:"+byteData.length);
	//for(int i = 0; i < byteData.length; i++){
	//System.out.println("qin"+(byteData[i]&0x00ff));
	//cout<<"锟斤拷锟斤拷锟�len:"<<size*3/4<<endl;
	/*for(int mm=0;mm<size*3/4;mm++)
	{
		cout<<"qin: "<<(byteData[mm]&0x00ff)<<endl;
		
	}//zhengque*/
	int dataUnitNum = ((byteData[0] & 0x000000ff) << 24)
				+ ((byteData[1] & 0x000000ff) << 16)
				+ ((byteData[2] & 0x000000ff) << 8)
				+ (byteData[3] & 0x000000ff);
	//System.out.println("data unit num:" + dataUnitNum);

	int index = 4;
	char currentByte;

	for (int i = 0; i < dataUnitNum; i++) {
		currentByte = (char) (byteData[index] & 0xff);
		++index;
//			System.out.println("curretn char flag:" + currentByte);
		if ((currentByte & (char) 0x80) == 0) {// 锟角匡拷锟狡碉拷元

			if ((currentByte & (char) 0x40) == 0) {// 锟斤拷锟街碉拷元
				// [self charUnitDecoder: currentByte andGrobal:grobalList
				// ];
				//cout<<"tianjia wenzi"<<endl;
				index = charUnitDecoder(byteData, index, array1);
			/*	list<DataUnit>::iterator du=array1.begin();
				list<BasePoint> bb;
				list<BasePoint>::iterator bite;
				for(int m=0;m<array1.size();m++,du++)
				{
					bb.clear();
					bb=(*du).getPoints();
					bite=bb.begin();
					for(int k=0;k<bb.size();k++,bite++)
					{
						cout<<"chaunit:"<<(*bite).getX()<<"  "<<(*bite).getY()<<endl;
					}

				}*/
				//cout<<index<<endl;
				//System.out.println("锟斤拷锟揭伙拷锟�);
			} else if ((currentByte & (char) 0x08) != 0) {// 图锟斤拷元
				// 锟斤拷踊锟酵硷拷锟皆�
				dataUnit = new DataUnit(TYPE_IMAGE);
				//DataUnit d=new DataUnit();
				array1.push_back(*dataUnit);
				//System.out.println("锟斤拷锟揭煌�);
			}

		} else {// 锟斤拷锟狡碉拷元
//				System.out.println("锟斤拷志锟斤拷"+(byte)(currentByte & CTRL_TYPE_MASK));
			switch ((char)(currentByte & (char) 0xF0)) {
			case (char)0x90:// 锟秸革拷元SPACE
			{
				// 锟斤拷涌崭锟皆�
				dataUnit = new DataUnit(TYPE_CTRL_SPACE);
				//dataUnit->dataType=DataType::TYPE_CTRL_SPACE;
				
				array1.push_back(*dataUnit);
				//System.out.println("锟斤拷锟揭伙拷崭锟�);
			}

				break;

			case (char)0xB0:// 锟轿匡拷锟狡碉拷元PARA(目前只锟斤拷锟斤拷锟斤拷锟揭伙拷爻锟�
			{
				// 锟斤拷踊爻锟斤拷锟皆�
				dataUnit = new DataUnit(TYPE_CTRL_ENTER);
				array1.push_back(*dataUnit);
				//System.out.println("锟斤拷锟揭伙拷爻锟�);
			}
				break;

			default:
				//System.out.println("there are some control unit mistake in DocumentDecoder.dataDecoder()!");
				break;
			}

		}

	}

	byteDataTemp = NULL;
	byteData = NULL;

}
int main(int argc, char * argv[])
{
	//ListTable *a=new ListTable();
	//ListTable::mk=0.5;
	//a->mk=0.5;
	//cout<<"result"<<a->mk<<endl;
	//ListTable::a=45;
//	ListTable lstTemp;
//	lstTemp.a=12;
	//ListTable::a=12;
	//cout<<"result"<<ListTable::a<<endl;
	//hash_map<int,int>k;
	//k.insert(std::pair<int,int>(2,3));
	 list<DataUnit> globalIndexTabletmp= list<DataUnit>();//锟街碉拷锟斤拷锟�
	//string addContent = "AAAAAzgAIAwAAQABAAEAAgABAACAAAAwDgAAAQACAAAAgQGBA4EBAAGBAAAAAQAAAAAAAQAAAIAAAPAFAAAAAoIEgwWDBYIEAAEAAIAAARAHAAABAgIDBQMDAoEAAIEAAIAAALARAAACAAQAA4EAAIAAAOAVAAEAAgEDAAMAAQCBAIIAAIAAAPAZAAACAAIAAgAAAAABggGBAoIBgwEBAAEAAgACgQAAAACAAICAOABgBgEAgQKBAoIDgQEAAAAAgAAAYAoBAAEAAgADAAQAAAAAAAABgQGCAoEAAACAAADQDgABAAIAAgAFAAUAAwCBgYEAAIAAAGAUAAEAAgABgQIAAAAAgAABABMAAAIBAgEBAQABAAAAAIAAgIA4ACAHAAACAQICAAAAAIAAADANAAABAAEBAQIBAgABAACAAAAwHQAAAYECggODAYMAggAAAACAAAEQAgAAAAABAgEBAACAAADAB4EAAAEAAwACAAEAAIAAANAKAAABAAMABQADAAIAAAAAAAABAACAAAFADAAAAAAAAAMABAACAAAAgAABYAwAAAACAAIAAgABAACAAAFgEgAAAQACgQEAAACAAAGQEQAAAAEBAgAAAACAAAFAFAEABAAHAAcAAACAAAFAGQAAgQEAAQABAACAAAHgFgEBAgEBAgAAgACAgD09";
	string addContent = "AAAAAzgAIAwAAQABAAEAAgABAACAAAAwDgAAAQACAAAAgQGBA4EBAAGBAAAAAQAAAAAAAQAAAIAAAPAFAAAAAoIEgwWDBYIEAAEAAIAAARAHAAABAgIDBQMDAoEAAIEAAIAAALARAAACAAQAA4EAAIAAAOAVAAEAAgEDAAMAAQCBAIIAAIAAAPAZAAACAAIAAgAAAAABggGBAoIBgwEBAAEAAgACgQAAAACAAICAOABgBgEAgQKBAoIDgQEAAAAAgAAAYAoBAAEAAgADAAQAAAAAAAABgQGCAoEAAACAAADQDgABAAIAAgAFAAUAAwCBgYEAAIAAAGAUAAEAAgABgQIAAAAAgAABABMAAAIBAgEBAQABAAAAAIAAgIA4ACAHAAACAQICAAAAAIAAADANAAABAAEBAQIBAgABAACAAAAwHQAAAYECggODAYMAggAAAACAAAEQAgAAAAABAgEBAACAAADAB4EAAAEAAwACAAEAAIAAANAKAAABAAMABQADAAIAAAAAAAABAACAAAFADAAAAAAAAAMABAACAAAAgAABYAwAAAACAAIAAgABAACAAAFgEgAAAQACgQEAAACAAAGQEQAAAAEBAgAAAACAAAFAFAEABAAHAAcAAACAAAFAGQAAgQEAAQABAACAAAHgFgEBAgEBAgAAgACAgD09";
	int contentsize=addContent.size();
    //byte[] byteArray = addContentData.getBytes("UTF-8");
	const char *byteArray=new char[contentsize];
	byteArray=addContent.c_str();
	decodeDataUnitArray(globalIndexTabletmp, byteArray,contentsize);
	cout<<globalIndexTabletmp.size()<<endl;
	Recognize *recog=new Recognize();
	//cout<<ListTable::Labels.substr(3458,2)<<endl;
	//cout<<ListTable::Labels.substr(2,2)<<endl;
	/*	list<DataUnit>::iterator du=array1.begin();
				list<BasePoint> bb;
				list<BasePoint>::iterator bite;
				for(int m=0;m<array1.size();m++,du++)
				{
					bb.clear();
					bb=(*du).getPoints();
					bite=bb.begin();
					for(int k=0;k<bb.size();k++,bite++)
					{
						cout<<"chaunit:"<<(*bite).getX()<<"  "<<(*bite).getY()<<endl;
					}

				}*/
	//globalIndexTabletmpshuzhi dui 
	recog->recognition(globalIndexTabletmp);
	list<string>::iterator it=ListTable::recognizeT.begin();
	for(;it!=ListTable::recognizeT.end();it++)
		cout<<*it<<endl;
	return 0;
}

