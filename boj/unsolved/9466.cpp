#include <iostream>
#include <cstring>
int team[100001];
bool hasTeam[100001]; // 메모이제이션
using namespace std;

int solve()
{
    int funcRet = n;
    for (int i=1;i<n;i++)
    {
        // 1. 나가는 간선으로 dfs 순회시 자기자신으로 돌아와야 함.
        // 2. 들어오는 간선과 나가는 간선의 수가 같아야 함.
        if (dfs(i)) --n;
    }
    return funcRet;
}

bool dfs(int x)
{
    int& funcRet = hasTeam[x];
    // TODO
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> T;
    for (int tc=0;tc<T;tc++)
    {
        memset(edgeCnt, 0, sizeof(edgeCnt));
        memset(team, 0, sizeof(team));
        int n;
        cin >> n;
        for (int i=1;i<n;i++)
        {
            cin >> team[i];
        }
        cout << solve() << '\n';
    }
    
    return 0;
}
