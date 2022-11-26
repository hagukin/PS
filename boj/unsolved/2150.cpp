#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <cstring>
using namespace std;
constexpr int UNVISITED = -1;
constexpr int INF = 987654321;

vector<int> adjList[10001];
int ids[10001]; // 방문 순서에 의해 결정되는 id
int low[10001]; // low[i]: i번 id노드에서 방문가능한 노드중 가장 작은 id
bool isInStack[10001] = {false,};
int V, E;
int sccCnt = 0;
int currId = 1; // 1부터 id 부여

stack<int> st;

vector<int> ret[10001];

bool cmp(const vector<int>& v1, const vector<int>& v2)
{
    int t1, t2;
    if (v1.empty()) t1 = INF;
    else t1 = v1[0];
    if (v2.empty()) t2 = INF;
    else t2 = v2[0];
    return t1 < t2;
}

void dfs(int cNode) // curr은 id가 아님에 주의
{
    ids[cNode] = currId++;
    low[cNode] = ids[cNode];
    st.push(cNode);
    isInStack[cNode] = true;
    
    for (int& child : adjList[cNode])
    {
        if (ids[child] == UNVISITED)
            dfs(child);
        if (isInStack[child]) low[cNode] = min(low[child], low[cNode]); // 중요
    }
    
    if (ids[cNode] == low[cNode]) // 루트
    {
        while (st.top() != cNode)
        {
            int tmp = st.top();
            ret[cNode].push_back(tmp);
            isInStack[tmp] = false;
            // low[tmp] = ids[cNode]; // 만약 low를 scc별로 묶고 싶다면
            st.pop();
        }
        ret[cNode].push_back(cNode); // 자기자신도 출력해야 하므로
        st.pop();
        sccCnt += 1;
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    memset(ids, UNVISITED, sizeof(ids));
    
    cin >> V >> E;
    int A, B;
    for (int i=1;i<=E;++i)
    {
        cin >> A >> B;
        adjList[A].push_back(B);
    }

    for (int i=1;i<=V;++i)
    {
        if (ids[i] == UNVISITED) dfs(i);
    }
    
    cout << sccCnt << '\n';
    for (int i=1;i<=V;++i)
    {
        if (!ret[i].empty())
        {
            sort(ret[i].begin(), ret[i].end());
        }
    }
    
    sort(ret+1, ret+V+1, cmp);
    for (int i=1;i<=V;++i)
    {
        if (!ret[i].empty())
        {
            for (auto& c : ret[i]) cout << c << " ";
            cout << -1 << '\n';
        }
    }
    return 0;
}
