#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int N; int M;
vector<int> graph[32001];
bool visited[32001];
vector<int> ret;

void dfs(int x)
{
    visited[x] = true;
    for (int j : graph[x])
    {
        if (!visited[j])
        {
            dfs(j);
        }
    }
    ret.push_back(x);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    memset(visited, false, sizeof(visited));
    ret.clear(); // memset, clear() 안할 경우 오답 발생 (정확한 원인은 모르겠음)
    cin >> N >> M;
    for (int i=0;i<M;i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    for (int i=1;i<=N;i++)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }
    reverse(ret.begin(), ret.end());
    for (auto k : ret)
    {
        cout << k << " "; // 문제에서 제대로 명시되어있지 않지만 공백으로 구분하지 않을 경우 오답처리함
    }
    return 0;
}
