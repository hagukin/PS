#include <iostream>
#include <cstring>
using namespace std;

int dp[1001][1001];
int n, k;

int solve(int cur, int x) // cur=고를 수 있는 색 갯수, k=골라야 하는 색 갯수
{
    if (cur <= 0 || cur < 2*x) return 0; // 1~N까지의 인덱스 사용 (따라서 cur==0이면 범위 초과한걸로 취급)
    if (x==1) return cur;
    
    int& cache = dp[cur][x];
    if (cache!=-1) return dp[cur][x];
    return cache = (solve(cur-2,x-1) + solve(cur-1,x)) % 1000000003;
}

int main()
{
    cin >> n >> k;
    memset(dp, -1, sizeof(dp));
    cout << solve(n,k) << endl;
    return 0;
}
