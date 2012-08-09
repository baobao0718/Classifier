#pragma once
#include <string.h>
class Transform
{
public:
	Transform(void);
	~Transform(void);
	static unsigned   char *InttoBytes(int num)
	{
		unsigned   char targets[4];
        targets[0] = (unsigned   char)(num & 0xff);
        targets[1] = (unsigned   char)((num >> 8) & 0xff);       
        targets[2]= (unsigned   char)((num >> 16) & 0xff);       
        targets[3]= (unsigned   char)(num >> 24);//yiwei youwenti 
        return targets;
	}
	static int BytestoInt(unsigned   char b[])
	{
		int targets= (b[0] & 0xff)
        | ((b[1]<<8) & 0xff00)   // | 表示按位或
        | ((b[2]<<24)>>8)
        | (b[3]<<24);
		return targets;
	}
	static  int toInt(unsigned char abyte0[], int offset) {
		int i = 0;

		for (int byte0 = offset; byte0 <= offset + 3; byte0++) {
			int j;
			if (abyte0[byte0] < 0) {
				abyte0[byte0] = (unsigned  char) (abyte0[byte0] & 0x7f);
				j = abyte0[byte0];
				j |= 0x80;
			} else {
				j = abyte0[byte0];
			}
			i |= j;
			if (byte0 < 3 + offset)
				i <<= 8;
		}
		return i;
	}
	 static  int toInt(unsigned  char abyte0[]) {
		return toInt(abyte0, 0);
	}
	 static float BytestoFloat(  char b[])
	{
		int l;
		l=b[0];
		l&=0xff;
		l|=((long)b[1]<<8);
		l&=0xffff;
		l|=((long)b[2]<<16);
		l&=0xffffff;
		l|=((long)b[3]<<24);
		l&=0xffffffffl;
	   // float   f=Float.intBitsToFloat(l); 
		float f=*(float*)&l;
	    return f;

	}
	 static unsigned  char *FloatToBytes(float   f) 
    { 
   // int   n=Float.floatToIntBits(f); 
		int n=(int)f;
		return   InttoBytes(n); 
    } 
	 static unsigned  char* DoubleToBytes(double d)
	{
		unsigned  char b[8];
		memcpy(b,&d,sizeof(unsigned char)*8);
		//long l=Double.doubleToLongBits(d);
		/*long l=(long)d;
		for(int i=0;i<b.length;i++)
		{
			b[i]=new Long(l).byteValue();
			l=l>>8;
		}*/
		return b;
	}
	 static double BytesToDouble(unsigned char b[])
	{
		long l;
		l=b[0];
		l&=0xff;
		l|=((long)b[1]<<8);
		l&=0xffff;
		l|=((long)b[2]<<16);
		l&=0xffffff;
		l|=((long)b[3]<<24);
		l&=0xffffffffl;
		l|=((long)b[4]<<32);
		l&=0xffffffffffl;
		l|=((long)b[5]<<40);
		l&=0xffffffffffffl;
		l|=((long)b[6]<<48);
		l&=0xffffffffffffffl;
		l|=((long)b[7]<<56);
		return (double)l;
	}
	 static char *BytesToChars(unsigned char bytes[])   { 
		//string   s=new   String(bytes); 
		//char   chars[]=s.toCharArray();
		 char chars[sizeof(bytes)];
		 strcpy(chars,(const char*)bytes);
		return   chars; 
		}
};

