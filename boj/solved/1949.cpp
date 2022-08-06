#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int N;
int population[10001];
vector<int> graph[10001];
int s[10001]; // 초기값 0
int ns[10001]; // 초기값 -1

int nsSubtree(int n, int parent);

int sSubtree(int n, int parent) // 루트(n)이 선택된 경우 최댓값
{
    // 기저: 자식노드가 없을 때 (단, 부모로 가는 간선은 가지고 있을 수 있음!)
    if (graph[n].size() == 1 && graph[n][0] == parent)
    {
        s[n] = population[n];
        return s[n];
    }
    if (s[n]) return s[n];
    int ret = population[n];
    for (int child : graph[n])
    {
        if (child != parent) ret += nsSubtree(child, n);
    }
    s[n] = ret;
    return ret;
}

int nsSubtree(int n, int parent) // 루트(n)이 선택되지 않은 경우 최댓값
{
    // 기저: 자식노드가 없을 때 (단, 부모로 가는 간선은 가지고 있을 수 있음!)
    if (graph[n].size() == 1 && graph[n][0] == parent) {ns[n] = 0; return 0;}
    if (ns[n] != -1) return ns[n];
    int ret = 0;
    for (int child : graph[n])
    {
        if (child != parent) ret += max(sSubtree(child, n), nsSubtree(child, n));
    }
    ns[n] = ret;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int a, b, tmp;
    int ans;
    memset(s, 0, sizeof(s));
    memset(ns, -1, sizeof(ns));
    
    cin >> N;
    for (int i=1;i<=N;i++)
    {
        cin >> population[i];
    }
    for (int i=0;i<N-1;i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int root=1;root<=N;root++)
    {
        if (!graph[root].empty())
        {
            ans = max(sSubtree(root, 0), nsSubtree(root, 0));
            break;
        }
    }
    cout << ans << '\n';
    return 0;
}
