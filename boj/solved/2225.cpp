// top-down과 bottom-up 감을 찾을 수 있는 좋은 베이직한 문제
// 두 방식 모두로 풀이가 가능하다.
// 모듈러 연산에 주의하지 않아 처음에 틀렸다.
/* 
틀린 코드
#include <iostream>
#include <string.h>

using namespace std;

int N, K;
long long dp[201][201];

long long sumCnt(int n, int k)
{
    long long cnt = 0; // 굳이 여기서 cnt를 사용해줄 필요가 없었다.
    if (n==0) return 1;
    if (k==1) return 1;
    if (dp[n][k]) return dp[n][k];
    for (int i=0;i<=n;i++)
    {
        cnt += sumCnt(i,1) * sumCnt(n-i,k-1); // cnt가 범위를 초과하는 경우를 고려하지 못함.
    }
    dp[n][k] = cnt;
    return cnt;
}

int main()
{
    cin >> N >> K;
    memset(dp, 0, sizeof(dp));
    cout << sumCnt(N, K) % 1000000000;
    return 0;
}
*/

// top down
#include <iostream>
#include <string.h>

using namespace std;

int N, K;
long long dp[201][201];

long long sumCnt(int n, int k)
{
    if (n==0) return 1;
    if (k==1) return 1;
    if (dp[n][k]) return dp[n][k];
    for (int i=0;i<=n;i++)
    {
        dp[n][k] += sumCnt(i,1) * sumCnt(n-i,k-1);
        dp[n][k] %= 1000000000;
    }
    return dp[n][k];
}

int main()
{
    cin >> N >> K;
    memset(dp, 0, sizeof(dp));
    cout << sumCnt(N, K);
    return 0;
}

// bottom up
#include <iostream>
#include <string.h>

using namespace std;

int n, k;
long long dp[201][201];

int main()
{
    cin >> n >> k;
    memset(dp, 0, sizeof(dp));
    for (int i=0;i<=n;i++) {dp[i][0] = 0; dp[i][1] = 1;} // 어차피 k=1은 1이므로 초기화
    
    // bottom up 탐색 순서: k가 증가하도록 탐색. 즉 이전 dp[?][k]에 대한 정보가 있어야 다음 k를 구함.
    // e.g. dp[6][4] = dp[0][3] + dp[1][3] + ... dp[6][3]이다. 왜냐면 얘들한테 숫자 하나만 더 붙여주면 dp[6][4]를 만들 수 있음.
    // 0 3 -> 0 0 0 여기 끝에 6붙여서 0 0 0 6 만들면 경우의 수에 포함.
    // 또 중복도 없음. 왜? dp[0][3]과 dp[1][3]은 무조건 세 자리의 수가 다르므로 뒤에 뭘 어떻게 붙이던 무조건 완전히 별개의 경우의 수가 됨.
    for (int a=2; a<=k; a++)
    {
        for (int b=0; b<=n; b++)
        {
            for (int c=0; c<=b; c++)
            {
                dp[b][a] += dp[c][a-1];
                dp[b][a] %= 1000000000;
            }
        }
    }
    cout << dp[n][k];
    return 0;
}

