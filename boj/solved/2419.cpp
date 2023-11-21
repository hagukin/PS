#include <iostream>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;

int dp[301][301][2] = {0,};
bool visited[301][301][2] = {0,};
vector<int> X;
int N, M;

inline int getDist(int s, int e) {return abs(X[s] - X[e]);}

int solve(int l, int r, int k, int w)
{
    if (w == 0) return 0;
    if (l == 0 && r == N) return 0;
    
    int& ret = dp[l][r][k];
    if (visited[l][r][k]) return ret;
    
    int curr = (k) ? r : l;
    
    if(l > 0) ret = max(ret, solve(l-1, r, 0, w-1) - w * getDist(curr, l-1) + M);
    if(r < N) ret = max(ret, solve(l, r+1, 1, w-1) - w * getDist(curr, r+1) + M);
    
    visited[l][r][k] = true;
    return ret;
}
 
int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;
    X.resize(N);
    bool isZero = false;
    for (int i = 0; i < N; i++) 
    {
        cin >> X[i];
        if (X[i] == 0) isZero = true;
    }
 
    if (!isZero) X.push_back(0);
    else N--;
    
    sort(X.begin(), X.end());
    int idx = lower_bound(X.begin(), X.end(), 0) - X.begin();
 
    int ans = 0;
    for (int i = 0; i <= N; ++i) 
    {
        memset(dp, 0, sizeof(dp));
        memset(visited, 0, sizeof(visited));
        int k = solve(idx, idx, 0, i);
        if (isZero) k += M;
        ans = max(ans, k);
    }
    cout << ans << '\n';
    return 0;
}
