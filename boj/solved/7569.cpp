#include <iostream>
#include <queue>
using namespace std;
int graph[100][100][100];
//rch
int dir[6][3]{ {1,0,0},{0,1,0},{-1,0,0},{0,-1,0},{0,0,1},{0,0,-1} };
int R, C, H;
int ret = 1;
queue<pair<pair<int, int>, int>> q;

void bfs() {
	while (!q.empty()) {
		int size = q.size();
		for (int i = 0; i < size;i++) {
			int r = q.front().first.first;
			int c = q.front().first.second;
			int h = q.front().second;
			q.pop();
			for (int j = 0; j < 6; j++) {
				int nr = r + dir[j][0];
				int nc = c + dir[j][1];
				int nh = h + dir[j][2];
				if (nr >= 0 && nr < R && nc >= 0 && nc < C && nh >= 0 && nh < H &&graph[nh][nr][nc] == 0) {
					q.push({ {nr,nc} ,nh });
					graph[nh][nr][nc] = graph[h][r][c] + 1;
					ret = max(graph[nh][nr][nc], ret);
				}
			}
		}
	}

    // 안익은 토마토 찾기
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				if (graph[i][j][k]==0) {
					cout << -1;
					return;
				}
			}
		}
	}
	cout << ret-1; // 시작노드들도 1을 값으로 가지므로
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> C >> R >> H;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < R; j++) {
			for (int k = 0; k < C; k++) {
				cin >> graph[i][j][k];
				if (graph[i][j][k] == 1) {
					q.push({ {j,k},i });
				}
			}
		}
	}
	bfs();

	return 0;
}
