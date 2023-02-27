#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

constexpr int MAXN = 404;
constexpr int INF = 987654321;

struct Edge
{
    int cF=0;
    int mF=0;
};

Edge tmpE;
int N, P;
int source = 1, sink = 2;
vector<vector<Edge >> e(MAXN,vector<Edge>(MAXN,tmpE));
bool visited[MAXN] = {false,};

int dfs(int curr, int bottleneck)
{
    visited[curr] = true;
    if (curr == sink) return bottleneck;
    for (int i=1;i<=N;++i)
    {
        if (!visited[i] && (e[curr][i].mF-e[curr][i].cF)>0)
        {
            int tmp = dfs(i, min(bottleneck, e[curr][i].mF - e[curr][i].cF));
            if (tmp == -1) continue;
            e[curr][i].cF += tmp;
            e[i][curr].cF -= tmp;
            return tmp;
        }
    }
    return -1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> P;
    
    int a, b;
    for (int i=0;i<P;++i)
    {
        cin >> a >> b;
        e[a][b].mF = 1; // 17412 조건
    }
    
    int ret = 0;
    while (true)
    {
        int tmp = 0;
        memset(visited, false, sizeof(visited));
        visited[source] = true;
        
        tmp = dfs(1, INF);
        if (tmp == -1) break;
        ret += tmp;
    }
    cout << ret << '\n';

    return 0;
}
