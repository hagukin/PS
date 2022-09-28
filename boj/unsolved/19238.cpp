#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
constexpr int GOAL = 987654321;
typedef pair<pair<int,int>, int> p3;

int N, M;
int grid[22][22]; // 승객의 인덱스. 벽은 -1, 빈칸은 0
bool visited[22][22];
pair<int,int> goals[404]; // i번 승객의 도착지 정보. (y,x)순
int fuel; // 남은 연료
int passCnt = 0; // 승객 수
int tsy, tsx; // 택시 시작 y,x
int dydxs[4][2] = {{-1,0}, {0,-1}, {0,1}, {1,0}};
int cPass, py, px; // 현재 탄/태우러 가는 승객 정보들

bool isPassenger(int my, int mx)
{
    return (grid[my][mx] > 0);
}

bool isGoal(int my, int mx)
{
    return (grid[my][mx] == GOAL);
}

int getDist(int sy, int sx, bool (*f)(int,int))
{
    queue<p3> q;
    p3 s;
    pair<int,int> start;
    start = make_pair(sy,sx);
    s = make_pair(start, 0);
    q.push(s);
    
    while(!q.empty())
    {
        p3 c = q.front();
        q.pop();
        
        int cy = c.first.first; 
        int cx = c.first.second;
        int cDist = c.second;
        visited[cy][cx] = true;
        
        if (f(cy, cx)) 
        {
            cPass = grid[cy][cx];
            py = cy; px = cx;
            return cDist;
        }
        
        for (int* dydx : dydxs)
        {
            int ny = cy + dydx[0];
            int nx = cx + dydx[1];
            if (grid[ny][nx] == -1 || visited[ny][nx]) continue; // 맵 범위 확인은 필요가 없음 (어차피 테두리가 다 벽이라)
            
            p3 n;
            pair<int,int> next;
            next = make_pair(ny,nx);
            n = make_pair(next, cDist+1);
            q.push(n);
        }
    }
    return -1;
}

int main()
{
    // 인풋
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(grid, -1, sizeof(grid)); // 테두리 벽
    cin >> N >> M >> fuel;
    int tmp;
    for (int i=1;i<=N;i++)
    {
        for (int j=1;j<=N;j++)
        {
            cin >> tmp;
            if (!tmp) grid[i][j] = 0; // 빈칸 생성
        }
    }
    cin >> tsy >> tsx;
    int sy, sx;
    for (int i=1;i<=M;i++)
    {
        cin >> sy >> sx;
        grid[sy][sx] = i; // 승객 번호 저장
        cin >> goals[i].first >> goals[i].second; // 도착지 저장
    }
    passCnt = M;
    
    int cy = tsy, cx = tsx;
    int toPass = 0; // 택시~승객
    int toGoal = 0; // 승객~도착지
    
    int cnt;
    for (cnt=0;cnt<M;cnt++)
    {
        // 승객이 1명 이상 있다는 전제 하에 진행
        
        // 승객 찾아가기
        toPass = getDist(cy, cx, isPassenger);
        if (toPass == -1) break; // 서치 불가
        memset(visited, false, sizeof(visited));
        fuel -= toPass;
        cy = py; cx = px; // 승객 좌표로 이동
        grid[py][px] = 0;
        
        // 승객 태우고 목적지까지 가기
        int& goal = grid[goals[cPass].first][goals[cPass].second];
        int prev = goal;
        goal = GOAL;
        toGoal = getDist(cy, cx, isGoal);
        if (toGoal == -1) break; // 서치 불가
        memset(visited, false, sizeof(visited));
        fuel -= toGoal;
        cy = py; cx = px; // 도착지 좌표 getDist()에서 pypx에 저장됨
        goal = prev;
        
        if (fuel < 0) break;
        fuel += toGoal * 2;
    }
    if (cnt!=M) {cout << -1 << '\n';}
    else {cout << fuel << '\n';}
    return 0;
}
