#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

typedef pair<double, double> P;
typedef pair<P, P> PP;
vector<P> v;
vector<int> st;
int startPoint,res;
int x, y;

bool cmp(const P a, const P b) {
	if ((x - b.first)*(y - a.second) == (x - a.first)*(y - b.second)) 
	{
		if (a.second == b.second)
			return a.first < b.first;
		else
			return a.second < b.second;
	}
	else 
	{
		return (x - b.first)*(y - a.second) < (x - a.first)*(y - b.second);			
	}
}

/*
//atan2 사용 가능
//long double일때 불가능함에 유의

bool cmp(const P a, const P b) {
    double aa = atan2(a.second - y, a.first - x);
    double bb = atan2(b.second - y, b.first - x);
    
	if (aa == bb) 
	{
		if (a.second == b.second)
			return a.first < b.first;
		else
			return a.second < b.second;
	}
	else return aa < bb;
}
*/


double ccw(PP a,P b) {
	P a1 = a.first,a2=a.second;
	double ccw11 = (a1.first*a2.second + a2.first*b.second + b.first*a1.second)
		- (a2.first*a1.second + b.first*a2.second + a1.first*b.second);

	return ccw11;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	int q, w;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> q >> w;
		v.push_back({ q,w });
		if (v[startPoint].second > w ||(v[startPoint].second==w && v[startPoint].first > q)) {
			startPoint = i;
		}
	}
	
	x = v[startPoint].first;
	y = v[startPoint].second;
	
	sort(v.begin(), v.end(), cmp);
	
	st.push_back(0);
	st.push_back(1);
	int t = 1; // top
	int idx = 2;
	
	while (idx < n) {
		double ccwV = ccw(make_pair(v[st[t-1]], v[st[t]]), v[idx]);
		if (ccwV>0) {
			st.push_back(idx);
			idx++;
			t++;
		}
		else if (ccwV == 0) {
			st.pop_back();
			st.push_back(idx);
			idx++;
		}
		else {
			st.pop_back();
			t--;
		}
	}
	cout << st.size() << '\n';
	return 0;
}
