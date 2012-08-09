#include "Recognize.h"
#include"ListTable.h"
#include"Transform.h"

using namespace std;
string ListTable::Labels = "";
double ListTable::C[316][160] = { 0.0 };
list<list<double> > ListTable::Classingroup = list<list<double> >();
double ListTable::eigvector[512][160] = { 0.0 };
double ListTable::u[3755][160] = { 0.0 };
double ListTable::d[3755][75] = { 0.0 };
float ListTable::v[20 * 160][8] = { 0.0 };
//double ListTable::C1[316*160]={0.0};
//float *ListTable::v=new float[20*160*8];

double ListTable::classsigma[3755] = { 0.0 };
list<string> ListTable::recognizeT = list<string>();

Recognize::Recognize(void) {

	ClassNum = 3755;
	GroupNum = 316;
	//readdataone1("C.txt",ListTable::C1,GroupNum,160);
	this->readdataone("C.txt", (double**) ListTable::C, GroupNum, 160);
	this->readdataone("eigvector.txt", (double**) ListTable::eigvector, 512,
			160);
	cout << "eigvector.txt readed!!" << endl;
	this->readdataone("U.txt", (double**) ListTable::u, ClassNum, 160);
	this->readdataone("D.txt", (double**) ListTable::d, ClassNum, 75);
	readData("classsigma.txt", ListTable::classsigma, ClassNum);
	cout << "classigma.txt readed!!" << endl;
	readData("Classingroup.txt", ListTable::Classingroup, GroupNum);
	cout << "Classingroup.txt readed!!" << endl;
	readlable("label.txt");
	cout << "label.txt readed!!" << endl;
	//读取特征向量矩阵文件的压缩码本文件和索引文件
	vqfileread = new VQFileRead("CodeBook.txt", "Indices.txt", 2, 160, 255, 8,
			3755);
	cout << "vqfileread!!" << endl;
	vqfileread->ReadCodeBook();
	cout << "vqfilereaded!" << endl;
	vqfileread->ReadIndices();
}

void Recognize::readdataone(string file, double **matrix, int Row, int Col) {

	int index = 0;
	FILE *fp = fopen(file.c_str(), "rb");
	//FILE*fp=fopen("D:\\蒲俊奇转交\\helloworld_zou_new\\JAVA\\C.txt","rb");
	fseek(fp, 0, SEEK_END);
	long int n = ftell(fp); //错误地点
	char *buffer = new char[n];
	//cout<<n<<endl;
	fseek(fp, 0, SEEK_SET);
	//cout<<ftell(fp)<<endl;
	size_t sRet = fread(buffer, sizeof(char), n, fp);
	/*if(ferror(fp)){
	 cout<<"error occurs"<<endl;
	 }else if(feof(fp)){
	 cout<<"feof"<<endl;
	 }*/
	//cout<<buffer[0]<<endl;
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++) {
			int l;
			l = buffer[index];
			l &= 0xff;
			l |= ((long) buffer[index + 1] << 8);
			l &= 0xffff;
			l |= ((long) buffer[index + 2] << 16);
			l &= 0xffffff;
			l |= ((long) buffer[index + 3] << 24);
			l &= 0xffffffffl;
			float f = *(float*) &l;
			//matrix[i][j]=f;
			*((double*) matrix + Col * i + j) = f;
			//cout<<f<<endl;
			index += 4;
		}
	fclose(fp);
}
void Recognize::readData(string file, double matrix[], int Col) {
	int index = 0;
	FILE *fp = fopen(file.c_str(), "rb");
	//FILE *fp=fopen("D:\\蒲俊奇转交\\helloworld_zou_new\\JAVA\\classsigma.txt","rb");
	fseek(fp, 0, SEEK_END);
	int n = ftell(fp);
	char *buffer = new char[n];
	char tembyte[4];
	fseek(fp, 0, SEEK_SET);
	//fgets(buffer,n,fp);
	size_t sRet = fread(buffer, sizeof(char), n, fp);
	for (int j = 0; j < Col; j++) {
		/*for(int t=0;t!=4;t++)
		 {
		 tembyte[t] = buffer[index+t];
		 int l=buffer[index+t];
		 cout<<l<<endl;
		 }
		 matrix[j]=Transform::BytestoFloat(tembyte);
		 //System.out.println("classsigma  f "+matrix[j]+" ");
		 index+=4;*/
		int l;
		l = buffer[index];
		l &= 0xff;
		l |= ((long) buffer[index + 1] << 8);
		l &= 0xffff;
		l |= ((long) buffer[index + 2] << 16);
		l &= 0xffffff;
		l |= ((long) buffer[index + 3] << 24);
		l &= 0xffffffffl;
		float f = *(float*) &l;
		//cout<<f<<endl;
		matrix[j] = f;
		//cout<<matrix[j]<<endl;
		index += 4;

	}
	fclose(fp);

}

void Recognize::readData(string file, list<list<double> > &Classingroup,
		int GroupNum) {
	string text = "";
	ifstream ifs(file.c_str());
	for (int k = 0; k < GroupNum; k++) {
		getline(ifs, text);
		list<double> tmp;
		char *line = new char[text.size() + 1];
		strcpy(line, text.c_str());
		char *token;
		token = strtok(line, " ");
		while (token != NULL) {
			tmp.push_back(atof(token));
			token = strtok(NULL, " ");
		}
		delete line;
		Classingroup.push_back(tmp);
	}
	ifs.close();
}

void Recognize::readlable(string file) {
	ifstream ifs;
	ifs.open(file.c_str(), ios::binary); // 改为你要打开的文件名
	ifs.seekg(0, ios::end);
	int length = ifs.tellg();
	cout << length << endl;
	ifs.seekg(0, ios::beg);
	char *buffer = new char[length + 1];
	buffer[length] = 0;
	ifs.read(buffer, length);
	string wstr;
	string po = buffer;
	//cout<<po.substr(124,length-124)<<endl;
	ListTable::Labels = po.substr(124, length - 124);

	ifs.close();
}
void Recognize::recognition(list<DataUnit> &lst) {
	/*list<DataUnit>::iterator du=lst.begin();//正确的坐标
	 list<BasePoint> bb;
	 list<BasePoint>::iterator bite;
	 for(int m=0;m<lst.size();m++,du++)
	 {
	 bb.clear();
	 bb=(*du).getPoints();
	 bite=bb.begin();
	 for(int k=0;k<bb.size();k++,bite++)
	 {
	 cout<<"chaunit:"<<(*bite).getX()<<"  "<<(*bite).getY()<<endl;
	 }

	 }*/
	int number = lst.size();
	list<MyStroke> recognizeTable;
	recognizeTable.clear();
	ListTable::recognizeT.clear();
	list<DataUnit>::iterator it = lst.begin();

	list<BasePoint> btm; //////////////
	list<BasePoint>::iterator bmt; /////////////
	list<MyStroke>::iterator iiit; /////////////
	BOOST_FOREACH(DataUnit du, lst){
		if(du.getDataType()==TYPE_CHAR){
			extractChar(du);
			get128CharUnit(du);
			getVector(du, recognizeTable);
			du.regResult=classifier(recognizeTable);
			ListTable::recognizeT.push_back(du.regResult);	//存放结果
			recognizeTable.clear();
		}
	}
}

/**
 * 将dataUnit转为MyStrock，传入recognizeTable中
 * */
void Recognize::getVector(DataUnit &charUnit, list<MyStroke> &recognizeTable) {
	recognizeTable.clear();
	list<BasePoint> &lst = charUnit.getPoints();
	MyStroke myStrock;
	myStrock.Clear();
	BOOST_FOREACH(BasePoint bp, lst){
		myStrock.addPoint(bp);
		if(bp.isEnd()){			// 输出笔画标志（是否是笔画的结束点）
			recognizeTable.push_back(myStrock);
			myStrock.Clear();
		}
	}
}

/**
 * 将dataUnit投影到128*128的坐标，并使居中
 * */
void Recognize::get128CharUnit(DataUnit &charUnit) {
	short size = 128;
	short height = charUnit.getHeight();
	short weight = charUnit.getWidth();
	short tmpX = 0;
	short tmpY = 0;
	bool isEnd = false;	// 是否是笔画结束点
	float ratio = 0.0f;
	list<BasePoint> &lst = charUnit.getPoints();

	if (height >= weight) {
		ratio = (float) size / height;
		BOOST_FOREACH(BasePoint &bp, lst){
			isEnd = bp.isEnd();
			tmpX = (short) (bp.getX() * ratio + (size - weight * ratio) / 2);	//横坐标居中
			tmpY = (short) (bp.getY() * ratio);
			tmpX=(tmpX>size)?size:tmpX;
			tmpY=(tmpY>size)?size:tmpY;

			bp.setX(tmpX);
			bp.setY(tmpY);
			bp.setEnd(isEnd);
		}
	} else {
		ratio = (float) size / weight;
		BOOST_FOREACH(BasePoint &bp, lst){
			isEnd = bp.isEnd();
			tmpX = (short) (bp.getX() * ratio);
			tmpY = (short) (bp.getY() * ratio + (size - height * ratio) / 2);	//纵坐标居中
			tmpX=(tmpX>size)?size:tmpX;
			tmpY=(tmpY>size)?size:tmpY;

			bp.setX(tmpX);
			bp.setY(tmpY);
			bp.setEnd(isEnd);
		}
	}
	charUnit.setHeight((short) 128);
	charUnit.setWidth((short) 128);
}

/**
 * 将dataUnit投影到（0，0）开始的坐标上
 * */
void Recognize::extractChar(DataUnit &dataUnit) {
	int pointNum = 0;
	//list<BasePoint> pointArray;
	int X = 0;
	int Y = 0;
	/*int maxX = -2147483648;
	 int minX =  2147483647;
	 int maxY =  -2147483647;
	 int minY =  2147483647;*/
	int maxX = 0x80000000;//or maxX=INT_MAX;
	int minX = 0x7fffffff;//or minX=INT_MIN;
	int maxY = 0x80000000;
	int minY = 0x7fffffff;

	list<BasePoint> &pointArray = dataUnit.getPoints();

	list<BasePoint>::iterator it = pointArray.begin();
	pointNum = pointArray.size();
	BasePoint p;
	/*	for (int k=0;k<pointNum&&it!=pointArray.end();k++)//zhuxiaoqing 2011.11.30
	 {
	 /*if(true==pointArray.get(k).isEnd()||true==pointArray.get(k).RecisEnd())
	 {
	 pointArray.get(k).RecsetEnd(true);
	 //System.out.println("~~~~~~~~~~~here bihuajieshu");
	 }else
	 {
	 pointArray.get(k).RecsetEnd(false);
	 }*/
	/*		if((true==(*it).isEnd())||(true==(*it).RecisEnd()))
	 {
	 (*it).RecsetEnd(true);
	 }else
	 {
	 (*it).RecsetEnd(false);
	 }
	 it++;
	 }*/
	list<BasePoint>::iterator it2 = pointArray.begin();
	for (int k = 0; k < pointNum && it2 != pointArray.end(); k++) {
		X = (*it2).getX();
		Y = (*it2).getY();
		it2++;
		if (X < minX) {
			minX = X;
		}
		if (X > maxX) {
			maxX = X;
		}
		if (Y < minY) {
			minY = Y;
		}
		if (Y > maxY) {
			maxY = Y;
		}
	}

	dataUnit.setWidth((short) (maxX - minX + 1 + 2));
	dataUnit.setHeight((short) (maxY - minY + 1 + 2));

	/* 将文字的左上角放在（0，0）的位置上 */
	BOOST_FOREACH(BasePoint &bp, pointArray){
		bp.setX((short)(bp.getX()-minX+1));
		bp.setY((short)(bp.getY()-minY+1));
	}
}


string Recognize::classifier(list<MyStroke> &recognizeTable_o) {
	int selectedNum = 5;
	list<MyStroke> recognizeTable;
	recognizeTable.clear();
	list<MyStroke> RecognizeTable;
	RecognizeTable.clear();
	P2DMNClass *p2dmn = new P2DMNClass();
	cout << "\t 笔画数: "<<recognizeTable_o.size() << endl;
	recognizeTable = transtosmall(recognizeTable_o);

	short test_o[64][64];
	DDA_disp(recognizeTable, test_o);
	RecognizeTable = p2dmn->P2DMN(test_o, recognizeTable);//recognizeTable是正确的 但是RecognizeTable不正确

	Feature *feature = new Feature();
	float input[1][160];
	double BT[1][512];
	feature->FeatureData(RecognizeTable, recognizeTable, BT);//改变策略，不用返回值将返回值放到BT中
	BiMatrix(BT, ListTable::eigvector, input);	//使用上面的BT，把返回值放到input中
	double* distance = new double[GroupNum];
	for (int i = 0; i < GroupNum; i++) {
		double tp = 0;
		for (int j = 0; j < 160; j++) {
			tp += pow(*((double*) ListTable::C + 160 * i + j) - input[0][j], 2);
		}
		distance[i] = tp;
	}
	int topkgroupnum = 100;
	int Grouplabel[100];
	Findmin(distance, topkgroupnum, GroupNum, Grouplabel);
	//for(int m=0;m<80;m++)
	//	cout<<Grouplabel[m]<<endl;///////ok
	list<double> tmp;
	list<list<double> >::iterator it;
	list<double>::iterator ittem;
	for (int i = 0; i < topkgroupnum; i++) {
		it = (ListTable::Classingroup.begin());
		for (int m = 0; m < Grouplabel[i]; m++) {
			it++;
		}
		ittem = (*it).begin();
		for (int j = 0; j < (*it).size(); j++, ittem++) {
			tmp.push_back((double) (*ittem));
		}
	}
	list<double>::iterator rt = tmp.begin();
	//for(int m=0;m<tmp.size();m++,rt++)
	//	cout<<(*rt)<<endl;//////ok
	int* Indexpre;
	Indexpre = new int[tmp.size()];
	list<double>::iterator im = tmp.begin();
	//cout<<tmp.size()<<endl;
	for (int i = 0; i < tmp.size(); i++, im++) {
		Indexpre[i] = (int) (*im);
		//	cout<<i<<"  "<<Indexpre[i]<<endl;
		//System.out.println("Indexpre tmp "+Indexpre[i]+" "+tmp.get(i));
	}
	double* Euclidean_Dis = new double[tmp.size()];
	int tmm = 0;
	for (int i = 0; i != tmp.size(); i++) {
		tmm = Indexpre[i];
		Euclidean_Dis[i] = Cal_Euclid_Dis((float**) input, tmm);
	}
	//for(int m=0;m<tmp.size();m++)
	//	cout<<Euclidean_Dis[m]<<endl;//ok
	int tmpmqdf[20];
	Findmin(Euclidean_Dis, 20, tmp.size(), tmpmqdf);
	//for(int m=0;m<20;m++)
	//	cout<<tmpmqdf[m]<<endl;
	int Index[20];
	for (int i = 0; i < 20; i++) {
		Index[i] = Indexpre[tmpmqdf[i]];
		//cout<<Index[i]<<endl;////zhengque 
	}
	tmp.clear();
	classtoindex.clear();
	for (int i = 0; i != 20; i++)
		tmp.push_back((double) Index[i]);
	int K = vqfileread->K;
	int DL = vqfileread->DL;
	int DQ = vqfileread->DQ;
	char Indice[4 * 160];
	char Vpre[80][8];
	//char* Indice= new byte[K*DL/DQ];
	//byte[][] Vpre = new byte[DL/DQ][K];
	//cout<<ListTable::Labels.substr(3458,2)<<" 1"<<endl;//有值。。。。。
	for (int i = 0; i != 20; i++) {
		//得到一个类的特征向量矩阵V
		//cout<<ListTable::Labels.substr(3458,2)<<endl;
		for (int jj = 0; jj < 4 * 160; jj++)
			Indice[jj] = vqfileread->Indices[Index[i] - 1][jj];
		for (int col = 0; col != 8; col++) {
			for (int row = 0; row != 80; row++)
				Vpre[row][col] = Indice[col * (80) + row];
		}

		for (int col = 0; col != 8; col++) {
			for (int row = 0; row != 80; row++)
				for (int count = row; count != row + 2; count++) {
					//*((double*)ListTable::v + 8*(i*160+row+count) + col)=vqfileread->CodeBook[(Vpre[row][col]&0xFF)-1][count-row];//影响了labels
					ListTable::v[i * 160 + row + count][col] =
							vqfileread->CodeBook[(Vpre[row][col] & 0xFF) - 1][count
									- row];
					//System.out.println(	"^^^ "+ListTable.v[i*160+row+count][col]);
					//cout<<"i="<<i<<"hangshu="<<(i*160+row+count)<<endl;
				}
		}
		//classtoindex.insert(Index[i],i);//hash_mapcharu
		//cout<<ListTable::Labels.substr(3458,2)<<endl;
		classtoindex.insert(pair<int, int>(i, Index[i]));
		//cout<<ListTable::Labels.substr(3458,2)<<"haha"<<endl;
		//System.out.println("Index "+Index[i]);
	}
	//cout<<ListTable::Labels.substr(3458,2)<<" 1"<<endl;//meiyouzhi
	boost::unordered_map<int, int>::iterator hm = classtoindex.begin();
	/*	for(int m=0;m<classtoindex.size();m++,hm++)
	 {
	 cout<<(*hm).first<<" "<<(*hm).second<<endl;
	 }*/
	double mqdf = 0;
	int table[5];
	double* G = new double[tmp.size()];
	double* TempG = new double[tmp.size()];
	//cout<<tmp.size()<<endl;//tmp.size=20
	//cout<<ListTable::Labels.substr(3458,2)<<endl;
	//for(int m=0;m<160;m++)
	//	cout<<input[0][m]<<endl;
	for (int label = 0; label < tmp.size(); label++) {
		mqdf = MQDF((float**) input, 8, Index[label],
				ListTable::classsigma[Index[label] - 1]);	//MQDF分类器
		//cout<<mqdf<<endl;
		G[label] = mqdf;
		TempG[label] = mqdf;
		//System.out.println("&& "+label+" "+mqdf);
	}
	int locak = 0;
	int locam = 0;
	int cmfclasslabel;
	int cmfsimilarclasslabel;
	double cmfk = 0, cmfm = 0;
	int NumofWin[4];
	FindminTmp(TempG, selectedNum, tmp.size(), table);
	//for(int m=0;m<5;m++)
	//	cout<<table[m]<<endl;
	list<double>::iterator tmpit, tmpit2;
	//cout<<ListTable::Labels.substr(3458,2)<<endl;
	for (int k = 0; k != selectedNum - 2; k++) {
		locak = table[k + 1];
		tmpit = tmp.begin();
		for (int yy = 0; yy < table[k + 1]; yy++) {
			tmpit++;
		}
		cmfclasslabel = (int) (*tmpit);
		for (int m = k + 1; m != selectedNum - 1; m++) {
			locam = table[m + 1];
			tmpit2 = tmp.begin();
			for (int yy = 0; yy < table[m + 1]; yy++) {
				tmpit2++;
			}
			cmfsimilarclasslabel = (int) (*tmpit2);
			cmfk = CMF(cmfclasslabel, cmfsimilarclasslabel, (float**) input, 8,
					G[locak], ListTable::classsigma[cmfclasslabel - 1]);
			cmfm = CMF(cmfsimilarclasslabel, cmfclasslabel, (float**) input, 8,
					G[locam], ListTable::classsigma[cmfsimilarclasslabel - 1]);
			//cout<<cmfk<<"  "<<cmfm<<endl;//ok
			if (cmfk <= cmfm)
				NumofWin[k] = NumofWin[k] + 1;
			else
				NumofWin[m] = NumofWin[m] + 1;
		}
	}
	int top2 = Max(NumofWin, selectedNum - 1);
	int tem = table[top2 + 1];
	table[top2 + 1] = table[1];
	table[1] = tem;
	list<double>::iterator iii;
	iii = tmp.begin();
	for (int i = 0; i < table[0]; i++) {
		iii++;
	}
	cmfclasslabel = (int) (*iii);
	iii = tmp.begin();
	for (int i = 0; i < table[1]; i++) {
		iii++;
	}
	//cout<<ListTable::Labels.substr(3458,2)<<endl;
	cmfsimilarclasslabel = (int) (*iii);

	cmfk = CMF(cmfclasslabel, cmfsimilarclasslabel, (float**) input, 8,
			G[table[0]], ListTable::classsigma[cmfclasslabel - 1]);
	cmfm = CMF(cmfsimilarclasslabel, cmfclasslabel, (float**) input, 8,
			G[table[1]], ListTable::classsigma[cmfsimilarclasslabel - 1]);
	if ((cmfk - cmfm) < (G[table[1]] - G[table[0]]) && cmfk > cmfm)
	//if(cmfk>cmfm)
			{
		//System.out.println("you "+ListTable.Labels.substring(tmp.get(table[0]).intValue()-1,tmp.get(table[0]).intValue())+"jiao huan wei "+ListTable.Labels.substring(tmp.get(table[1]).intValue()-1,tmp.get(table[1]).intValue()));
		tem = table[0];
		table[0] = table[1];
		table[1] = tem;
	}
	//cout<<ListTable::Labels.substr(3458,2)<<endl;
	list<string> Resulttable;
	/*for(int m=0;m<ListTable::Labels.size();)
	 {
	 cout<<ListTable::Labels.substr(m,2)<<endl;
	 m
	 }*/
	for (int i = 0; i < selectedNum; i++) {
		iii = tmp.begin();
		for (int yy = 0; yy < table[i]; yy++)
			iii++;
		//cout<<"ha"<<(*iii)<<endl;
		//cout<<ListTable::Labels.substr((*iii)-1,2)<<endl;
		Resulttable.push_back(ListTable::Labels.substr(2 * ((*iii) - 1), 2));
		cout << ListTable::Labels.substr(2 * ((*iii) - 1), 2) << endl;
		//cout<<ListTable::Labels.substr(((*iii)+2),2)<<endl;
	}
	string s = "";
	list<string>::iterator str = Resulttable.begin();
	for (int i = 0; i < selectedNum; i++, str++)		//5
		s += (*str);
	return s;

}

/**
 * 做变化和平滑处理
 * */
list<MyStroke> Recognize::transtosmall(list<MyStroke> &recognizeTable) {
	list<MyStroke> array1;
	list<MyStroke> Array;
	MyStroke stro;
	list<short> xx;
	list<short> yy;

	/*对原list<MyStroke>的中点做变换，存入array1中*/
	BOOST_FOREACH(MyStroke myStroke, recognizeTable){
		MyStroke stroke;
		BOOST_FOREACH(BasePoint bp, myStroke.getPoints()){
			short x = 0, y = 0;
			x = (short) ((float) bp.getX() / 2 + 0.5);
			y = (short) ((float) bp.getY() / 2 + 0.5);
			x=(x<1)?1:x;
			x=(x>64)?64:x;
			y=(y<1)?1:y;
			y=(y>64)?64:y;
			stroke.addPoint(new BasePoint(--x, --y));
		}
		array1.push_back(stroke);
	}

	const float t = (float) ((float) 1.0 / (float) 4.0);

	BOOST_FOREACH(MyStroke myStroke, array1){
		xx.clear();
		yy.clear();
		xx.push_back(myStroke.getPoints().front().getX());
		yy.push_back(myStroke.getPoints().front().getY());
		//xx, yy共有N+2个元素
		BOOST_FOREACH(BasePoint bp, myStroke.getPoints()){
			xx.push_back((short) ((float) bp.getX() + 0.5));
			yy.push_back((short) ((float) bp.getY() + 0.5));
		}
		xx.push_back((short)(myStroke.getPoints().back().getX()+0.5));
		yy.push_back((short)(myStroke.getPoints().back().getY()+0.5));


		list<short>::iterator ix = xx.begin();
		list<short>::iterator ix2 = xx.begin();
		ix2++;
		list<short>::iterator ix3 = xx.begin();
		ix3++;
		ix3++;
		list<short>::iterator iy = yy.begin();
		list<short>::iterator iy2 = yy.begin();
		iy2++;
		list<short>::iterator iy3 = yy.begin();
		iy3++;
		iy3++;
		stro.Clear();
		for ( ; ix3 != xx.end(); ix++, ix2++, ix3++, iy++, iy2++, iy3++ ) {
			//。。。？
			for (int k = 2; k < 3; k++) {
				float t1 = (k - 1) * t;
				float t2 = t1 * t1;
				float a = (float) ((t2 - 2 * t1 + 1) / 2.0);
				float b = (float) (t1 - t2 + 1 / 2.0);
				float c = (float) (t2 / 2.0);
				short X = 0, Y = 0;
				X = (short) ((a * (*ix) + b * (*ix2) + c * (*ix3)) + 0.5);
				Y = (short) ((a * (*iy) + b * (*iy2) + c * (*iy3)) + 0.5);
				X=(X<1)?1:X;
				X=(X>64)?64:X;
				Y=(Y<1)?1:Y;
				Y=(Y>64)?64:Y;
				BasePoint bp(--X, --Y);
				stro.addPoint(bp);
			}
		}
		Array.push_back(stro);
	}
	return Array;
}
void Recognize::BiMatrix(double a[1][512], double b[512][160],
		float z[1][160]) {
	for (int xx = 0; xx < 1; xx++) {
		for (int yy = 0; yy < 160; yy++) {
			double result = 0;
			for (int oo = 0; oo < 512; oo++) {
				result = result + a[xx][oo] * b[oo][yy];
			}

			z[xx][yy] = (float) result;

		}
	}
}

/**
 * DDA插值
 * */
void Recognize::DDA_disp(list<MyStroke> &recognizeTable, short test[64][64]) {
	short matrix[64][64];
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++)
			matrix[i][j] = 1;
	DDA *dda = new DDA();

	list<BasePoint>::iterator iter, iterTmp;
	BOOST_FOREACH(MyStroke myStroke, recognizeTable){
		//对相邻的两个点计算DDA，存入points中
		for(iter=myStroke.getPoints().begin(), iterTmp=iter, iterTmp++ ; iterTmp!=myStroke.getPoints().end(); iter++, iterTmp++){
			list<BasePoint> points;
			points=dda->DDAData(*iter, *iterTmp);
			BOOST_FOREACH(BasePoint bp, points){
				matrix[bp.getX()][bp.getY()]=0;
			}
		}
	}
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			test[i][j] = matrix[j][i];
		}
	}
	delete dda;
}
void Recognize::FindminTmp(double distance[], int k, int n, int Grouplabel[]) {
	//int[] Grouplabel=new int[k];
	for (int i = 0; i < k; i++) {
		int index = 0;
		index = Min(distance, n);
		Grouplabel[i] = index;
		distance[index] = DBL_MAX;
	}
	//return Grouplabel;
}
void Recognize::Findmin(double distance[], int k, int n, int Grouplabel[]) {
	for (int i = 0; i < k; i++) {
		int index = -1;
		index = Min(distance, n);
		Grouplabel[i] = index;
		distance[index] = DBL_MAX;
	}
}
int Recognize::Min(double array[], int n) {
	double min = DBL_MAX;
	int index = 0;
	for (int i = 0; i < n; i++)
		if (array[i] < min) {
			min = array[i];
			index = i;
		}
	return index;
}
int Recognize::Max(int array[], int n) {
	int index = 0;
	double max = DBL_MIN;
	for (int i = 0; i < n; i++) {
		if (array[i] > max) {
			max = array[i];
			index = i;
		}
	}
	return index;
}
double Recognize::MQDF(float**input, int k, int index, double classsigma) {
	double alpha = 0.2;
	double s = 0, tmp = 0;
	double g1 = 0, g11 = 0, g10 = 0, g2 = 0, g3 = 0, g4 = 0, g = 0;
	double temp[160];
	double tm[160];
	//cout<<index<<" "<<classsigma<<endl;
	boost::unordered_map<int, int>::iterator it = classtoindex.begin();
	for (; it != classtoindex.end(); it++) {
		if (it->second == index)
			break;
	}
	//int indexv = classtoindex..get(index);	
	int indexv = it->first;
	//cout<<indexv<<endl;
	classsigma = classsigma * alpha;
	for (int i = 0; i != 160; i++) {

		temp[i] = *((float*) input + i)
				- (*((double*) ListTable::u + 160 * (index - 1) + i));
		g10 += pow(temp[i], 2);
	}
	//cout<<g10<<endl;
	for (int i = 0; i != k; i++) {
		s = 0;
		for (int j = 0; j != 160; j++) {
			s += temp[j] * (ListTable::v[indexv * 160 + j][i]);
			//s+=temp[j]*(*(float*)(&(*(ListTable::v + 8*(indexv*160+j) + i))));//zhege vbudui
			//s+=temp[j]*(float*)ListTable::v+8*(indexv*)
			//s+=temp[j]*ListTable::v[(index-1)*160+j][i];
			//cout<<temp[j]<<" "<<(ListTable::v[indexv*160+j][i])<<" "<<s<<endl;
			//System.out.println("tmp[j] v "+temp[j]+" "+ListTable.v[indexv*160+j][i] );
		}
		//cout<<s<<endl;
		tmp = (1
				- classsigma
						/ (*((double*) ListTable::d + 75 * (index - 1) + i)))
				* pow(s, 2);

		g11 += tmp;

	}
	//cout<<g11<<endl;
	g1 = (g10 - g11) / classsigma;
	//System.out.println("g11 classsigam "+g11+" "+classsigma);
	s = 0;
	for (int i = 0; i != k; i++) {
		s = log((*((double*) ListTable::d + 75 * (index - 1) + i)))
				/ log((double) 2);
		g2 += s;
	}

	g3 = (160 - k) * (log(classsigma) / log((double) 2));
	g = g1 + g2 + g3;
	//System.out.println("g1 g2 g3 "+g1+" "+g2+" "+g3);
	//cout<<g<<endl;
	return g;
}
double Recognize::CMF(int cmfclasslabel, int cmfsimilarclasslabel,
		float** input, int k, double mqdf, double classsigma) {
	double g = 0;
	double s = 0;
	double t = 0;
	double alpha = 0.2;
	//double[] d0= new double[k];
	//int len = input[0].length;//160
	//int indexvcmfclasslabel = cmfclasslabel-1;
	boost::unordered_map<int, int>::iterator it = classtoindex.begin();
	for (; it != classtoindex.end(); it++) {
		if (it->second == cmfclasslabel)
			break;
	}
	int indexvcmfclasslabel = it->first;
	double u1u0[160];
	double u0[160];
	//float[][] v0 = new float[len][k];	
	double u1[160];
	double g1, g2, g20 = 0, g21 = 0, g23 = 0, g24 = 0, beda = 0.5;
	double temp[160];
	classsigma *= alpha;
	//*((double*)ListTable::u + 160*(index-1) + i)
	for (int mm = 0; mm < 160; mm++) {
		u0[mm] = *((double*) ListTable::u + 160 * (cmfclasslabel - 1) + mm);
		u1[mm] = *((double*) ListTable::u + 160 * (cmfsimilarclasslabel - 1)
				+ mm);
		//cout<<u0[mm]<<" "<<u1[mm]<<endl;
	}
	//u0 = ListTable.u[cmfclasslabel-1];
	//u1 = ListTable.u[cmfsimilarclasslabel-1];

	g1 = mqdf;

	for (int i = 0; i != 160; i++) {
		temp[i] = *((float*) input + i) - u0[i];
	}
	for (int i = 0; i != 160; i++) {
		u1u0[i] = u1[i] - u0[i];
		g20 += temp[i] * u1u0[i];
		g23 += pow(u1u0[i], 2);
	}
	//cout<<g20<<"  "<<g23<<endl;
	for (int i = 0; i != k; i++) {
		s = 0;
		t = 0;
		for (int j = 0; j != 160; j++) {

			//s+= temp[j]*(*((double*)ListTable::v + 8*(indexvcmfclasslabel*160+j) + i));
			//t+= u1u0[j]*(*((double*)ListTable::v + 8*(indexvcmfclasslabel*160+j) + i));		
			s += temp[j] * ListTable::v[indexvcmfclasslabel * 160 + j][i];
			t += u1u0[j] * ListTable::v[indexvcmfclasslabel * 160 + j][i];
			//cout<<s<<"  "<<t<<endl;
		}
		g21 += s * t;
		g24 += t * t;
	}
	//cout<<g21<<"  "<<g24<<endl;
	g2 = pow(g20 - g21, 2);
	g2 = g2 / (classsigma * (g23 - g24));
	g = (1 - beda) * g1 + beda * g2;
	//System.out.println("g2 g1 g "+g2+" "+g1);
	return g;
}
double Recognize::Cal_Euclid_Dis(float**input, int index) {

	double dis = 0;
	for (int i = 0; i != 160; i++) {
		//cout<<*((float*)input  + i)<<"  "<<*((double*)ListTable::u + 160*(index-1) + i)<<endl;
		dis += pow(
				(*((float*) input + i)
						- (*((double*) ListTable::u + 160 * (index - 1) + i))),
				2);
	}	//dis+=pow((input[0][i] - ListTable::u[index - 1][i]),2);
	return dis;
}

Recognize::~Recognize(void) {
}
