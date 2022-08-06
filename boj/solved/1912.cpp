#include <iostream>
#include <math.h>
#include <limits.h>
using namespace std;
// 누적합 문제
int N;
int dp[100001]; // dp[i]는 i번 수를 무조건 사용하는 최대 연속합
int arr[100001]; // 수열
int ret = INT_MIN;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> N;
    for(int i=1;i<=N;i++)
    {
        cin >> arr[i];
        dp[i] = max(dp[i-1]+arr[i], arr[i]);
        ret = max(ret, dp[i]);
    }
    cout << ret;
    return 0;
}
