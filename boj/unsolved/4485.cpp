#include <iostream>
#include <climits>
#include <cstring>
using namespace std;
int grid[126][126];
int sumGrid[126][126];
int dydxs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

void dfs(int cy, int cx, int val, int N)
{
    val += grid[cy][cx];
    if (val < sumGrid[cy][cx])
    {
        sumGrid[cy][cx] = val;
        cout << "DDD" << endl;
    }
    else return; // 재방문 방지 + 최솟값만 남기기
    
    int ny, nx;
    for (auto dydx : dydxs)
    {
        ny = cy + dydx[0];
        nx = cx + dydx[1];
        if (ny >= 0 && ny < N && nx >= 0 && nx < N)
        {
            dfs(ny, nx, val, N); cout << ny << nx << val << endl;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int tc = 0;
    while (true)
    {
        tc++;
        int N;
        cin >> N;
        if (N==0) break;
        memset(grid, 0, sizeof(grid));
        memset(sumGrid, INT_MAX, sizeof(sumGrid));
        for (int y=0;y<N;y++)
        {
            for (int x=0;x<N;x++)
            {
                cin >> grid[y][x];
            }
        }
        dfs(0,0,0,N);
        cout << "Problem " << tc << ": " << sumGrid[N-1][N-1] << '\n';
    }
    return 0;
}
