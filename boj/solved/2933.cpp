#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int,int> coor; // x,y
constexpr int INF = 987654321;

int R, C, N;
int udlr[4][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
vector<string> grid;
vector<string> cluster;

void fallCluster(int r, int c)
{
    // r,c 위치의 클러스터를 추락시킨다
    char cl = cluster[r][c];
    vector<coor> clCoor;
    
    // 클러스터 x 단위들에 대해 최소 이동거리 계산
    int fallDist = INF;
    int hasCluster;
    
    for (int x=0; x<C; ++x) {
        hasCluster = 0;
        for (int j=0; j<R; ++j) {
            if (hasCluster) {
                if (cluster[j][x] != '.' && cluster[j][x] != cl) {
                    // 충돌 발생
                    fallDist = min(fallDist, j - hasCluster - 1);
                }
            }
            if (cluster[j][x] == cl) {
                hasCluster = j;
                clCoor.push_back({x, j});
            }
        }
        
        if (hasCluster) { // 바닥 충돌
            fallDist = min(fallDist, R - hasCluster - 1);
        }
    }
    
    // 추락할 클러스터가 없을 경우 (애초에 발생해선 안됨)
    if (fallDist >= INF) return;
    
    // 중력 연산
    for (coor c : clCoor) {
        cluster[c.second][c.first] = '.';
        grid[c.second][c.first] = '.';
    }
    for (coor c : clCoor) {
        cluster[c.second + fallDist][c.first] = cl;
        grid[c.second + fallDist][c.first] = 'x';
    }
}

// 클러스터 갯수 반환
int initCluster()
{
    int ret = 0;
    char clCnt = 'A';
    cluster = grid; // 복사
    
    for (int i=0; i<R; ++i) {
        for (int j=0; j<C; ++j) {
            if (cluster[i][j] == 'x') {
                // bfs
                queue<coor> q;
                q.push({j,i}); // x,y
                while(!q.empty()) {
                    coor curr = q.front();
                    q.pop();
                    if (cluster[curr.second][curr.first] != 'x') continue; // 이미 방문
                    cluster[curr.second][curr.first] = clCnt;
                    for (int* dxdy : udlr) {
                        if (curr.first + dxdy[0] < 0 || curr.first + dxdy[0] >= C || curr.second + dxdy[1] < 0 || curr.second + dxdy[1] >= R) continue;
                        q.push({curr.first + dxdy[0], curr.second + dxdy[1]});
                    }
                }
                ret = clCnt - 'A' + 1;
                clCnt++;
            }
        }
    }
    return ret;
}

void simulate(int h, bool fromL/*true: l to r*/)
{
    // 파괴
    int cr, cc;
    char brokenCl;
    if (fromL) {
        for (int i=0; i<C; ++i) {
            if (grid[h][i] == 'x') {
                cr = h; cc = i; brokenCl = cluster[h][i];
                grid[h][i] = '.'; cluster[h][i] = '.';
                break;
            }
        }
    }
    else {
        for (int i=C-1; i>=0; --i) {
            if (grid[h][i] == 'x') {
                cr = h; cc = i; brokenCl = cluster[h][i];
                grid[h][i] = '.'; cluster[h][i] = '.';
                break;
            }
        }
    }
    
    // 클러스터 업데이트
    initCluster();

    // 위 클러스터 추락
    char clNum = 0;
    if (cr-1 > 0 && cr-1 < R) {
        clNum = (cluster[cr-1][cc] != '.') ? cluster[cr-1][cc] : 0;
    }
    if (clNum) fallCluster(cr-1, cc);
    
    // 진행방향 클러스터 추락
    clNum = 0;
    int dx = fromL ? 1 : -1;
    if (cc+dx > 0 && cc+dx < C) {
        clNum = (cluster[cr][cc+dx] != '.') ? cluster[cr][cc+dx] : 0;
    }
    if (clNum) fallCluster(cr, cc+dx);
    
    // 아래 클러스터 추락
    clNum = 0;
    if (cr+1 > 0 && cr+1 < R) {
        clNum = (cluster[cr+1][cc] != '.') ? cluster[cr+1][cc] : 0;
    }
    if (clNum) fallCluster(cr+1, cc);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout.tie(NULL); cin.tie(NULL);
    
    // 인풋1
    cin >> R >> C;
    grid.reserve(R);
    
    for (int i=0; i<R; ++i) {
        string row;
        cin >> row;
        grid.push_back(row);
        cluster.push_back(row);
    }
    
    // 클러스터 초기화
    initCluster();
    
    // 인풋2
    cin >> N;
    int x;
    for (int i=0; i<N; ++i) {
        cin >> x;
        simulate(R-x, i%2 ? false : true);
    }
    
    // 정답
    for (int i=0; i<R; ++i) {
        cout << grid[i] << '\n';
    }

    return 0;
}

