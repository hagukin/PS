#include <iostream>
#include <string>
#include <climits>
using namespace std;

string grid[10];
int dxdys[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int rStart[2], bStart[2], hole[2]; // x, y순
int N, M, ret=INT_MAX;

bool checkClear(const bool& crGoal, const bool& cbGoal)
{
    if (crGoal && !cbGoal) return true;
    return false;
}

bool checkOtherMarbleCollision(int dx, int dy, int nx, int ny, const int& omx, const int& omy, const bool& isRed, const bool& crGoal, const bool& cbGoal) // true: 충돌함
{
    if ((isRed && cbGoal) || (!isRed && crGoal))
    {
        return false; // 다른 구슬이 이미 구멍에 들어갔으면 충돌할 수가 없음.
    }
    else
    {
        return (nx+dx==omx && ny+dy==omy);
    }
}

void moveMarble(int dx, int dy, int& cx, int& cy, int omx, int omy, bool isRed, bool& crGoal, bool& cbGoal)
{
    // dx,dy: 이동방향
    // cx,cy: 현재위치 (레퍼런스)
    // omx,omy: 다른 구슬의 위치
    // 이동 전일 수도 있고 이동 후일 수도 있음. 
    // 애초에 이동순서를 잘 고려하므로 이 값이 이동 후의 좌표값일 경우만 충돌 가능성 있음.
    int nx=cx, ny=cy;
    while(nx+dx < M && nx+dx >= 0 && ny+dy < N && ny+dy >= 0 && !checkOtherMarbleCollision(dx, dy, nx, ny, omx, omy, isRed, crGoal, cbGoal) && grid[ny+dy][nx+dx] == '.')
    {
        nx += dx;
        ny += dy;
        if (nx == hole[0] && ny == hole[1])
        {
            if (isRed) crGoal = true;
            else cbGoal = true;
            break;
        } //도착
    }
    cx = nx;
    cy = ny;
    return;
}

void move(int dx, int dy, int& rx, int& ry, int& bx, int& by, bool& crGoal, bool& cbGoal)
{
    // dxdy
    if (dx==0)
    {
        if (dy==1)
        {
            // 0 1
            // 아랫쪽 먼저
            if (ry >= by)
            {
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
            }
        }
        else
        {
            // 0 -1
            // 윗쪽 먼저
            if (ry <= by)
            {
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
            }
        }
    }
    else
    {
        if (dx==1)
        {
            // 1 0
            // 우측 먼저
            if (rx >= bx)
            {
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
            }
        }
        else
        {
            // -1 0
            // 좌측 먼저
            if (rx <= bx)
            {
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry, false, crGoal, cbGoal);
                moveMarble(dx, dy, rx, ry, bx, by, true, crGoal, cbGoal);
            }
        }
    }
    return;
}

void solve(int moveCnt, int rx, int ry, int bx, int by, bool rGoal, bool bGoal)
{
    if (moveCnt > 10) return;
    for (int* dxdy : dxdys)
    {
        int crx=rx, cry=ry, cbx=bx, cby=by;
        bool crGoal=rGoal, cbGoal=bGoal;
        move(dxdy[0], dxdy[1], crx, cry, cbx, cby, crGoal, cbGoal);
        if (checkClear(crGoal, cbGoal))
        {
            ret = min(ret, moveCnt);
            return; // 한 방향에서 답이 나왔으면 다른 방향에서는 나올 수가 없음
        }
        solve(moveCnt+1, crx, cry, cbx, cby, crGoal, cbGoal);
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    for (int i=0;i<N;i++)
    {
        cin >> grid[i];
        for (int j=0;j<grid[i].size();j++)
        {
            switch(grid[i][j])
            {
                case 'R':
                    {rStart[0] = j; rStart[1] = i; grid[i][j] = '.'; break;}
                case 'B':
                    {bStart[0] = j; bStart[1] = i; grid[i][j] = '.'; break;}
                case 'O':
                    {hole[0] = j; hole[1] = i; grid[i][j] = '.'; break;}
                default:
                    break;
            }
        }
    }
    solve(1, rStart[0], rStart[1], bStart[0], bStart[1], false, false);
    if (ret == INT_MAX) ret = -1;
    cout << ret << '\n';
    return 0;
}
