#include <iostream>

using namespace std;
int N, M;
string grid[1001];
int visited[1001][1001];
int ret = 0;

char getGrid(int y, int x)
{
    return grid[y][x];
}

void dfs(int y, int x, int num)
{
    if (y>=0 && x>=0 && y<N && x<M) // warning
    {
        if (visited[y][x])
        {
            if (visited[y][x] == num)
            {
                // 새로운 사이클 발견
                ret++;
            }
            return;
        }
        visited[y][x] = num;
        switch(getGrid(y,x))
        {
            case 'U':
                return dfs(y-1,x,num);
            case 'D':
                return dfs(y+1,x,num);
            case 'L':
                return dfs(y,x-1,num);
            case 'R':
                return dfs(y,x+1,num);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> M;
    for(int i=0;i<N;i++)
    {
        cin >> grid[i];
    }
    
    int cnt = 0;//cnt != ret
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<M;j++)
        {
            if (!visited[i][j]) dfs(i,j,++cnt);
        }
    }
    cout << ret << '\n';

    return 0;
}
