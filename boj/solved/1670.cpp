#include <iostream>
#include <cstring>

constexpr long long MOD = 987654321;

using namespace std;

long long dp[5001]; // dp[k] = k*2일때의 값
int N;

long long getCnt(int x)
{
    if (dp[x/2]) {return dp[x/2];}
    if (x==0) return 1; // inner or outer가 0일 경우
    
    long long ret = 0;
    for (int i=1;i<x;i+=2) // 점 0~x-1까지 있다 (총 x개)
    // i는 0번점과 이어진 점
    // i+=2의 이유: 남는 점들의 갯수가 inner outer 양쪽 다 짝수여야 함.
    {
        int inner = i-1;
        int outer = x-inner-2;
        ret += getCnt(inner) * getCnt(outer);
        ret %= MOD;
    }
    dp[x/2] = ret;
    return ret;
}

int main()
{
    cin >> N;
    memset(dp, 0, sizeof(dp));
    
    dp[1] = 1;
    dp[2] = 2;
    
    cout << getCnt(N) << '\n';
    return 0;
}
