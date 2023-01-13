#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
using namespace std;
constexpr int INF = 987654321;

struct Info
{
    int val, y, x, move;
};

struct cmp
{
    bool operator<(const Info& i1, const Info& i2)
    {
        return i1.val < i2.val;
    }
}


typedef priority_queue<Info, vector<Info>, cmp> PQ;

int N, M;
int sx, sy, ex, ey;
int origin[101][101];
int dist[101][101][3]; // 3k+n번째 이동으로 격자 (i,j)에 들어간 경우의 최소 충격량
// 해당 칸에 도착해서 받는 충격량까지 포함한다
bool visited[101][101][3];

bool checkMove(int ty, int tx)
{
    // if 하나로 코드 정리가능
    if (ty < 0 || ty >= N || tx < 0 || tx >= M) return false;
    if (visited[ty][tx]) return false;
    if (origin[ty][tx] == -1) return false;
    return true;
}

void setDist(int y, int x, int move, int val, PQ& pq)
{
    // y,x는 checkMove 통과했다고 간주
    dist[y][x][move] = min(dist[y][x][move], val);
    Info tmp = {dist[y][x][move], y, x, move};
    pq.push(tmp);
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // init
    for (int i=0;i<101;++i)
        for (int j=0;j<101;++j)
            for (int k=0;k<3;++k)
                dist[i][j][k] = INF;
    memset(visited, false, sizeof(visited));
    memset(origin, 0, sizeof(origin));
    
    cin >> N >> M;
    cin >> sx >> sy >> ex >> ey;
    for (int i=0;i<N;++i)
    {
       for (int j=0;j<M;++j)
       {
           cin >> origin[i][j];
       }
    }
    
    // 풀이: 다익스트라
    // 추상화해서 생각하면 단순함, 그냥 3k, 3k+1, 3k+2번 이동에 해당하는 각 격자들의 각 칸들이 하나의 노드라고 생각하면
    // 주어진 이동규칙 하에 이동하는 것을 그냥 노드의 간선을 따라 이동하는 것으로 볼 수 있음
    // 그럼 결국 그냥 다익스트라임
    int cy, cx, cmove;
    
    PQ pq;
    Info start = {0, {sy, sx, 1}};
    pq.push(start);
    while (!pq.empty())
    {
        cy = pq.top().y;
        cx = pq.top().x;
        cmove = pq.top().move;
        pq.pop();
        
        if (cy == ey && cx == ex)
        {
            
        }
        
        if (cmove == 1 || cmove == 0)
        {
            if (checkMove(cy+1,cx))
            {
                setDist(cy+1, cx, cmove+1, dist[cy][cx][cmove] + origin[cy][cx], pq);
            }
            if (checkMove(cy-1,cx))
            {
                setDist(cy-1, cx, cmove+1, dist[cy][cx][cmove] + origin[cy][cx], pq);
            }
        }
        if (cmove == 2 || cmove == 0)
        {
            if (checkMove(cy,cx+1))
            {
                setDist(cy, cx+1, cmove+1, dist[cy][cx][cmove] + origin[cy][cx], pq);
            }
            if (checkMove(cy,cx-1))
            {
                setDist(cy, cx-1, cmove+1, dist[cy][cx][cmove] + origin[cy][cx], pq);
            }
        }
        visited[cy][cx][cmove] = true;
        cmove = (cmove+1)%3;
    }
    
    int ey = 1; int ex = 0;
    cout << min(dist[ey][ex][0], min(dist[ey][ex][1], dist[ey][ex][2])) << '\n';
    return 0;
}
