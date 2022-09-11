#include <iostream>
#include <cstring>
#include <set>
using namespace std;
constexpr int MAXN = 53;
int M, N;
int tiles[MAXN][MAXN]; // [i][j] = k: 해당 타일이 k번방에 속함. 맵은 1,1부터 시작.
int walls[MAXN][MAXN]; // [i][j] = k: k의 비트에 따라 어디어디에 벽이 있는지를 저장.
bool visited[MAXN][MAXN]; // NOTE: tiles -1을 nonvisited로 만들면 메모리 줄이기 가능할지도
int doorDir[4] = {2,8,1,4}; // udlr
int moveDir[4][2] = {{0,-1},{0,1},{-1,0},{1,0}}; // dxdy
int roomSizes[2501];
set<int> adjRoom[2501]; // adj[i]: i번방과 adjacent한 방들의 집합

// R = 2500
// 방의 갯수: dfs O(R^2) 1250만
// 방의 넓이: dfs 1과 같이
// 벽 제거: O(R^3) 1250만 * 2500 -> 시간초과
// 모든 벽을 제거해볼 필요 없이 방A와 방B의 면적을 합쳤을때의 최댓값을 찾으면됨. (단 A와B는 인접)
// -> 결국 인접한 방들의 목록을 찾으라는 문제
// 일단 모든 타일들에 대해 속하는 방을 번호로 저장 (dfs로 가능) R^2
// 그 후 모든 타일에 대해 iterate하면서 해당 타일에 있는 벽을 다시 iterate(max 4), 인접한 두 방의 정보를 bool isAdj에 저장 R^2 * 4
// 이후 isAdj를 돌면서 나올 수 있는 모든 경우의 수에 대해 두 방의 크기를 더해줌 R^2
// ===> O(R^2)에 풀이 가능!

inline bool hasWallAtDir(int y, int x, int cDir)
{
    return cDir & walls[y][x];
}

void dfs(int sy, int sx, int roomNum, int& roomSize)
{
    tiles[sy][sx] = roomNum;
    visited[sy][sx] = true;
    for (int d=0;d<4;d++)
    {
        if (!hasWallAtDir(sy,sx,doorDir[d]))
        {
            int nx = sx + moveDir[d][0];
            int ny = sy + moveDir[d][1];
            // 범위초과 및 방문 확인
            if (visited[ny][nx] || nx < 1 || nx > N || ny < 1 || ny > M) continue; 
            roomSize += 1;
            dfs(ny, nx, roomNum, roomSize);
        }
    }
    return;
}



int main()
{
    // 입력
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
    // 주의: 맵 밖을 -1번 방으로 지정, -1번방은 무시.
    memset(tiles, -1, sizeof(tiles));
    memset(walls, -1, sizeof(walls)); // wall = -1은 맵 밖을 의미
    memset(visited, false, sizeof(visited));
    
    cin >> N >> M;
    for (int i=1;i<=M;i++)
    {
        for (int j=1;j<=N;j++)
        {
            cin >> walls[i][j];
        }
    }
    
    // 1,2번
    int cnt = 0;
    int maxSize = -1;
    for (int i=1;i<=M;i++)
    {
        for (int j=1;j<=N;j++)
        {
            int roomSize = 1;
            if (!visited[i][j])
            {
                dfs(i, j, cnt, roomSize);
                roomSizes[cnt] = roomSize;
                cnt++;
                if (roomSize > maxSize) maxSize = roomSize;
            }
        }
    }
    
    // debug
    for (int i=1;i<=M;i++)
    {
        for (int j=1;j<=N;j++)
        {
            cout << tiles[i][j];
        }
        cout << endl;
    }
    
    // 3번
    // for (int i=1;i<=M;i++)
    // {
    //     for (int j=1;j<=N;j++)
    //     {
    //         for (int d=0;d<4;d++)
    //         {
    //             if (hasWallAtDir(i,j,doorDir[d]))
    //             {
    //                 int nx = j + moveDir[d][0];
    //                 int ny = i + moveDir[d][1];
    //                 adjRoom[tiles[ny][nx]].insert(tiles[i][j]);
    //                 adjRoom[tiles[i][j]].insert(tiles[ny][nx]);
    //             }
    //         }
    //     }
    // }
    // int ret3 = -1;
    // for (int r1=0;r1<2500;r1++)
    // {
    //     for (int r2 : adjRoom[r1])
    //     {
    //         ret3 = max(ret3, roomSizes[r1] + roomSizes[r2]);
    //     }
    // }
    
    // cout << cnt << maxSize << ret3 << '\n';
    
    return 0;
}
