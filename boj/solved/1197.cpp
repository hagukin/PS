#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int a, b, c;
};

int V, E;
vector<Edge> edges;
long long ret = 0;
int uf[10001];

bool cmp(const Edge& e1, const Edge& e2)
{
    return e1.c < e2.c;
}

int find_root(int n)
{
    if (uf[n] == n) return n;
    else return uf[n]=find_root(uf[n]);
}

int union_two(int n1, int n2)
{
    int tmp = find_root(n1); // n1이 상위가 된다
    int tmp2 = find_root(n2);
    uf[tmp2] = tmp;
    return tmp;
}

void solve()
{
    Edge fe = edges.front();
    int root = union_two(fe.a, fe.b);
    ret += fe.c;
    
    for (int i=1;i<E;i++)
    {
        Edge& ce = edges[i];
        if (find_root(ce.a) == find_root(ce.b)) continue; // 사이클
        else
        {
            union_two(ce.a, ce.b);
            ret += ce.c;
        }
    }
    cout << ret << '\n';
}

int main()
{
    cin >> V >> E;
    for (int i=1;i<=V;i++) uf[i] = i; // 자기자신을 루트로
    int A, B, C;
    for(int i=0;i<E;i++)
    {
        cin >> A >> B >> C;
        Edge ne = {A,B,C};
        edges.push_back(ne);
    }
    sort(edges.begin(), edges.end(), cmp);
    solve();
    return 0;
}
