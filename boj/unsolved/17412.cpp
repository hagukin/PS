#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

constexpr int MAXN = 404;
constexpr int INF = 987654321;

struct Edge
{
    bool exist = false;
    int cF=0;
    int mF=0;
};

Edge tmpE;
int N, P;
int source = 1, sink = 2;
vector<vector<Edge >> e(MAXN,vector<Edge>(MAXN,tmpE));
bool visited[MAXN] = {false,};

int dfs(int curr, int bottleneck, vector<int>& nodes)
{
    visited[curr] = true;
    nodes.push_back(curr);
    if (curr == sink) return bottleneck;
    for (int i=1;i<=N;++i)
    {
        if (e[curr][i].exist && !visited[i] && (e[curr][i].mF-e[curr][i].cF)>0)
        {
            int tmp = dfs(i, min(bottleneck, e[curr][i].mF - e[curr][i].cF), nodes);
            if (tmp == -1)
            {
                visited[i] = false;
                nodes.pop_back();
                continue;
            }
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
        e[a][b].exist = true;
        e[a][b].mF = 1; // 17412 조건
    }
    
    int ret = 0;
    vector<int> v;
    while (true)
    {
        int tmp = 0;
        memset(visited, false, sizeof(visited));
        visited[source] = true;
        v.clear();
        
        tmp = dfs(1, INF, v);
        if (tmp == -1) break;
        ret += tmp;
        
        // edge flow 업데이트 및 residual path 생성
        for (int i=1;i<v.size();++i)
        {
            int aa = v[i-1];
            int bb = v[i];
            
            e[aa][bb].cF += tmp;
            e[bb][aa].exist = true;
            e[bb][aa].cF -= tmp;
        }
    }
    cout << ret << '\n';

    return 0;
}
