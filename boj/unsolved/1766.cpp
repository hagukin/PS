/*
위상정렬을 DFS로 구현해서는 시간초과로 풀 수 없다
+ 아래 코드는 시간초과가 나기 전에 테케에서 걸러지는데, 어디 이상한 데서 구현을 실수한 듯 하다
애초에 위상정렬 문제임을 인지하고 푼 게 아니기 때문에 풀이 정당성 증명하는 과정에서 실수가 있었을 수 있다
priority_queue를 이용한 위상정렬, bfs를 이용한 위상정렬 개념을 익히고, dfs 위상정렬도 다시 복습한 후 돌아와 다시 풀어보던가 하자.

#include <iostream>
#include <vector>
#include <set>
using namespace std;

int N, M;
set<int> graph[32001]; // 방향 그래프(graph[a]가 b를 가지고있다: a->b 존재)
bool visited[32001] = {false,};
vector<vector<int>> retV;

void dfs(int c, vector<int>& route)
{
    route.push_back(c);
    visited[c] = true;
    for (int nxt=1;nxt<=N;++nxt) // 자식을 오름차순으로 서치하는게 중요
    {
        if (graph[c].find(nxt) != graph[c].end() && !visited[nxt])
        {
            dfs(nxt, route);
        }
    }
    return;
}

int main()
{
    cin >> N >> M;
    int A, B;
    for (int i=0;i<M;++i)
    {
        cin >> A >> B;
        graph[A].insert(B);
    }
    vector<int> route;
    for (int i=N;i>=1;--i)
    {
        if (visited[i]) continue;
        route.clear();
        dfs(i, route);
        retV.push_back(route);
    }
    for (int i=retV.size()-1;i>=0;--i)
    {
        for (auto& x : retV[i]) cout << x << ' ';
    }
    return 0;
}
*/
