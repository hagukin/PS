#include <iostream>
#include <vector>
using namespace std;
int n, m;
int uf[500001]; // 무방향이므로 루트는 해당 그룹의 가장 작은 수로 통일

int getRoot(int x)
{
    int curr = x;
    int root = uf[x];
    if (curr == root) return curr;
    
    int funcRet = getRoot(root);
    uf[x] = funcRet;
    return funcRet;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    
    for (int i=0;i<=n;++i) uf[i] = i;
    vector<int> tmp;
    vector<vector<int>> adjList(n, tmp);
    
    int a, b;
    for (int i=1;i<=m;++i)
    {
        cin >> a >> b;
        int ra = getRoot(a);
        int rb = getRoot(b);
        
        if (ra == rb)
        {
            cout << i << '\n';
            return 0;
        }
        else if (ra < rb) uf[rb] = ra;
        else uf[ra] = rb;
    }
    cout << 0 << '\n';

    return 0;
}
