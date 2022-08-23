#include <iostream>
#include <cstring>
using namespace std;

struct Shark
{
    int y, x, speed, direction, size;
    bool isAlive; // 낚이거나 포식당하면 false
    // false일 경우 모든 인터랙션에서 무시된다.
};

int ret = 0;
int R, C, M;
Shark sharks[10001];
int grid[101][101]; // 상어의 인덱스가 저장된다, -1일 경우 공백
int dydx[5][2] = {{0,0},{-1,0},{1,0},{0,1},{0,-1}}; // dy,dx순, 0번 인덱스는 무시
int fisherman = 0; // 낚시꾼의 x축 위치

void placeShark(int idx, int y, int x, int cGrid[][101])
{
    // 상어를 주어진 위치에 고정시킨다.
    // 이동이 완료되어 멈춰있는 상어만 고정된 것으로 간주한다.
    cGrid[y][x] = idx;
    return;
}

void emptyTile(int y, int x, int cGrid[][101])
{
    // 타일을 비운다.
    cGrid[y][x] = -1;
    return;
}

void removeShark(int idx)
{
    // 상어를 제거한다.
    Shark& s = sharks[idx];
    s.isAlive = false;
    return;
}

void applyCollisionAndPlace(int idx)
{
    // 다른 상어와 충돌했는지 감지하고,
    // 충돌했을 경우 둘 중 더 작은 상어를 제거한다.
    // 더 큰 상어를 격자에 배치한다.
    Shark& cs = sharks[idx];
    int tmp = grid[cs.y][cs.x];
    if (tmp != -1)
    {
        Shark& ns = sharks[tmp];
        if (ns.size > cs.size)
        {
            emptyTile(cs.y, cs.x, grid);
            removeShark(idx);
            placeShark(tmp, ns.y, ns.x, grid);
        }
        else
        {
            emptyTile(ns.y, ns.x, grid);
            removeShark(tmp);
            placeShark(idx, cs.y, cs.x, grid);
        }
    }
    else placeShark(idx, cs.y, cs.x, grid);
}

int reverseDir(int origin)
{
    // 입력방향과 반대방향을 반환한다.
    switch(origin)
    {
        case 1:
            return 2;
        case 2:
            return 1;
        case 3:
            return 4;
        case 4:
            return 3;
    }
    return 0; // invalid
}

void moveSharkOneTile(int idx)
{
    // 상어를 1칸만큼 이동시킨다.
    // 만약 바로 앞이 벽이라 이동하지 못한다면 1칸만큼 반대방향으로 이동한다.
    Shark& s = sharks[idx];
    int dy = dydx[s.direction][0];
    int dx = dydx[s.direction][1];
    if (s.x + dx > C || s.x + dx <= 0 || s.y + dy > R || s.y + dy <= 0)
    {
        s.direction = reverseDir(s.direction);
        return moveSharkOneTile(idx);
    }
    s.x += dx;
    s.y += dy;
    return;
}

void moveShark(int idx)
{
    // 상어를 1턴간 끝까지 이동시킨다.
    // 끝까지 이동 후 포식당하거나 포식하는게 가능한지 확인 후 처리한다.
    Shark& s = sharks[idx];
    emptyTile(s.y, s.x, grid);
    int moveCnt = 0;
    while (moveCnt < s.speed)
    {
        moveSharkOneTile(idx);
        moveCnt++;
    }
    applyCollisionAndPlace(idx);
    return;
}

void catchShark(int idx)
{
    // 주어진 인덱스의 상어를 낚는다.
    Shark& s = sharks[idx];
    ret += s.size;
    removeShark(idx);
    emptyTile(s.y, s.x, grid);
    return;
}

int findShark(int column)
{
    // 현재 열의 가장 위의 상어를 찾아 인덱스를 반환한다.
    for (int j=1;j<=R;++j)
    {
        int tmp = grid[j][column];
        if (tmp != -1 && sharks[tmp].isAlive)
        {
            return tmp;
        }
    }
    return -1;
}

void moveFisherman()
{
    fisherman+=1;
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(grid, -1, sizeof(grid));
    cin >> R >> C >> M;
    int r,c,s,d,z;
    for (int i=0;i<M;++i)
    {
        cin >> r >> c >> s >> d >> z;
        Shark ns = {r,c,s,d,z,true};
        sharks[i] = ns;
        placeShark(i, r, c, grid);
    }
    
    // simulate
    for (int i=1;i<=C;++i)
    {
        moveFisherman();
        int catchThis = findShark(fisherman);
        if (catchThis != -1) catchShark(catchThis);
        memset(grid, -1, sizeof(grid));
        for (int j=0;j<M;++j)
        {
            if (sharks[j].isAlive)
            {
                moveShark(j);
            }
        }
    }
    cout << ret << '\n';
    return 0;
}
