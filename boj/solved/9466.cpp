#include <iostream>
#include <cstring>
int team[100001];
int visited[100001]; // 3이면 팀 존재
bool isDone[100001];
int T;
using namespace std;

void dfs(int x)
{
    if (isDone[x]) return;
    if (visited[x] >= 2) return;
    visited[x]++; 
    dfs(team[x]);
    isDone[x] = true;
    return;
}

int solve(int n)
{
    int funcRet = 0;
    for (int i=1;i<=n;i++)
    {
        // 1. 나가는 간선으로 dfs 순회시 자기자신으로 돌아와야 함.
        // 2. 들어오는 간선과 나가는 간선의 수가 같아야 함.
        if (!visited[i]) dfs(i);
    }
    for (int i=1;i<=n;i++)
    {
        if (visited[i]<2) funcRet++;
    }
    return funcRet;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> T;
    int n;
    for (int tc=0;tc<T;tc++)
    {
        memset(visited, 0, sizeof(visited));
        memset(team, 0, sizeof(team));
        memset(isDone, false, sizeof(isDone));
        cin >> n;
        for (int i=1;i<=n;i++)
        {
            cin >> team[i];
        }
        cout << solve(n) << '\n';
    }
    
    return 0;
}
