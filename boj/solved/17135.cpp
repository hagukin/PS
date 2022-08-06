#include <iostream>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <utility>
#include <vector>

using namespace std;

int N, M, D;
int enemyCnt;
bool grid[15][15];
bool archer[15];
int ret = 0;

int dist(int r1, int c1, int r2, int c2)
{
    return abs(r1-r2) + abs(c1-c2);
}

int playerTurn(bool currGrid[][15])
{
    int funcRet = 0; // 반환: 해당 턴에 죽인 적의 수
    vector<pair<int,int >> targets;
    for (int arcX=0;arcX<M;arcX++)
    {
        if (!archer[arcX]) continue;
        
        int minDist = INT_MAX;
        pair<int,int> targetPos(-1,-1); // row(y), column(x)
        
        /* 
        이부분을 BFS로 변경해야함. (시간초과)
        */
        //-------------------------
        for (int i=0;i<N;i++)
        {
            for (int j=0;j<M;j++)
            {
                if (currGrid[i][j])
                {
                    int cDist = dist(i, j, N, arcX); // N: 성벽 위치 (가상의 인덱스)
                    if (cDist <= minDist && cDist <= D) // cDist "<" minDist이어야 거리가 같으면 왼쪽을 우선공격하는거 아닌가? <=로 해야 풀림.
                    {
                        minDist = cDist;
                        targetPos = make_pair(i, j);
                    }
                }
            }
        }
        //-------------------------
        
        // 타겟이 아예 없을 경우 방지
        if (targetPos.first != -1 && targetPos.second != -1)
            targets.push_back(targetPos);
    }
    // 공격 실행
    for (auto target : targets)
    {
        if (currGrid[target.first][target.second]) 
        {
            funcRet += 1; // 타겟이 있을때만 킬카운트 업 (중복방지)
        }
        currGrid[target.first][target.second] = false;
    }
    return funcRet;
}

int enemyTurn(bool currGrid[][15])
{
    // 반환: 해당 턴에 맵 밖으로 나간 적의 수
    // memcpy로 일부분만 복사해서 최적화 가능해보임
    int funcRet = 0;
    bool newGrid[15][15];
    memset(newGrid, 0, sizeof(newGrid));
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            if (currGrid[i][j])
            {
                if (i+1>=N) { funcRet++; continue; } // 맵나감
                newGrid[i+1][j] = true;
            }
        }
    }
    memcpy(currGrid, newGrid, sizeof(newGrid));
    return funcRet;
}

void startGame()
{
    bool currGrid[15][15];
    memcpy(currGrid, grid, sizeof(grid));
    
    int kill = 0; int gone = 0;
    while (gone < enemyCnt)
    {
        int tmp = playerTurn(currGrid);
        kill += tmp; gone += tmp;
        gone += enemyTurn(currGrid);
    }
    ret = max(ret, kill);
    return;
}

void solve(int placedArcher, int lastArc)
{
    // 모든 궁수의 포지션 경우의 수
    if (placedArcher == 3) { startGame(); return;}
    if (lastArc >= M) return;
    for (int i=lastArc+1;i<M;i++)
    {
        archer[i] = true;
        solve(placedArcher+1, i);
        archer[i] = false;
        solve(placedArcher, i);
    }
}

int main() 
{
    memset(grid, false, sizeof(grid));
    memset(archer, false, sizeof(archer));
    cin >> N >> M >> D;
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            cin >> grid[i][j];
            if (grid[i][j]) enemyCnt +=1;
        }
    }
    solve(0, -1);
    cout << ret << '\n';
    return 0;
}
