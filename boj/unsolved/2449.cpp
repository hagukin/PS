#include <iostream>
#include <memory.h>
#include <vector>
using namespace std;
constexpr int INF = 987654321;

int N, K;
int origin[201];
vector<int> lights;
int dp[201][201][21]; // i,j,k = [i,j)를 k로 바꾸기 위해 필요한 횟수
int ret = INF;

int unifyCnt(int i, int j, int k)
{
    // [i,j)를 k로 바꾸기 위해 필요한 횟수
    if (dp[i][j][k] != -1) return dp[i][j][k];
    int funcRet = INF;
    int a, b, c;
    a = lights[i];
    b = lights[i+1];
    if (j-i == 3) // abc
    {
        c = lights[i+2];
        if (a == k || b == k || c == k) 
        {
            if (a == k && c == k) funcRet = 1; // aba to a
            else funcRet = 2;
        }
        else if (a == c) funcRet = 2; // aba to c
        else funcRet = 3;
    }
    else if (j-i == 2) // ab
    {
        if (a == k || b == k) funcRet = 1;
        else funcRet = 2;
    }
    else if (j-i == 1)
    {
        if (a == k) funcRet = 0;
        else funcRet = 1;
    }
    else
    {
        for (int l=i+1;l<j;++l)
        {
            funcRet = min(unifyCnt(i,l,k) + unifyCnt(l,j,k), funcRet);
        }
    }
    return dp[i][j][k] = funcRet;
}

void simplify()
{
    lights.push_back(origin[0]);
    for (int i=1;i<N;++i)
    {
        if (origin[i] == origin[i-1]) continue;
        lights.push_back(origin[i]);
    }
    N = lights.size();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> N >> K;
    for (int i=0;i<N;++i)
    {
        cin >> origin[i];
    }
    simplify();
    
    for (int c=1;c<=K;++c)
    {
        unifyCnt(0,N,c);
    }
    for (int c=1;c<=K;++c)
    {
        ret = min(ret, dp[0][N][c]);
    }
    cout << ret << '\n';

    return 0;
}
