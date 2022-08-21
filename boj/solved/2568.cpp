#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <climits>
using namespace std;
constexpr int MAXN = 500001;
int N;
int lines[MAXN];
int lis[100001] = {0,};
int memo[MAXN];
vector<int> ret;

int main()
{
    memset(lines, -1, sizeof(lines));
    memset(memo, -1, sizeof(memo));
    cin >> N;
    int ll, rr;
    for (int i=0;i<N;i++)
    {
        cin >> ll >> rr;
        lines[ll] = rr;
    }
    
    int cnt = 0; // lis 원소 갯수
    for (int i=0;i<MAXN;i++)
    {
        if (lines[i] < 0) continue; // not connected to any
        if (lines[i] > lis[cnt-1]) 
        {
            lis[cnt] = lines[i]; 
            memo[i] = cnt;
            cnt++;
            continue;
        }
        int lbIdx = lower_bound(lis, lis+cnt, lines[i]) - lis;
        lis[lbIdx] = lines[i];
        memo[i] = lbIdx;
    }
    
    cout << N - cnt << '\n';
    int prev = cnt;
    for (int j=MAXN-1;j>=1;--j)
    {
        if (memo[j] == -1) continue;
        else if (memo[j] == prev-1) prev = memo[j];
        else ret.push_back(j);
    }
    for (int i=ret.size()-1;i>=0;--i) cout << ret[i] << '\n';
    return 0;
}
