#include <iostream>
#include <vector>
#include <cstring>
#include <set>
using namespace std;
int N, M;
bool visited[500001];
int group[500001]; // 소속된 그룹의 루트노드번호

bool dfs(int c, vector<vector<int>>& adjList)
{
    bool ret = false;
    visited[c] = true;
    for (int& next : adjList[c])
    {
        if (group[next] == group[c]) return true;
        group[next] = group[c];
        ret |= dfs(next, adjList);
    }
    return ret;
}

bool checkCycle(vector<vector<int>>& adjList)
{
    for (int i=0;i<N;++i)
        group[i] = i;
    for (int i=0;i<N;++i)
    {
        if (visited[i]) continue;
        if (dfs(i, adjList)) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(visited, false, sizeof(visited));
    
    cin >> N >> M;
    vector<int> tmp;
    vector<vector<int>> adjList(N+1, tmp);
    
    int a, b, turn = 0;
    for (int i=0;i<M;++i)
    {
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
        
        if (checkCycle(adjList)) 
        {
            cout << i << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
    return 0;
}
