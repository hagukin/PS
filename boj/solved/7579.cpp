#include <iostream>
#include <cstring>
using namespace std;
constexpr int MAXMEM = 10001;
int N, M;
int a[101]; int c[101];
int dp[101][MAXMEM];

int main()
{
    cin >> N >> M;
    for (int i=0;i<N;i++)
    {
        cin >> a[i];
    }
    for (int i=0;i<N;i++)
    {
        cin >> c[i];
    }
    memset(dp, 0, sizeof(dp));
    
    // solve
    // 맨 윗줄
    for (int j=0;j<MAXMEM;j++)
    {
        if (j>=c[0]) dp[0][j] = a[0];
    }
    // 나머지
    for (int i=1;i<N;i++)
    {
        for (int j=0;j<MAXMEM;j++)
        {
            dp[i][j] = dp[i-1][j];
            if (j-c[i] >= 0) dp[i][j] = max(dp[i-1][j], dp[i-1][j-c[i]] + a[i]);
        }
    }
    for (int i=0;i<MAXMEM;i++)
    {
        if (dp[N-1][i] >= M) {cout << i << '\n'; break;}
    }
    return 0;
}
