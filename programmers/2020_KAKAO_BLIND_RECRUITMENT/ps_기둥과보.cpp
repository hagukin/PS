#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool wall[105][105][2] = {false,}; // 시계 12, 3, 6, 9 순
// [y][x][0] = 해당 교차점에서 위로 솟는 기둥의 존재유무
// [y][x][1] = 해당 교차점에서 우로 가는 보의 존재유무

inline void build(int x, int y, int t)
{
    wall[y][x][t] = true;
}

inline void remove(int x, int y, int t)
{
    wall[y][x][t] = false;
}

bool canBuild(int x, int y, int t)
{
    // 설치의 경우: 설치 조건을 만족하는지 설치 타일에 대해 확인
    if (t==0) // 기둥
    {
        if (y == 0 || (y-1>=0 && wall[y-1][x][0]) || wall[y][x][1] || (x-1>=0 && wall[y][x-1][1])) return true;
    }
    else if (t==1) // 보
    {
        if (wall[y-1][x][0] || wall[y-1][x+1][0] || ((x-1>=0 && wall[y][x-1][1]) && wall[y][x+1][1])) return true;
    }
    return false;
}

bool canExist(int x, int y, int t)
{
    if (wall[y][x][t]) return canBuild(x, y, t);
    return true; // 애초에 해당 위치에 아무 것도 없을 경우 true 반환
}

bool canRemove(int x, int y, int t)
{
    // 삭제의 경우: 삭제한 상태에서 주변 기물들을 재설치 가능한지 확인
    remove(x, y, t);
    bool ans = false;
    if (t == 0) // 기둥
    {
        if (canExist(x,y+1,1) && canExist(x-1,y+1,1) && canExist(x,y+1,0)) ans = true;
    }
    else if (t == 1) // 보
    {
        if (canExist(x-1,y,1) && canExist(x+1,y,1) && !canExist(x,y,0) && canExist(x+1,y,0)) ans = true;
    }
    build(x, y, t); // 복구
    return ans;
}

void apply(vector<int>& b)
{
    if (b[3] == 1)
    {
        if (!canBuild(b[0], b[1], b[2])) return;
        build(b[0], b[1], b[2]);
    }
    else if (b[3] == 0)
    {
        if (!canRemove(b[0], b[1], b[2])) return;
        remove(b[0], b[1], b[2]);
    }
    return;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    for (vector<int>& bf : build_frame)
    {
        apply(bf);
    }
    for (int y=0;y<=n;++y)
    {
        for (int x=0;x<=n;++x)
        {
            for (int t=0;t<=1;++t)
            {
                if (wall[y][x][t]) answer.push_back({x,y,t});
            }
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}
