#include <iostream>
using namespace std;
typedef long long ll; // 10억^2도 커버가 가능함! 
//int 최댓값이 21억가량인데 long long이 비트를 그 두 배 차지한다는 것을 생각하면 간당간당하게 커버된다는 걸 알 수 있음.
constexpr int P = 1000000007;

ll N, K;

ll powerMod(ll a, ll k, ll p)
{
    // a^k의 mod p를 O(log(k))에 구한다
    if (k==0) return 1;
    if (k%2 != 0) return ((a % p) * powerMod(a,k-1,p)) % p;
    ll tmp = powerMod(a,k/2,p);
    return (tmp * tmp) % p;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin >> N >> K;
    
    /*
    nCk = n! / (n-k)!k!
    nCk % p
    = ((n! % p) * (((n-k)!k!)^-1 % p)) % p
    
    (n-k)!k! ^ (-1) % p
    = (n-k)!k! ^ (p-2) % p
    = (((n-k)!k! ^ (p-2)/2 % p) * ((n-k)!k! ^ (p-2)/2 % p))  %  p   (단 p-2가 짝수)
    ...
    = 작은 수의 모듈러의 곱들로 표현이 가능해진다
    
    코드 구현시에는 분수의 분자부분이 n!이었던 위 수식보다 더 빠르게 계산하기 위해
    n! / (n-k)! 을 하나의 for loop으로 구현해버릴 수도 있다.
    이 경우 (n-k)!k! ^ (p-2) 대신 k! ^ (p-2)만 구하면 된다
    */
    
    // n!
    ll up = 1;
    ll i;
    for (i=N;i>=N-K+1;--i) up = (up * i) % P;
    
    // (n-k)!k!
    ll down = 1;
    for (i=1;i<=K;++i) down = (down * i) % P;
    
    ll ret =  (up * powerMod(down, P-2, P)) % P;
    cout << ret << '\n';
    return 0;
}
