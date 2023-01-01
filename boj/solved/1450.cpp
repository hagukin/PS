#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int N, C;
ll ret = 0;
int weights[31] = {0,};
vector<int> v1;
vector<int> v2;

void dfs(int ci, int e, vector<int>& v, int sum)
{
    // weights의 [start,e) 범위에 대해 나올 수 있는 모든 조합들의 요소들의 합을 v에 저장한다.
    // 단 합이 C 초과일 경우 무시
    if (sum > C) return;
    if (ci == e)
    {
        v.push_back(sum);
        return;
    }
    dfs(ci+1, e, v, sum);
    dfs(ci+1, e, v, sum+weights[ci]);
    return;
}

int main()
{
    // 문제 조건이 좀 애매하게 적혀있다, 물건을 아예 안넣는 것도 1개의 경우로 포함한다.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> C;
    for (int i=0;i<N;++i)
    {
        cin >> weights[i];
    }
    dfs(0, N/2, v1, 0);
    dfs(N/2, N, v2, 0);
    
    sort(v2.begin(), v2.end());
    ll cnt = 0;
    
    for (int x : v1)
    {
        auto&& tmp = upper_bound(v2.begin(), v2.end(), C-x);
        cnt = tmp - v2.begin();
        ret += cnt;
    }
    cout << ret << '\n';
    return 0;
}
