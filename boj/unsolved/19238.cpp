#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
constexpr int GOAL = 987654321;
typedef pair<pair<int,int>, int> p3;

int N, M;
int grid[23][23]; // 승객의 인덱스. 벽은 -1, 빈칸은 0
bool visited[23][23];
pair<int,int> goals[401]; // i번 승객의 도착지 정보. (y,x)순
int fuel; // 남은 연료
int passCnt = 0; // 승객 수
int tsy, tsx; // 택시 시작 y,x
int dydxs[4][2] = {{-1,0}, {0,-1}, {0,1}, {1,0}};
int cPass, py, px; // 현재 탄/태우러 가는 승객 정보들

/*
모든 칸에 승객이 있을 수 있다
한 칸에 두 명 이상의 승객이 있을 수 없다
그러나 두 승객의 목적지가 같을 순 있다 -> 고로 목적지는 격자로 저장하면 안된다 -> 목적지는 승객 - 목적지 로 맵핑해야함
승객이 도착지에서 시작할 순 없다
도착하면서 연료가 0이 되는 건 실패가 아니다

의사코드:
시작 위치에서 벽 및 맵 경계를 피해 상하좌우 BFS를 돌며 가장 가까운 승객을 찾는다 (경로 몰라도됨)
이때 depth가 같은 경우 반드시 행,열이 작은 순으로 방문하도록 해야한다!
이동하며 연료 체크, 부족 시 게임오버
찾았다면 그 승객의 도착지점 정보를 가져오고, 다시 한번 BFS로 도착지점까지의 거리를 구한다 (경로 몰라도됨)
이동하며 연료 체크, 부족 시 게임오버, 도착 이후 이동거리의 합 * 2 만큼 연료증가
승객 정보를 grid에서 지워주고(빈칸으로 만들기) 위 과정 반복

시간복잡도:
BFS 1회당 O(N^2)
승객 1명당 BFS 2회 (승객찾기 + 도착지찾기)
400 * 400 * 2 (*memset) = 320000, 1초내 가능!

구현과정:
인풋 구현 o
게임 루프 구현 o
BFS 구현 o
연료 소비 및 충전 로직 구현 o
게임 오버 구현 o
*/

bool isPassenger(int my, int mx)
{
    return (grid[my][mx] > 0);
}

bool isGoal(int my, int mx)
{
    return (grid[my][mx] == GOAL);
}

int getDist(int sy, int sx, bool (*f)(int,int)) // 거리 반환
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
        
        cout << cy << cx << cDist << "SSS" << endl;
        
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

void test()
{
    for (int i=0;i<=22;i++)
    {
        for (int j=0;j<=22;j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    return;
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
        ++passCnt;
        cin >> goals[i].first >> goals[i].second; // 도착지 저장
    }
    
    // 메인 루프
    // 태우러 가야하는 또는 태우고 있는 승객
    int cy = tsy, cx = tsx; // 첫 승객 태우러 갈때 시작은 택시 초기위치에서 
    int toPass = 0; // 택시~승객 거리
    int toGoal = 0; // 승객~도착지 거리
    
    
    
    
    
    
    toPass = getDist(cy, cx, isPassenger); //test
    cout << cPass << py << px << toPass << endl;
    grid[py][px] = 0;
    cy = goals[cPass].first; 
    cx = goals[cPass].second;
    test();
    memset(visited, false, sizeof(visited));
    toPass = getDist(cy, cx, isPassenger); //test
    cout << cPass << py << px << toPass << endl;
    
    
    
    while(passCnt)
    {
        // 승객이 1명 이상 있다는 전제 하에 진행
    
        // 1. 승객 찾아가기
        // 거리, 승객인덱스, 승객 좌표 구하기
        toPass = getDist(cy, cx, isPassenger);
        memset(visited, false, sizeof(visited));
        fuel -= toPass;
        cy = py; cx = px; // 승객 좌표로 이동
        
        // 2. 승객 태우고 목적지까지 가기
        // 골인 지점 설정
        int& goal = grid[goals[cPass].first][goals[cPass].second];
        goal = GOAL;
        
        // 최단 경로 찾기
        toGoal = getDist(cy, cx, isGoal);
        memset(visited, false, sizeof(visited));
        fuel -= toGoal;
        cy = goals[cPass].first; cx = goals[cPass].second; // 목적지 좌표로 이동
        
        // 연료 0이어도 괜찮다
        if (fuel < 0) break;
        fuel += toGoal * 2;
        
        // 승객 및 골인지점 삭제
        passCnt--;
        grid[py][px] = 0;
        goal = 0;
    }
    if (fuel < 0) {cout << -1 << '\n';}
    else {cout << fuel << '\n';}

    return 0;
}
