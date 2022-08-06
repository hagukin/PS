#include <iostream>
using namespace std;
int R, C;
char grid[10001][501];
bool visited[10001][501];
int directions[3][2] = {{1,-1},{1,0},{1,1}};
int ret = 0;

bool dfs(int cx, int cy)
{
    visited[cy][cx] = true;
    if (cx == C-1)
    {
        ret++;
        return true;
    }
    
    int nx, ny;
    for (int i=0;i<3;i++)
    {
        ny = cy+directions[i][1];
        nx = cx+directions[i][0];
        if (nx >= C || nx < 0 || ny >= R || ny < 0 || visited[ny][nx]) continue;
        if (grid[ny][nx] != 'x')
        {
            if (dfs(nx, ny)) return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> R >> C;
    for(int i=0;i<R;i++)
    {
        for(int j=0;j<C;j++)
        {
            cin >> grid[i][j];
        }
    }
    for (int y=0;y<R;y++)
    {
        dfs(0,y);
    }
    cout << ret << '\n';
    return 0;
}
