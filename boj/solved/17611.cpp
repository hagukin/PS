#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N;
vector<pair<int,int>> hor;
vector<pair<int,int>> ver;

inline void addLine(int px, int py, int x, int y)
{
    if (y == py) {
        hor.push_back({min(px,x), max(px,x)});
    } else if (x == px) {
        ver.push_back({min(py,y), max(py,y)});
    }
}

int getMachineCnt(vector<pair<int,int>>& v) {
    priority_queue<int, vector<int>, greater<int>> machines; // minHeap
    sort(v.begin(), v.end());
    for (pair<int,int> p : v) {
        if (machines.empty() || machines.top() > p.first) {
            machines.push(p.second);
        } else {
            machines.pop();
            machines.push(p.second);
        }
    }
    return machines.size();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> N;
	
    int sx, sy, px, py, x, y;
	for (int i = 0; i < N; ++i) {
	    px = x;
	    py = y;
	    cin >> x >> y;
	    if (i == 0) {
	        sx = x;
	        sy = y;
	    } else {
	        addLine(px, py, x, y);
	    }
	}
	addLine(x, y, sx, sy); // 마지막 선분
	
	cout << max(getMachineCnt(hor), getMachineCnt(ver)) << '\n';
	return 0;
}
