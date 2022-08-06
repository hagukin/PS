#include <iostream>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool nRank[501][501];
bool visited[501];
bool finished[501];
bool hasCycle = false;
bool hasMultiRet = false;
vector<int> ret;
int tc; int N; int M;

void dfs(int x)
{
    visited[x] = true;
    for (int i=1;i<=N;i++)
    {
        if (nRank[x][i])
        {
            if (!visited[i]) dfs(i);
            else if (!finished[i]) hasCycle = true;
            /* 
            keypoint1) DFS로 위상정렬을 하면서 사이클을 찾는법: 
            x 노드에서 시작에 재귀를 통해 계속 자식노드를 타고 내려가던 도중
            어떤 노드를 만났는데 그 노드가 visited == true이고
            finished == false라면 해당 노드는 현재의 재귀 스택 속에 있다는 뜻이고,
            이는 즉 다시 위로 타고 올라가면 해당 노드를 만난다는 뜻이며,
            이는 즉 x의 자식 노드가 x의 부모 노드와 이어진다는 뜻이다. (=사이클 형성)
            */
        }
    }
    finished[x] = true; // finished란 어떤 노드 x에서 시작하는 dfs를 모두 탐색하고 끝마쳤음을 의미한다.
    ret.push_back(x);
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> tc;
    for (int t=0;t<tc;t++)
    {
        // reset
        hasCycle = false;
        hasMultiRet = false;
        ret.clear();
        memset(nRank, 0, sizeof(nRank));
        memset(visited, false, sizeof(visited));
        memset(finished, false, sizeof(finished));
        
        // prev rank
        int prevRank[501];
        memset(prevRank, 0, sizeof(prevRank));
        cin >> N;
        for (int i=1;i<=N;i++)
        {
            cin >> prevRank[i];
        }
        for (int i=N;i>=1;i--)
        {
            for (int m=1;m<i;m++)
            {
                nRank[prevRank[m]][prevRank[i]] = true;
            }
        }
        
        // change rank
        cin >> M;
        for (int j=0;j<M;j++)
        {
            int a, b;
            cin >> a >> b;
            nRank[a][b] = !nRank[a][b]; // reverse
            nRank[b][a] = !nRank[b][a];
        }
        
        //solve
        for (int l=1;l<=N;l++)
        {
            if (!visited[l])
            {
                dfs(l);
            }
        }
        
        //print
        if (hasCycle)
        {
            cout << "IMPOSSIBLE" << '\n';
        }
        else if (hasMultiRet)
        {
            cout << "?" << '\n'; // keypoint2) 확실한 답이 없는 경우는 있을 수 없다. 애초에 모든 결과를 1회 다 주고 시작하기 떄문.
        }
        else
        {
            reverse(ret.begin(), ret.end());
            for (int r : ret)
            {
                cout << r << " ";
            }
            cout << '\n';
        }
    }
    return 0;
}
