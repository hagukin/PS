// O(N)으로 풀이했으나 시간제한에 걸린다
// 답 자체는 구해지나 제한시간에 맞추려면 행렬곱을 이용해야 하는듯 해 보인다
#include <iostream>
#include <string>
using namespace std;
int dp[100][100][2]; 
// dp[i][j][k] = x*i + y*j의 마지막 두자리
// k=0:++ =1:+-  --> --나 -+의 경우는 i,j의 순서를 바꿔서 계산
int x, y, a0, a1, n;

void printN(int n)
{
    // 필요시 맨 앞에 0을 붙여서 출력하는 함수
    if (n >= 10 || n <= -10) cout << n << '\n';
    else if (n<0) cout << "-0" << abs(n) << '\n';
    else cout << '0' << n << '\n';
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> x >> y >> a0 >> a1 >> n;
    for (int i=0;i<=99;++i)
    {
        for (int j=0;j<=99;++j)
        {
            dp[i][j][0] = (i*x + j*y) % 100;
            dp[i][j][1] = (i*x - j*y) % 100;
        }
    }
    
    int an, an_1 = a1, an_2 = a0;
    for (int i=0;i<n-1;++i)
    {
        if (an_1 >= 0)
        {
            if (an_2 >= 0)
            {
                // ++
                an = dp[an_1][an_2][0];
            }
            else
            {
                // +-
                an = dp[an_1][abs(an_2)][1];
            }
        }
        else
        {
            if (an_2 >= 0)
            {
                // -+
                an = dp[abs(an_1)][an_2][1] * -1;
            }
            else
            {
                // --
                an = dp[abs(an_1)][abs(an_2)][0] * -1;
            }
        }
        an_2 = an_1;
        an_1 = an;
    }
    printN(an);
    return 0;
}
