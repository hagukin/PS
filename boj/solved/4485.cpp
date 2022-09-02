#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int,pair<int,int>> coor;
int grid[126][126];
int sumGrid[126][126];
int dydxs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

void bfs(int N)
{
    queue<coor> q; // y,x
    q.push(make_pair(grid[0][0], make_pair(0, 0)));
    while(!q.empty())
    {
        coor curr = q.front();
        q.pop();
        
        int val = curr.first;
        int cy = curr.second.first;
        int cx = curr.second.second;
        sumGrid[cy][cx] = val;
        
        int ny, nx;
        for (auto dydx : dydxs)
        {
            ny = cy + dydx[0];
            nx = cx + dydx[1];
            if (ny >= 0 && ny < N && nx >= 0 && nx < N)
            {
                int nVal = val + grid[ny][nx];
                if (nVal < sumGrid[ny][nx] || sumGrid[ny][nx] == -1) 
                {
                    sumGrid[ny][nx] = nVal;
                    coor np = make_pair(nVal, make_pair(ny, nx));
                    q.push(np);
                }
                else continue; // 재방문 방지 + 최솟값만 남기기
            }
        }
    }
    return;
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
        memset(sumGrid, -1, sizeof(sumGrid));
        for (int y=0;y<N;y++)
        {
            for (int x=0;x<N;x++)
            {
                cin >> grid[y][x];
            }
        }
        bfs(N);
        cout << "Problem " << tc << ": " << sumGrid[N-1][N-1] << '\n';
    }
    return 0;
}
