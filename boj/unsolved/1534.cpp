#include <iostream>
#include <cstring>
using namespace std;

constexpr int DIVN = 1000000000LL;
constexpr int MAXN = 101;
typedef long long ll;
int N, K;
ll dp[MAXN][MAXN];

ll divide(int dn, int dk)
{
    if (!dk) return 0;
    if (dp[dn][dk]) return dp[dn][dk];
    int nSum = dn+2;
    ll funcRet = 0;
    for (int k=0;k<dn;k++)
    {
        for (int i=3;i<=nSum-3;i++)
        {
            ll tmp = divide(i,dk-1);
            if (tmp < 0) continue;
            funcRet += tmp;
            funcRet %= DIVN;
        }
    }
    funcRet /= 2;
    dp[dn][dk] = funcRet;
    return funcRet;
}

void initialize()
{
    memset(dp, 0, sizeof(dp));
    for (int i=0;i<MAXN;i++)
    {
        for (int j=0;j<MAXN;j++)
        {
            if (i<3 || j>i-2) dp[i][j] = -1;
            else if (j==1) dp[i][j] = 1;
        }
    }
    dp[4][2] = 2;
}

int main()
{
    cin >> N >> K;
    initialize();
    cout << divide(N,K) << '\n';
    return 0;
}
