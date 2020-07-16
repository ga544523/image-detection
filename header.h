#include<opencv2/opencv.hpp>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <complex>¡@
#include <cstdio>
#include <cstring>
#include <deque>¡@¡@¡@¡@¡@
#include <functional>¡@¡@¡@
#include <list>¡@¡@¡@¡@¡@¡@
#include <map>¡@¡@¡@¡@¡@¡@ 
#include <iomanip>       
#include <iostream>
#include <queue>¡@¡@¡@¡@¡@
#include <set>¡@¡@¡@¡@¡@¡@
#include <stack>
#include <string>¡@¡@¡@¡@¡@
#include <vector>¡@¡@¡@¡@
#include "opencv2/imgcodecs/legacy/constants_c.h"
#include "opencv2/imgproc/types_c.h"
#include <opencv2/opencv.hpp>

using namespace std;
#define con continue
#define bk break
#define ms(a, b) memset((a), (b), sizeof(a))
#define mp make_pair
#define sz size()
#define len(X) strlen(X)
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define de cout<<"test"<<endl;
#define st system("pause");
#define pt cout<<endl;
using namespace cv;

struct region {
	Point pos[2];
	double size = 0;
	vector<double> text;
	vector<double> color;
};




void datapass(Mat ori,Mat seg,int *f);
vector<double> getcolor(Mat img, Point p1, Point p2);
vector<double> gettext(Mat img, Point p1, Point p2);
double comparecolor(region r1, region r2);
double comparetext(region r1, region r2);
double smallregion(region r1, region r2);
double fillregion(region r1, region r2);
region merge(region r1, region r2);




