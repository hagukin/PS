#include <iostream>
#include <algorithm>
using namespace std;

int N, W;
int dp[1001][1001];
int visited[1001][1001];
int cases[1001][2]; // 사건들의 x,y좌표

int getDist(int initXY, int a, int b) 
// initXY는 a가 움직이는지 b가 움직이는지에 따라 달라지는데, 만약 0번 지점(출발지)에서 출발할 경우 initXY값을 거리계산에 사용한다
// initXY는 1또는 N이다, 또 x==y이므로 값 하나만 전달해도 된다
{
    return abs((a ? cases[a][0] : initXY) - cases[b][0]) + abs((a ? cases[a][1] : initXY) - cases[b][1]);
}

int r(int x, int y) 
{
    int goal = max(x, y) + 1;
    if (goal > W) return 0; // W개의 인풋만 주어지므로
    if (visited[x][y]) return dp[x][y];
    visited[x][y] = 1;
    return dp[x][y] = min(r(goal, y) + getDist(1, x, goal), r(x, goal) + getDist(N, y, goal)); // 1번이 움직이는 경우, 2번이 움직이는 경우 분리
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> W;
    for (int i=1;i<=W;i++)
    {
        cin >> cases[i][0] >> cases[i][1];
    }
    
    cout << r(0, 0) << '\n';
    
    for (int i=0,j=0,k=1;k<=W;k++) 
    {
        if (dp[k][j] == dp[i][j] - getDist(1, i, k)) 
        {
            cout << 1 << '\n';
            i = k;
        }
        else 
        {
            cout << 2 << '\n';
            j = k;
        }
    }
    return 0;
}
