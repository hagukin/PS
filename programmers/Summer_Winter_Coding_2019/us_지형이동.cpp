#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <iostream>

using namespace std;

/*
BFS로 일단 각 영역들을 분리
300*300*300

문제의 핵심은 어디에 사다리를 설치할 것인가인데,
우리는 두 칸의 맞닿은 지점(모서리)들을 살펴보며 어떤 두 그룹을 잇기 위한 사다리 비용의 최솟값들을 tracking할 수 있음
다 살펴보는데 비용: N(N+1)*2

즉 우리는 각 그룹들을 하나의 노드로 만들고 그 노드들을 모두 지나는 경로를 찾아야 함. (자기 노드로 돌아올 필요는 X)
이게 핵심 알고리즘인데,
진짜 단순히 생각하면 다익스트라를 N번 돌리면 되는데, 느낌상 시간초과임. 왜냐?
height가 1일 경우 그룹이 개많이 생기게 되는데, 이런 워스트케이스의 경우 노드가 900개, 간선이 20만여개 생김.
TC가 1.8억이라 시간초과

크루스칼 알고리즘: Minimum Spanning Tree를 사용하면 풀린다!
이거 Union-find로 구현하면된다
TC는 그리디라 걱정없겠다

---
검증) 테케1:
빨 파 노 순 0 1 2

0 - 1 : 10
0 - 2 : INF
1 - 2 : 5

테케2:
0 - 1 : 10
0 - 2 : 8
1 - 2 : 19

검증완료
*/

constexpr int MAXNODE = 90001;
typedef pair<int, pair<int,int>> PP;

int N; // N*N 격자가 주어진다
int answer = 0;
bool visited[301][301] = {false, }; // TODO: groups 하나로 방문여부 관리가능
int groups[301][301]; // -1로 초기화
map<int,int> minLadder[MAXNODE]; // minLadder[i][j] = i to j로 가는 경로의 최솟값. 만약 키 없으면 이어지지 않은 것.

struct cmp
{
    bool operator()(PP a, PP b)
    {
        return a.first > b.first;
    }
};
priority_queue<PP, vector<PP>, cmp> pq;

int uf[MAXNODE]; // union-find
int maxGroupId = 0;

void init()
{
    for (int i=0;i<MAXNODE;++i) uf[i] = i;
    for (int i=0;i<301;++i)
        for (int j=0;j<301;++j)
            groups[i][j] = -1;
}

// 일단 각 그룹에 0~N*N까지 각 칸별로 서로 다른 값들이 들어있어야함
void bfs(const vector<vector<int>>& land, int height)
{
    int dydx[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    // 0,0에서 시작
    queue<pair<int,int>> q;
    int groupId = -1; // 0부터 시작
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            if (visited[i][j]) continue;
            groupId++;
            q.emplace(i,j);
            groups[i][j] = groupId;
            visited[i][j] = true;
            
            while (!q.empty())
            {
                int ty = q.front().first;
                int tx = q.front().second;
                q.pop();
                
                // 상하좌우
                for (int d=0;d<4;++d)
                {
                    int cy = ty + dydx[d][0];
                    int cx = tx + dydx[d][1];              
                    if (!visited[cy][cx] && cy >= 0 && cx >= 0 && cy < N && cx < N && abs(land[ty][tx]-land[cy][cx]) <= height) // 큐에 같은 좌표 두번 넣는것 방지
                    {
                        q.emplace(cy,cx);
                        groups[cy][cx] = groupId;
                        visited[cy][cx] = true;
                    }
                }
            }
        }
    }
    maxGroupId = groupId;
}

inline void updateMinLadder(int& a, int& b, int val)
{
    // group a와 b의 min ladder 값을 업데이트한다
    if (minLadder[a].find(b) == minLadder[a].end()) minLadder[a][b] = val;
    else minLadder[a][b] = min(minLadder[a][b], val);
    
    if (minLadder[b].find(a) == minLadder[b].end()) minLadder[b][a] = val;
    else minLadder[b][a] = min(minLadder[b][a], val);
}

void getMinLadder(const vector<vector<int>>& land)
{
    for (int i=0;i<N;++i)
    {
        for (int j=0;j<N;++j)
        {
            // 아랫변과 우측변만 확인하면 된다!
            if (i+1<N && groups[i+1][j] != groups[i][j]) updateMinLadder(groups[i+1][j], groups[i][j], abs(land[i+1][j] - land[i][j]));
            if (j+1<N && groups[i][j+1] != groups[i][j]) updateMinLadder(groups[i][j+1], groups[i][j], abs(land[i][j+1] - land[i][j]));
        }
    }
    return;
}

void initPQ()
{
    // pq: {distance, {node A, node B}} 순 저장, A idx < B idx 항상 만족
    for (int i=0;i<=maxGroupId;++i)
    {
        for (int j=i+1;j<=maxGroupId;++j)
        {
            if (minLadder[i].find(j) != minLadder[i].end())
            {
                pq.push({minLadder[i][j], {i,j}});
            }
        }
    }
}

void ufUnion()
{
    
}

void ufFind()
{
    
}

void findMST()
{
    int n = maxGroupId;
    
}

int solution(vector<vector<int>> land, int height) {
    N = land.size();
    init();
    // bfs로 group id가 저장된 N*N 그리드 생성
    bfs(land, height);
    // 생성된 그리드 정보를 통해 그룹 A -> B로 가기 위한 최솟값을 저장
    getMinLadder(land);
    // 크루스칼을 위한 데이터 변형: 노드(그룹) 간선을 오름차순으로 정렬
    initPQ();
    // 크루스칼 알고리즘을 통해 MST 찾기
    findMST();
    return answer;
}
