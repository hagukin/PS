#include <iostream>
#include <string>
#include <climits>
using namespace std;

string grid[10];
int dxdys[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int rStart[2], bStart[2], hole[2]; // x, y순
int N, M, ret=INT_MAX;
bool rGoal = false, bGoal = false;

bool checkClear(const int& rx, const int& ry, const int& bx, const int& by)
{

}

void moveMarble(int dx, int dy, int& cx, int& cy, int omx, int omy, bool isRed)
{
    // dx,dy: 이동방향
    // cx,cy: 현재위치 (레퍼런스)
    // omx,omy: 다른 구슬의 위치
    // 이동 전일 수도 있고 이동 후일 수도 있음. 
    // 애초에 이동순서를 잘 고려하므로 이 값이 이동 후의 좌표값일 경우만 충돌 가능성 있음.
    
    int nx=cx, ny=cy;
    while(nx+dx < M && nx+dx >= 0 && ny+dy < N && ny+dy >= 0 && nx+dx != omx && ny+dy != omy && grid[ny+dy][nx+dx] != '.')
    {
        nx += dx;
        ny += dy;
        if (nx == hole[0] && ny == hole[1])
        {
            if (isRed) rGoal = true;
            else bGoal = true;
            // TODO
            //
            // 
            //
            break;
        } //도착
    }
    cx = nx;
    cy = ny;
    return;
}

void move(int dx, int dy, int& rx, int& ry, int& bx, int& by)
{
    // dxdy
    if (dx==0)
    {
        if (dy==1)
        {
            // 0 1
            // 위쪽 먼저
            if (ry < by)
            {
                moveMarble(dx, dy, rx, ry, bx, by);
                moveMarble(dx, dy, bx, by, rx, ry);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry);
                moveMarble(dx, dy, rx, ry, bx, by);
            }
        }
        else
        {
            // 0 -1
            // 아랫쪽 먼저
            if (ry > by)
            {
                moveMarble(dx, dy, rx, ry, bx, by);
                moveMarble(dx, dy, bx, by, rx, ry);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry);
                moveMarble(dx, dy, rx, ry, bx, by);
            }
        }
    }
    else
    {
        if (dx==1)
        {
            // 1 0
            // 우측 먼저
            if (rx > bx)
            {
                moveMarble(dx, dy, rx, ry, bx, by);
                moveMarble(dx, dy, bx, by, rx, ry);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry);
                moveMarble(dx, dy, rx, ry, bx, by);
            }
        }
        else
        {
            // -1 0
            // 좌측 먼저
            if (rx < bx)
            {
                moveMarble(dx, dy, rx, ry, bx, by);
                moveMarble(dx, dy, bx, by, rx, ry);
            }
            else
            {
                moveMarble(dx, dy, bx, by, rx, ry);
                moveMarble(dx, dy, rx, ry, bx, by);
            }
        }
    }
    return;
}

void solve(int moveCnt, int rx, int ry, int bx, int by)
{
    if (moveCnt > 10) return;
    if (checkClear(rx, ry, bx, by))
    {
        ret = min(ret, moveCnt);
        return;
    }
    
    for (int* dxdy : dxdys)
    {
        int crx=rx, cry=ry, cbx=bx, cby=by;
        move(dxdy[0], dxdy[1], crx, cry, cbx, cby);
        solve(moveCnt+1, crx, cry, cbx, cby);
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
    solve(0, rStart[0], rStart[1], bStart[0], bStart[1]);
    if (ret == INT_MAX) ret = -1;
    cout << ret << '\n';
    return 0;
}
