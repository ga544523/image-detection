#include <header.h>
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
#include <time.h>   /* 時間相關函數 */

struct node {
	double w;
	pair< pair<int, int>, pair<int, int> > pos;

};
int compareTo(node a, node b) {
	return a.w < b.w;
}

node edge[5000005] = {};

double maxc[5000005] = {};
double countc[5000005] = {};
int vis[2505][2505] = {};
int f[5000005] = {};
int Rank[5000005] = {};

int Find(int x) {

	if (x == f[x]) {
		return x;
	}
	else {
		return f[x] = Find(f[x]);
	}
}

double mint(int a, int b,double t) {

	double t1 = t / countc[a];
	double t2 = t / countc[b];
	return min(maxc[a] + t1, maxc[b] + t2);
}

int fcolor[5000005][3] = {};

int main() {

	for (int T = 50;T <= 10000;T += 100) {
		double K = T;
		for (int i = 0;i < 5000005;i++) {
			f[i] = i;
			countc[i] = 1;
			Rank[i] = 1;
			maxc[i] = 0;
		}
		for (int i = 0;i < 2505;i++) {
			for (int j = 0;j < 2505;j++) {
				vis[i][j] = 0;
			}
		}
		/*
		Mat ori = imread("test1.png", CV_LOAD_IMAGE_COLOR);
		Mat img = imread("test1.png", CV_LOAD_IMAGE_COLOR);
		Mat out = imread("test1.png");
		*/
		
		
		Mat ori = imread("touhou.png", CV_LOAD_IMAGE_COLOR);
		Mat img = imread("touhou.png", CV_LOAD_IMAGE_COLOR);
		Mat out = imread("touhou.png");
		


		img.convertTo(img, CV_32FC3);
	


		int channels = img.channels();
		int height = img.rows;
		int width = img.cols;

		int cnt = 0;
		int di[8] = { 0,0, -1,1,1 ,-1,-1,1 };
		int dj[8] = { 1,-1 ,0, 0,1,-1,1,-1 };
		for (int i = 0;i < height;i++) {

			for (int j = 0;j < width;j++) {


				pair<int, int>now = make_pair(i, j);

				for (int r = 0;r < 4;r++) {
					int flag = 0;
					int nei = i + di[r], nej = j + dj[r];
					pair<int, int>nex = make_pair(nei, nej);
					if ((nei >= 0 && nei < height) && (nej >= 0 && nej < width)) {
						flag = 1;
					}
					if (!flag)
						con;
					if (vis[nei][nej])
						con;

					edge[cnt].pos = make_pair(now, nex);
					Vec3f pix1 = img.at<Vec3f>(i, j);
					Vec3f pix2 = img.at<Vec3f>(nei, nej);

					edge[cnt].w = sqrt((pix1 - pix2).dot((pix1 - pix2)));
					cnt++;
				}
				vis[i][j] = 1;

			}


		}
		sort(edge, edge + cnt, compareTo);


		for (int i = 0;i < cnt;i++) {

			node tmp = edge[i];
			pair<int, int>t1, t2;
			t1 = make_pair(edge[i].pos.first.first, edge[i].pos.first.second);
			t2 = make_pair(edge[i].pos.second.first, edge[i].pos.second.second);

			int u = Find(t1.first * width + t1.second);
			int v = Find(t2.first * width + t2.second);

			if (u == v) {
				con;
			}


			else {

				if (u != v && (tmp.w <=mint(u,v,K) ) ) {
					if (Rank[u] < Rank[v]) {
						f[u] = v;
						maxc[v] = tmp.w;
						countc[v] += countc[u];
						countc[u] = 0;
					}

					else if (Rank[v] < Rank[u]) {
						f[v] = u;
						maxc[u] = tmp.w;
						countc[u] += countc[v];
						countc[v] = 0;
					}
					else {
						f[u] = v;
						maxc[v] = tmp.w;
						Rank[v] += 1;
						countc[v] += countc[u];
						countc[u] = 0;
					}
				}




			}

		}

		for (int i = 0;i < cnt;i++) {

			node tmp = edge[i];
			pair<int, int>t1, t2;
			t1 = make_pair(edge[i].pos.first.first, edge[i].pos.first.second);
			t2 = make_pair(edge[i].pos.second.first, edge[i].pos.second.second);

			int u = Find(t1.first * width + t1.second);
			int v = Find(t2.first * width + t2.second);

			if (u == v) {
				con;
			}

			else {
				if (countc[u] < 1000 || countc[v] < 1000) {
					f[v] = u;
					countc[u] += countc[v];
					countc[v] = 0;
				}

			}

		}

		int color = 1;
		int maxseg = 0;
		int maxid = 0;
		map<int, int>col;

		for (int i = 0;i < height;i++) {
			for (int j = 0;j < width;j++) {

				int g = Find(i * width + j);
				if (!col[g]) {
					fcolor[g][0] = out.at<Vec3b>(i, j)[0];
					fcolor[g][1] = out.at<Vec3b>(i, j)[1];
					fcolor[g][2] = out.at<Vec3b>(i, j)[2];
					col[g] = 1;

				}

			}

		}


		vector<pair<int, int> >sor;
		for (int i = 0;i < 5000005;i++) {
			if (countc[i] > 1) {
				sor.push_back(make_pair(countc[i], i));
			}
		}
		sort(sor.begin(), sor.end());
		reverse(sor.begin(), sor.end());

		int R[10240] = {};
		int B[10240] = {};
		int G[10240] = {};
		for (int i = 0;i < sor.sz;i++) {
			R[i] = rand() % 256;
			G[i] = rand() % 256;
			B[i] = rand() % 256;
		}

		for (int k = 0;k < sor.sz;k++) {

			for (int i = 0;i < height;i++) {
				for (int j = 0;j < width;j++) {
					if (Find(i * width + j) == sor[k].second) {
						out.at<Vec3b>(i, j)[0] = R[k];
						out.at<Vec3b>(i, j)[1] = G[k];
						out.at<Vec3b>(i, j)[2] = B[k];

					}

					/*
					else {
						out.at<Vec3b>(i, j)[0] = 0;
						out.at<Vec3b>(i, j)[1] = 0;
						out.at<Vec3b>(i, j)[2] = 0;
					}
					*/

				}
			}
		}
		/*
		imshow("outseg", out);
		waitKey();
		*/

		datapass(ori, out, f);

	}
	return 0;
}