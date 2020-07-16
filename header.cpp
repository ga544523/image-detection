#include <header.h>
using namespace std;
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define de cout<<"test"<<endl;
#define st system("pause");
#define pt cout<<endl;
using namespace cv;

double imgsize = 0;
const int N = 5000005;
int minx[N] = {};
int miny[N] = {};
int maxx[N] = {};
int maxy[N] = {};
map<pair< pair<int, int>, pair<int, int> >, int > countregion;

vector<double> getcolor(Mat img,region r) {
	vector<double>ans;
	double tmp = 0;
	for (int k = 0;k < 3;k++) {
		double num[256] = {};
		for (int i = r.pos[0].y;i <= r.pos[1].y;i++) {
			for (int j = r.pos[0].x;j <= r.pos[1].x;j++) {
				Vec3b pix1 = img.at<Vec3b>(i, j);
				
				num[ int(pix1[k]) ]++;
				
			}
		}
		double res = 0;
		for (int i = 0;i < 256;i++) {
			res +=num[i] ;
			if (i % 25 == 24) {
				res /= 25;
				ans.push_back(res);
				tmp += res;
				res = 0;
			}
		}
	}
	for (int i = 0;i < ans.size();i++) {
		ans[i] /= tmp;
	}
	return ans;
}
vector<double> gettext(Mat img, Point p1, Point p2) {
	int di[8] = { 0,0, -1,1,1 ,-1,-1,1 };
	int dj[8] = { 1,-1 ,0, 0,1,-1,1,-1 };
	int channels = img.channels();
	int height = img.rows;
	int width = img.cols;
	vector<double>ans;
	double tmp = 0;
	for (int k = 0;k < 3;k++) {
		double num[256] = {};
		for (int r = 0;r < 8;r++) {
		for (int i = p1.y;i <= p2.y;i++) {
			for (int j = p1.x;j <= p2.x;j++) {
				Vec3b pix1 = img.at<Vec3b>(i, j);
				int nei = i + di[r], nej = j + dj[r];
				int flag = 0;

				if ((nei >= 0 && nei < height) && (nej >= 0 && nej < width)) {
					flag = 1;
				}
				if (!flag)
					con;
				Vec3b pix2 = img.at<Vec3b>(nei, nej);
				num[ abs(int(pix1[k] - pix2[k]) ) ]++;
				}
				
			}
		}
		double res = 0;
		for (int i = 0;i < 256;i++) {
			res +=num[i];
			if (i % 25 == 24) {
				res /= 25;
				ans.push_back(res);
				tmp += res;
				res = 0;
			}
		}
	}
	for (int i = 0;i < ans.size();i++) {
		ans[i]/=tmp;
	}
	return ans;
}
double getsize(region r) {
	return (r.pos[1].x - r.pos[0].x) * (r.pos[1].y - r.pos[0].y);
}

double comparecolor(region r1,region r2) {
	double num = 0;
	for (int i = 0;i < r1.color.size();i++) {
		num += min(r1.color[i], r2.color[i]);
	}
	return num;
}

double comparetext(region r1, region r2) {
	double num = 0;
	for (int i = 0;i < r1.text.size();i++) {
		num += min(r1.text[i], r2.text[i]);
	}
	return num;
}

double smallregion(region r1, region r2) {
	return 1.0 - ( (r1.size + r2.size) / imgsize);
}

double fillregion(region r1, region r2) {
	
	double maxx = max(r1.pos[1].x, r2.pos[1].x);
	double minx = min(r1.pos[0].x, r2.pos[0].x);

	double maxy = max(r1.pos[1].y, r2.pos[1].y);
	double miny = max(r1.pos[0].y, r2.pos[0].y);
	double bounding = (maxx - minx) * (maxy - miny);

	return 1.0 - ( (bounding-(r1.size + r2.size)) / imgsize);
}
region merge(region r1,region r2) {
	region newregion;
	newregion.pos[0].x = min(r1.pos[0].x, r2.pos[0].x), newregion.pos[0].y = min(r1.pos[0].y, r2.pos[0].y);
	newregion.pos[1].x = max(r1.pos[1].x, r2.pos[1].x), newregion.pos[1].y = max(r1.pos[1].y, r2.pos[1].y);

	double total = r1.size + r2.size;

	for (int i = 0;i < r1.color.size();i++) {
		newregion.color.push_back(r1.color[i] * (r1.size / total) + r2.color[i] * (r2.size / total));
		newregion.text.push_back(r1.text[i] * (r1.size / total) + r2.text[i] * (r2.size / total));
	}
	newregion.size = (newregion.pos[1].x - newregion.pos[0].x) * (newregion.pos[1].y - newregion.pos[0].y);
	return newregion;

}
int call = 0;
vector<region>R;
vector<region>origionalR;
void datapass(Mat ori,Mat seg,int *f) {

	call++;
	cout << call << endl;
	int channels = ori.channels();
	int height = ori.rows;
	int width = ori.cols;
	if (call == 1) {
		for (int i = 0;i < N;i++) {
			minx[i] = 100000;
			miny[i] = 100000;
			maxx[i] = -1;
			maxy[i] = -1;

		}

		for (int i = 0;i < height;i++) {
			for (int j = 0;j < width;j++) {

				int g = f[i * width + j];

				minx[g] = min(j, minx[g]);
				miny[g] = min(i, miny[g]);
				maxx[g] = max(j, maxx[g]);
				maxy[g] = max(i, maxy[g]);
			}
		}
	

		for (int i = 0;i < N;i++) {

			if (maxx[i] != -1) {
				region tmp;
				tmp.pos[0] = cvPoint(minx[i], miny[i]);
				tmp.pos[1] = cvPoint(maxx[i], maxy[i]);
				tmp.size = (maxx[i] - minx[i]) * (maxy[i] - miny[i]);
				R.push_back(tmp);
			}
		}

		for (int i = 0;i < R.size();i++) {
			R[i].color = getcolor(ori, R[i]);
			R[i].text = gettext(ori, R[i].pos[0], R[i].pos[1]);
			R[i].size = getsize(R[i]);
		}
		origionalR = R;
	}
	for (int bit = 1;bit <= 8;bit++) {
		
		R = origionalR;
		imgsize = height * width;

		/*
		for (int i = 0;i < R.size();i++) {

			cv::rectangle(ori, R[i].pos[0], R[i].pos[1], Scalar(255, 0, 0), 1, 1, 0);
			imshow("HelloCV1", ori);
			waitKey();
		}
		*/



		while (R.size() > 1) {
			
			double maxsim = -1000;
			pair<int, int>mergeregion;
			vector<region>newregion;
			for (int i = 0;i < R.size();i++) {

				for (int j = i + 1;j < R.size();j++) {
					double tmp = ( (bit&1) >0)*fillregion(R[i], R[j]) + ( (bit&2) >0)*smallregion(R[i], R[j]) + ( (bit&4) >0) * comparecolor(R[i], R[j]) + ( (bit&8) >0) * comparetext(R[i], R[j]);

					if (tmp > maxsim) {
						maxsim = tmp;
						mergeregion = make_pair(i, j);

					}
				}
			}
			/*
			cv::rectangle(ori, R[mergeregion.first].pos[0], R[mergeregion.first].pos[1], Scalar(255, 0, 0), 1, 1, 0);
			cv::rectangle(ori, R[mergeregion.second].pos[0], R[mergeregion.second].pos[1], Scalar(255, 0, 0), 1, 1, 0);
			imshow("HelloCV1", ori);
			waitKey(1000);
			*/

			region aftermerge = merge(R[mergeregion.first], R[mergeregion.second]);
			for (int i = 0;i < R.size();i++) {
				if (i != mergeregion.first && i != mergeregion.second) {
					newregion.push_back(R[i]);
				}
			}

			if (newregion.size() > 2) {
				pair<int, int>A1 = make_pair(aftermerge.pos[0].x, aftermerge.pos[0].y);
				pair<int, int>A2 = make_pair(aftermerge.pos[1].x, aftermerge.pos[1].y);
				countregion[make_pair(A1, A2)]++;

			}

			newregion.push_back(aftermerge);
			R = newregion;
		}
	}
	map<int, vector<pair< pair<int, int>, pair<int, int> > >,greater<int> > outputregion;


	if (call == 1){
		


		for (auto itr = countregion.begin(); itr != countregion.end(); ++itr) {
			outputregion[itr->second].push_back(itr->first);
		}
		for (auto itr = outputregion.begin(); itr != outputregion.end(); ++itr) {
			cout << itr->first << endl;
			for (int i = 0;i < itr->second.size();i++) {
				Mat showimg = imread("pa.png", CV_LOAD_IMAGE_COLOR);
				int area = (itr->second[i].second.first - itr->second[i].first.first) * (itr->second[i].second.second - itr->second[i].first.second);
				cv::rectangle(showimg, cvPoint(itr->second[i].first.first, itr->second[i].first.second), cvPoint(itr->second[i].second.first, itr->second[i].second.second), Scalar(255, 0, 0), 1, 1, 0);
				if (area >= 3000 && area <= 8000) {
					imshow("HelloCV1", showimg);
					waitKey(3000);
				}
			}

		}
	}


	/*
	for (int i = 0;i < outputregion.size();i++) {

		cv::rectangle(ori, R[i].pos[0], R[i].pos[1], Scalar(255, 0, 0), 1, 1, 0);
		imshow("HelloCV1", ori);
		waitKey(1000);
	}
	*/

}